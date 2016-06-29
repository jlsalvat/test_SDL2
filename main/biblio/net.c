#include <SDL2/SDL_net.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//UDP connection
UDPsocket gOurSocket;
IPaddress gServerIP;
UDPpacket *gPacket;

#define true 1
#define false 0



void CreatePacket( int32_t packetSize )
{
    printf( "\tCreating packet with size: %d\n ", packetSize);
    // Allocate memory for the packet
    gPacket = SDLNet_AllocPacket( packetSize );
    if ( gPacket == NULL )
    {
        printf("\tSDLNet_AllocPacket failed :%d\n ", SDLNet_GetError());
        exit(1);
    }
    // Set the destination host and port
    // We got these from calling SetIPAndPort()
    gPacket->address.host = gServerIP.host;
    gPacket->address.port = gServerIP.port;
}
void OpenPort( int32_t port )
{
    printf("Opening port %d\n",port);
    // Sets our sovket with our local port
    gOurSocket = SDLNet_UDP_Open( port );
    if ( gOurSocket == NULL )
    {
        printf("\tSDLNet_UDP_Open failed : ", SDLNet_GetError());
        exit(1);
    }
}
void SetIPAndPort( const char *ip, uint16_t port )
{
    printf( "Setting IP ( %s ) and port ( %d ) \n", ip, port);

    // Set IP and port number with correct endianess
    if ( SDLNet_ResolveHost(&gServerIP, ip, port )  == -1 )
    {
        printf("\tSDLNet_ResolveHost failed : %s\n" ,SDLNet_GetError());
        exit(1);
    }
}

void InitSDL_Net()
{
    printf("Initializing SDL_net...\n");

    if ( SDLNet_Init() == -1 )
    {
        printf( "\tSDLNet_Init failed : %s\n", SDLNet_GetError());
        exit(1);
    }
}

void net_init( char *ip, int32_t remotePort, int32_t localPort )
{
    printf("Connecting to IP : %s , remote port %d , local port :%d\n", ip, remotePort,localPort);

    // Initialize SDL_net
    InitSDL_Net();
    OpenPort( localPort  );
    SetIPAndPort( ip, remotePort );
    CreatePacket( 512 );

}

// Send data.
int net_send( const char *msg )
{
    // Set the data
    // UDPPacket::data is an Uint8, which is similar to char*
    // This means we can't set it directly.
    //
    // std::stringstreams let us add any data to it using << ( like std::cout )
    // We can extract any data from a std::stringstream using >> ( like std::cin )
    //
    //str

    memcpy(gPacket->data, msg, strlen(msg));
    gPacket->len = strlen(msg);

    printf("==========================================================================================================\n");
    printf(" Sending %d char : %s \n",gPacket->len,gPacket->data);
           // Send
           // SDLNet_UDP_Send returns number of packets sent. 0 means error
           if ( SDLNet_UDP_Send(gOurSocket, -1, gPacket) == 0 )
{
    printf( "\tSDLNet_UDP_Send failed : %s\n" ,SDLNet_GetError());
        return 0;
    }
    else
        return gPacket->len;
}
int net_CheckForData(const char *msg)
{
    int len=0;
    //printf("Check for data...\n");

    // Check t see if there is a packet wauting for us...
    if ( SDLNet_UDP_Recv(gOurSocket, gPacket))
    {
        printf( "\tData received : %d\n ", gPacket->len);
    strcpy(msg,gPacket->data);
    len=gPacket->len;
    }

    return len;
}
void net_cleanup()
{
    SDLNet_FreePacket(gPacket);
    SDLNet_Quit();
}

