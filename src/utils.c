/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:24:33 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/07 19:49:43 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	ping_timer(int interval)
{
	struct timeval tv_current;
	struct timeval tv_next;

	if (gettimeofday(&tv_current, NULL) < 0)
		return;
	tv_next = tv_current;
	tv_next.tv_sec += interval;
	while (tv_current.tv_sec < tv_next.tv_sec || tv_current.tv_usec < tv_next.tv_usec)
		if (gettimeofday(&tv_current, NULL) < 0)
			return;
}

void	free_args(t_ping *ping)
{
	free(ping->dest);
	free(ping->dest_ip);
	free(ping->sacrecv);
}

void	init_ping(t_ping *ping)
{
	ping->v = 0;
	ping->h = 0;
	ping->q = 0;
	ping->d = 0;
	ping->ttl = PING_TTL;
	ping->count_max = -1;
	ping->rtt_min = -1;
	ping->rtt_max = -1;
	ping->rtt_sum = 0;
	ping->rtt_sum_sq = 0;
	ping->msg_sent = 0;
	ping->msg_count = 1;
	ping->msg_recv_count = 0;
	ping->fqdn = NULL;
	ping->dest = NULL;
	ping->dest_ip = NULL;
	ping->info = NULL;
	ping->datalen = PING_PACKET_S;
	ping->sasend = NULL;
	ping->sacrecv = NULL;
	ping->salen = 0;
}

unsigned short	checksum(void *b, int len)
{
	unsigned short	*buf;
	unsigned int	sum;
	unsigned short	result;

	buf = b;
	sum = 0;
	while (len > 1)
	{
		sum += *buf++;
		len -= 2;
	}
	if (len == 1)
		sum += *(unsigned char *)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return (result);
}
