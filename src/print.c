/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:24:19 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/07 19:50:05 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static double	square_root(double a)
{
	double	s;
	double	l;
	double	mid;

	s = 1;
	l = a;
	mid = 0;
	while (s <= l)
	{
		mid = (s + l) / 2;
		if ((mid * mid) == a)
			break ;
		if ((mid * mid) < a)
			s = mid + 1;
		else
			l = mid - 1;
	}
	mid = (s + l) / 2;
	return (mid);
}

void	print_rtt(t_ping *ping)
{
	double	rtt_mdev;
	double	mean;
	double	smean;

	mean = ping->rtt_sum / ping->msg_recv_count;
	smean = ping->rtt_sum_sq / ping->msg_recv_count;
	rtt_mdev = square_root(smean - (mean * mean));
	printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
		ping->rtt_min, mean, ping->rtt_max, rtt_mdev);
}

void	print_final_stats(t_ping *ping)
{
	struct timeval	end_time;
	long			total_time;

	gettimeofday(&end_time, NULL);
	total_time = end_time.tv_sec * 1000 + end_time.tv_usec / 1000;
	total_time = total_time - \
		(ping->launch_time.tv_sec * 1000 + ping->launch_time.tv_usec / 1000);
	if (ping->q)
		printf("\n");
	printf("\033[1m\033[033m\n--- %s ping statistics ---\n", ping->dest);
	if (!ping->msg_count)
		ping->msg_count++;
	printf("%d packets transmitted, %d received, \033[1m\033[031m%d%% packet loss\033[1m\033[033m, time: %ld ms\n",
		ping->msg_count, ping->msg_recv_count,
		((ping->msg_count - ping->msg_recv_count) / ping->msg_count) * 100,
		total_time);
	if (ping->msg_recv_count)
		print_rtt(ping);
}

void	print_usage(void)
{
	printf("\033[1m\033[035mUsage: ft_ping [-Dhqv] [-c count] [-i interval] [-s packetsize] [-t ttl] host\n");
	// printf("\033[1m\033[035m\nUsage\n  ft_ping [options] <destination>\n\nOptions:\n  <destination>\t\tdns name or ip address\n  -c <count>\t\tstop after <count> replies\n  -D\t\t\tprint timestamps\n  -h\t\t\tprint help and exit\n  -i <interval>\t\tseconds between sending each packet\n  -q\t\t\tquiet output\n  -t <ttl>\t\tdefine time to live\n  -v\t\t\tverbose output\n");
}
