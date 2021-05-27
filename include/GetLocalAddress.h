#include <iostream>
#include <iostream>     ///< cout
#include <cstring>      ///< memset
#include <errno.h>      ///< errno
#include <sys/socket.h> ///< socket
#include <netinet/in.h> ///< sockaddr_in
#include <arpa/inet.h>  ///< getsockname
#include <unistd.h>     ///< close
#include<string.h>
#include<netinet/in.h> //#define INET_ADDRSTRLEN 16 #define INET6_ADDRSTRLEN 46
#include <cstring>      ///< memset

int getLocalAddress(std::string& myIP);