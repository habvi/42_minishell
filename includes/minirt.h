/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:42:42 by takira            #+#    #+#             */
/*   Updated: 2023/04/25 12:11:39 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <float.h>

# include "./../minilibx-linux/mlx.h"
# include "./../libs/include/libft.h"

/********** return value **********/
# define PROCESS_ERROR	3
# define INVALID_ID		(-1)

/********** color **********/
# define RED			0xFF0000
# define BLUE			0x0000FF
# define CORNFLOWERBLUE	0x6495ED
# define GRAY			0x808080

/********** window **********/
//# define ASPECT_WIDTH	16
//# define ASPECT_HEIGHT	9
//# define WINDOW_WIDTH	384
//# define ASPECT_WIDTH	1
//# define ASPECT_HEIGHT	1
# define ASPECT				(16.0f / 9.0f)
# define WINDOW_HEIGHT		540
# define WINDOW_WIDTH		960
# define WINDOW_TITLE		"miniRT"
//# define SCREEN_WIDTH	2
//# define SCREEN_HEIGHT	2

/********** key hook **********/
# define EVENT_DESTROY		33
# define EVENT_KEY_PRESS	2
# define KEY_ESC			0xff1b

/********** Macro **********/
#define SQR(x)		((x) * (x))
#define MIN(a, b)	(a <= b ? a : b)
#define MAX(a, b)	(a >= b ? a : b)
#define ABS(x)		(x >= 0 ? x : -1 * x)

#define CLAMP(val, minval, maxval)	MIN(MAX(val, minval), maxval)

#define SET_COLOR(col, r_, g_, b_)	{ col.r = r_; col.g = g_; col.b = b_; }
#define SET_VECTOR(vec, x_, y_, z_)	{ vec.x = x_; vec.y = y_; vec.z = z_; }


//#define EPSILON			(1.0f / 512.0f)
//#define EPSILON			(1.0f / 256.0f)
//#define EPSILON			(1.0f / 128.0f)
//#define EPSILON			(1.0f / 64.0f)
#define EPSILON			(1.0f / 32.0f)

#define MAX_RECURSION	8
#define OP_CHECKER_TEXTURE	"checker"
#define OP_PERFECT_REF		"perfect_ref"
#define OP_IMAGE_TEXTURE	"image"


/********** enum **********/
typedef enum	e_shape_type
{
	ST_PLANE,
	ST_SPHERE,
	ST_CYLINDER,
	ST_CORN,
} t_shape_type;

typedef enum	e_light_type
{
	LT_POINT,		// 点光源
	LT_DIRECTIONAL,	// 平行光源
	LT_SPOT,
} t_light_type;

typedef enum	e_material_type
{
	MT_DEFAULT,		// 通常の質感
	MT_PERFECT_REFLECTION,	// 完全鏡面反射
	MT_REFRACTION,	// 完全鏡面反射・屈折
} t_material_type;

typedef enum	e_identifier
{
	id_camera = 0,
	id_ambient = 1,
	id_point_light = 2,
	id_spot_light = 3,
	id_sphere = 4,
	id_plane = 5,
	id_cylinder = 6,
	id_corn = 7,
} t_identifier;

/********** struct **********/
typedef struct	s_data
{
	void	*mlx;
	void	*win;
	void	*img;

	int		win_width;
	int		win_height;

	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
} t_vector;

typedef struct s_matrix
{
	float	m11, m12, m13;
	float	m21, m22, m23;
	float	m31, m32, m33;
} t_matrix;

typedef struct	s_colorf
{
	float	r;
	float	g;
	float	b;
} t_colorf;

typedef struct	s_img
{
	int	height;
	int width;
	int	*data;	// data=[R11,G11,B11, R12,G12,B12, ..., R21,G21,B21,..., Rhw,Ghw,Bhw]
} t_img;

typedef struct	s_ray
{
	t_vector	start;		// 始点
	t_vector	direction;	// 方向ベクトル（単位？）
} t_ray;

typedef struct	s_plane
{
	t_vector	normal;		// 単位法線ベクトル
	t_vector	position;	// planeが通る点の位置ベクトル
} t_plane;

typedef struct	s_sphere
{
	float		radius;	// 半径
	t_vector	center;	// 中心
} t_sphere;

typedef struct	s_cylinder
{
	t_vector	normal;		// 単位法線ベクトル todo:direction
	t_vector	position;	// 中心位置ベクトル
	float		height;
	float		radius;
} t_cylinder;

typedef struct	s_corn
{
	t_vector	normal;		// 単位法線ベクトル todo:direction
	t_vector	position;	// 底面中心位置ベクトル
	t_vector	origin;		// 中心位置（先端）ベクトル
	float		height;
	float		radius;
} t_corn;


typedef union	u_shape_data // sphere or plane
{
	t_plane			plane;
	t_sphere		sphere;
	t_cylinder		cylinder;
	t_corn			corn;

} t_shape_data;

