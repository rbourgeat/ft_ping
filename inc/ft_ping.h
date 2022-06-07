/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:24:51 by rbourgea          #+#    #+#             */
/*   Updated: 2022/06/07 19:26:05 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING
# define FT_PING

# define GREY    	=	"\033[030m"
# define RED     	=	"\033[031m"
# define GREEN   	=	"\033[032m"
# define YELLOW  	=	"\033[033m"
# define BLUE    	=	"\033[034m"
# define MAGENTA 	=	"\033[035m"
# define CYAN		=	"\033[036m"
# define BOLD		=	"\033[1m"
# define RESET   	=	"\033[0m"

# define BUFSIZE		1500
# define PING_PACKET_S	56
# define IP_STR_SIZE	129
# define PING_TTL		64
# define RECV_TIMEOUT	1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in_systm.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_ping_packet
{
	struct msghdr	mhdr;
	struct iovec	iov[1];
	char			databuf[BUFSIZE];
	char			ctrl[BUFSIZE];
	struct ip		*ip;
	struct icmp		*icmp;
}				t_ping_packet;

typedef struct s_ping
{
	int				count_max;
	int				interval;
	int				h;
	int				v;
	int				q;
	int				d;
	int				ttl;
	struct addrinfo	*info;
	struct timeval	launch_time;
	struct timeval	before;
	struct timeval	after;
	double			rtt_min;
	double			rtt_max;
	double			rtt_sum;
	double			rtt_sum_sq;
	int				msg_sent;
	int				msg_count;
	int				msg_recv_count;
	char			*fqdn;
	char			*dest;
	char			*dest_ip;
	int				datalen;
	int				sockfd;
	struct sockaddr	*sasend;
	struct sockaddr	*sacrecv;
	socklen_t		salen;
	pid_t			pid;
}				t_ping;

extern t_ping	g_ping;

// libft
void			ft_bzero(void *s, size_t n);
char			*ft_strdup(const char *s1);
int				ft_strlen(const char *str);
int				ft_atoi(const char *str);
void			*ft_memset(void *pointer, int value, size_t count);

// ft_ping
int				get_args(t_ping *ping, int ac, char **av);
void			init_ping(t_ping *ping);
void			free_args(t_ping *ping);
char			*set_inetaddr(struct sockaddr *sa);
int				ping(t_ping *ping);
void			recv_msg(t_ping *ping, t_ping_packet *pckt);
struct addrinfo	*reverse_dns_info(char *host, char *serv, int family, int socktype);
char			*get_fqdn_info(struct sockaddr *addr);
void			send_msg(void);
int				set_socket(t_ping *ping);
void			print_final_stats(t_ping *ping);
void			catch_sigint(int signal);
void			catch_sigalrm(int signal);
unsigned short	checksum(void *b, int len);
void			print_usage(void);
void			ping_timer(int interval);

#endif