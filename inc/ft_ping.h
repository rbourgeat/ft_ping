#ifndef FT_PING_H
# define FT_PING_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netinet/ip_icmp.h>
# include <netdb.h>
# include <errno.h>
# include <signal.h>

# define PAYLOAD_SIZE 56
# define MAX_LATENCIES 10


typedef struct s_ping {
	struct sockaddr_in *res;
	int		sockfd;
	char	ip[INET6_ADDRSTRLEN];
	char	target[INET6_ADDRSTRLEN];
	int		timeout;

	int		is_verbose;

	double	min;
	double	max;
	double	sum;

	int		seq;
	int		received;
	double	min_rtt;
	double	max_rtt;
	double	sum_rtt;
	double	mdev_rtt;
	long	total_time;

	double latencies[MAX_LATENCIES];
}			t_ping;

void	parse_arg(int ac, char **av);
void	init_socket();

#endif