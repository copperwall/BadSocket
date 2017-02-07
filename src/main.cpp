#include <iostream>
#include "Socket.h"

using namespace std;

int main()
{
    Socket sock;
    sock.connect("reddit.com", 80);
    sock.disconnect();
    cout << "Hello world!" << endl;
    return 0;
}
