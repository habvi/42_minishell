/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:30:56 by takira            #+#    #+#             */
/*   Updated: 2023/04/24 17:42:38 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 screen_x: [0, WIDTH)
 screen_y: [0, HEIGHT)
   v v v
 world_x: screen_x * u
 world_y: screen_y * v
 */

// calc_ray_dir : camera_pos(x,y,z) -> screen(x,y,z)
t_vector	calc_ray_dir(int i, int j, t_camera camera)
{
	t_vector	ray_dir;
	t_vector	screen_local;
	t_vector	screen_world;

	screen_local.x = (float)i - WINDOW_WIDTH / 2.0f;
	screen_local.y = 0.0f;
	screen_local.z = WINDOW_HEIGHT / 2.0f - (float)j;

	screen_world = mul_matrix_vec(camera.translate_matrix_c2w, screen_local);
	ray_dir = add(&camera.vec_camera_to_sc_center, &screen_world);

	normalize(&ray_dir);
	return (ray_dir);
}
