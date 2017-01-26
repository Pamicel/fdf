/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamicel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:34:59 by pamicel           #+#    #+#             */
/*   Updated: 2017/01/10 14:40:48 by pamicel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wu.h"

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
