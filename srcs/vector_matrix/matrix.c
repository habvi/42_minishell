/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:50:56 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 19:24:18 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	get_tr_matrix_world2tangent(t_vector w_dir)
{
	t_vector	eu, ew, ev;
	t_vector	ex, ey, ez;
	t_matrix	Tr;

	SET_VECTOR(ex, 1.0f, 0.0f, 0.0f);
	SET_VECTOR(ey, 0.0f, 1.0f, 0.0f);
	SET_VECTOR(ez, 0.0f, 0.0f, 1.0f);

	ev = w_dir;
	eu = cross(&ev, &ey);
	ew = cross(&eu, &ev);

	if (ev.x == ey.x && ev.y == ey.y && ev.z == ey.z)
	{
		eu = ex;
		ew = ez;
	}
	if (ev.x == ey.x && ev.y == -ey.y && ev.z == ey.z)
	{
		eu = normalize_vec_inv(&ex);
		ew = normalize_vec_inv(&ez);
	}
	Tr = set_vec_to_matrix(eu, ev, ew);
	return(Tr);
}

t_matrix	get_tr_matrix_world2obj_yup(t_vector w_dir)
{
	t_vector	eu, ew, ev;
	t_vector	ex, ey, ez;
	t_matrix	Tr;

	SET_VECTOR(ex, 1.0f, 0.0f, 0.0f);
	SET_VECTOR(ey, 0.0f, 1.0f, 0.0f);
	SET_VECTOR(ez, 0.0f, 0.0f, 1.0f);

	ev = w_dir;
	eu = cross(&ev, &ey);
	ew = cross(&eu, &ev);

	if (ev.x == ey.x && ev.y == ey.y && ev.z == ey.z)
	{
		eu = ex;
		ew = ez;
	}
	if (ev.x == ey.x && ev.y == -ey.y && ev.z == ey.z)
	{
		eu = ex;
		ew = normalize_vec_inv(&ez);
	}

	Tr = set_vec_to_matrix(eu, ev, ew);	// (x,y,z)->(u,w,v)への変換matrix
	return (Tr);
}

t_matrix	get_tr_matrix_world2obj_zup(t_vector w_dir)
{
	t_vector	eu, ew, ev;
	t_vector	ex, ey, ez;
	t_matrix	Tr;

	SET_VECTOR(ex, 1.0f, 0.0f, 0.0f);
	SET_VECTOR(ey, 0.0f, 1.0f, 0.0f);
	SET_VECTOR(ez, 0.0f, 0.0f, 1.0f);

	ev = normalize_vec(&w_dir);
	eu = cross(&ev, &ez);
	ew = cross(&eu, &ev);
	if (ev.x == ez.x && ev.y == ez.y && ev.z == ez.z)
	{
		eu = ex;
		ew = normalize_vec_inv(&ey);
	}
	if (ev.x == ez.x && ev.y == ez.y && ev.z == -ez.z)
	{
		eu = ex;
		ew = ey;
	}
//	 こっちでもOK
//	ew = cross(&ex, &ev);
//	eu = cross(&ev, &ew);
//	if (ev.x == ex.x && ev.y == ex.y && ev.z == ex.z)
//	{
//		eu = normalize_vec_inv(&ey);
//		ew = ez;
//	}
//	if (ev.x == -ex.x && ev.y == ex.y && ev.z == ex.z)
//	{
//		eu = ey;
//		ew = ez;
//	}
	Tr = set_vec_to_matrix(eu, ev, ew);	// (x,y,z)->(u,v,w)への変換matrix
	return (Tr);
}

t_matrix	set_vec_to_matrix(t_vector m1, t_vector m2, t_vector m3)
{
	t_matrix	Mt;

	Mt.m11 = m1.x; Mt.m12 = m1.y; Mt.m13 = m1.z;
	Mt.m21 = m2.x; Mt.m22 = m2.y; Mt.m23 = m2.z;
	Mt.m31 = m3.x; Mt.m32 = m3.y; Mt.m33 = m3.z;
	return (Mt);
}

t_vector	mul_matrix_vec(t_matrix Matrix, t_vector vec)
{
	t_vector	v;

	v.x = Matrix.m11 * vec.x + Matrix.m12 * vec.y + Matrix.m13 * vec.z;
	v.y = Matrix.m21 * vec.x + Matrix.m22 * vec.y + Matrix.m23 * vec.z;
	v.z = Matrix.m31 * vec.x + Matrix.m32 * vec.y + Matrix.m33 * vec.z;
	return (v);
}

t_matrix	transpose_matrix(t_matrix Matrix)
{
	t_matrix	Mt;

	Mt.m11 = Matrix.m11; Mt.m12 = Matrix.m21; Mt.m13 = Matrix.m31;
	Mt.m21 = Matrix.m12; Mt.m22 = Matrix.m22; Mt.m23 = Matrix.m32;
	Mt.m31 = Matrix.m13; Mt.m32 = Matrix.m23; Mt.m33 = Matrix.m33;
	return (Mt);
}