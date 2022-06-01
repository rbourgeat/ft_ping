/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:56:09 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/01 11:57:05 by rbourgea         ###   ########.fr       */
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
	if (get_args(&g_ping, argc, argv))
	{
		print_help();
		return (-1);
	}
	free_args(&g_ping);
	return (0);
}
