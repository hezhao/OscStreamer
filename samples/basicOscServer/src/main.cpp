/*
* main.cpp
*
* Copyright (c) 2015 Zhao He, Wieden+Kennedy
*
*/

#include <conio.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>
#include "OscStreamer.h"
using namespace std;

int main(int argc, char *argv[])
{
	char *destIp = argv[1];
	char *port = argv[2];

	if (argc == 1) {
		cerr << "Usage: " << endl;
		cerr << "  basicOscServer [destination_ip] [port]" << endl;
		cerr << "  e.g. basicOscServer" << endl;
		cerr << "       basicOscServer 192.168.1.255" << endl;
		cerr << "       basicOscServer 192.168.1.101 3000" << endl;
		cerr << endl;
	}

	OscStreamer *oscStreamer;

	if (destIp == NULL) {
		oscStreamer = new OscStreamer();
	}
	else if (port == NULL) {
		oscStreamer = new OscStreamer(destIp);
	}
	else {
		oscStreamer = new OscStreamer(destIp, atoi(port));
	}

	oscStreamer->init();
	cout << "[basicOscServer] streaming to " << oscStreamer->getClientIP() << ":" << oscStreamer->getClientPort() << "..." << endl;

	int data = 0;

	while (true) {
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << "[basicOscServer] " << data << endl;
		oscStreamer->send(data++);
	}

	delete oscStreamer;
	return 0;
}
