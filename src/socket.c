/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:24:31 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/07 18:56:41 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	set_socket(t_ping *ping)
{
	int				sock;
	int				size;

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sock < 0)
	{
		printf("\033[1m\033[031mft_ping: fail to create socket\n");
		return (-1);
	}
	size = 60 * 1024;
	setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size)); // api options
	setsockopt(sock, IPPROTO_IP, IP_TTL, &ping->ttl, sizeof(ping->ttl));
	// setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &size, sizeof(size));
	return (sock);
}
