/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:24:26 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/07 19:10:17 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	send_msg(void)
{
	int			len;
	int			ret;
	struct icmp	*icmp;
	char		sendbuf[BUFSIZE];

	icmp = (struct icmp *)sendbuf;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_id = g_ping.pid;
	icmp->icmp_seq = g_ping.msg_sent;
	ft_memset(icmp->icmp_data, 0xa5, g_ping.datalen);
	gettimeofday(&g_ping.before, NULL);
	gettimeofday((struct timeval *)icmp->icmp_data, NULL);
	len = 8 + g_ping.datalen;
	icmp->icmp_cksum = 0;
	icmp->icmp_cksum = checksum((u_short *) icmp, len);
	ret = sendto(g_ping.sockfd, sendbuf, len, 0, g_ping.sasend, g_ping.salen);
	if (ret)
		g_ping.msg_sent++;
}
