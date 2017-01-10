#include "matrix.h"

void ft_matrix_identity(t_mat4 m)
{
    m[0] = m[5] = m[10] = m[15] = 1.0;
    m[1] = m[2] = m[3] = m[4] = 0.0;
    m[6] = m[7] = m[8] = m[9] = 0.0;
    m[11] = m[12] = m[13] = m[14] = 0.0;
}

void ft_matrix_trans(double x, double y, double z, t_mat4 matrix)
{
    ft_matrix_identity(matrix);
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
}

void ft_matrix_scale(double sx, double sy, double sz, t_mat4 matrix)
{
    ft_matrix_identity(matrix);
    matrix[0] = sx;
    matrix[5] = sy;
    matrix[10] = sz;
}

void ft_matrix_mult(t_mat4 m1, t_mat4 m2, t_mat4 result)
{
  int i;

  i = 0;
  while (i < 16)
  {
    result[i + 0] =\
    m1[0] * m2[i] + m1[4] * m2[i + 1] + m1[8] * m2[i + 2] + m1[12] * m2[i + 3];
    result[i + 1] =\
    m1[1] * m2[i] + m1[5] * m2[i + 1] + m1[9] * m2[i + 2] + m1[13] * m2[i + 3];
    result[i + 2] =\
    m1[2] * m2[i] + m1[6] * m2[i + 1] + m1[10] * m2[i + 2] + m1[14] * m2[i + 3];
    result[i + 3] =\
    m1[3] * m2[i] + m1[7] * m2[i + 1] + m1[11] * m2[i + 2] + m1[15] * m2[i + 3];
    i += 4;
  }
}
