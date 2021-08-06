#include <iostream>
#include <winsock2.h>
#include "env.h"
using namespace std;
//linkear libadvapi32.a
//linkear libmswsock.a
//linkear libwsock32.a
int main(){
    if(revision_Winsock()) return 0;//inicializar winsock
    Socket s;
    if(s.revision_Socket()) return 0;//revisar el socket creado
    Hosts h;
    if(h.revision_hosts()) return 0;//revisar el hosts creado
    // Setup our socket address structure
    Sockaddrs r(h);//conecta el hosts
    // Attempt to connect to server
    if(r.conectar(s)) return 0;//conexion
    // If iMode!=0, non-blocking mode is enabled.
    u_long iMode=1;
    ioctlsocket(s.s,FIONBIO,&iMode);
    // Enciar Mensaje
    while(true){
        send_msg(s.s);
    }
    WSACleanup();
    system("PAUSE");
    return 0;
}
