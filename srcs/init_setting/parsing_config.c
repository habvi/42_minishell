/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:10:39 by takira            #+#    #+#             */
/*   Updated: 2023/04/25 12:13:46 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	increment_idx_to_next_format(const char *line, size_t *idx, char *prev_str)
{
	*idx += ft_strlen_ns(prev_str);
	skip_spece(line, idx);
}

char	*get_identifier_str(const char *line, size_t idx)
{
	char		*id_str;
	size_t 		str_len;

	str_len = 0;
	while (line[idx + str_len] && !ft_isspace(line[idx + str_len]))
		str_len++;
	id_str = ft_substr(line, idx, str_len);
	if (!id_str)
		return (NULL);
	return (id_str);
}

//todo: 本実装時にはparsing_int_numも
int	parsing_double_num(const char *line, float *double_num, size_t *idx)
{
	size_t	len;
	char	*num_str;
	bool	is_success;

	skip_spece(line, idx);

	len = 0;
	while (line[*idx + len] && !ft_isspace(line[*idx + len]) && line[*idx + len] != ',')
		len++;

	num_str = ft_substr(line, *idx, len);
	if (!num_str)
	{
		perror("malloc");
		return (FAILURE);
	}
	*idx += len;
	*double_num = (float)ft_strtod(num_str, &is_success, NULL);
	free(num_str);

	if (!is_success)
		return (FAILURE);
	return (SUCCESS);
}

void	skip_spece(const char *line, size_t *idx)
{
	while (line[*idx] && ft_isspace(line[*idx]))
		*idx += 1;
}

void	skip_delimiter(const char *line, size_t *idx)
{
	skip_spece(line, idx);
	if (line[*idx] == ',')
		*idx += 1;
	skip_spece(line, idx);
}

// double_num1, double_num2, double_num3
int parsing_vec(const char *line, t_vector *vec, size_t *idx)
{
	skip_spece(line, idx);
	if (parsing_double_num(line, &vec->x, idx) == FAILURE)
	{
		printf("    parsing_vec NG :: parsing_double_num 1\n");
		return (FAILURE);
	}

	skip_delimiter(line, idx);

	if (parsing_double_num(line, &vec->y, idx) == FAILURE)
	{
		printf("    parsing_vec NG :: parsing_double_num 2\n");
		return (FAILURE);
	}

	skip_delimiter(line, idx);

	if (parsing_double_num(line, &vec->z, idx) == FAILURE)
	{
		printf("    parsing_vec NG :: parsing_double_num 3\n");
		return (FAILURE);
	}

	skip_spece(line, idx);


	printf("    parsing_vec :: SUCCESS, (x,y,z)=(%f,%f,%f)\n", vec->x, vec->y, vec->z);

	return (SUCCESS);
}

// int_num1, int_num2, int_num3
int parsing_color(const char *line, t_colorf *color, size_t *idx)
{
	skip_spece(line, idx);

	if (parsing_double_num(line, &color->r, idx) == FAILURE)
	{
		printf("    parsing_color NG :: parsing_int_num 1, r:%d\n", (int)color->r);
		return (FAILURE);
	}
//	printf("    parsing_color :: r:%f\n", color->r);

	skip_delimiter(line, idx);

	if (parsing_double_num(line, &color->g, idx) == FAILURE)
	{
		printf("    parsing_color NG :: parsing_int_num 2\n");
		return (FAILURE);
	}
//	printf("    parsing_color :: g:%f\n", color->g);

	skip_delimiter(line, idx);

	if (parsing_double_num(line, &color->b, idx) == FAILURE)
	{
		printf("    parsing_color NG :: parsing_int_num 3\n");
		return (FAILURE);
	}
//	printf("    parsing_color :: b:%f\n", color->b);

	skip_spece(line, idx);

	printf("    parsing_color :: SUCCESS, (r,g,b)=(%f,%f,%f)\n", color->r, color->g, color->b);
	return (SUCCESS);
}
