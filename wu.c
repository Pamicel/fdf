#include "wu.h"

// // // // // //
#include <stdio.h>
#include <stdlib.h>
// // // // // //

void                    ft_set_env(t_data *env)
{
    env->intensity_bits = 8;
    env->n_levels = 256;
    env->color = 0xFFFFFF;
    env->alpha = 0;
    env->dx = 0;
    env->dy = 0;
    env->xdir = 1;
}

int                     ft_mouse_hook(int button, int x, int y, void *p)
{
    t_params            *params;
    t_point             *pt1;
    t_point             *pt2;

    params = (t_params*)p;
    pt1 = params->pt1;
    pt2 = params->pt2;
    if (button == 1)
    {
        if ((x <= (pt2->x + 3) || x >= (pt2->x - 3)) &&\
         (y <= (pt2->y + 3) || y >= (pt2->y - 3)))
        {
            pt2->x = x;
            pt2->y = y;
        }
        else if ((x <= (pt1->x + 3) || x >= (pt1->x - 3)) &&\
         (y <= (pt1->y + 3) || y >= (pt1->y - 3)))
        {
            pt1->x = x;
            pt1->y = y;
        }
        ft_draw_wu(params, params->env->mlx, params->env->win);
        return (1);
    }
    return (0);
}

int                     ft_hook(void *p)
{
    t_params            *params;
    int                 i;
    void *mlx;
    void *win;

    while (1)
    {
        params = (t_params*)p;
        mlx = params->mlx;
        win = params->win;
        i = 1;
        ft_draw_wu(params, mlx, win);
    }
    return (i);
}

void                    ft_set_params(t_params *params, t_data *env,\
     t_point *pt1, t_point *pt2)
{
    params->pt1 = pt1;
    params->pt2 = pt2;
    params->env = env;
}

int                     main(void)
{
    t_point             *pt1;
    t_point             *pt2;
    t_data              *env;
    t_params            *params;
    void                *mlx;
    void                *win;

    pt1 = (t_point*)ft_memalloc(sizeof(t_point));
    pt2 = (t_point*)ft_memalloc(sizeof(t_point));
    env = (t_data*)ft_memalloc(sizeof(t_data));
    params = (t_params*)ft_memalloc(sizeof(t_params));
    mlx = mlx_init();
    win = mlx_new_window(mlx, 400, 400, "hello Wu");
    params->mlx = mlx;
    params->win = win;

    // pt1->x = 300;
    // pt1->y = 200;
    // pt2->x = 100;
    // pt2->y = 100;
    // ft_set_env(env);
    // ft_set_params(params, env, pt1, pt2);
    // ft_draw_wu(params, mlx, win);
    //
    // pt1->x = 30;
    // pt1->y = 150;
    // pt2->x = 10;
    // pt2->y = 10;
    // ft_set_env(env);
    // ft_set_params(params, env, pt1, pt2);
    // ft_draw_wu(params, mlx, win);

    pt1->x = 0;
    pt1->y = 0;
    pt1->color = 0xFF0000;
    pt2->x = 400;
    pt2->y = 350;
    pt2->color = 0x00FF00;
    ft_set_env(env);
    ft_set_params(params, env, pt1, pt2);
    ft_draw_wu(params, mlx, win);

    pt1->x = 300;
    pt1->y = 0;
    pt2->x = 0;
    pt2->y = 400;
    ft_set_env(env);
    ft_set_params(params, env, pt1, pt2);
    ft_draw_wu(params, mlx, win);

    // mlx_mouse_hook(mlx, &ft_mouse_hook, params);
    // mlx_loop_hook(mlx, ft_hook, params);
    mlx_loop(mlx);
    return (0);
}
