/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_wu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamicel <pamicel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 18:21:22 by pamicel           #+#    #+#             */
/*   Updated: 2017/01/29 18:38:08 by pamicel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wu.h"

void				set_env(t_data *env)
{
	env->intensity_bits = 8;
	env->n_levels = pow(2, env->intensity_bits);
	env->color = 0xffff;
	env->alpha = 0;
	env->dx = 0;
	env->dy = 0;
	env->xdir = 1;
}

int					main(void)
{
	t_params		*params;

	params = (t_params*)ft_memalloc(sizeof(t_params));
	params->env.mlx = mlx_init();
	params->env.win = mlx_new_window(params->env.mlx, 800, 400, "hello Wu");

	params->pt1.color = 0xffffff;
	params->pt2.color = 0xffffff;

	set_env(&(params->env));

	params->pt1.x = 50;
	params->pt1.y = 0;
	params->pt2.x = 450;
	params->pt2.y = 350;
	draw_line_wu(params);

	params->pt1.x = 0;
	params->pt1.y = 0;
	params->pt2.x = 400;
	params->pt2.y = 350;
	draw_line_wu(params);

	params->pt1.x = 0;
	params->pt1.y = 0;
	params->pt2.x = 200;
	params->pt2.y = 350;
	draw_line_wu(params);

	mlx_loop(params->env.mlx);
	return (0);
}
