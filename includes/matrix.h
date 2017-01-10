#ifndef MATRIX_H
# define MATRIX_H
# include <math.h>
# define D_PI_180        0.017453
# define D_180_PI        57.295780
# define DEG_TO_RAD(x)   (x * D_PI_180)
# define RAD_TO_DEG(x)   (x * D_180_PI)

typedef double t_mat4[16];

void ft_matrix_identity(t_mat4 m);
void ft_matrix_trans(double x, double y, double z, t_mat4 matrix);
void ft_matrix_scale(double sx, double sy, double sz, t_mat4 matrix);
void ft_matrix_mult(t_mat4 m1, t_mat4 m2, t_mat4 result);
void ft_matrix_rot_x(double degrees, t_mat4 matrix);
void ft_matrix_rot_y(double degrees, t_mat4 matrix);
void ft_matrix_rot_z(double degrees, t_mat4 matrix);

#endif
