//#ifndef NET_h
//#define NET_h


// SLDSNetCLientOrServer
void net_init( char *ip, int32_t remotePort, int32_t localPort );

// Send data.
int net_send( const char *msg );

//verify if data is present
int net_CheckForData(const char *msg);

// erase structures used for netting
void net_cleanup();

//#endif
