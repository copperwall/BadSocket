#include "Socket.h"

#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

Socket::Socket() : MAXREAD(2048)
{
    if ((_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        throw SocketFailure();
    }

    // This part is from Beej's Guide to Networking
    int yes = 1;
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        throw SocketFailure();
    }
};

void Socket::connect(std::string host, uint16_t port)
{
    hostent *ent = gethostbyname(host.c_str());
    if (!ent) {
        throw SocketFailure();
    }

    sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr = *((struct in_addr *)ent->h_addr);

    // This is necessary?
    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));

    if(::connect(_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        throw SocketFailure();
    }
}

void Socket::disconnect()
{
    close(_socket);
}

std::string Socket::read() {
   char buf[MAXREAD];
   unsigned int bytes;

   if ((bytes = recv(_socket, buf, MAXREAD - 1, 0)) == -1) {
      throw SocketFailure();
   }

   if (bytes > 0) {
      return std::string(buf);
   }

   // If no bytes are read then close socket
   disconnect();

   return "";
}

void Socket::write(std::string data) {
   if (send(_socket, data.c_str(), data.size(), 0) == -1) {
      throw SocketFailure();
   }
}

const char *Socket::SocketFailure::what() const noexcept
{
    return "Could not open socket";
};
