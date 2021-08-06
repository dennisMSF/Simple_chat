#include <iostream>
#include <winsock2.h>
using namespace std;
class mensaje{//lo que se va a enviar o leer
    public:
    char oracion[1000];//mesnaje que se va a entrar
    mensaje(){//constructor
        memset(oracion,0,999);//limpia el mensaje
    }
    void imprimir_mensaje_recep(){cout<<"receptado: "<<oracion<<endl;}
    void imprimir_mensaje_envi(){cout<<"enviar: "<<oracion<<endl;}
    void ingresar_mensaje(){cin.getline(oracion,1000);}//entrada de oracion
};
class Socket{
    public:
    SOCKET s;//crea un Socket
    Socket(){
        s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    }
    bool revision_Socket(){
        if(s==INVALID_SOCKET){//validacion de socket
            cout<<"Error en Winsock - Error en Creacion de Socket"<<endl;
            WSACleanup();
            system("PAUSE");
            return 1;
        }
        return 0;
    }

};
class Hosts{
    public:
    struct hostent *host;
    Hosts(){
        cout<<"ingrese la ip"<<endl;
        string str;
        cin>>str;//192.168.1.2
        const char * c = str.c_str();
        host=gethostbyname(c);//establece la ip
    }
    bool revision_hosts(){
        if(host==NULL){
            cout<<"Fallo conectandose al host"<<endl;//revisa el host
            WSACleanup();
            system("PAUSE");
            return 1;
        }
        return 0;
    }
};
class Sockaddrs{
    public:
    SOCKADDR_IN SockAddr;
    Sockaddrs(Hosts &h){
        cout<<"ingrese el port"<<endl;
        int num;
        cin>>num;
        SockAddr.sin_port=htons(num);//determina la puerta
        SockAddr.sin_family=AF_INET;//tipo de conexion
        SockAddr.sin_addr.s_addr=*((unsigned long*)h.host->h_addr);
    }
    bool conectar(Socket s){
        if(connect(s.s,(SOCKADDR*)(&SockAddr),sizeof(SockAddr))!=0){//conexion
            cout<<"Failed to establish connection with server"<<endl;
            WSACleanup();
            system("PAUSE");
            return 1;
        }
        return 0;
    }
};
int send_msg(SOCKET &s){//funcion para enviar mensaje
    mensaje m;
        cout<<"SEND: ";
        m.ingresar_mensaje();
        send(s,m.oracion,strlen(m.oracion),0);
        memset(m.oracion,0,999);//limpia mensaje
}
bool revision_Winsock(){//inicializa winsock
    WSADATA WsaDat;
    if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0){
        cout<<"Error en Winsock- Inicializacion fallida"<<endl;
        WSACleanup();
        system("PAUSE");
        return 1;
    }
    return 0;
}
