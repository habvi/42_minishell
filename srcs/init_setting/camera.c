/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:20:47 by takira            #+#    #+#             */
/*   Updated: 2023/04/24 17:42:56 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_camera(t_camera *camera)
{
	float		fov_radians;

	normalize(&camera->dir);

	fov_radians  = camera->fov_deg * (float)M_PI / 180.0f;
	camera->distance_camera_to_sc = (WINDOW_HEIGHT * ASPECT / 2.0f) / tanf(fov_radians / 2.0f);
	camera->vec_camera_to_sc_center = mult(camera->distance_camera_to_sc, &camera->dir);

	camera->translate_matrix_w2c = get_tr_matrix_world2obj_yup(
			normalize_vec_inv(&camera->dir));
	camera->translate_matrix_c2w = transpose_matrix(camera->translate_matrix_w2c);
}
