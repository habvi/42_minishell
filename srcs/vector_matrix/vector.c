/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:48:43 by takira            #+#    #+#             */
/*   Updated: 2023/04/10 20:00:29 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdarg.h>

t_vector	init_vector(float x, float y, float z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vector	normalize_vec(const t_vector *a)
{
	t_vector	vec;

	vec = copy_vec(a);
	normalize(&vec);
	return (vec);
}

t_vector	normalize_vec_inv(const t_vector *a)
{
	t_vector	vec;

	vec = copy_vec(a);
	vec = mult(-1.0f, &vec);
	normalize(&vec);
	return (vec);
}

t_vector	vec_calc(float k1, t_vector *a, float k2, t_vector *b)
{
	t_vector	k1a;
	t_vector	k2b;

	k1a = mult(k1, a);
	k2b = mult(ABS(k2), b);
	if (k2 >= 0)
		return (add(&k1a , &k2b));
	return (sub(&k1a, &k2b));
}

t_vector	copy_vec(const t_vector *a)
{
	t_vector	vec;

	vec.x = a->x;
	vec.y = a->y;
	vec.z = a->z;
	return (vec);
}

t_vector	mult(float k, const t_vector *a)
{
	t_vector	vec;

	vec.x = k * a->x;
	vec.y = k * a->y;
	vec.z = k * a->z;
	return (vec);
}

t_vector	add(const t_vector *a, const t_vector *b)
{
	t_vector	vec;

	vec.x = a->x + b->x;
	vec.y = a->y + b->y;
	vec.z = a->z + b->z;
	return (vec);
}

t_vector sub(const t_vector *a, const t_vector *b)
{
	t_vector	vec;

	vec.x = a->x - b->x;
	vec.y = a->y - b->y;
	vec.z = a->z - b->z;
	return (vec);
}

/* num: num of args    */
/* k1, v1, k2, v2, ... */
t_vector	sigma_sum(int num, ...)
{
	va_list		ap;
	t_vector	vec;
	float		ki;
	t_vector	vi;
	int			i;

	init_vector(0.0f, 0.0f, 0.0f);
	i = 0;
	va_start(ap, num);
	va_arg(ap, int);
	while (i < num)
	{
		ki = va_arg(ap, double);
		vi = va_arg(ap, t_vector);
//		printf("ki:%lf, vi:%s\n", ki, vector_str(&vi));
		vec.x += ki * (&vi)->x;
		vec.y += ki * (&vi)->y;
		vec.z += ki * (&vi)->z;
		i++;
	}
	va_end(ap);
	return (vec);
}

float	dot(const t_vector *a, const t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

float	squared_norm(const t_vector *vec)
{
	return (SQR(vec->x) + SQR(vec->y) + SQR(vec->z));
}

float	norm(const t_vector *vec)
{
	return (sqrtf(squared_norm(vec)));
}

float	normalize(t_vector *vec)
{
	float	vnorm;

	vnorm = norm(vec);
	vec->x /= vnorm;
	vec->y /= vnorm;
	vec->z /= vnorm;
	return (vnorm);
}

t_vector	cross(const t_vector *a, const t_vector *b)
{
	t_vector	o;

	o.x = a->y * b->z - a->z * b->y;
	o.y = a->z * b->x - a->x * b->z;
	o.z = a->x * b->y - a->y * b->x;
	return (o);
}

// TODO : delete
const char	*vector_str(const t_vector *vec)
{
	static char buf[1024];
	memset(buf, 0, sizeof(buf));
	sprintf((void*)buf, "(%f, %f, %f)", vec->x, vec->y, vec->z);
	return (buf);
}
