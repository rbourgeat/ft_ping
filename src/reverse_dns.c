/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_dns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:24:24 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/07 19:24:44 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

char	*get_fqdn_info(struct sockaddr *addr)
{
	char		buf[BUFSIZE];
	socklen_t	len;

	len = sizeof(struct sockaddr_in);
	if (getnameinfo(addr, len, buf, sizeof(buf), NULL, 0, NI_NAMEREQD))
		return (NULL);
	return (ft_strdup(buf));
}

struct addrinfo	*reverse_dns_info(char *host, char *serv, int family, int socktype)
{
	struct addrinfo	*res;
	struct addrinfo	hints;

	ft_memset(&hints, 0, sizeof hints);
	hints.ai_family = family;
	hints.ai_socktype = socktype;
	hints.ai_flags = AI_CANONNAME;
	if (getaddrinfo(host, serv, &hints, &res) != 0)
	{
		printf("\033[1m\033[031mft_ping: %s: Name or service not known\n", host);
		return (NULL);
	}
	return (res);
}
