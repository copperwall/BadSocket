#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <exception>

class Socket
{
    public:
        // I feel like the constructor should create the socket
        Socket();
        void connect(std::string host, uint16_t port);
        void disconnect();
        std::string read();
        void write(std::string data);

        struct SocketFailure : std::exception {
            const char *what() const noexcept;
        };
    private:
        const int MAXREAD;
        int _socket;
};

#endif // SOCKET_H
