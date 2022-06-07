/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:24:07 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/07 19:49:08 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	check_options(t_ping *ping)
{
	if (ping->datalen > BUFSIZE)
		g_ping.datalen = BUFSIZE - (sizeof(struct icmphdr) + sizeof(struct ip));
	if (!ping->dest)
		return (1);
	if (ping->ttl < 0 || ping->ttl > 255)
	{
		printf("\033[1m\033[031mft_ping: invalid argument: '%d': out of range: 0 <= value\n", ping->ttl);
		return (1);
	}
	if (ping->ttl == 0)
	{
		printf("\033[1m\033[031mft_ping: can't set unicast time-to-live: Invalid argument\n");
		return (1);
	}
	if (ping->datalen < 0)
	{
		printf("\033[1m\033[031mft_ping: invalid argument: '%d': out of range: 0 <= value\n", ping->datalen);
		// printf("\033[1m\033[031mft_ping: illegal packet size\n");
		return (1);
	}
	else if (ping->count_max <= 0 && ping->count_max != -1)
	{
		printf("\033[1m\033[031mft_ping: bad number of packets to transmit.\n");
		return (1);
	}
	return (0);
}

int	set_flag(t_ping *ping, char **argv, int *n, int x)
{
	if (argv[*n][x] == 'c')
		ping->count_max = ft_atoi(argv[++(*n)]);
	else if (argv[*n][x] == 'D')
		ping->d = 1;
	else if (argv[*n][x] == 'h')
		ping->h = 1;
	else if (argv[*n][x] == 'i')
		ping->interval = ft_atoi(argv[++(*n)]);
	else if (argv[*n][x] == 'q')
		ping->q = 1;
	else if (argv[*n][x] == 's')
		ping->datalen = ft_atoi(argv[++(*n)]);
	else if (argv[*n][x] == 't')
		ping->ttl = ft_atoi(argv[++(*n)]);
	else if (argv[*n][x] == 'v')
		ping->v = 1;
	else
	{
		printf("\033[1m\033[031mft_ping: invalid option -- '%c'\n", argv[*n][x]);
		return (1);
	}
	return (0);
}

int	set_option_loop(t_ping *ping, int argc, char **argv, int *n)
{
	int	x;

	x = 0;
	while (argv[*n][++x])
	{
		if (argv[*n][x] == 'i' || argv[*n][x] == 't' || argv[*n][x] == 's' || argv[*n][x] == 'c')
		{
			if (argv[*n][x + 1])
				return (1);
			if (*n + 1 == argc)
			{
				printf("\033[1m\033[031mft_ping: option requires an argument -- '%c'\n", argv[*n][x]);
				return (1);
			}
			return (set_flag(ping, argv, n, x));
		}
		if (set_flag(ping, argv, n, x))
			return (1);
	}
	return (0);
}

int	get_args(t_ping *ping, int argc, char **argv)
{
	int	n;

	n = 0;
	while (++n < argc)
	{
		if (argv[n][0] && argv[n][0] == '-')
		{
			if (set_option_loop(ping, argc, argv, &n))
				return (1);
		}
		else if (ping->dest)
			return (1);
		else
			ping->dest = ft_strdup(argv[n]);
	}
	if (check_options(ping))
		return (1);
	return (0);
}
