/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_wu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamicel <pamicel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 12:23:02 by pamicel           #+#    #+#             */
/*   Updated: 2017/01/29 17:16:40 by pamicel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wu.h"

/* Data needed for Wu antialiased line drawer.
**  mlx, win = pointers specific to minilibx
**  dx, dy, xdir = deltaX, deltaY and direction of X
**               = data necessary for ploting, initialized and
**                 modified within the functions
**  color = color # of first color in block used for antialiasing, the
**          100% intensity version of the drawing color
**  n_levels = size of color block, with BaseColor+NumLevels-1 being the
**          0% intensity version of the drawing color
**  intensity_bits = log base 2 of NumLevels; the # of bits used to describe
**          the intensity of the drawing color.
**  (2 * pow(intensity_bits) == n_levels)
*/
/*
** Thanks to M. Michael Abrash for his intro to this
** algorithm, and for his awesomeness
*/

void				plot(t_params *params, int alpha_inc)
{
	int             color;

	color = (params->env.color & params->pt1.color) + (alpha_inc << 24) + (params->env.alpha << 24);
	mlx_pixel_put(params->env.mlx, params->env.win, params->pt1.x, params->pt1.y, color);
}

static void			ymajor_line(t_params *params)
{
	unsigned int	error_adj;
	unsigned int	error_acc;
	unsigned int	weighting;
	unsigned int	weighting_complement_mask;
	unsigned int	intensity_shift;

	error_acc = 0;
	intensity_shift = 16 - params->env.intensity_bits;
	weighting_complement_mask = params->env.n_levels - 1;
	error_adj = ((unsigned long) params->env.dx << 16) / (unsigned long) params->env.dy;
	while (--params->env.dy)
	{
		if (((error_acc + error_adj) & 0xFFFF) <= (error_acc & 0xFFFF))
			params->pt1.x += params->env.xdir;
		error_acc += error_adj;
		params->pt1.y++;
		weighting = error_acc >> intensity_shift;
		plot(params, weighting);
		params->pt1.x += params->env.xdir;
		plot(params, (weighting ^ weighting_complement_mask));
		params->pt1.x -= params->env.xdir;
	}
}

static void			xmajor_line(t_params *params)
{
	unsigned int	error_adj;
	unsigned int	error_acc;
	unsigned int	weighting;
	unsigned int	weighting_complement_mask;
	unsigned int	intensity_shift;

	error_acc = 0;
	intensity_shift = 16 - params->env.intensity_bits;
	weighting_complement_mask = params->env.n_levels - 1;
	error_adj = ((unsigned long) params->env.dy << 16) / (unsigned long) params->env.dx;
	while (--params->env.dx)
	{
		if (((error_acc + error_adj) & 0xFFFF) <= (error_acc & 0xFFFF))
			params->pt1.y++;
		error_acc += error_adj;
		params->pt1.x += params->env.xdir;
		weighting = error_acc >> intensity_shift;
		plot(params, weighting);
		params->pt1.y++;
		plot(params, (weighting ^ weighting_complement_mask));
		params->pt1.y--;
	}
}

void				draw_line_wu(t_params *params)
{
	t_point			temp;

	if (params->pt1.y > params->pt2.y)
	{
		ft_memcpy(&(temp), &(params->pt1), sizeof(t_point));
		ft_memcpy(&(params->pt1), &(params->pt2), sizeof(t_point));
		ft_memcpy(&(params->pt2), &(temp), sizeof(t_point));
	}
	plot(params, 0);
	if (special_lines(params))
		return ;
	if (params->env.dx < params->env.dy)
	{
		ymajor_line(params);
		params->pt1 = params->pt2;
		plot(params, 0);
		return;
	}
	xmajor_line(params);
	params->pt1 = params->pt2;
	plot(params, 0);
}
