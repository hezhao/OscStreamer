/*
* OscStreamer.cpp
*
* Copyright (c) 2015 Zhao He, Wieden+Kennedy
*
*/

#include <iostream>
#include "OscStreamer.h"

OscStreamer::OscStreamer()
{
    this->oscClientIP   = DEFAULT_OSC_CLIENT_IP;
    this->oscClientPort = DEFAULT_OSC_CLIENT_PORT;
}

OscStreamer::OscStreamer(const char *ip)
{
    this->oscClientIP = ip;
    this->oscClientPort = DEFAULT_OSC_CLIENT_PORT;
}

OscStreamer::OscStreamer( const char *ip, int port )
{
    this->oscClientIP   = ip;
    this->oscClientPort = port;
}

OscStreamer::~OscStreamer()
{
    delete this->transmitSocket;
}

void OscStreamer::init()
{
    this->transmitSocket = new UdpTransmitSocket( IpEndpointName( this->oscClientIP, this->oscClientPort ) );
    this->transmitSocket->SetEnableBroadcast(true);
}

void OscStreamer::send(int x)
{
	char buffer[OUTPUT_BUFFER_SIZE];
	osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);

	p << osc::BeginMessage(OSC_MESSAGE_ADDRESS);
	p << x;
	p << osc::EndMessage;

	this->transmitSocket->Send(p.Data(), p.Size());
}

void OscStreamer::send( int ID, int isTracked, float x, float y, float z, float qx, float qy, float qz, float qw)
{
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );

    p << osc::BeginMessage(OSC_MESSAGE_ADDRESS);
    p << ID;
    p << isTracked << x << y << z << qx << qy << qz << qw;
    p << osc::EndMessage;

    this->transmitSocket->Send( p.Data(), p.Size() );
}

const char *OscStreamer::getClientIP()
{
	return this->oscClientIP;
}

int OscStreamer::getClientPort()
{
	return this->oscClientPort;
}