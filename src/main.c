/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:24:14 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/06 19:41:09 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_ping	g_ping;

int	ret_val(int ret)
{
	if (ret < 0)
		return (ret);
	if (g_ping.msg_recv_count)
		return (0);
	else if (g_ping.msg_sent)
		return (2);
	return (1);
}

int	main(int argc, char **argv)
{
	int	ret;

	// if (argc == 1)
	// {
	// 	printf("\033[1m\033[031mft_ping: usage error: Destination address required\n");
	// 	return (-1);
	// }
	if (getuid() != 0)
	{
		printf("\033[1m\033[031mft_ping: need to use this with sudo\n");
		return (-1);
	}
	init_ping(&g_ping);
	if (get_args(&g_ping, argc, argv))
	{
		print_usage();
		return (-1);
	}
	if (g_ping.h)
		print_usage();
	else
		ret = ping(&g_ping);
	free_args(&g_ping);
	return (ret_val(ret));
}
