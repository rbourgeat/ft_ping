# include "../inc/ft_ping.h"

extern t_ping g_ping;

void print_help() {
	printf("\nUsage\n  ping [options] <destination>\n\nOptions:\n  <destination>      dns name or ip address\n  -h                 print help and exit\n  -v                 verbose output\n\nFor more details see https://github.com/rbourgeat/ft_ping.\n");
}

void parse_hostname(char *target) {
    struct addrinfo hints;
    struct addrinfo *res;
    int             status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(target, NULL, &hints, &res)) != 0) {
        fprintf(stderr,"getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    void *addr;

    if (res->ai_family == AF_INET) { // IPv4
        g_ping.res = (struct sockaddr_in *)res->ai_addr;
        addr = &((g_ping.res)->sin_addr);
    } else { // IPv6
        fprintf(stderr, "Error IPv6 not supported\n");
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
   }

    if (inet_ntop(res->ai_family, addr, g_ping.ip, sizeof g_ping.ip) == NULL) {
        perror("inet_ntop");
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }

	printf("PING %s (%s) %d(%ld) bytes of data.\n", target, g_ping.ip, ICMP_DATA_SIZE, ICMP_DATA_SIZE + sizeof(struct icmphdr));
    freeaddrinfo(res);
}

void parse_arg(int ac, char **av) {
	char *arg;
	int i = 1;
	int j = 1;

	if (ac < 2) {
		printf("ft_ping: usage error: Destination address required\n");
		exit(1);
	}

	while (i < ac) {
		arg = av[i];
		if (arg[0] == '-') {
			if (strlen(arg) < 2) {
				printf("Error option not found\n./ft_ping [-v] [-h] target\n");
				exit(1);
			}
			while (arg[j] != '\0') {
				if (arg[j] == 'h') {
					print_help();
					exit(2);
				}
				else if (arg[j] == 'v')
					g_ping.is_verbose = 1;
				else {
					printf("ping: option requires an argument -- '%c'\n", arg[j]);
					print_help();
					exit(EXIT_FAILURE);
				}
				j++;
			}
		}
		else {
			parse_hostname(arg);
			snprintf(g_ping.target, sizeof(g_ping.target), "%s", arg);
		}
		i++;
	}
}