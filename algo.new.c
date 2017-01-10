#include "wu.h"
#include <stdio.h>


/* Data needed for Wu antialiased line drawer.
**  mlx, win = pointers specific to minilibx
**  dx, dy, xdir = deltaX, deltaY and direction of X
**               = data necessary for ploting
**  color = color # of first color in block used for antialiasing, the
**          100% intensity version of the drawing color
**  n_levels = size of color block, with BaseColor+NumLevels-1 being the
**          0% intensity version of the drawing color
**  intensity_bits = log base 2 of NumLevels; the # of bits used to describe
**          the intensity of the drawing color. 2**IntensityBits==NumLevels
*/

// ///////////////////////////////////////////////////////////////////////////////
// // wu.h
//
// typedef struct      s_data
// {
//     void            *mlx;
//     void            *win;
//     int             color;
//     unsigned int    intensity_bits;
//     unsigned int    n_levels;
//     int             dx;
//     int             dy;
//     int             xdir;
// }                   t_data;
//
// typedef struct      s_point
// {
//     int             x;
//     int             y;
//     int             z;
// }                   t_point;
//
// ///////////////////////////////////////////////////////////////////////////////

void         ft_plot(t_params *params, int alpha_inc, void *mlx, void *win)
{
    int color;

    color = params->env->color + (alpha_inc << 24) + (params->env->alpha << 24);
    // printf("params->env->color = %X\n", params->env->color);
    // printf("(alpha_inc << 24) = %X\n", (alpha_inc << 24));
    // printf("(params->env->alpha << 24) = %X\n", (params->env->alpha << 24));
    mlx_pixel_put(mlx, win, params->pt1->x, params->pt1->y, color);
}

///////////////////////////////////////////////////////////////////////////////
// simple_lines.c

static int          ft_horizontal_line(t_params *params, void *mlx, void *win)
{
    while (params->env->dx-- != 0)
    {
        params->pt1->x += params->env->xdir;
        ft_plot(params, 0, mlx, win);
    }
    return (1);
}

static int          ft_vertical_line(t_params *params, void *mlx, void *win)
{
    while (params->env->dy)
    {
        params->pt1->y++;
        ft_plot(params, 0, mlx, win);
        params->env->dy--;
    }
    return (1);
}

static int          ft_diagonal_line(t_params *params, void *mlx, void *win)
{
    while (params->env->dy)
    {
        params->pt1->x += params->env->xdir;
        params->pt1->y++;
        ft_plot(params, 0, mlx, win);
        params->env->dy--;
    }
    return (1);
}

int                 ft_special_lines(t_params *params, void *mlx, void *win)
{
    params->env->xdir = 1;
    if ((params->env->dx = params->pt2->x - params->pt1->x) < 0)
    {
        params->env->xdir = - params->env->xdir;
        params->env->dx = - params->env->dx;
    }
    if ((params->env->dy = params->pt2->y - params->pt1->y) == 0)
        return (ft_horizontal_line(params, mlx, win));
    if (params->env->dx == 0)
        return (ft_vertical_line(params, mlx, win));
    if (params->env->dx == params->env->dy)
        return (ft_diagonal_line(params, mlx, win));
    return (0);
}

///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////  DEBUG   //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// static char *bigger_mother_fucker(char *str, int n_digits)
// {
//     char *new;
//     int n = ft_strlen(str);
//     if (n < n_digits)
//     {
//         new = ft_strnew(n_digits);
//         ft_strcpy(&(new[n_digits - n]), str);
//         for (int i = 0; i < n_digits - n; i++)
//             new[i] = '0';
//         return (new);
//     }
//     return (str);
// }

// static void print(int num)
// {
//     printf("%s\n", bigger_mother_fucker(ft_itoa_base(num, 2), 32));
// }

////////////////////////////////////////////////////////////////////////////////
////////  DEBUG   //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

static void         ft_ymajor_line(t_params *params, void *mlx, void *win)
{
    unsigned int error_adj;
    unsigned int error_acc;
    unsigned int weighting;
    unsigned int weighting_complement_mask;
    unsigned int intensity_shift;

    error_acc = 0;
    intensity_shift = 16 - params->env->intensity_bits;
    weighting_complement_mask = params->env->n_levels - 1;
    error_adj = ((unsigned long) params->env->dx << 16) / (unsigned long) params->env->dy;
    printf("dx = %d, dy = %d\n", params->env->dx, params->env->dy);
    printf("error_adj = %d\n", error_adj);
    while (--params->env->dy)
    {
        if (((error_acc + error_adj) ^ 0xFFFF0000) <= (error_acc ^ 0xFFFF0000))
            params->pt1->x += params->env->xdir;
        error_acc += error_adj;
        //print(error_acc);
        params->pt1->y++;
        weighting = error_acc >> intensity_shift;
        ft_plot(params, weighting, mlx, win);
        params->pt1->x += params->env->xdir;
        ft_plot(params, (weighting ^ weighting_complement_mask), mlx, win);
        params->pt1->x -= params->env->xdir;
    }
}

static void         ft_xmajor_line(t_params *params, void *mlx, void *win)
{
    unsigned int error_adj;
    unsigned int error_acc;
    unsigned int weighting;
    unsigned int weighting_complement_mask;
    unsigned int intensity_shift;

    error_acc = 0;
    intensity_shift = 16 - params->env->intensity_bits;
    weighting_complement_mask = params->env->n_levels - 1;
    error_adj = ((unsigned long) params->env->dy << 16) / (unsigned long) params->env->dx;
    printf("dx = %d, dy = %d\n", params->env->dx, params->env->dy);
    printf("error_adj = %d\n", error_adj);
    while (--params->env->dx)
    {
        if (((error_acc + error_adj) ^ 0xFFFF0000) <= (error_acc ^ 0xFFFF0000))
            params->pt1->y++;
        error_acc += error_adj;
        //print(error_acc);
        params->pt1->x += params->env->xdir;
        weighting = error_acc >> intensity_shift;
        ft_plot(params, weighting, mlx, win);
        params->pt1->y++;
        ft_plot(params, (weighting ^ weighting_complement_mask), mlx, win);
        params->pt1->y--;
    }
}

void                ft_draw_wu(t_params *params, void *mlx, void *win)
{
    int             temp;

    if (params->pt1->y > params->pt2->y)
    {
        temp = params->pt1->y;
        params->pt1->y = params->pt2->y;
        params->pt2->y = temp;
        temp = params->pt1->x;
        params->pt1->x = params->pt2->x;
        params->pt2->x = temp;
    }
    ft_plot(params, 0, mlx, win);
    if (ft_special_lines(params, mlx, win))
        return ;
    if (params->env->dx < params->env->dy)
    {
        ft_ymajor_line(params, mlx, win);
        params->pt1 = params->pt2;
        ft_plot(params, 0, mlx, win);
        return;
    }
    ft_xmajor_line(params, mlx, win);
    params->pt1 = params->pt2;
    ft_plot(params, 0, mlx, win);
}
