#ifndef WU_H
# define WU_H

#include "mlx.h"
#include "libft.h"

typedef struct      s_data
{
    int             alpha;
    int             color;
    unsigned int    intensity_bits;
    unsigned int    n_levels;
    int             dx;
    int             dy;
    int             xdir;
    void            *mlx;
    void            *win;
}                   t_data;

typedef struct      s_point
{
    int             x;
    int             y;
    int             z;
    int             color;
}                   t_point;

typedef struct      s_params
{
    t_point         *pt1;
    t_point         *pt2;
    t_data          *env;
    void            *mlx;
    void            *win;
}                   t_params;

void                ft_plot(t_params *params, int alpha_inc, void *mlx, void *win);
void                ft_draw_wu(t_params *params, void *mlx, void *win);
int                 ft_special_lines(t_params *params, void *mlx, void *win);
#endif
