#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include<iostream>
#include <thread>
#include "rec.h"
using namespace std;
//linkear libadvapi32.a
//linkear libmswsock.a
//linkear libwsock32.a
int main(){
    revision_Winsock();//Inicializa winsock
    Socket s , new_socket;//crea sockets
    Sockaddrs server , client;//crea sockaddrs
    int c;
    s.revision_Socket();
    //prepara el socket
    server.constructor();
    //Bind
    if( bind(s.s ,(struct sockaddr *)&server.r , sizeof(server.r)) == SOCKET_ERROR)//hace el bind
    {
        cout<<"falla en bind "<<WSAGetLastError()<<endl;
        return 0;
    }
    //escucha las conexiones
    listen(s.s , 3);

    cout<<"Esperando conexiones"<<endl;

    c = sizeof(struct sockaddr_in);
    new_socket.constructor2(s,client.r,c);
    new_socket.revision_Socket2();

    cout<<"conexion aceptada"<<endl;
    while(true){
        if(receive_msg(new_socket.s)==0)break;//recibe mensajes
    }
    closesocket(s.s);
    WSACleanup();
    system("PAUSE");
    return 0;
}
