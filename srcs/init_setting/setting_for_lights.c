/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_setting_for_lights.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:40:17 by takira            #+#    #+#             */
/*   Updated: 2023/04/12 16:11:48 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light_type	get_light_type(t_identifier id)
{
	if (id == id_point_light)
		return (LT_POINT);
	return (LT_SPOT);
}


// L   XYZ   brightness_ratio[0,1]   RGB[0,255]
// sl  XYZ   brightness_ratio[0,1]   RGB[0,255]   angle[0,180]
int get_setting_for_lights(const char *line, t_scene *scene, t_identifier id)
{
	t_light		*light;
	size_t		idx;
	t_list		*new_list;
	float		brightness_ratio;
	t_colorf	color;

	light = (t_light *) ft_calloc(sizeof(t_light), 1);
	if (!light)
		return (FAILURE);

	light->type = get_light_type(id);
	idx = 0;
	if (parsing_vec(line, &light->position, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_double_num(line, &brightness_ratio, &idx) == FAILURE)
		return (FAILURE);
	if (brightness_ratio < 0.0f || 1.0f < brightness_ratio)
		return (FAILURE);

	if (parsing_color(line, &color, &idx) == FAILURE)
		return (FAILURE);

	if (!is_color_in_range(color))
		return (FAILURE);

	if (light->type == LT_SPOT)
	{
		if (parsing_double_num(line, &light->angle, &idx) == FAILURE)
			return (FAILURE);
		if (light->angle < 0.0f || 180.0f < light->angle)
			return (FAILURE);
	}

	if (line[idx])
		return (FAILURE);

	color = get_color_k1c1(1.0f / 255.0f, color);
	light->illuminance = get_color_k1c1(brightness_ratio, color);

	new_list = ft_lstnew(light);
	if (!new_list)
		return (FAILURE);
	ft_lstadd_back(&scene->light_list, new_list);

	printf("lights OK :)\n");

	return (SUCCESS);
}