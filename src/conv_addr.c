/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_addr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:24:09 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/06 18:28:17 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

char	*set_inetaddr(struct sockaddr *sa)
{
	struct sockaddr_in	*sin;
	char				str[IP_STR_SIZE];

	sin = (struct sockaddr_in *)sa;
	if (!inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)))
		return (ft_strdup("error"));
	return (ft_strdup(str));
}
