/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_group.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:31:49 by tmarkita          #+#    #+#             */
/*   Updated: 2020/12/02 17:30:20 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

void	spare_routes(t_lemin *lemin)
{
	int i;
	int k;
	int len;

	free_routes(&lemin->best_routes);
	if (!(lemin->best_routes = ft_memalloc((lemin->num_routes + 1) * 2)))
		put_error("ERROR");
	i = 0;
	k = 0;
	while (i < lemin->num_routes)
	{
		if (lemin->routes[i])
		{
			len = route_len(lemin, lemin->routes[i]) + 1;
			lemin->best_routes[k] = malloc((len + 1) * sizeof(int));
			lemin->best_routes[k][len] = 0;
			ft_memcpy(lemin->best_routes[k], lemin->routes[i], (len) * 4);
			k++;
		}
		i++;
	}
	lemin->best_len = group_steps(lemin);
}
