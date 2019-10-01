#pragma once

// #define SK_32BIT_INDICES
// #define SK_NO_FLATSCREEN

#if defined(_DLL)
#define SK_API extern "C" __declspec(dllexport)
#define SK_API_S __declspec(dllexport)
#else
#define SK_API extern "C" __declspec(dllimport)
#define SK_API_S __declspec(dllimport)
#endif

#define SK_DeclarePrivateType(name) struct _ ## name; typedef struct _ ## name *name;
#define SK_MakeFlag(enumType) \
inline enumType  operator| (enumType  a, enumType b) {return static_cast<enumType>(static_cast<int>(a) | static_cast<int>(b));} \
inline enumType &operator|=(enumType& a, const enumType& b) { a = a | b; return a; } \
inline enumType  operator& (enumType  a, enumType b) {return static_cast<enumType>(static_cast<int>(a) & static_cast<int>(b));} \
inline enumType &operator&=(enumType& a, const enumType& b) { a = a & b; return a; } \
inline enumType  operator~ (const enumType& a) { return static_cast<enumType>(~static_cast<int>(a)); }

#include <stdint.h>
#include <math.h>

typedef int32_t bool32_t;

///////////////////////////////////////////

enum sk_runtime_ {
	sk_runtime_flatscreen   = 0,
	sk_runtime_mixedreality = 1
};

struct sk_settings_t {
	int32_t flatscreen_pos_x;
	int32_t flatscreen_pos_y;
	int32_t flatscreen_width;
	int32_t flatscreen_height;
};

SK_API bool32_t sk_init      (const char *app_name, sk_runtime_ preferred_runtime, bool32_t fallback = true);
SK_API void     sk_shutdown  ();
SK_API bool32_t sk_step      (void (*app_update)(void));

SK_API float       sk_timef();
SK_API double      sk_time();
SK_API float       sk_time_elapsedf();
SK_API double      sk_time_elapsed();
SK_API sk_runtime_ sk_active_runtime();
SK_API void        sk_set_settings(sk_settings_t &settings);

///////////////////////////////////////////

struct color32 {
	uint8_t r, g, b, a;
};
struct color128 {
	float r, g, b, a;
};
struct vec2 {
	float x, y;
};
struct vec3 {
	float x, y, z;
};
struct vec4 {
	float x, y, z, w;
};
struct rect {
	float x, y, w, h;
};
struct quat {
	float i, j, k, a;
};
struct matrix {
	vec4 row[4];
};
struct ray_t {
	vec3 pos;
	vec3 dir;
};
struct pose_t {
	vec3 position;
	quat orientation;
};

static inline vec2  operator*(const vec2 &a, const float b) { return { a.x * b, a.y * b }; }
static inline vec2  operator/(const vec2 &a, const float b) { return { a.x / b, a.y / b }; }
static inline vec2  operator+(const vec2 &a, const vec2 &b) { return { a.x + b.x, a.y + b.y }; }
static inline vec2  operator-(const vec2 &a, const vec2 &b) { return { a.x - b.x, a.y - b.y }; }
static inline vec2  operator*(const vec2 &a, const vec2 &b) { return { a.x * b.x, a.y * b.y }; }
static inline vec2  operator/(const vec2 &a, const vec2 &b) { return { a.x / b.x, a.y / b.y }; }
static inline vec2& operator+=(vec2& a, const vec2& b)     { a.x += b.x; a.y += b.y; return a; }
static inline vec2& operator-=(vec2& a, const vec2& b)     { a.x -= b.x; a.y -= b.y; return a; }
static inline vec2& operator*=(vec2& a, const float b)     { a.x *= b; a.y *= b; return a; }
static inline vec2& operator/=(vec2& a, const float b)     { a.x /= b; a.y /= b; return a; }

