/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:56:15 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/03 15:18:22 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING
# define FT_PING

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h> // inet_ntop

typedef struct s_ping
{
	int		h;
	int		v;
	char		*dest;
	struct timeval	time;
	struct addrinfo	*addr;
	char		*ip;
	int		databytes;
}			t_ping;

extern t_ping	g_ping;

// ping.c
int	exec_ping(t_ping *ping);
// parsing.c
int	get_args(t_ping *ping, int argc, char **argv);
// libft.c
char	*ft_strdup(const char *s1);
void	*ft_memset(void *pointer, int value, size_t count);
// utils.c
void	print_help(void);

#endif