/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_refraction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:34:26 by takira            #+#    #+#             */
/*   Updated: 2023/04/24 13:50:50 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ##### バグとりきれず保留 #####

t_colorf	calc_inflection_refraction(
		const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level,
		t_intersection_point intp, t_shape *shape)
{
	float		eta_1;			// 物質1（屈折前）の絶対屈折率
	float		eta_2;			// 物質2（屈折後）の絶対屈折率
	float		eta_r;			// 一時変数eta_r
	t_vector	re_dir, fe_dir;	// 反射方向、屈折方向
	t_ray		fe_ray;			// 屈折ray
	t_colorf	fe_color;		// 屈折光の輝度
	float		cos_theta1, cos_theta2;
	float		rho_p, rho_s;	// p偏光反射率, s偏光反射率
	float		cr, ct;			// 反射率, 透過率
	float		omega;			// 一時変数

	t_colorf	color;
	t_vector	eye_dir;
	t_vector	n_dir;			// 法線ベクトル
	float		vn_dot;
	t_vector	inv_eye_dir;

	t_ray		re_ray;		// 反射ray,
	t_colorf	re_color;	// 反射光の輝度

	SET_COLOR(color, 0.0f, 0.0f, 0.0f);
	if (shape->material.type != MT_REFRACTION)
		return (color);

	n_dir = normalize_vec(&intp.normal);
	eye_dir = normalize_vec(&eye_ray->direction);

	/* 視線ベクトルの逆ベクトルの計算 */
	inv_eye_dir = normalize_vec_inv(&eye_dir);

	/* 視線ベクトルの逆ベクトルと法線ベクトルの内積 */
	vn_dot = dot(&inv_eye_dir, &n_dir);

	if (vn_dot >= 0.0f)
	{
		eta_1 = scene->global_refraction_index;
		eta_2 = shape->material.refraction_index;
	}
	else // 物体の裏側から入射した場合
	{
		/* 法線ベクトルをひっくり返し内積を計算しなおす */
		n_dir = normalize_vec_inv(&n_dir);
		vn_dot = dot(&inv_eye_dir, &n_dir);

		/* 屈折率1,2を入れ替える */
		eta_1 = shape->material.refraction_index;
		eta_2 = scene->global_refraction_index;
	}

	eta_r = eta_2 / eta_1;

	/* cos(theta1), cos(theta2)の計算 */
	cos_theta1 = vn_dot;
	cos_theta2 = eta_1 / eta_2 * sqrtf(SQR(eta_r) - (1.0f - SQR(cos_theta1)));

	/* 一時変数omegaの計算 */
	omega = eta_r * cos_theta2 - cos_theta1;


	/* 完全鏡面反射率、透過率の計算 */
	rho_p = (eta_r * cos_theta1 - cos_theta2) / ((eta_r * cos_theta1 + cos_theta2));
	rho_s = -1.0f * omega / (cos_theta1 + eta_r * cos_theta2);
	cr = 0.5f * (SQR(rho_p) + SQR(rho_s));
	ct = 1.0f - cr;


	/* 正反射方向ベクトルの計算 */
	re_dir = vec_calc(2.0f * vn_dot, &n_dir, -1.0f, &inv_eye_dir);
	normalize(&re_dir);

	/* 正反射方向のレイの始点を計算 */
	re_ray.start = vec_calc(1.0f, &intp.position, EPSILON, &re_dir);
	re_ray.direction = re_dir;


	/* 屈折方向のレイの始点を計算 */
	fe_ray.start = vec_calc(1.0f, &intp.position, EPSILON, &fe_dir);
	fe_ray.direction = fe_dir;

	/* 屈折方向ベクトルの計算 */
	fe_dir = vec_calc(eta_1 / eta_2, &eye_dir, eta_1 / eta_2 * omega, &n_dir);
	normalize(&fe_dir);


	/* colorの初期化 */
	re_color = *out_col;
	fe_color = *out_col;

	/* 再帰呼び出し（反射） */
	recursive_raytrace(scene, &re_ray, &re_color, recursion_level + 1);
	/* 再帰呼び出し（屈折） */
	recursive_raytrace(scene, &fe_ray, &fe_color, recursion_level + 1);

	/* 完全鏡面反射、屈折光を計算 */
	color = colorf_mul_k1c1k2c2(&color, 1.0f, &shape->material.reflect_ref, cr,
								&re_color);
	color = colorf_mul_k1c1k2c2(&color, 1.0f, &shape->material.reflect_ref, ct,
								&fe_color);
	return (color);
}