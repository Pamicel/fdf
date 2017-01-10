#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

static void print_mat4(t_mat4 mat)
{
  for (int a = 0; a < 4; a++)
  {
    for (int i = a; i < 16; i += 4)
      printf("%lf\t", mat[i]);
    printf("\n\n");
  }
}

int main(void)
{
  t_mat4 mat1;
  t_mat4 mat2;
  t_mat4 result;

  ft_matrix_identity(mat1);
  print_mat4(mat1);
  printf("\n");
  for (int i = 0; i < 16; i++)
    mat1[i] = (double)(rand() % 100);
  print_mat4(mat1);
  printf("\n");
  for (int i = 0; i < 16; i++)
    mat2[i] = (double)(rand() % 100);
  print_mat4(mat2);
  printf("\n");
  ft_matrix_mult(mat1, mat2, result);
  print_mat4(result);
  printf("\n");
  ft_matrix_rot_z(20 , result);
  print_mat4(result);
  printf("\n");

}
