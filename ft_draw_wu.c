/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamicel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 12:23:02 by pamicel           #+#    #+#             */
/*   Updated: 2017/01/10 14:32:38 by pamicel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wu.h"
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
/*
** Thank you M. Michael Abrash for being such a god
*/

void				ft_plot(t_params *params, int alpha_inc, void *mlx, void *win)
{
	int             color;

	color = (params->env->color & params->pt1->color) + (alpha_inc << 24) + (params->env->alpha << 24);
	mlx_pixel_put(mlx, win, params->pt1->x, params->pt1->y, color);
}

static void			ft_ymajor_line(t_params *params, void *mlx, void *win)
{
	unsigned int	error_adj;
	unsigned int	error_acc;
	unsigned int	weighting;
	unsigned int	weighting_complement_mask;
	unsigned int	intensity_shift;

	error_acc = 0;
	intensity_shift = 16 - params->env->intensity_bits;
	weighting_complement_mask = params->env->n_levels - 1;
	error_adj = ((unsigned long) params->env->dx << 16) / (unsigned long) params->env->dy;
	while (--params->env->dy)
	{
		if (((error_acc + error_adj) ^ 0xFFFF0000) <= (error_acc ^ 0xFFFF0000))
			params->pt1->x += params->env->xdir;
		error_acc += error_adj;
		params->pt1->y++;
		weighting = error_acc >> intensity_shift;
		ft_plot(params, weighting, mlx, win);
		params->pt1->x += params->env->xdir;
		ft_plot(params, (weighting ^ weighting_complement_mask), mlx, win);
		params->pt1->x -= params->env->xdir;
	}
}

static void			ft_xmajor_line(t_params *params, void *mlx, void *win)
{
	unsigned int	error_adj;
	unsigned int	error_acc;
	unsigned int	weighting;
	unsigned int	weighting_complement_mask;
	unsigned int	intensity_shift;

	error_acc = 0;
	intensity_shift = 16 - params->env->intensity_bits;
	weighting_complement_mask = params->env->n_levels - 1;
	error_adj = ((unsigned long) params->env->dy << 16) / (unsigned long) params->env->dx;
	while (--params->env->dx)
	{
		if (((error_acc + error_adj) ^ 0xFFFF0000) <= (error_acc ^ 0xFFFF0000))
			params->pt1->y++;
		error_acc += error_adj;
		params->pt1->x += params->env->xdir;
		weighting = error_acc >> intensity_shift;
		ft_plot(params, weighting, mlx, win);
		params->pt1->y++;
		ft_plot(params, (weighting ^ weighting_complement_mask), mlx, win);
		params->pt1->y--;
	}
}

void				ft_draw_wu(t_params *params, void *mlx, void *win)
{
	t_point			*temp;

	if (params->pt1->y > params->pt2->y)
	{
		temp = params->pt1;
		params->pt1 = params->pt2;
		params->pt2 = temp;
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
