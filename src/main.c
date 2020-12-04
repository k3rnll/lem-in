/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:44:20 by tmarkita          #+#    #+#             */
/*   Updated: 2020/12/03 14:24:50 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/lem_in.h"

void		put_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void		print_input_data(t_lemin *lemin)
{
	int i;
	int	len;

	len = lemin->data_len;
	i = 0;
	while (i < len)
	{
		write(1, lemin->first_data[i], ft_strlen(lemin->first_data[i]));
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

t_lemin		*init_lemin(void)
{
	t_lemin	*lemin;

	if (!(lemin = malloc(sizeof(t_lemin))) ||
		!(lemin->first_data = malloc(BUFF * sizeof(char*))))
		put_error("ERROR");
	lemin->data_len = BUFF;
	lemin->routes = NULL;
	lemin->num_ants = 0;
	lemin->ants_flag = 0;
	lemin->num_rooms = 0;
	lemin->num_links = 0;
	lemin->num_routes = 0;
	lemin->p_routes = 0;
	lemin->p_data = 1;
	lemin->p_matrix = 0;
	return (lemin);
}

void		parse_flags(t_lemin *lemin, int ac, char **av)
{
	int		i;

	i = 1;
	while (av[i] && ac)
	{
		if (av[i] && ft_strequ("-r", av[i]) && !lemin->p_routes)
			lemin->p_routes = 1;
		else if (av[i] && ft_strequ("-d", av[i]) && lemin->p_data)
			lemin->p_data = 0;
		else if (av[i] && ft_strequ("-m", av[i]) && !lemin->p_matrix)
			lemin->p_matrix = 1;
		else
			put_error(
				" ================================\n"
				" USAGE: ./lem-in < map\n\n FLAGS: -r show routes\n"
				"        -d do not show input data\n"
				"        -m show matrix           \n"
				" ================================");
		i++;
	}
}

int			main(int ac, char **av)
{
	t_lemin		*lemin;

	lemin = init_lemin();
	parse_flags(lemin, ac, av);
	read_data(lemin);
	parse_data(lemin);
	rooms_to_massive(lemin);
	bfs(lemin);
	if (lemin->rooms_links[0][lemin->num_rooms - 1])
		make_one_route(lemin);
	else
		make_routes_group(lemin);
	lemin->p_routes && !lemin->p_matrix ? print_routes(lemin) : 0;
	lemin->p_matrix ? print_matrix(lemin) : 0;
	lemin->p_matrix ? 0 : flow_ants(lemin);
	exit(0);
}
