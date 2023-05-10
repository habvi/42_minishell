/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_setting_for_objects.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:40:32 by takira            #+#    #+#             */
/*   Updated: 2023/04/24 20:24:48 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_path(const char *line, size_t *idx)
{
	char	*path;
	size_t	len;

	while (line[*idx] && ft_isspace(line[*idx]))
		*idx += 1;
	if (line[*idx] != '"')
		return (NULL);
	*idx += 1;
	len = 0;
	while (line[*idx + len] && line[*idx + len] != '"')
		len++;
	if (line[*idx + len] != '"')
		return (NULL);
	path = ft_substr(line, *idx, len);
	if (!path)
		return (NULL);
	*idx += len + 1;
	return (path);
}

static int get_checker_format(const char *line, t_shape *shape, size_t *idx)
{
	t_colorf	checker_color;

	if (!ft_isdigit(line[*idx]))
		return (FAILURE);
	shape->material.is_checker = true;
	if (parsing_color(line, &checker_color, idx) == FAILURE)
		return (FAILURE);
	if (!is_color_in_range(checker_color))
		return (FAILURE);
	shape->material.checker_color = get_color_k1c1(1.0f / 255.0f, checker_color);
//		shape->material.diffuse_ref = get_color_k1c1(1.0f / 255.0f, shape->material.diffuse_ref);

	skip_spece(line, idx);

	return (SUCCESS);
}

static int get_perfect_ref_format(const char *line, t_shape *shape, size_t *idx)
{
	SET_COLOR(shape->material.reflect_ref, 1.0f, 1.0f, 1.0f);
	shape->material.type = MT_PERFECT_REFLECTION;

	skip_spece(line, idx);

	return (SUCCESS);
}

static int get_image_texture_format(const char *line, t_shape *shape, size_t *idx)
{
	char		*path;

	path = get_path(line, idx);
	if (!path)
		return (FAILURE);
	printf("img_path:[%s]\n", path);

	if (ft_strlen_ns(path) > 0)
	{
		if (get_img(&shape->material.texture, path) == FAILURE)
		{
			free(path);
			return (FAILURE);
		}
	}
	free(path);

	skip_delimiter(line, idx);

	path = get_path(line, idx);
	if (!path)
		return (PROCESS_ERROR);
	printf("bump_path:[%s]\n", path);
	if (ft_strlen_ns(path) > 0)
	{
		if (get_img(&shape->material.bump, path) == FAILURE)
		{
			free(path);
			return (FAILURE);
		}
	}
	free(path);
	skip_spece(line, idx);

	return (SUCCESS);
}

static int get_bonus_option(const char *line, t_shape *shape, size_t *idx)
{
	char		*op_str;
	int 		ret_value;

	op_str = get_identifier_str(line, *idx);
	increment_idx_to_next_format(line, idx, op_str);
	if (!op_str)
		return (PROCESS_ERROR);
	ret_value = FAILURE;
	if (is_same_str(op_str, OP_CHECKER_TEXTURE))
	{
		ret_value = get_checker_format(line, shape, idx);
	}
	else if (is_same_str(op_str, OP_PERFECT_REF))
	{
		ret_value = get_perfect_ref_format(line, shape, idx);
	}
	else if (is_same_str(op_str, OP_IMAGE_TEXTURE))
	{
		ret_value = get_image_texture_format(line, shape, idx);
	}
	else
		printf("invalid bonus option:[%s]\n", op_str);
	free(op_str);
	if (line[*idx])
		return (FAILURE);
	printf("get_bonus_op SUCCESS\n");
	return (ret_value);
}

// sp   XYZ                    diameter            RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
static int get_setting_for_sphere(const char *line, t_shape *shape)
{
	size_t		idx;
	float 		diameter;
	t_colorf	color;

	shape->type = ST_SPHERE;
	idx = 0;
	if (parsing_vec(line, &shape->data.sphere.center, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_double_num(line, &diameter, &idx) == FAILURE)
		return (FAILURE);
	if (diameter <= 0.0f)
		return (FAILURE);
	shape->data.sphere.radius = diameter / 2.0f;
	printf("   [sp] diameter:%f\n", diameter);

	if (parsing_color(line, &color, &idx) == FAILURE)
		return (FAILURE);
	if (!is_color_in_range(color))
		return (FAILURE);

	shape->material.diffuse_ref = get_color_k1c1(1.0f / 255.0f, color);
//	shape->material.diffuse_ref = get_color_k1c1(1.0f / 255.0f, shape->material.diffuse_ref);

	if (!line[idx])
		return (SUCCESS);

	if (get_bonus_option(line, shape, &idx) == FAILURE)
		return (FAILURE);
	if (line[idx])
		return (FAILURE);
	return (SUCCESS);
}

// pl   XYZ   norm_vec[-1,1]                       RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
static int get_setting_for_plane(const char *line, t_shape *shape)
{
	size_t		idx;
	t_colorf	color;

	shape->type = ST_PLANE;
	idx = 0;
	if (parsing_vec(line, &shape->data.plane.position, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_vec(line, &shape->data.plane.normal, &idx) == FAILURE)
		return (FAILURE);

	if (!is_vec_in_normal_range(shape->data.plane.normal))
		return (FAILURE);
	normalize(&shape->data.plane.normal);

	if (parsing_color(line, &color, &idx) == FAILURE)
		return (FAILURE);
	if (!is_color_in_range(color))
		return (FAILURE);
//	shape->material.diffuse_ref = get_color_k1c1(1.0f / 255.0f, shape->material.diffuse_ref);
	shape->material.diffuse_ref = get_color_k1c1(1.0f / 255.0f, color);

	if (!line[idx])
		return (SUCCESS);
	if (get_bonus_option(line, shape, &idx) == FAILURE)
		return (FAILURE);
	if (line[idx])
		return (FAILURE);
	return (SUCCESS);
}

// cy   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
static int get_setting_for_cylinder(const char *line, t_shape *shape)
{
	size_t		idx;
	float		diameter;
	t_colorf	color;

	shape->type = ST_CYLINDER;
	idx = 0;
	if (parsing_vec(line, &shape->data.cylinder.position, &idx) == FAILURE)
		return (FAILURE);

	if (parsing_vec(line, &shape->data.cylinder.normal, &idx) == FAILURE)
		return (FAILURE);
	if (!is_vec_in_normal_range(shape->data.cylinder.normal))
		return (FAILURE);
	normalize(&shape->data.cylinder.normal);

	if (parsing_double_num(line, &diameter, &idx) == FAILURE)
		return (FAILURE);
	if (diameter <= 0.0f)
		return (FAILURE);
	shape->data.cylinder.radius = diameter / 2.0f;
	printf("   [cylinder] diameter:%f\n", diameter);

	if (parsing_double_num(line, &shape->data.cylinder.height, &idx) == FAILURE)
		return (FAILURE);
	if (shape->data.cylinder.height <= 0.0f)
		return (FAILURE);
	printf("   [cylinder] height:%f\n", shape->data.cylinder.height);

	if (parsing_color(line, &color, &idx) == FAILURE)
		return (FAILURE);
	if (!is_color_in_range(color))
		return (FAILURE);
//	shape->material.diffuse_ref = get_color_k1c1(255.0f, shape->material.diffuse_ref);
	shape->material.diffuse_ref = get_color_k1c1(1.0f / 255.0f, color);

	if (!line[idx])
		return (SUCCESS);
	if (get_bonus_option(line, shape, &idx) == FAILURE)
		return (FAILURE);
	if (line[idx])
		return (FAILURE);
	return (SUCCESS);
}

// co   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
static int get_setting_for_corn(const char *line, t_shape *shape)
{
	size_t		idx;
	float		diameter;
	t_colorf	color;

	shape->type = ST_CORN;
	idx = 0;
	if (parsing_vec(line, &shape->data.corn.position, &idx) == FAILURE)
		return (FAILURE);
	if (parsing_vec(line, &shape->data.corn.normal, &idx) == FAILURE)
		return (FAILURE);
	if (!is_vec_in_normal_range(shape->data.corn.normal))
		return (FAILURE);
	normalize(&shape->data.corn.normal);


	if (parsing_double_num(line, &diameter, &idx) == FAILURE)
		return (FAILURE);
	if (diameter <= 0.0f)
		return (FAILURE);
	shape->data.corn.radius = diameter / 2.0f;
	printf("   [corn] diameter:%f\n", diameter);
	if (parsing_double_num(line, &shape->data.corn.height, &idx) == FAILURE)
		return (FAILURE);
	if (shape->data.corn.height <= 0.0f)
		return (FAILURE);
	printf("   [corn] height:%f\n", shape->data.corn.height);
	if (parsing_color(line, &color, &idx) == FAILURE)
		return (FAILURE);
	if (!is_color_in_range(color))
		return (FAILURE);
//	shape->material.diffuse_ref = get_color_k1c1(255.0f, shape->material.diffuse_ref);

	shape->material.diffuse_ref = get_color_k1c1(1.0f / 255.0f, color);
	shape->data.corn.origin = vec_calc(1.0f, &shape->data.corn.position, shape->data.corn.height, &shape->data.corn.normal);

	if (!line[idx])
		return (SUCCESS);
	if (get_bonus_option(line, shape, &idx) == FAILURE)
		return (FAILURE);
	if (line[idx])
		return (FAILURE);
	return (SUCCESS);
}

// sp   XYZ                    diameter            RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
// pl   XYZ   norm_vec[-1,1]                       RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
// cy   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
// co   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION:RGB[0,255]   image_paths>
int get_setting_for_objects(const char *line, t_scene *scene, t_identifier id)
{
	int		ret_value;
	t_shape	*shape;
	t_list	*new_list;

	shape = (t_shape *) ft_calloc(sizeof(t_shape), 1);
	if (!shape)
		return (FAILURE);

	shape->material.type = MT_DEFAULT;
	shape->material.shininess = 8.0f;
	SET_COLOR(shape->material.specular_ref, 0.3f, 0.3f, 0.3f)
	shape->material.refraction_index = 1.51f;

	ret_value = FAILURE;
	if (id == id_sphere)
		ret_value = get_setting_for_sphere(line, shape);
	else if (id == id_plane)
		ret_value = get_setting_for_plane(line, shape);
	else if (id == id_cylinder)
		ret_value = get_setting_for_cylinder(line, shape);
	else if (id == id_corn)
		ret_value = get_setting_for_corn(line, shape);

	if (ret_value == FAILURE)
	{
		free(shape);
		return (FAILURE);
	}

	new_list = ft_lstnew(shape);
	if (!new_list)
	{
		free(shape);
		return (FAILURE);
	}
	ft_lstadd_back(&scene->shape_list, new_list);

	printf("objs(id:%d) OK :)\n", id);

	return (ret_value);
}
