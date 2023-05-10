/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_perfect_reflection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:34:10 by takira            #+#    #+#             */
/*   Updated: 2023/04/24 14:06:07 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colorf	calc_perfect_reflection(
		const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level,
		t_intersection_point intp, t_shape *shape)
{
	t_colorf	color;
	t_vector	eye_dir;
	t_vector	n_dir;			// 法線ベクトル
	float		vn_dot;
	t_vector	ref_dir;
	t_vector	inv_eye_dir;

	t_ray		perfect_reflection_ray;		// 反射ray,
	t_colorf	perfect_reflection_color;	// 反射光の輝度

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);

	if (shape->material.type != MT_PERFECT_REFLECTION)
		return (color);

	/* 完全鏡面反射 */
	n_dir = normalize_vec(&intp.normal);
	eye_dir = normalize_vec(&eye_ray->direction);

	/* 視線ベクトルの逆ベクトルの計算 */
	inv_eye_dir = normalize_vec_inv(&eye_dir);

	/* 視線ベクトルの逆ベクトルと法線ベクトルの内積 */
	vn_dot = dot(&inv_eye_dir, &n_dir);

	/* vn_dot <= 0 のとき */
	if (vn_dot <= 0.0f)
		return (color);

	/* 視線ベクトルの正反射ベクトルを計算 */
	ref_dir = vec_calc(2.0f * vn_dot, &n_dir, -1, &inv_eye_dir);
	normalize(&ref_dir);

	/* 正反射方向のrayを計算 */
	perfect_reflection_ray.start = vec_calc(1.0f, &intp.position, EPSILON, &ref_dir);
	perfect_reflection_ray.direction = ref_dir;

	/* raytrace */
	perfect_reflection_color = *out_col;
	recursive_raytrace(scene, &perfect_reflection_ray, &perfect_reflection_color, recursion_level + 1);

	/* 完全鏡面反射を計算 */
	color = get_color_k1c1k2c2(1.0f, &shape->material.reflect_ref,1.0f, &perfect_reflection_color);
	return (color);
}