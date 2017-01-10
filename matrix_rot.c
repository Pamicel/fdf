#include "matrix.h"

void ft_matrix_rot_x(double degrees, t_mat4 matrix)
{
    double radians;

    radians = DEG_TO_RAD(degrees);
    ft_matrix_identity(matrix);
    matrix[5] = cosf(radians);
    matrix[6] = -sinf(radians);
    matrix[9] = -matrix[6];
    matrix[10] = matrix[5];
}

void ft_matrix_rot_y(double degrees, t_mat4 matrix)
{
    double radians;

    radians = DEG_TO_RAD(degrees);
    ft_matrix_identity(matrix);
    matrix[0] = cosf(radians);
    matrix[2] = sinf(radians);
    matrix[8] = -matrix[2];
    matrix[10] = matrix[0];
}

void ft_matrix_rot_z(double degrees, t_mat4 matrix)
{
    double radians;

    radians = DEG_TO_RAD(degrees);
    ft_matrix_identity(matrix);
    matrix[0] = cosf(radians);
    matrix[1] = sinf(radians);
    matrix[4] = -matrix[1];
    matrix[5] = matrix[0];
}
