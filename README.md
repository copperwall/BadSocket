# BadSocket

I tried writing a Socket class around a really small part of the C socket API.
I originally wanted to try making a C++ IRC bot, but I thought a socket wrapper
might be a good stepping stone to that.

This can currently take a hostname and port and open a TCP connection on that
port. You can't read or write, but that's coming soon :)

My end goal is to be able to connect to an IRC server, and use the Socket
object like an ostream so you could write to it like 

```cpp
Socket sock;
sock.connect("irc.freenode.net", 6667);

sock << "PRIVMSG #" << channel << " :" << message << endl;
```