typedef struct	s_material
{
	t_colorf		ambient_ref;	// ka 環境光反射率RGB
	t_colorf		diffuse_ref;	// kd 拡散反射率RGB

	t_colorf		specular_ref;	// ks 鏡面反射率RGB
	float			shininess;		// alpha 光沢度

	t_material_type	type;			// default or 完全鏡面反射

	t_colorf		reflect_ref;	// kf 完全鏡面反射光/屈折光係数RGB
	float			refraction_index;	// 絶対屈折率

	t_colorf		checker_color;

	t_img			texture;
	t_img			bump;
	bool			is_checker;

} t_material;

typedef struct	s_shape
{
	t_shape_type	type;		// sphere or plane
	t_shape_data	data;		// sphere or plane の情報
	t_material		material;	// 物体表面の質感
} t_shape;

typedef struct	s_light
{
	t_light_type	type;			// point, directional or spot
	t_vector		position;		// 光源位置 or 光線方向（*光線への方向？光線からの方向？）
	t_vector		direction;
	t_colorf		illuminance;	// 光源の照度 Ii RGB
	float			angle;			// spot_light, angle
} t_light;

typedef struct	s_scene
{
//	t_shape		*shapes;				// 物体リストへのポインタ
//	size_t		num_shapes_capacity;	// 物体リストの最大格納数
//	size_t		num_shapes;				// 物体リストに格納されている数
//	t_light		*lights;				// 光源リストへのポインタ
//	size_t		num_lights_capacity;	// 光源リストの最大格納数
//	size_t		num_lights;				// 光源リストに格納されている数


	t_colorf	ambient_illuminance;	// 環境光の強さIa RGB
	float		global_refraction_index;// 大気の絶対屈折率

	t_list		*light_list;
	t_list		*shape_list;
} t_scene;

typedef struct	s_intersection_point
{
	float		distance;	// 交点までの距離
	t_vector	position;	// 交点の位置ベクトル
	t_vector	normal;		// 交点における物体表面の法線ベクトル
} t_intersection_point;

typedef struct	s_camera
{
	t_vector	pos;
	t_vector	dir;
	t_vector	vec_camera_to_sc_center;
	t_matrix	translate_matrix_w2c;
	t_matrix	translate_matrix_c2w;
	float		distance_camera_to_sc;
	float		fov_deg;
} t_camera;

typedef struct	s_texture_map
{
	float	u;
	float	v;
} t_texture_map;


/********** vector **********/
t_vector	init_vector(float x, float y, float z);
float		dot(const t_vector *a, const t_vector *b);
t_vector	add(const t_vector *a, const t_vector *b);
t_vector	sub(const t_vector *a, const t_vector *b);
t_vector	mult(float k, const t_vector *a);
t_vector	sigma_sum(int num, ...);
float		squared_norm(const t_vector *vec);
float		norm(const t_vector *vec);
float		normalize(t_vector *vec);
t_vector	cross(const t_vector *a, const t_vector *b);
//void		cross(t_vector *o, t_vector *a, t_vector *b);
const char	*vector_str(const t_vector *vec);
t_vector	copy_vec(const t_vector *a);
t_vector	vec_calc(float k1, t_vector *a, float k2, t_vector *b);
t_vector	normalize_vec(const t_vector *a);
t_vector	normalize_vec_inv(const t_vector *a);


/********** screen **********/
t_vector	calc_ray_dir(int i, int j, t_camera camera);


/********** camera **********/
void	init_camera(t_camera *camera);


/********** sphere **********/
t_sphere	init_sphere(float x, float y, float z, float r);
bool		is_intersect_to_sphere(t_sphere sphere, t_vector vec_eye, t_vector vec_screen, float *t);


/********** reflection **********/
//t_light		init_light(float x, float y, float z);
int			shading(t_vector vec_eye, t_vector vec_screen, t_light light, t_sphere sphere, float t);


/********** color **********/
t_colorf	init_color(float r, float g, float b);
t_colorf	colorf_mul_k1c1k2c2(const t_colorf *c, float k1, const t_colorf *c1, float k2, const t_colorf *c2);
t_colorf	colorf_add(t_colorf c1, t_colorf c2);
t_colorf	colorf_muladd_k1c2_k2c2(t_colorf c, float k1, t_colorf c1, float k2, t_colorf c2);
t_colorf	get_color_k1c1k2c2(float k1, const t_colorf *c1, float k2, const t_colorf *c2);
t_colorf	get_color_k1c1(float k1, const t_colorf c1);

/********** mlx_keyhooks **********/
void		mlx_hooks(t_data data);


/********** intersection **********/
int			intersection_test(t_shape *shape, const t_ray * ray, t_intersection_point * out_intp);
int			get_nearest_shape(const t_scene *scene, const t_ray *ray, float max_dist, int exit_once_found,
					  t_shape **out_shape, t_intersection_point *out_intp);

