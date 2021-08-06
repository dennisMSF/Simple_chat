#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include<iostream>
#include <thread>
using namespace std;
class mensaje{
    public:
    char oracion[1000];
    mensaje(){
        memset(oracion,0,999);//limpia el mensaje
    }
    void imprimir_mensaje_recep(){cout<<"receptado: "<<oracion<<endl;}
    void imprimir_mensaje_envi(){cout<<"enviar: "<<oracion<<endl;}
    void ingresar_mensaje(){cin.getline(oracion,1000);}
};
class Socket{//crea un socket y algunas de sus funciones
    public:
    SOCKET s;//crea un Socket
    void constructor (){
        s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    }
    void constructor2(Socket d,sockaddr_in &client,int &c){
        s = accept(d.s , (struct sockaddr *)&client, &c);
    }
    bool revision_Socket(){
        if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
        {
            printf("Could not create socket : %d" , WSAGetLastError());
        }
    }
    bool revision_Socket2(){
        if (s == INVALID_SOCKET){
            printf("accept failed with error code : %d" , WSAGetLastError());
        }
    }

};
class Sockaddrs{//sockaddr_in
    public:
    struct sockaddr_in r;
    void constructor(){
        r.sin_family = AF_INET;
        r.sin_addr.s_addr = INADDR_ANY;
        int num;
        cout<<"ingrese el port"<<endl;
        cin>>num;
        r.sin_port = htons( num );
    }
};
bool receive_msg(SOCKET &Socket){//recibe mensajes
        mensaje m;
        int inDataLength=recv(Socket,m.oracion,1000,0);
        m.imprimir_mensaje_recep();
        int error=WSAGetLastError();
        if(error!=WSAEWOULDBLOCK && error!=0){
            cout<<"codigo de error Winsock: "<<error<<endl;
            cout<<"Servidor desconectado!"<<endl;
            return 0;
        }
        return 1;
}
bool revision_Winsock(){//inicializa el winsock
    WSADATA WsaDat;
    if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0){
        cout<<"Error en Winsock- Inicializacion fallida"<<endl;
        WSACleanup();
        system("PAUSE");
        return 1;
    }
    return 0;
}
