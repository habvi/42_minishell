/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyhooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:25:59 by takira            #+#    #+#             */
/*   Updated: 2023/04/24 19:53:35 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_window(void *mlx)
{
	printf("close window\n");
	mlx_loop_end(mlx);
	return (0);
}

static int	key_hook(int keycode, void *mlx)
{
	if (keycode == KEY_ESC)
	{
//		printf("ESC pressed\n");
		return (close_window(mlx));
	}
	if (keycode == 'w')
	{
		printf("up\n");
	}
	if (keycode == 'a')
	{
		printf("left\n");
	}
	if (keycode == 's')
	{
		printf("down\n");
	}
	if (keycode == 'd')
	{
		printf("right\n");
	}

	return (0);
}

void	mlx_hooks(t_data data)
{
	const int	mask_key_press = 1L << 0;
	const int	mask_button_press = 1L << 17;

	mlx_hook(data.win, EVENT_KEY_PRESS, mask_key_press, key_hook, data.mlx);
	mlx_hook(data.win, EVENT_DESTROY, mask_button_press, close_window, data.mlx);
}
