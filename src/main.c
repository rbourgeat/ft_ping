# include "../inc/ft_ping.h"

t_ping g_ping;

int main(int ac, char **av) {
   parse_arg(ac, av); 
   init_socket();
}