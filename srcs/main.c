/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:14:24 by takira            #+#    #+#             */
/*   Updated: 2023/04/24 20:10:10 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	init_data(t_data *data)
{

	data->win_width = WINDOW_WIDTH;
	data->win_height = WINDOW_HEIGHT;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (FAILURE);
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, WINDOW_TITLE);
	if (!data->win)
		return (FAILURE);
	data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!data->img)
		return (FAILURE);

	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);

	return (SUCCESS);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}


void	free_scene(t_scene *scene)
{

	ft_lstclear(&scene->light_list, free);
//	ft_lstclear(&scene.shape_list, free);

	t_list		*shape_node;
	t_list		*next;
	t_shape		*shape;

	shape_node = scene->shape_list;
	while (shape_node)
	{
//		printf("# shape_node:%p, texture.data:%p, bump.data:%p\n", shape_node, shape->material.texture.data, shape->material.bump.data);
		next = shape_node->next;
		shape = shape_node->content;

		free(shape->material.texture.data);
		free(shape->material.bump.data);
		free(shape);
		free(shape_node);
		shape_node = next;
	}

}

t_colorf	get_gradation_background_color(float height_ratio)
{
	t_colorf	color;
	float		r, g, b;

	r = 1.0f - height_ratio + height_ratio * 0.5f;
	g = 1.0f - height_ratio + height_ratio * 0.7f;
	b = 1.0f - height_ratio + height_ratio * 1.0f;
	SET_COLOR(color, r, g, b);
	return (color);
}

/* **********************

 Coordinates : Left hand

   +y
   |  +z
   | /
   |/_____ +x

 ********************** */

void	draw_screen(t_data data, t_camera camera, t_scene scene)
{
	t_ray		eye_ray;
	t_colorf	color;
	int			i, j;
	int			r, g, b;
	float		height_ratio = 1.0f;

	eye_ray.start = camera.pos;

	j = 0;
	while (j < data.win_height)
	{
		i = 0;
		while (i < data.win_width)
		{
			color = get_gradation_background_color(height_ratio);
			eye_ray.direction = calc_ray_dir(i, j, camera);
			raytrace(&scene, &eye_ray, &color);

			r = (int)(255 * CLAMP(color.r, 0, 1));
			g = (int)(255 * CLAMP(color.g, 0, 1));
			b = (int)(255 * CLAMP(color.b, 0, 1));

			my_mlx_pixel_put(&data, i, j, r << 16 | g << 8 | b);

			i++;
		}
		j++;
		height_ratio = 1.0f - (float)j / (float)data.win_height;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_scene		scene;
	t_camera	camera;
	int 		ret_val;

	if (argc != 2)
	{
		ft_dprintf(STDERR_FILENO, "[Error]Invalid argument.\n"
								  "       $> ./miniRT <scene filepath>\n");
		return (1);
	}

	ret_val = get_and_validate_scene_config(&scene, &camera, argv[1]);
	if (ret_val != SUCCESS)
	{
		//todo:error mgs, free_params
		ft_dprintf(STDERR_FILENO, "Error\n");
		free_scene(&scene);
		return (1);
	}

	init_camera(&camera);

	if (init_data(&data) == FAILURE)
	{
		free_scene(&scene);
		return (EXIT_FAILURE);
	}

	draw_screen(data, camera, scene);

	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hooks(data);
	mlx_loop(data.mlx);

	free_data(&data);
	free_scene(&scene);
	return (0);
}

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q miniRT");
}