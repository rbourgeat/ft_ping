/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:10:47 by rbourgea          #+#    #+#             */
/*   Updated: 2023/10/17 07:10:48 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/ft_ping.h"

t_ping g_ping;

void sigint_handler(int signo) {
    if (signo == SIGINT) {
        printf("\n--- %s ping statistics ---\n", g_ping.target);
        printf("%d packets transmitted, %d received, %.2f%% packet loss, time %ldms\n", g_ping.seq, g_ping.received, ((float)(g_ping.seq - g_ping.received) / g_ping.seq) * 100, g_ping.total_time);

        if (g_ping.received > 0) {
            printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n", g_ping.min_rtt, g_ping.sum_rtt / g_ping.received, g_ping.max_rtt, g_ping.mdev_rtt);
        }

        close(g_ping.sockfd);
        exit(0);
    }
}

int main(int ac, char **av) {

	if (getuid() != 0) {
        printf("You need to run it with sudo.\n");
		exit(1);
    }

	parse_arg(ac, av);

	if (signal(SIGINT, sigint_handler) == SIG_ERR) {
		perror("signal");
	}

	init_socket();
}