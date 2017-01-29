/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamicel <pamicel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:34:59 by pamicel           #+#    #+#             */
/*   Updated: 2017/01/29 17:03:58 by pamicel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wu.h"

static int          horizontal_line(t_params *params)
{
    while (params->env.dx-- != 0)
    {
        params->pt1.x += params->env.xdir;
        plot(params, 0);
    }
    return (1);
}

static int          vertical_line(t_params *params)
{
    while (params->env.dy)
    {
        params->pt1.y++;
        plot(params, 0);
        params->env.dy--;
    }
    return (1);
}

static int          diagonal_line(t_params *params)
{
    while (params->env.dy)
    {
        params->pt1.x += params->env.xdir;
        params->pt1.y++;
        plot(params, 0);
        params->env.dy--;
    }
    return (1);
}

int                 special_lines(t_params *params)
{
    params->env.xdir = 1;
    if ((params->env.dx = params->pt2.x - params->pt1.x) < 0)
    {
        params->env.xdir = - params->env.xdir;
        params->env.dx = - params->env.dx;
    }
    if ((params->env.dy = params->pt2.y - params->pt1.y) == 0)
        return (horizontal_line(params));
    if (params->env.dx == 0)
        return (vertical_line(params));
    if (params->env.dx == params->env.dy)
        return (diagonal_line(params));
    return (0);
}
