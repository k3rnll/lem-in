/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:45:58 by tmarkita          #+#    #+#             */
/*   Updated: 2020/12/02 17:56:04 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

void	change_route(t_lemin *lemin, int rt, int **new)
{
	free(lemin->routes[rt]);
	lemin->routes[rt] = *new;
}

void	del_last_route(t_lemin *lemin)
{
	free(lemin->routes[lemin->num_routes - 1]);
	lemin->routes[lemin->num_routes - 1] = NULL;
	lemin->num_routes--;
}

int		has_room(t_lemin *lemin, int rt, int room)
{
	int i;
	int *arr;

	i = route_len(lemin, lemin->routes[rt]) - 1;
	while (i >= 0)
	{
		if (lemin->routes[rt][i] == room)
		{
			ft_bzero(lemin->rooms_links[lemin->routes[rt][i]],
				lemin->num_rooms * 4);
			reset_bfs(lemin);
			arr = check_route(lemin,
				lemin->routes[rt][route_len(lemin, lemin->routes[rt]) - 1]);
			if (route_len(lemin, arr) == 0)
			{
				del_last_route(lemin);
				free(arr);
				return (0);
			}
			else
				change_route(lemin, rt, &arr);
		}
		i--;
	}
	return (1);
}

int		search_in_routes(t_lemin *lemin, int room)
{
	int i;

	i = lemin->num_routes - 2;
	while (i >= 0)
	{
		if (!(has_room(lemin, i, room)))
			return (0);
		i--;
	}
	return (1);
}

int		check_double_room(t_lemin *lemin)
{
	int	i;
	int *last;

	last = lemin->routes[lemin->num_routes - 1];
	i = route_len(lemin, last) - 1;
	while (i >= 0)
	{
		if (!(search_in_routes(lemin, last[i])))
			return (0);
		i--;
	}
	return (1);
}
