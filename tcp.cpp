#include "tcp.h"

void tcp_client ()
{
    std::cout << "client"<< std::endl;
    std::string addr;
    std::cin >> addr;
    int Socket = socket(
        AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP);
    struct sockaddr_in SockAddr;
    struct sockaddr_in SockAddr2;
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(12345);
    inet_pton(AF_INET,addr.c_str(), &SockAddr.sin_addr.s_addr);
    //SockAddr.sin_addr.s_addr = inet_addr(addr.c_str());

    std::cout << connect (Socket, (struct sockaddr *) (&SockAddr), sizeof(SockAddr))<<std::endl;
    unsigned int size;
    recv(Socket, &size, sizeof(unsigned int),MSG_NOSIGNAL);
    recv(Socket, (void*)(&SockAddr2),size,MSG_NOSIGNAL);
    shutdown(Socket, SHUT_RDWR);
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &SockAddr2.sin_addr.s_addr, str, INET_ADDRSTRLEN );
    std::cout << str << std::endl;
    std::cout << ntohs(SockAddr2.sin_port) << std::endl;
}

void tcp_server ()
{
    std::cout << "server" << std::flush;
    int MasterSocket = socket(
        AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP);
    struct sockaddr_in MasterSockAddr;
    struct sockaddr_in SlaveSockAddr;
    unsigned int size;
    MasterSockAddr.sin_family = AF_INET;
    MasterSockAddr.sin_port = htons(12345);
    MasterSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(MasterSocket, (struct sockaddr *)(&MasterSockAddr), sizeof(MasterSockAddr));
    std::cout <<std::endl<< listen(MasterSocket,SOMAXCONN)<< std::endl;
    while (1)
    {
        int SlaveSocket = accept(MasterSocket, (struct sockaddr *)(&SlaveSockAddr), &size);
        std::cout << SlaveSocket << std::endl;
        send(SlaveSocket, &size, sizeof(unsigned int),MSG_NOSIGNAL);
        send(SlaveSocket, (void *)(&SlaveSockAddr),size,MSG_NOSIGNAL);
        close(SlaveSocket);
    }
}