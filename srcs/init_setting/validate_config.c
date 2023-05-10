/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:22:51 by takira            #+#    #+#             */
/*   Updated: 2023/04/24 17:23:44 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int is_vec_in_normal_range(t_vector vec)
{
	const float x = vec.x;
	const float y = vec.y;
	const float z = vec.z;

	return ((-1.0f <= x && x <= 1.0f) && (-1.0f <= y && y <= 1.0f) && (-1.0f <= z && z <= 1.0f));
}

int is_color_in_range(t_colorf color)
{
	const float	r = color.r;
	const float	g = color.g;
	const float	b = color.b;

	return ((0.0f <= r && r <= 255.0f) && (0.0f <= g && g <= 255.0f) && (0.0f <= b && b <= 255.0f));
}