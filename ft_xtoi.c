/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamicel <pamicel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 10:57:31 by pamicel           #+#    #+#             */
/*   Updated: 2017/01/26 14:40:29 by pamicel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_xtoi_char(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else
		return ((c >= 'a' ? c - 'a' : c - 'A') + 10);
}

long		ft_xtoi(char *nbr)
{
	ssize_t		i;
	long		ret;

	if (!*nbr)
		return (0);
	ret = ft_xtoi_char(*nbr);
	if ((i = ft_strlen(nbr)))
		ret *= pow(16, i - 1);
	return (ret + ft_xtoi(nbr + 1));
}
