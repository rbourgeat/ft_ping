/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:16:27 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/02 17:54:32 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

struct addrinfo	*rev_dns_info(char *host, char *serv, int family, int socktype)
{
	struct addrinfo	*res;
	struct addrinfo	hints;

	ft_memset(&hints, 0, sizeof hints);
	hints.ai_family = family;
	hints.ai_socktype = socktype;
	hints.ai_flags = AI_CANONNAME;
	if (getaddrinfo(host, serv, &hints, &res) != 0)
	{
		printf("ft_ping: %s: Name or service not known\n", host);
		return (NULL);
	}
	return (res);
}

static struct addrinfo	*get_addr(t_ping *ping)
{
	struct addrinfo	*addr;

	addr = rev_dns_info(ping->dest, NULL, AF_INET, 0); // AF_INET = IPV4 // AF_INET6 = IPV6
	if (!addr)
		return (NULL);
	ping->ip = set_inetaddr(addr->ai_addr);
	printf("FT_PING %s (%s) %d(%d) bytes of data\n", addr->ai_canonname ? addr->ai_canonname : ping->dest,
		ping->ip, ping->databytes, ping->databytes + sizeof(struct iphdr) + sizeof(struct icmphdr));
	if (addr->ai_family != AF_INET)
		return (NULL);
	return (addr);
}

int	exec_ping(t_ping *ping)
{
	gettimeofday(&ping->time, NULL);
	ping->addr = get_addr(ping);
	return (0);
}