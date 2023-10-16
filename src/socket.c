# include "../inc/ft_ping.h"

extern t_ping g_ping;

unsigned short checksum(unsigned short *buf, int bufsz) {
	unsigned long sum = 0;
	unsigned short result;

	while (bufsz > 1) {
		sum += *buf++;
		bufsz -= 2;
	}

	if (bufsz == 1)
		sum += *(unsigned char *)buf;

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	result = ~sum;
	return (result);
}

void ping_loop() {
	struct msghdr msg;
	struct iovec iov;
	struct icmp icmp;
	struct icmp *icmp_rec;
	char buf[64];
	struct timeval send_time, recv_time;
	struct ip *ip;
	int seq_sum = 1;

	while (1) {
		memset(&iov, 0, sizeof(iov));
		memset(&msg, 0, sizeof(msg));
		memset(&icmp, 0, sizeof(icmp));

		icmp.icmp_type = ICMP_ECHO;
		icmp.icmp_code = 0;
		icmp.icmp_id = getpid();
		icmp.icmp_seq = seq_sum++;
		gettimeofday(&send_time, NULL);
		memcpy(icmp.icmp_data, &send_time, sizeof(struct timeval));

		icmp.icmp_cksum = 0;
		icmp.icmp_cksum = checksum((unsigned short *)&icmp, sizeof(icmp));

		iov.iov_base = buf;
		iov.iov_len = sizeof(buf);

		msg.msg_name = NULL;
		msg.msg_namelen = 0;
		msg.msg_iov = &iov;
		msg.msg_iovlen = 1;
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
		msg.msg_flags = 0;

		if (sendto(g_ping.sockfd, &icmp, sizeof(icmp), 0, (struct sockaddr *)g_ping.res, sizeof(struct sockaddr)) < 0) {
			perror("sendto");
			close(g_ping.sockfd);
			exit(EXIT_FAILURE);
		}

		int nbytes = recvmsg(g_ping.sockfd, &msg, 0);

		if (nbytes < 0) {
			if (errno == EAGAIN)
				printf("Request timeout for icmp_seq\n");
			else
				perror("recvfrom");
			continue;
		}

		gettimeofday(&recv_time, NULL);

		ip = (struct ip *)buf;
		icmp_rec = (struct icmp *)(buf + (ip->ip_hl << 2));
		struct timeval *out = (struct timeval *)(icmp_rec->icmp_data);

		double latency = (recv_time.tv_sec - out->tv_sec) * 1000 + (recv_time.tv_usec - out->tv_usec) / 1000;
		printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.2f ms\n", nbytes, g_ping.ip, icmp.icmp_seq, ip->ip_ttl, latency);

		g_ping.seq++;
		g_ping.total_time += latency;
		if (g_ping.received == 0 || latency < g_ping.min_rtt) {
			g_ping.min_rtt = latency;
		}
		if (g_ping.received == 0 || latency > g_ping.max_rtt) {
			g_ping.max_rtt = latency;
		}
		g_ping.sum_rtt += latency;

		if (g_ping.received > 1) {
			double mean = g_ping.sum_rtt / g_ping.received;
			double squared_diff_sum = 0.0;

			for (int i = 0; i < g_ping.received; i++) {
				double diff = g_ping.latencies[i] - mean;
				squared_diff_sum += diff * diff;
			}

			double squared_std_dev = squared_diff_sum / g_ping.received;
			g_ping.mdev_rtt = squared_std_dev;
		}

		if (g_ping.received < MAX_LATENCIES) {
			g_ping.latencies[g_ping.received] = latency;
		}

		g_ping.received++;
		
		usleep(1000000);
	}
}

void init_socket() {
	g_ping.sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (g_ping.sockfd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	g_ping.timeout = 1;
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if (setsockopt(g_ping.sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)) < 0) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	ping_loop();
}
