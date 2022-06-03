/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:56:09 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/03 15:09:31 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_ping	g_ping;

void	init_ping(t_ping *ping)
{
	ping->h = 0;
	ping->v = 0;
	ping->dest = NULL;
}

void	free_args(t_ping *ping)
{
	free(ping->dest);
}

int	main(int argc, char **argv)
{
	init_ping(&g_ping);
	if (argc == 1)
	{
		printf("ft_ping: usage error: Destination address required\n");
		return (-1);
	}
	if (get_args(&g_ping, argc, argv))
	{
		print_help();
		return (-1);
	}
	if (g_ping.h)
		print_help();
	else
		return(exec_ping(&g_ping));
	free_args(&g_ping);
	return (0);
}
