#include "network.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/in6.h>
#include <sys/socket.h>

void addr_to_str(struct sockaddr *addr, char *res) {

  void *res_addr;
  if (addr->sa_family == AF_INET) {
    struct sockaddr_in *ip4 = (struct sockaddr_in *)addr;
    res_addr = &ip4->sin_addr;
  } else {
    struct sockaddr_in6 *ip6 = (struct sockaddr_in6 *)addr;
    res_addr = &ip6->sin6_addr;
  }

  inet_ntop(addr->sa_family, res_addr, res, INET6_ADDRSTRLEN);
}
