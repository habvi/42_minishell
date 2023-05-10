/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_setting_for_id.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:36:11 by takira            #+#    #+#             */
/*   Updated: 2023/04/24 17:18:33 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// XYZ : 0.0, 0.0, 0.0
// RGB : 255, 0, 255
// image_path : image_path, bumpmap_path

// C   XYZ   orientation_vec[-1,1]   FOV[0,180]
int get_setting_for_camera(const char *line, t_camera *camera)
{
	size_t		idx;

	idx = 0;
	skip_spece(line, &idx);

	if (parsing_vec(line, &camera->pos, &idx) == FAILURE)
	{
		printf(" Error: parsing_vec 1 (camera)\n");
		return (FAILURE);
	}
	if (parsing_vec(line, &camera->dir, &idx) == FAILURE)
	{
		printf(" Error: parsing_vec 2 (camera)\n");
		return (FAILURE);
	}
	if (!is_vec_in_normal_range(camera->dir))
	{
		printf(" Error: normal vec out of range (camera)\n");
		return (FAILURE);
	}
	if (parsing_double_num(line, &camera->fov_deg, &idx) == FAILURE)
	{
		printf(" Error: parsing_double_num (camera)\n");
		return (FAILURE);
	}
	if (camera->fov_deg < 0.0f || 180.0f < camera->fov_deg)
	{
		printf(" Error: fov deg out of range (camera)\n");
		return (FAILURE);
	}
	printf("    camera :: fov:%f\n", camera->fov_deg);

	skip_spece(line, &idx);
	if (line[idx])
	{
		printf(" Error: invalid string (camera)\n");
		return (FAILURE);
	}
	printf("camera OK :)\n");
	return (SUCCESS);
}
