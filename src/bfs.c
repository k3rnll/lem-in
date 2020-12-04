/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:49:00 by tmarkita          #+#    #+#             */
/*   Updated: 2020/12/03 14:31:34 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

void	reset_bfs(t_lemin *lemin)
{
	int x;
	int y;
	int len;

	y = 0;
	len = lemin->num_rooms;
	while (y < len)
	{
		x = 0;
		while (x < len)
		{
			if (lemin->rooms_links[y][x])
				lemin->rooms_links[y][x] = 1;
			x++;
		}
		y++;
	}
	bfs(lemin);
}

void	shift_ocrd(t_lemin *lemin)
{
	int	i;
	int	tmp;
	int	rooms;

	i = 0;
	rooms = lemin->num_rooms * 4;
	tmp = lemin->ocrd[i];
	while (tmp && i < rooms)
	{
		tmp = lemin->ocrd[i + 1];
		lemin->ocrd[i] = tmp;
		i++;
	}
}

int		ocrd_add(t_lemin *lemin, int *ocrd, int y, int step)
{
	int	x;
	int	len;

	x = 0;
	len = 0;
	while (*ocrd != 0)
		ocrd++;
	while (x < lemin->num_rooms)
	{
		if (lemin->rooms_links[y][x] == 1)
		{
			lemin->rooms_links[y][x] = step;
			if (x > 0 && x < lemin->num_rooms - 1)
			{
				*ocrd = x;
				ocrd++;
				len++;
			}
			if (x == lemin->num_rooms - 1 && not_in_routes(lemin, y))
				return (-1);
		}
		x++;
	}
	return (len);
}

void	bfs(t_lemin *lemin)
{
	int		len[2];
	int		step;
	int		tmp;

	ft_bzero(lemin->ocrd, (lemin->num_rooms * 4) * sizeof(int));
	step = 1;
	len[0] = ocrd_add(lemin, lemin->ocrd, 0, step++);
	len[1] = 0;
	tmp = 0;
	while (*lemin->ocrd && len[0] && tmp >= 0)
	{
		tmp = ocrd_add(lemin, lemin->ocrd, *lemin->ocrd, step);
		len[1] += tmp;
		shift_ocrd(lemin);
		len[0]--;
		if (len[0] == 0)
		{
			step++;
			len[0] = len[1];
			len[1] = 0;
		}
	}
	lemin->p_matrix ? print_matrix(lemin) : 0;
}