/********** checker **********/
t_colorf	get_checker_color(t_intersection_point intp, t_shape *shape);


/********** texture_map **********/
//t_texture_map	get_cylindrical_map(t_vector pos_local, t_matrix Tr, float h);
//t_texture_map	get_conical_map(t_vector pos_local, t_matrix Tr, float h);

//t_texture_map	get_spherical_map(t_vector pos_local);
//t_texture_map	get_planar_map(t_vector pos_local, t_matrix Tr);


t_texture_map	get_planar_map(t_vector int_pos, t_vector center_pos, t_vector obj_normal);
t_texture_map	get_spherical_map(t_vector int_pos, t_vector center_pos, float obj_radius);
t_texture_map	get_conical_map(t_vector int_pos, t_vector center_pos, t_vector obj_dir, float obj_height);
t_texture_map	get_cylindrical_map(t_vector int_pos, t_vector center_pos, t_vector obj_dir, float obj_height);


/********** matrix **********/
t_matrix	rot_matrix(t_vector E);
t_matrix	transpose_matrix(t_matrix R);
t_matrix	set_vec_to_matrix(t_vector m1, t_vector m2, t_vector m3);
t_vector	mul_matrix_vec(t_matrix T, t_vector v);
t_matrix	get_tr_matrix_world2obj_zup(t_vector w_dir);
t_matrix	get_tr_matrix_world2obj_plane(t_vector w_dir);
t_matrix	get_tr_matrix_world2obj_yup(t_vector w_dir);
t_matrix	get_tr_matrix_world2tangent(t_vector w_dir);


/********** img **********/
int			get_img(t_img *img, const char *img_path);
void		draw_img_test(t_data data, t_img img);
t_colorf	get_img_color(t_intersection_point intp, t_shape *shape, t_img img);
t_vector	get_bump_normal(t_intersection_point intp, t_shape *shape);


/********** calc_reflection **********/
t_colorf	calc_ambient_reflection(t_colorf ka, t_colorf Ia);
t_colorf calc_diffuse_reflection(const t_scene *scene, t_intersection_point intp, t_ray eye_ray, t_shape *shape);
t_colorf	calc_perfect_reflection(
		const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level,
		t_intersection_point intp, t_shape *shape);

t_colorf	calc_inflection_refraction(
		const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level,
		t_intersection_point intp, t_shape *shape);

t_colorf calc_specular_reflection(const t_scene *scene, const t_ray *eye_ray,
								  t_intersection_point intp, t_shape *shape);


t_vector	get_dir_pos2light(t_light light, t_vector pos);
int is_obj_exists_between_light_and_eye(const t_scene *scene, t_vector dir_pos2light, t_light *light, t_intersection_point intp);

/********** raytrace **********/
int	recursive_raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col, int recursion_level);
int	raytrace(const t_scene *scene, const t_ray *eye_ray, t_colorf *out_col);



/********** init **********/
//void		scene_setting(t_scene *scene);
//void		init_shape(t_shape *shape, t_shape_type st, ...);
//void		init_material(t_material *mat,
//				   float ambR, float ambG, float ambB,
//				   float difR, float difG, float difB,
//				   float speR, float speG, float speB,
//				   float shns,
//				   t_material_type type,
//				   float refR, float refG, float refB,
//				   float refraction_index,
//				   char *texture_path, char *bump_path, bool is_checker);
//
//void init_light(t_light *light, t_light_type lt,
//				float px, float py, float pz,
//				float dirx, float diry, float dirz,
//				float illR, float illG, float illB,
//				float angle);



/********** get_input **********/
int get_and_validate_scene_config(t_scene *scene, t_camera *camera, const char *path);


/********** setting **********/
int get_setting_for_camera(const char *line, t_camera *camera);

int	get_and_validate_setting_for_ambient(const char *line, t_scene *scene);

int get_setting_for_lights(const char *line, t_scene *scene, t_identifier id);

int get_setting_for_objects(const char *line, t_scene *scene, t_identifier id);

/********** parsing_config **********/
char	*get_identifier(const char *line, size_t *idx);
double	ft_strtod(const char *str, bool *is_success, char **err);

int		parsing_int_num(const char *line, float *int_num, size_t *idx);
int		parsing_double_num(const char *line, float *double_num, size_t *idx);

int 	parsing_vec(const char *line, t_vector *vec, size_t *idx);
int 	parsing_color(const char *line, t_colorf *color, size_t *idx);

int 	is_color_in_range(t_colorf color);
int 	is_vec_in_normal_range(t_vector vec);
void	skip_delimiter(const char *line, size_t *idx);
void	skip_spece(const char *line, size_t *idx);


char	*get_identifier_str(const char *line, size_t idx);
void	increment_idx_to_next_format(const char *line, size_t *idx, char *prev_str);
int		increment_idx_to_next_char(const char *line, size_t *idx);



/********** main **********/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif //MINIRT_H
