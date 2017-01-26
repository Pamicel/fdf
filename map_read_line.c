/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamicel <pamicel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 10:48:48 by pamicel           #+#    #+#             */
/*   Updated: 2017/01/26 18:29:18 by pamicel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#define BUFF_SIZE 100

void		err_exit(char *msg)
{
	ft_putendl(msg);
	exit(0);
}

int			size_of_tab(char **temp)
{
	int n;

	n = 0;
	if (!temp)
		return (0);
	while (temp[n])
		n++;
	return (n);
}

char		***map_read_n_lines(char *file)
{
	char *memory;
	char **temp;
	char ***map;
	int i;
	int n;

	if ((fd = open(file)) == -1)
		err_exit("Not a valid file. SoAB err");
	ft_bufferize(fd, &memory, 0);
	temp = ft_strsplit(memory, '\n');
	map = (char***)ft_memalloc(sizeof(char**) * size_of_tab(temp););
	n = 0;
	while (temp[n])
		map[n] = ft_strsplit(temp[n], ' ');
	i = size_of_tab(map[0]);
	n = -1;
	while (map[++n])
		if (size_of_tab(map[n]) != i)
			err_exit("Go to hell, gimme a good map");
}


/*
	1- lit la map
		1- open
			si == -1, "not a valid file", ~exit~
		2- recuperer la file
			1- ft_strsplit '\n'
			2- n = taille de tableau
			3- ft_strsplit ' '
			4- nl = taille ligne
			4- while (n--) if (nl != taille de ligne[n]), "missing point" ~exit~
	2- ecrit les lignes
		1- prend point
