/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_routes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 18:16:48 by tmarkita          #+#    #+#             */
/*   Updated: 2020/12/02 18:21:33 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

int			*find_short_route(t_lemin *lemin)
{
	int i;
	int len;
	int t_len;
	int *arr;
	int k;

	i = 0;
	k = 0;
	len = lemin->num_rooms;
	arr = NULL;
	while (i < lemin->num_routes && lemin->routes)
	{
		t_len = route_len(lemin, lemin->routes[i]);
		if (t_len > 0 && t_len < len)
		{
			len = t_len;
			k = i;
			arr = lemin->routes[i];
		}
		i++;
	}
	if (lemin->routes)
		lemin->routes[k] = 0;
	return (arr);
}

int			is_not_double(t_lemin *lemin, int room)
{
	int i;

	i = 0;
	while (i < lemin->num_routes)
	{
		if (lemin->routes[i] && lemin->routes[i][0] == room)
			return (0);
		i++;
	}
	return (1);
}

void		sort_routes(t_lemin *lemin)
{
	int **routes;
	int *arr;
	int i;
	int k;

	if (!(routes = ft_memalloc((lemin->num_routes + 2) * 2)))
		put_error("ERROR");
	i = 0;
	k = 0;
	while (i < lemin->num_routes)
	{
		arr = find_short_route(lemin);
		if (arr && is_not_double(lemin, *arr))
			routes[k++] = arr;
		i++;
	}
	if (*routes)
	{
		free(lemin->routes);
		lemin->routes = routes;
		lemin->num_routes = k;
	}
	else
		free(routes);
}
