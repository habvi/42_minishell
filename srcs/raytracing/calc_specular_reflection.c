/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_specular_reflection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:12:39 by takira            #+#    #+#             */
/*   Updated: 2023/04/24 14:04:02 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colorf calc_specular_reflection(const t_scene *scene, const t_ray *eye_ray,
								  t_intersection_point intp, t_shape *shape)
{
	t_colorf	color;
	t_light		*light;
	t_vector	dir_pos2light, normal;
	float		nl_dot;
	t_colorf	color_specular_ref;

	t_vector	ref_dir, inv_eye_dir;
	float		vr_dot, vr_dot_pow;
	t_vector	light_to_pos;
	float		alpha;

	t_list		*light_node;

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

		if (light->type == LT_SPOT)
		{
			light_to_pos = normalize_vec_inv(&dir_pos2light);
			alpha = acosf(dot(&light_to_pos, &light->direction));

			if (alpha > light->angle / 2.0f * (float)M_PI / 180.0f)
				continue ;
		}

		if (nl_dot <= 0.0f)
			continue ;

		ref_dir = vec_calc(2.0f * nl_dot, &normal, -1.0f, &dir_pos2light);
		normalize(&ref_dir);

		inv_eye_dir = normalize_vec_inv(&eye_ray->direction);
		vr_dot = CLAMP(dot(&inv_eye_dir, &ref_dir), 0.0f, 1.0f);

		if (vr_dot <= 0.0f)
			continue ;

		vr_dot_pow = powf(vr_dot, shape->material.shininess);
		color_specular_ref = get_color_k1c1k2c2( 1.0f, &shape->material.specular_ref,
												 vr_dot_pow, &light->illuminance);

		color = colorf_add(color, color_specular_ref);
	}
	return (color);
}
