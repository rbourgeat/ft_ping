/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:30:25 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/03 15:12:29 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	set_option(t_ping *ping, char **av, int *n, int x)
{
	if (av[*n][x] == 'h')
		ping->h = 1;
	else if (av[*n][x] == 'v')
		ping->v = 1;
	else
	{
		printf("ft_ping: invalid option -- '%c'\n", av[*n][x]);
		return (1);
	}
	return (0);
}

int	foreach_option(t_ping *ping, int argc, char **argv, int *n)
{
	int	x;

	x = 1;
	while (argv[*n][x])
	{
		if (*n + 1 == argc)
		{
			printf("ft_ping: option requires an argument -- '%c'\n", argv[*n][x]);
			return (1);
		}
		if (set_option(ping, argv, n, x))
			return (1);
		x++;
	}
	return (0);
}

int	get_args(t_ping *ping, int argc, char **argv)
{
	int	n;

	n = 1;
	while (n < argc)
	{
		if (argv[n][0] && argv[n][0] == '-')
		{
			if (foreach_option(ping, argc, argv, &n))
				return (1);
		}
		else if (ping->dest)
			return (1);
		else
			ping->dest = ft_strdup(argv[n]);
		n++;
	}
	return (0);
}