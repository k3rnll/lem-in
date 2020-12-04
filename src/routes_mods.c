/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes_mods.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 20:54:12 by tmarkita          #+#    #+#             */
/*   Updated: 2020/12/02 18:19:39 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

void	make_routes_group(t_lemin *lemin)
{
	find_routes(lemin);
	lemin->routes = lemin->best_routes;
	lemin->num_routes = 0;
	while (lemin->routes && lemin->routes[lemin->num_routes])
		lemin->num_routes++;
}

void	make_one_route(t_lemin *lemin)
{
	if (!(lemin->routes = ft_memalloc(2 * 2)) ||
	!(lemin->routes[0] = ft_memalloc(2)))
		put_error("ERROR");
	lemin->routes[0][0] = lemin->num_rooms - 1;
	lemin->min_route_len = 0;
	lemin->num_routes = 1;
}

int		route_len(t_lemin *lemin, int *arr)
{
	int	len;
	int rooms;

	rooms = lemin->num_rooms;
	len = 0;
	if (arr && arr[len])
	{
		while (arr[len] != rooms - 1 && len < rooms)
			len++;
	}
	return (len);
}
