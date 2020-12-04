/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:35:29 by tmarkita          #+#    #+#             */
/*   Updated: 2020/12/02 18:10:53 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

int		get_in_point(t_lemin *lemin, int y, int x)
{
	int rooms;

	rooms = lemin->num_rooms;
	while (x < rooms)
	{
		if (!(lemin->rooms_links[y][x]))
		{
			x++;
			continue ;
		}
		if (lemin->rooms_links[y][x] == lemin->rooms_links[x][y] + 1)
			return (x);
		x++;
	}
	return (0);
}

int		*check_route(t_lemin *lemin, int y)
{
	int	*arr;
	int	i;
	int	x;

	if (!(arr = ft_memalloc(lemin->num_rooms + 1)))
		put_error("ERROR");
	x = lemin->num_rooms - 1;
	i = lemin->rooms_links[y][lemin->num_rooms - 1] - 1;
	i = i < 0 ? 0 : i;
	arr[i--] = x;
	while (i >= 0)
	{
		arr[i] = y;
		y = get_in_point(lemin, y, 0);
		if (y == 0 && i > 0)
			while (!(y = get_in_point(lemin, arr[i + 1], arr[i] + 1)))
				i++;
		else
			i--;
	}
	return (arr);
}

int		not_in_routes(t_lemin *lemin, int room)
{
	int i;
	int len;

	i = 0;
	while (i < lemin->num_routes)
	{
		if (lemin->routes[i])
		{
			len = route_len(lemin, lemin->routes[i]);
			if (lemin->routes[i][len - 1] == room)
				return (0);
		}
		i++;
	}
	return (1);
}

int		make_route(t_lemin *lemin, int y)
{
	if ((lemin->routes[lemin->num_routes] = check_route(lemin, y)))
	{
		lemin->num_routes += 1;
		check_double_room(lemin);
		sort_routes(lemin);
		if (group_steps(lemin) <= lemin->best_len)
			spare_routes(lemin);
		if (lemin->num_ants == 1 ||
			lemin->num_routes > routes_to_use(lemin, lemin->num_ants))
			return (0);
		reset_bfs(lemin);
	}
	return (1);
}

void	find_routes(t_lemin *lemin)
{
	int	y;
	int rooms;

	if (!(lemin->routes = ft_memalloc((lemin->num_rooms + 1) * 2)))
		put_error("ERROR");
	lemin->min_route_len = lemin->num_rooms;
	lemin->best_len = 2147483647;
	y = 0;
	rooms = lemin->num_rooms;
	while (y < rooms)
	{
		if (lemin->rooms_links[y][rooms - 1] > 1 &&
			lemin->rooms_links[y][rooms - 1] < 100 && not_in_routes(lemin, y))
		{
			if (!make_route(lemin, y))
				break ;
			y = 0;
		}
		y++;
	}
	free_routes(&lemin->routes);
}
