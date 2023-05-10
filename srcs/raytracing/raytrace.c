/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:26:30 by takira            #+#    #+#             */
/*   Updated: 2023/04/12 14:33:49 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	recursive_raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level)
{
	int						intersect_result;	// 交差判定の結果
	t_shape					*shape;				// 交差した物体へのポインタ
	t_intersection_point	intp;				// 交点

	t_colorf				color;
	t_colorf				perfect_reflect_color;
	t_colorf				inflection_refraction_color;
	t_colorf				diffuse_reflect_color;
	t_colorf				specular_reflect_color;
	t_colorf				ambient_reflect_color;

	if (recursion_level > MAX_RECURSION)
		return (0);

	intersect_result = get_nearest_shape(scene, eye_ray, FLT_MAX, 0, &shape, &intp);

	/* 視線方向に物体がなかった場合 */
	if (!intersect_result)
		return (0);

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	ambient_reflect_color = scene->ambient_illuminance;
	diffuse_reflect_color = calc_diffuse_reflection(scene, intp, *eye_ray, shape);
	specular_reflect_color = calc_specular_reflection(scene, eye_ray, intp, shape);
	perfect_reflect_color = calc_perfect_reflection(scene, eye_ray, out_col, recursion_level, intp, shape);
	inflection_refraction_color = calc_inflection_refraction(scene, eye_ray, out_col, recursion_level, intp, shape);

	color = colorf_add(color, ambient_reflect_color);
	color = colorf_add(color, diffuse_reflect_color);
	color = colorf_add(color, specular_reflect_color);
	color = colorf_add(color, perfect_reflect_color);
	color = colorf_add(color, inflection_refraction_color);

	*out_col = color;
	return (1);
}

int	raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col)
{
	return (recursive_raytrace(scene, eye_ray, out_col, 0));
}
