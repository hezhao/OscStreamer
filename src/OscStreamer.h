/*
* OscStreamer.h
*
* Copyright (c) 2015 Zhao He, Wieden+Kennedy
*
*/

#ifndef __OSCSTREAMER_H__
#define __OSCSTREAMER_H__

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#define OSC_MESSAGE_ADDRESS         "/transformation"
#define DEFAULT_OSC_CLIENT_IP       "192.168.1.255"
#define DEFAULT_OSC_CLIENT_PORT     3000
#define OUTPUT_BUFFER_SIZE          1024

// required windows libs for oscpack
#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")
#endif

class OscStreamer 
{
private:
     UdpTransmitSocket *transmitSocket;
     const char *oscClientIP;
     int  oscClientPort;
public:
    OscStreamer();
    OscStreamer( const char *ip );
    OscStreamer( const char *ip, int port );
    ~OscStreamer();
    void init();
	void send(int x);
    void send( int ID, int isTracked, float x, float y, float z, float qx, float qy, float qz, float qw);
	const char *getClientIP();
	int getClientPort();
};


#endif
