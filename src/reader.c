/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:54:30 by tmarkita          #+#    #+#             */
/*   Updated: 2020/12/02 16:39:00 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/lem_in.h"

void	check_start_end(t_lemin *lemin)
{
	if (lemin->start_room_name == NULL ||
		lemin->end_room_name == NULL)
		put_error("ERROR");
}

void	check_commands(t_lemin *lemin)
{
	int	i;
	int	start;
	int	end;
	int len;

	i = 0;
	start = 0;
	end = 0;
	len = lemin->data_len;
	while (i < len)
	{
		start = ft_strequ(*(lemin->first_data + i), "##start") ?
				start + 1 : start;
		end = ft_strequ(*(lemin->first_data + i), "##end") ?
				end + 1 : end;
		i++;
	}
	if (i > 0 && !ft_strncmp(*(lemin->first_data + i - 1), "##", 2))
		put_error("ERROR");
	if (start != 1 || end != 1)
		put_error("ERROR");
}

void	check_coords(t_lemin *lemin, int *xy)
{
	int i;
	int	rooms;

	rooms = lemin->num_rooms;
	i = 0;
	while (i < rooms)
	{
		if (lemin->rooms_coords[i][0] == xy[0] &&
			lemin->rooms_coords[i][1] == xy[1])
			put_error("ERROR");
		i++;
	}
}

void	parse_data(t_lemin *lemin)
{
	if (!(lemin->rooms_names = ft_memalloc(lemin->data_len * 2)) ||
		!(lemin->rooms_coords = ft_memalloc(lemin->data_len * 2)) ||
		!(lemin->links_names = ft_memalloc(lemin->data_len * 4)))
		put_error("ERROR");
	lemin->start_room_name = NULL;
	lemin->end_room_name = NULL;
	check_commands(lemin);
	check_room_names(lemin);
	check_start_end(lemin);
	check_link_names(lemin);
	if (lemin->num_ants < 1 ||
		!lemin->num_rooms ||
		!lemin->num_links)
		put_error("ERROR");
}

void	read_data(t_lemin *lemin)
{
	char	*line;
	int		i;
	int		ret;

	i = 0;
	while ((ret = get_next_line(0, &line)))
	{
		if (ret < 0)
			put_error("ERROR");
		if (i == lemin->data_len)
			realloc_data(lemin);
		lemin->first_data[i] = line;
		i++;
	}
	lemin->data_len = i;
}
