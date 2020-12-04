/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 18:20:01 by tmarkita          #+#    #+#             */
/*   Updated: 2020/12/02 18:26:42 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

int			biggest_len(t_lemin *lemin, int *arr)
{
	int i;
	int len;
	int	tmp;

	i = 0;
	len = 0;
	while (arr[i])
	{
		tmp = route_len(lemin, lemin->routes[i]) + arr[i];
		if (tmp > len)
			len = tmp;
		i++;
	}
	free(arr);
	return (len);
}

int			group_steps(t_lemin *lemin)
{
	int i;
	int ants;
	int use;
	int	*lens;

	if (!(lens = ft_memalloc(lemin->num_routes + 1)))
		put_error("ERROR");
	ants = routes_to_use(lemin, lemin->num_ants);
	while (ants < lemin->num_ants)
	{
		use = routes_to_use(lemin, ants);
		i = 0;
		while (i < use)
		{
			lens[i]++;
			ants++;
			i++;
		}
	}
	return (biggest_len(lemin, lens));
}
