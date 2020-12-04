/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:22:31 by tmarkita          #+#    #+#             */
/*   Updated: 2020/12/03 14:22:31 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

void	put_header(t_lemin *lemin)
{
	int x;

	x = 0;
	while (x < lemin->num_rooms)
	{
		ft_putstr(lemin->rooms_names[x]);
		write(1, " ", 1);
		x++;
	}
	write(1, "\n\n", 2);
}

void	put_lines(t_lemin *lemin)
{
	int x;
	int y;

	y = 0;
	while (y < lemin->num_rooms)
	{
		x = 0;
		while (x < lemin->num_rooms)
		{
			lemin->rooms_links[y][x] ?
			ft_putnbr(lemin->rooms_links[y][x]) : write(1, "0", 1);
			write(1, " ", 1);
			x++;
		}
		write(1, "  ", 3);
		ft_putstr(lemin->rooms_names[y]);
		write(1, "\n", 1);
		y++;
	}
}

int		print_matrix(t_lemin *lemin)
{
	system("clear");
	if (lemin->num_rooms > 80)
		write(1, "\nMatrix is too big\n", 19);
	else
	{
		put_header(lemin);
		put_lines(lemin);
	}
	write(1, "\n", 1);
	print_routes(lemin);
	write(1, "\n", 1);
	sleep(1);
	return (1);
}
