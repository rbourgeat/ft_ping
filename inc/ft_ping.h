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

# define ICMP_DATA_SIZE 56

typedef struct s_ping {
	struct sockaddr_in *res;
	int		sockfd;
	char	ip[INET6_ADDRSTRLEN];
	int		timeout;

	int		is_verbose;

	double	min;
	double	max;
	double	sum;
}			t_ping;

void	pars_arg(int ac, char **av);
// int	set_sock(void);

#endif