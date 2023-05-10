/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:02:44 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 16:53:11 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// c + k1c1 * k2c2
t_colorf	colorf_mul_k1c1k2c2(const t_colorf *c, float k1, const t_colorf *c1, float k2, const t_colorf *c2)
{
	t_colorf	color;

	color.r = c->r + k1 * c1->r * k2 * c2->r;
	color.g = c->g + k1 * c1->g * k2 * c2->g;
	color.b = c->b + k1 * c1->b * k2 * c2->b;
	return (color);
}

// c + k1c1
t_colorf	colorf_muladd_k1c2_k2c2(const t_colorf c, float k1, const t_colorf c1, float k2, const t_colorf c2)
{
	t_colorf	color;

	color.r = c.r + k1 * c1.r + k2 * c2.r;
	color.g = c.g + k1 * c1.g + k2 * c2.g;
	color.b = c.b + k1 * c1.b + k2 * c2.b;
	return (color);
}

t_colorf	get_color_k1c1k2c2(float k1, const t_colorf *c1, float k2, const t_colorf *c2)
{
	t_colorf	color;

	color.r = k1 * c1->r * k2 * c2->r;
	color.g = k1 * c1->g * k2 * c2->g;
	color.b = k1 * c1->b * k2 * c2->b;
	return (color);
}

t_colorf	get_color_k1c1(float k1, const t_colorf c1)
{
	t_colorf	color;

	color.r = k1 * c1.r;
	color.g = k1 * c1.g;
	color.b = k1 * c1.b;
	return (color);
}

t_colorf	colorf_add(const t_colorf c1, const t_colorf c2)
{
	t_colorf	color;

	color.r = c1.r + c2.r;
	color.g = c1.g + c2.g;
	color.b = c1.b + c2.b;
	return (color);
}

t_colorf	init_color(float r, float g, float b)
{
	t_colorf	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}
