/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:10:56 by rbourgea          #+#    #+#             */
/*   Updated: 2023/10/17 07:39:03 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/ft_ping.h"

extern t_ping g_ping;

void print_help() {
	printf("Usage: ping [-hv] destination\n");
}

void parse_hostname(char *target) {
    struct addrinfo hints;
    struct addrinfo *res;
    int             status;

    ft_memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(target, NULL, &hints, &res)) != 0) {
        fprintf(stderr,"ft_ping: %s: %s\n", g_ping.target, gai_strerror(status));
        exit(1);
    }

    void *addr;

    if (res->ai_family == AF_INET) { // IPv4
        g_ping.res = (struct sockaddr_in *)res->ai_addr;
        addr = &((g_ping.res)->sin_addr);
    } else { // IPv6
        fprintf(stderr, "Error IPv6 not supported\n");
        freeaddrinfo(res);
        exit(1);
   }

    if (inet_ntop(res->ai_family, addr, g_ping.ip, sizeof g_ping.ip) == NULL) {
        perror("inet_ntop");
        freeaddrinfo(res);
        exit(1);
    }

    freeaddrinfo(res);
}

void parse_arg(int ac, char **av) {
	char *arg;
	int i = 1;
	int j = 1;

	if (ac < 2) {
		print_help();
		exit(1);
	}

	while (i < ac) {
		arg = av[i];
		if (arg[0] == '-') {
			if (strlen(arg) < 2) {
				printf("ft_ping: -: Name or service not known\n");
				exit(2);
			}
			while (arg[j] != '\0') {
				if (arg[j] == 'h') {
					print_help();
					exit(2);
				}
				else if (arg[j] == 'v')
					g_ping.is_verbose = 1;
				else {
					printf("ft_ping: option requires an argument -- '%c'\n", arg[j]);
					print_help();
					exit(2);
				}
				j++;
			}
		}
		else {
			snprintf(g_ping.target, sizeof(g_ping.target), "%s", arg);
			parse_hostname(arg);
		}
		i++;
	}
}