/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:24:16 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/07 19:44:59 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	set_packt(t_ping *ping, t_ping_packet *pckt)
{
	pckt->mhdr.msg_name = ping->sacrecv;
	pckt->mhdr.msg_namelen = ping->salen;
	pckt->mhdr.msg_iov = pckt->iov;
	pckt->mhdr.msg_iovlen = 1;
	pckt->mhdr.msg_control = &pckt->ctrl;
	pckt->mhdr.msg_controllen = sizeof(pckt->ctrl);
	pckt->iov[0].iov_base = pckt->databuf;
	pckt->iov[0].iov_len = sizeof(pckt->databuf);
}

static int	ping_loop(t_ping *ping)
{
	t_ping_packet	pckt;

	if (!(ping->sockfd = set_socket(ping)))
		return (-1);
	catch_sigalrm(SIGALRM);
	signal(SIGINT, &catch_sigint);
	ft_bzero(&pckt, sizeof(pckt));
	set_packt(ping, &pckt);
	while (ping->count_max)
	{
		recv_msg(ping, &pckt);
		ping->msg_count++;
		ping->count_max--;
	}
	print_final_stats(ping);
	return (0);
}

static struct addrinfo	*get_addr_info(t_ping *ping)
{
	struct addrinfo	*info;

	if (!(info = reverse_dns_info(ping->dest, NULL, AF_INET, 0)))
		return (NULL);
	ping->dest_ip = set_inetaddr(info->ai_addr);
	printf("\033[1m\033[034mFT_PING %s (%s) %d(%ld) bytes of data.\n",
		info->ai_canonname ? info->ai_canonname : ping->dest,
		ping->dest_ip, ping->datalen,
		ping->datalen + sizeof(struct iphdr) + sizeof(struct icmphdr));
	if (info->ai_family != AF_INET)
		return (NULL);
	return (info);
}

int	ping(t_ping *ping)
{
	int	ret;

	signal(SIGALRM, &catch_sigalrm);
	gettimeofday(&ping->launch_time, NULL);
	ping->before = ping->launch_time;
	if (!(ping->info = get_addr_info(ping)))
		return (-1);
	ping->sasend = ping->info->ai_addr;
	ping->sacrecv = malloc(ping->info->ai_addrlen);
	ft_bzero(ping->sacrecv, ping->info->ai_addrlen);
	ping->salen = ping->info->ai_addrlen;
	ret = ping_loop(ping);
	freeaddrinfo(ping->info);
	return (ret);
}