static inline vec3  operator*(const vec3 &a, const float b) { return { a.x * b, a.y * b, a.z * b }; }
static inline vec3  operator/(const vec3 &a, const float b) { return { a.x / b, a.y / b, a.z / b }; }
static inline vec3  operator+(const vec3 &a, const vec3 &b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
static inline vec3  operator-(const vec3 &a, const vec3 &b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
static inline vec3  operator-(const vec3 &a)                { return { -a.x, -a.y, -a.z }; }
static inline vec3  operator*(const vec3 &a, const vec3 &b) { return { a.x * b.x, a.y * b.y, a.z * b.z }; }
static inline vec3  operator/(const vec3 &a, const vec3 &b) { return { a.x / b.x, a.y / b.y, a.z / b.z }; }
static inline vec3& operator+=(vec3& a, const vec3& b)     { a.x += b.x; a.y += b.y; a.z += b.z; return a; }
static inline vec3& operator-=(vec3& a, const vec3& b)     { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; }
static inline vec3& operator*=(vec3& a, const float b)     { a.x *= b; a.y *= b; a.z *= b; return a; }
static inline vec3& operator/=(vec3& a, const float b)     { a.x /= b; a.y /= b; a.z /= b; return a; }

static inline float vec3_magnitude_sq(const vec3 &a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
static inline float vec3_magnitude   (const vec3 &a) { return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z); }
static inline vec3  vec3_normalize   (const vec3 &a) { return a / vec3_magnitude(a); }
static inline vec3  vec3_lerp        (const vec3 &a, const vec3 &b, float t) { return a + (b - a)*t; }
static inline float vec3_dot         (const vec3 &a, const vec3 &b) { return a.x*b.x + a.y*b.y + a.z*b.z; }

static inline vec2  vec2_lerp        (const vec2 &a, const vec2 &b, float t) { return a + (b - a)*t; }

SK_API quat quat_difference(const quat &a, const quat &b);
SK_API quat quat_lookat    (const vec3 &from, const vec3 &at);
SK_API quat quat_euler     (const vec3 &euler_degrees);
SK_API quat quat_lerp      (const quat &a, const quat &b, float t);
SK_API quat quat_normalize (const quat &a);
SK_API quat quat_mul       (const quat &a, const quat &b);
SK_API vec3 quat_mul_vec   (const quat &a, const vec3 &b);

SK_API matrix pose_matrix    (const pose_t &pose);
SK_API void   pose_matrix_out(const pose_t &pose, matrix &out_result);

SK_API void   matrix_inverse      (const matrix &a, matrix &out_matrix);
SK_API void   matrix_mul          (const matrix &a, const matrix &b, matrix &out_matrix);
SK_API vec3   matrix_mul_point    (const matrix &transform, const vec3 &point);
SK_API vec3   matrix_mul_direction(const matrix &transform, const vec3 &direction);
SK_API matrix matrix_trs          (const vec3 &position, const quat &orientation = quat{0,0,0,1}, const vec3 &scale = vec3{1,1,1});
SK_API void   matrix_trs_out      (matrix &out_result, const vec3 &position, const quat &orientation = quat{0,0,0,1}, const vec3 &scale = vec3{1,1,1});

SK_API bool32_t ray_intersect_plane(ray_t ray, vec3 plane_pt, vec3 plane_normal, float &out_t);

static inline vec3   operator*(const quat   &a, const vec3   &b) { return quat_mul_vec(a, b); }
static inline quat   operator*(const quat   &a, const quat   &b) { return quat_mul(a, b); }
static inline matrix operator*(const matrix &a, const matrix &b) { matrix result; matrix_mul(a, b, result); return result; }

static const float deg2rad = 0.01745329252f;
static const float rad2deg = 57.295779513f;
static const float cm2m = 0.01f;
static const float mm2m = 0.001f;
static const float m2cm = 100.f;
static const float m2mm = 1000.f;

static const vec3 vec3_one      = vec3{ 1,1, 1 };
static const vec3 vec3_zero     = vec3{ 0,0, 0 };
static const vec3 vec3_up       = vec3{ 0,1, 0 };
static const vec3 vec3_forward  = vec3{ 0,0,-1 };
static const vec3 vec3_right    = vec3{ 1,0, 0 };
static const quat quat_identity = quat{ 0,0, 0,1 };
static const matrix matrix_identity = matrix{ vec4{1,0,0,0}, vec4{0,1,0,0}, vec4{0,0,1,0}, vec4{0,0,0,1} };

#define unit_cm(cm) ((cm)*0.01f)
#define unit_mm(mm) ((mm)*0.001f)
#define unit_dmm(dmm, distance) ((dmm)*(distance))

///////////////////////////////////////////

struct vert_t {
	vec3    pos;
	vec3    norm;
	vec2    uv;
	color32 col;
};

#ifdef SK_32BIT_INDICES
typedef uint32_t vind_t;
#else
typedef uint16_t vind_t;
#endif

SK_DeclarePrivateType(mesh_t);

SK_API mesh_t mesh_find         (const char *id);
SK_API mesh_t mesh_create       (const char *id);
SK_API void   mesh_release      (mesh_t mesh);
SK_API void   mesh_set_verts    (mesh_t mesh, vert_t *vertices, int32_t vertex_count);
SK_API void   mesh_set_inds     (mesh_t mesh, vind_t *indices,  int32_t index_count);
SK_API void   mesh_set_draw_inds(mesh_t mesh, int32_t index_count);

SK_API mesh_t mesh_gen_cube        (const char *id, vec3 dimensions, int32_t subdivisions = 0);
SK_API mesh_t mesh_gen_sphere      (const char *id, float diameter,  int32_t subdivisions = 4);
SK_API mesh_t mesh_gen_rounded_cube(const char *id, vec3 dimensions, float edge_radius, int32_t subdivisions);

///////////////////////////////////////////

enum tex_type_ {
	tex_type_image_nomips  = 1 << 0,
	tex_type_cubemap       = 1 << 1,
	tex_type_rendertarget  = 1 << 2,
	tex_type_depth         = 1 << 3,
	tex_type_mips          = 1 << 4,
	tex_type_dynamic       = 1 << 5,
	tex_type_image         = tex_type_image_nomips | tex_type_mips,
};
SK_MakeFlag(tex_type_);

enum tex_format_ {
	tex_format_rgba32 = 0,
	tex_format_rgba64,
	tex_format_rgba128,
	tex_format_depthstencil,
	tex_format_depth32,
	tex_format_depth16,
};

enum tex_sample_ {
	tex_sample_linear = 0,
	tex_sample_point,
	tex_sample_anisotropic
};

enum tex_address_ {
	tex_address_wrap = 0,
	tex_address_clamp,
	tex_address_mirror,
};

SK_DeclarePrivateType(tex2d_t);

SK_API tex2d_t tex2d_find       (const char *id);
SK_API tex2d_t tex2d_create     (const char *id,   tex_type_ type = tex_type_image, tex_format_ format = tex_format_rgba32);
SK_API tex2d_t tex2d_create_file(const char *file);
SK_API tex2d_t tex2d_create_cubemap_file (const char *equirectangular_file);
SK_API tex2d_t tex2d_create_cubemap_files(const char **cube_face_file_xxyyzz);
SK_API void    tex2d_release    (tex2d_t texture);
SK_API void    tex2d_set_colors (tex2d_t texture, int32_t width, int32_t height, void *data);
SK_API void    tex2d_set_options(tex2d_t texture, tex_sample_ sample = tex_sample_linear, tex_address_ address_mode = tex_address_wrap, int32_t anisotropy_level = 4);
SK_API void    tex2d_add_zbuffer(tex2d_t texture, tex_format_ format = tex_format_depthstencil);
SK_API void    tex2d_rtarget_clear     (tex2d_t render_target, color32 color);
SK_API void    tex2d_rtarget_set_active(tex2d_t render_target);
SK_API void    tex2d_get_data   (tex2d_t texture, void *out_data, size_t out_data_size);

///////////////////////////////////////////

SK_DeclarePrivateType(font_t);

SK_API font_t  font_find   (const char *id);
SK_API font_t  font_create (const char *file);
SK_API void    font_release(font_t font);
SK_API tex2d_t font_get_tex(font_t font);

///////////////////////////////////////////

SK_DeclarePrivateType(shader_t);

SK_API shader_t shader_find        (const char *id);
SK_API shader_t shader_create      (const char *id, const char *hlsl);
SK_API shader_t shader_create_file (const char *filename);
SK_API bool32_t shader_set_code    (shader_t shader, const char *hlsl);
SK_API bool32_t shader_set_codefile(shader_t shader, const char *filename);
SK_API void     shader_release     (shader_t shader);

///////////////////////////////////////////

enum material_alpha_ {
	material_alpha_none = 1,
	material_alpha_blend,
	material_alpha_test,
};
enum material_cull_ {
	material_cull_ccw = 0,
	material_cull_cw,
	material_cull_none,
};
enum material_param_ {
	material_param_float = 0,
	material_param_color128,
	material_param_vector,
	material_param_matrix,
	material_param_texture,
};

SK_DeclarePrivateType(material_t);

SK_API material_t material_find            (const char *id);
SK_API material_t material_create          (const char *id, shader_t shader);
SK_API material_t material_copy            (const char *id, material_t material);
SK_API void       material_release         (material_t material);
SK_API void       material_set_alpha_mode  (material_t material, material_alpha_ mode);
SK_API void       material_set_cull        (material_t material, material_cull_ mode);
SK_API void       material_set_queue_offset(material_t material, int32_t offset);
SK_API void       material_set_float       (material_t material, const char *name, float    value);
SK_API void       material_set_color       (material_t material, const char *name, color128 value);
SK_API void       material_set_vector      (material_t material, const char *name, vec4     value);
SK_API void       material_set_matrix      (material_t material, const char *name, matrix   value);
SK_API bool32_t   material_set_texture     (material_t material, const char *name, tex2d_t  value);
SK_API bool32_t   material_set_texture_id  (material_t material, uint64_t    id,   tex2d_t  value);
SK_API void       material_set_param       (material_t material, const char *name, material_param_ type, const void *value);
SK_API void       material_set_param_id    (material_t material, uint64_t    id,   material_param_ type, const void *value);
SK_API bool32_t   material_get_param       (material_t material, const char *name, material_param_ type, void *out_value);
SK_API bool32_t   material_get_param_id    (material_t material, uint64_t    id,   material_param_ type, void *out_value);
SK_API void       material_get_param_info  (material_t material, int index, char **out_name, material_param_ *out_type);
SK_API int        material_get_param_count (material_t material);
SK_API void       material_set_shader      (material_t material, shader_t shader);
SK_API shader_t   material_get_shader      (material_t material);

///////////////////////////////////////////

struct transform_t {
	vec3 _position;
	vec3 _scale;
	quat _rotation;

	bool32_t _dirty;
	matrix   _transform;
};

SK_API void transform_initialize  (transform_t &transform);
SK_API void transform_set         (transform_t &transform, const vec3 &position, const vec3 &scale, const quat &rotation );
SK_API void transform_set_position(transform_t &transform, const vec3 &position);
SK_API vec3 transform_get_position(transform_t &transform);
SK_API void transform_set_scale   (transform_t &transform, const vec3 &scale);
SK_API vec3 transform_get_scale   (transform_t &transform);
SK_API void transform_set_rotation(transform_t &transform, const quat &rotation);
SK_API quat transform_get_rotation(transform_t &transform);
SK_API void transform_lookat      (transform_t &transform, const vec3 &at);
SK_API vec3 transform_forward     (transform_t &transform);

SK_API void   transform_update    (transform_t &transform);
SK_API void   transform_matrix_out(transform_t &transform, matrix &result);
SK_API matrix transform_matrix    (transform_t &transform);
SK_API vec3   transform_world_to_local    (transform_t &transform, const vec3 &world_coordinate);
SK_API vec3   transform_local_to_world    (transform_t &transform, const vec3 &local_coordinate);
SK_API vec3   transform_world_to_local_dir(transform_t &transform, const vec3 &world_direction);
SK_API vec3   transform_local_to_world_dir(transform_t &transform, const vec3 &local_direction);

///////////////////////////////////////////

enum text_align_ {
	text_align_x_left      = 0,
	text_align_y_top       = 0,
	text_align_x_center    = 1 << 1,
	text_align_y_center    = 1 << 2,
	text_align_x_right     = 1 << 3,
	text_align_y_bottom    = 1 << 4,
};
SK_MakeFlag(text_align_);

typedef int32_t text_style_t;

SK_API text_style_t text_make_style(font_t font, float character_height, material_t material, text_align_ align);
SK_API void         text_add_at    (text_style_t style, const matrix &transform, const char *text, text_align_ position = text_align_x_center | text_align_y_center, float off_x = 0, float off_y = 0, float off_z = 0);
SK_API vec2         text_size      (text_style_t style, const char *text);

///////////////////////////////////////////

enum solid_type_ {
	solid_type_normal = 0,
	solid_type_immovable,
	solid_type_unaffected,
};

typedef void* solid_t;

SK_API solid_t solid_create       (const vec3 &position, const quat &rotation, solid_type_ type = solid_type_normal);
SK_API void    solid_release      (solid_t solid);
SK_API void    solid_add_sphere   (solid_t solid, float diameter = 1,           float kilograms = 1, const vec3 *offset = nullptr);
SK_API void    solid_add_box      (solid_t solid, const vec3 &dimensions,       float kilograms = 1, const vec3 *offset = nullptr);
SK_API void    solid_add_capsule  (solid_t solid, float diameter, float height, float kilograms = 1, const vec3 *offset = nullptr);
SK_API void    solid_set_type     (solid_t solid, solid_type_ type);
SK_API void    solid_set_enabled  (solid_t solid, bool32_t enabled);
SK_API void    solid_move         (solid_t solid, const vec3 &position, const quat &rotation);
SK_API void    solid_teleport     (solid_t solid, const vec3 &position, const quat &rotation);
SK_API void    solid_set_velocity    (solid_t solid, const vec3 &meters_per_second);
SK_API void    solid_set_velocity_ang(solid_t solid, const vec3 &radians_per_second);
SK_API void    solid_get_transform(const solid_t solid, transform_t &out_transform);

///////////////////////////////////////////

SK_DeclarePrivateType(model_t);

SK_API model_t    model_find        (const char *id);
SK_API model_t    model_create_mesh (const char *id, mesh_t mesh, material_t material);
SK_API model_t    model_create_file (const char *filename);
SK_API material_t model_get_material(model_t model, int32_t subset);
SK_API int32_t    model_subset_count(model_t model);
SK_API void       model_release     (model_t model);

///////////////////////////////////////////

SK_DeclarePrivateType(sprite_t);

enum sprite_type_ {
	sprite_type_atlased = 0,
	sprite_type_single
};

SK_API sprite_t sprite_create     (tex2d_t     sprite,   sprite_type_ type = sprite_type_atlased, const char *atlas_id = "default");
SK_API sprite_t sprite_create_file(const char *filename, sprite_type_ type = sprite_type_atlased, const char *atlas_id = "default");
SK_API void     sprite_release    (sprite_t sprite);
SK_API float    sprite_get_aspect (sprite_t sprite);
SK_API void     sprite_draw       (sprite_t sprite, const matrix &transform, color32 color = {255,255,255,255});

///////////////////////////////////////////

struct camera_t {
	float fov;
	float clip_near;
	float clip_far;
};

SK_API void camera_initialize(camera_t &cam, float fov, float clip_near, float clip_far);
SK_API void camera_view      (transform_t &cam_transform, matrix &result);
SK_API void camera_proj      (camera_t    &cam,           matrix &result);

///////////////////////////////////////////

SK_API void render_set_camera  (camera_t &cam);
SK_API void render_set_view    (transform_t &cam_transform);
SK_API void render_set_light   (const vec3 &direction, float intensity, const color128 &color);
SK_API void render_set_skytex  (tex2d_t sky_texture, bool32_t show_sky);
SK_API void render_add_mesh    (mesh_t mesh, material_t material, const matrix &transform);
SK_API void render_add_mesh_tr (mesh_t mesh, material_t material, transform_t &transform);
SK_API void render_add_model   (model_t model, const matrix &transform);
SK_API void render_add_model_tr(model_t model, transform_t &transform);
SK_API void render_blit        (tex2d_t to_rendertarget, material_t material);
SK_API void render_get_device  (void **device, void **context);

///////////////////////////////////////////

enum input_source_ {
	input_source_any        = 0x7FFFFFFF,
	input_source_hand       = 1 << 0,
	input_source_hand_left  = 1 << 1,
	input_source_hand_right = 1 << 2,
	input_source_gaze       = 1 << 4,
	input_source_gaze_head  = 1 << 5,
	input_source_gaze_eyes  = 1 << 6,
	input_source_gaze_cursor= 1 << 7,
	input_source_can_press  = 1 << 8,
};
SK_MakeFlag(input_source_);

enum pointer_state_ {
	pointer_state_none      = 0,
	pointer_state_available = 1 << 0,
};
SK_MakeFlag(pointer_state_);

enum handed_ {
	handed_left  = 0,
	handed_right = 1,
	handed_max   = 2,
};

enum input_state_ {
	input_state_none        = 0,
	input_state_any         = 0x7FFFFFFF,
	input_state_tracked     = 1 << 0,
	input_state_justtracked = 1 << 1,
	input_state_untracked   = 1 << 2,
	input_state_pinch       = 1 << 3,
	input_state_justpinch   = 1 << 4,
	input_state_unpinch     = 1 << 5,
	input_state_grip        = 1 << 6,
	input_state_justgrip    = 1 << 7,
	input_state_ungrip      = 1 << 8,
};
SK_MakeFlag(input_state_);

struct pointer_t {
	input_source_  source;
	pointer_state_ state;
	ray_t          ray;
	quat           orientation;
};

struct hand_t {
	pose_t  fingers[5][5];
	pose_t  wrist;
	pose_t  root;
	handed_ handedness;
	input_state_ state;
};

SK_API int           input_pointer_count(input_source_ filter = input_source_any);
SK_API pointer_t     input_pointer      (int32_t index, input_source_ filter = input_source_any);
SK_API const hand_t &input_hand         (handed_ hand);
SK_API void          input_hand_visible (handed_ hand, bool32_t visible);
SK_API void          input_hand_solid   (handed_ hand, bool32_t solid);
SK_API void          input_hand_material(handed_ hand, material_t material);

SK_API void input_subscribe  (input_source_ source, input_state_ event, void (*event_callback)(input_source_ source, input_state_ event, const pointer_t &pointer));
SK_API void input_unsubscribe(input_source_ source, input_state_ event, void (*event_callback)(input_source_ source, input_state_ event, const pointer_t &pointer));
SK_API void input_fire_event (input_source_ source, input_state_ event, const pointer_t &pointer);

///////////////////////////////////////////

enum log_{
	log_info = 0,
	log_warning,
	log_error
};
enum log_colors_ {
	log_colors_ansi = 0,
	log_colors_none
};

SK_API void log_write     (log_ level, const char *text);
SK_API void log_writef    (log_ level, const char *text, ...);
SK_API void log_set_filter(log_ level);
SK_API void log_set_colors(log_colors_ colors);