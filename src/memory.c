/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 16:24:53 by tmarkita          #+#    #+#             */
/*   Updated: 2020/12/02 17:59:35 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/lem_in.h"

void	realloc_data(t_lemin *lemin)
{
	char	**new;

	if (!(new = malloc((lemin->data_len + BUFF) * sizeof(int*))))
		put_error("ERROR");
	ft_memcpy(new, lemin->first_data, lemin->data_len * sizeof(char*));
	free(lemin->first_data);
	lemin->data_len += BUFF;
	lemin->first_data = new;
}

void	free_strsplit(char **arr)
{
	while (arr && *arr)
	{
		free(*arr);
		arr++;
	}
}

void	free_routes(int ***routes)
{
	int i;

	i = 0;
	if (*routes)
	{
		while ((*routes)[i])
			free((*routes)[i++]);
		free(*routes);
	}
}
