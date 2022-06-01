/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:56:15 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/01 11:57:37 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING
# define FT_PING

#include <stdio.h>
#include <stdlib.h>

typedef struct s_ping
{
	int	h;
	int	v;
	char	*dest;
}		t_ping;

extern t_ping	g_ping;

// parsing.c
int	get_args(t_ping *ping, int argc, char **argv);
// libft.c
char	*ft_strdup(const char *s1);
// utils.c
void	print_help(void);

#endif