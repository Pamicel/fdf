/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamicel <pamicel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:10:58 by pamicel           #+#    #+#             */
/*   Updated: 2017/01/29 18:21:18 by pamicel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#define LINE_ERR "Error. Incorrect map : all lines are not of equal length."
#define MEM_ERR "Error. Could not allocate memory."
#define OPEN_ERR "Error. Could not open file."

typedef struct	  s_point
{
	int			 x;
	int			 y;
	int			 z;
	int			 color;
}				   t_point;

void		err_exit(char *msg)
{
	ft_putendl(msg);
	exit(0);
}

static int	size_of_tab(void *tab, int size)
{
	int		n;
	int		inc;
	char	*tmp;

	tmp = (char*)tab;
	inc = size / sizeof(char);
	n = inc - 1;
	if (!tmp)
		return (0);
	while (tmp[n] && \
			(inc <= 1 || tmp[n - 1]) && \
			(inc <= 2 || tmp[n - 2]) && \
			(inc <= 3 || tmp[n - 3]))
		n += inc;
	return (n / inc);
}

// t_point *pt1;
// t_point *pt2;
//
// pt1 = (t_point*)ft_memalloc(sizeof(t_point));
// pt2 = (t_point*)ft_memalloc(sizeof(t_point));

void		line(char ***map, int x, int y, int tilt)
{
	t_point point;

	point.x = tilt * x + posx;
	if (x != 0)
		draw_line(map[y][x], map[y][x - 1]);
	if (y != 0)
		draw_line(map[y][x], map[y - 1][x]);
}

char		***fdf_parsing(int fd)
{
	char	*memory;
	char	**temp;
	char	***map;
	int		n;

	if ((memory = ft_strnew(0)))
		ft_bufferize(fd, &memory, 0);
	if ((temp = ft_strsplit(memory, '\n')))
		map = ft_memalloc(sizeof(char**) * size_of_tab(temp, sizeof(char**)));
	if (!temp || !map)
		err_exit(MEM_ERR);
	n = -1;
	while (temp[++n])
		if (!(map[n] = ft_strsplit(temp[n], ' ')))
			err_exit(MEM_ERR);
	while (map[--n])
		if (size_of_tab(map[n], sizeof(char**)) != \
				size_of_tab(map[0], sizeof(char**)))
			err_exit(LINE_ERR);
	free(temp);
	free(memory);
	return (map);
}

void		draw_map(char ***map, int tilt, t_data env)
{
	int		len;
	int		hei;
	int		x;
	int		y;

	hei = size_of_tab(map, sizeof(char**));
	len = size_of_tab(map[0], sizeof(char*));
	x = -1;
	while (++x < len)
	{
		y = -1;
		while (++y < hei)
			line(map, n, params);
	}
}

void					set_env(t_data *env)
{
	env->intensity_bits = 8;
	env->n_levels = 256;
	env->color = 0xFFFFFF;
	env->alpha = 0;
	env->dx = 0;
	env->dy = 0;
	env->xdir = 1;
}

int			main(int ac, char **av)
{
	char	***map;
	int		fd;
	int		i;
	int		j;

	if (ac != 2)
	{
		ft_putendl("usage : ./fdf <text_file>");
		return (1);
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
		err_exit(OPEN_ERR);
	if (!(map = fdf_parsing(fd)))
		err_exit(MEM_ERR);

	close(fd);
	return (0);
}
