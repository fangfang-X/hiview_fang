#ifndef _rtp_socket_h_
#define _rtp_socket_h_

#if defined(__cplusplus)
extern "C" {
#endif

#include "rtsp-server-st.h"


#define SOCKET_ADDRLEN INET6_ADDRSTRLEN


void rtp_socket_set_port_range(unsigned short base, unsigned short num);
void rtp_socket_get_port_range(unsigned short *base, unsigned short *num);

void rtp_socket_set_multicast_range(const char* multicast, unsigned int num);
void rtp_socket_get_multicast_range(char multicast[SOCKET_ADDRLEN], unsigned int *num);

int socket_addr_setport(struct sockaddr* sa, socklen_t salen, u_short port);
int socket_getpeername(int sock, char ip[SOCKET_ADDRLEN], u_short* port);
int socket_addr_to(const struct sockaddr* sa, socklen_t salen, char ip[SOCKET_ADDRLEN], u_short* port);
int socket_addr_from(struct sockaddr_storage* ss, socklen_t* len, const char* ipv4_or_ipv6_or_dns, u_short port);
int rtp_socket_create(const char* ip, st_netfd_t rtp[2], unsigned short port[2]);

#if defined(__cplusplus)
}
#endif
#endif /* !_rtp_socket_h_ */
