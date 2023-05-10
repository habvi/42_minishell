/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_diffuse_reflection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:12:18 by takira            #+#    #+#             */
/*   Updated: 2023/04/24 14:03:37 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	get_dir_pos2light(t_light light, t_vector pos)
{
	t_vector	dir_pos2light;

	if (light.type == LT_POINT || light.type == LT_SPOT)
		dir_pos2light = sub(&light.position, &pos);
	else
		dir_pos2light = normalize_vec_inv(&light.direction);	// 平行光源
	normalize(&dir_pos2light);
	return (dir_pos2light);
}

int is_obj_exists_between_light_and_eye(const t_scene *scene, t_vector dir_pos2light, t_light *light, t_intersection_point intp)
{
	int 		shadow_intersect_result;
	t_ray		shadow_ray;
	t_vector	vec_pi_to_light;
	float		search_distance;

	/* shadow_rayを計算 */
	shadow_ray.start = vec_calc(1.0f, &intp.position, EPSILON, &dir_pos2light);
	shadow_ray.direction = dir_pos2light;
	if (light->type == LT_POINT || light->type == LT_SPOT)
	{
		vec_pi_to_light = sub(&light->position, &intp.position);
		search_distance = norm(&vec_pi_to_light) - EPSILON;
	}
	else
		search_distance = FLT_MAX;
	shadow_intersect_result = get_nearest_shape(scene, &shadow_ray, search_distance, true, NULL, NULL);
	return (shadow_intersect_result);
}

t_colorf	get_checker_reflection_color(t_shape *shape, t_intersection_point intp, float nl_dot, t_light *light)
{
	t_colorf	color;
	t_colorf	checker_col;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	/* checker */
	if (!shape->material.is_checker)
		return (color);

	checker_col = get_checker_color(intp, shape);
	color = get_color_k1c1k2c2(1.0f, &checker_col, nl_dot, &light->illuminance);
	return (color);
}

t_colorf	get_image_reflection_color(t_shape *shape, t_intersection_point intp, float nl_dot, t_light *light)
{
	t_colorf	color;
	t_colorf	img_col;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	/* image texture */
	if (!shape->material.texture.data)
		return (color);

	img_col = get_img_color(intp, shape, shape->material.texture);
	color = get_color_k1c1k2c2(1.0f, &img_col, nl_dot, &light->illuminance);

	return (color);
}

t_colorf	get_diffuse_reflection_color(t_shape *shape, float nl_dot, t_light *light, t_vector dir_pos2light, t_vector eye_dir)
{
	t_colorf	color;
	t_vector	light_to_pos;
	float		alpha;
	t_colorf	color_diffuse_ref;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	if (shape->material.texture.data)
		return (color);

	if (light->type == LT_SPOT)
	{
		light_to_pos = normalize_vec_inv(&dir_pos2light);
		alpha = acosf(dot(&light_to_pos, &light->direction));

		if (alpha > light->angle / 2.0f * (float)M_PI / 180.0f)
			return (color) ;
	}

	color_diffuse_ref = get_color_k1c1k2c2(1.0f,&shape->material.diffuse_ref,nl_dot, &light->illuminance);
	color = colorf_add(color, color_diffuse_ref);

	return (color);
}

t_colorf calc_diffuse_reflection(const t_scene *scene, t_intersection_point intp, t_ray eye_ray, t_shape *shape)
{
	t_colorf	color;
	t_light		*light;
	t_vector	dir_pos2light, normal;
	float		nl_dot;
	t_colorf	color_checker_texture, color_image_texture, color_diffuse_ref;
	t_list 		*light_node;

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);
	if (shape->material.type == MT_PERFECT_REFLECTION)
		return (color);

	normal = intp.normal;
	if (shape->material.bump.data)
		normal = get_bump_normal(intp, shape);

	light_node = scene->light_list;
	while (light_node)
	{
		light = light_node->content;
		light_node = light_node->next;

		dir_pos2light = get_dir_pos2light(*light, intp.position);
		nl_dot = CLAMP(dot(&normal, &dir_pos2light), 0.0f, 1.0f);

		if (is_obj_exists_between_light_and_eye(scene, dir_pos2light, light, intp))
			continue ;

		color_diffuse_ref = get_diffuse_reflection_color(shape, nl_dot, light, dir_pos2light, eye_ray.direction);
		color_image_texture = get_image_reflection_color(shape, intp, nl_dot, light);
		color_checker_texture = get_checker_reflection_color(shape, intp, nl_dot, light);

		color = colorf_add(color, color_diffuse_ref);
		color = colorf_add(color, color_image_texture);
		color = colorf_add(color, color_checker_texture);

	}
	return (color);
}
