/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wu.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamicel <pamicel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 18:21:33 by pamicel           #+#    #+#             */
/*   Updated: 2017/01/29 18:22:49 by pamicel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WU_H
# define WU_H

# include "mlx.h"
# include "libft.h"
# include <math.h>

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef struct		s_data
{
	int	 			alpha;
	int	 			color;
	unsigned int	intensity_bits;
	unsigned int	n_levels;
	int	 			dx;
	int	 			dy;
	int	 			xdir;
	t_point			pos;
	int				tilt;
	void			*mlx;
	void			*win;
}					t_data;

typedef struct		s_params
{
	t_point			pt1;
	t_point			pt2;
	t_data			env;
}					t_params;

void				plot(t_params *params, int alpha_inc);
void				draw_line_wu(t_params *params);
int					special_lines(t_params *params);

#endif
