/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:24:29 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/07 19:43:44 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	catch_sigint(int signal)
{
	(void)signal; // dont rm this (incompatible error)
	print_final_stats(&g_ping);
	if (g_ping.info)
		freeaddrinfo(g_ping.info);
	free_args(&g_ping);
	if (g_ping.msg_recv_count)
		exit(0);
	else if (g_ping.msg_sent)
		exit(2);
	exit(1);
}

void	catch_sigalrm(int signal)
{
	if (signal != SIGALRM)
		return;
	send_msg();
	alarm(1);
}
