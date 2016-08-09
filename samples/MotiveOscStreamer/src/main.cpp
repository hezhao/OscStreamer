/*
* main.cpp
*
* Copyright (c) 2015 Zhao He, Wieden+Kennedy
* Copyright (c) 2014 Bjorn Blissing
*
*/

#include <conio.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>
#include "easylogging++.h"
#include "motive.h"
#include "OscStreamer.h"
using namespace std;

INITIALIZE_EASYLOGGINGPP

vector<RigidBody> rigidbodies;

void printRigidBodies()
{
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(100));
		for (int i = 0; i < rigidbodies.size(); i++) {
			RigidBody &r = rigidbodies[i];
			LOG(INFO) << "Rigid Body " << i << setprecision(4) << fixed << " x: " << r.x << ", y: " << r.y << ", z: " << r.z;
		}
	}
}

void streamRigidBodies(Motive *tracker, OscStreamer *oscStreamer)
{
	while (true) {
		if (tracker->update() == true) {
			rigidbodies.clear();
			for (int i = 0; i < tracker->getNumberOfRigidBodies(); i++) {
				RigidBody r;
				tracker->getPositionAndOrientation(i, r.x, r.y, r.z, r.qx, r.qy, r.qz, r.qw, r.yaw, r.pitch, r.roll);
				int ID = tracker->getRigidBodyID(i);
				bool isTracked = tracker->isRigidBodyTracked(i);
				oscStreamer->send(ID, isTracked, r.x, r.y, r.z, r.qx, r.qy, r.qz, r.qw);
				rigidbodies.push_back(r);
			}
		}
	}
}

int main(int argc, char *argv[])
{
	char *projectFile = argv[1];
	char *destIp = argv[2];
	char *port = argv[3];

	if (projectFile == NULL) {
		cerr << "Usage: " << endl;
		cerr << "  MotiveStreamer project_file [destination_ip] [port]" << endl;
		cerr << "  e.g. MotiveStreamer project.ttp" << endl;
		cerr << "       MotiveStreamer project.ttp 192.168.1.255" << endl;
		cerr << "       MotiveStreamer project.ttp 192.168.1.101 3000" << endl;
		cerr << "Press any key to exit..." << endl;
		_getch();
		return -1;
	}

	Motive *tracker = new Motive();
	tracker->setProjectFile(projectFile);
	tracker->init();
	
	int nCameras = tracker->getNumberOfCameras();
	LOG(INFO) << "Number of cameras: " << nCameras;
	for (int i = 0; i < nCameras; ++i) {
		LOG(INFO) << "Camera name (" << i << "): " << tracker->getNameOfCamera(i);
	}

	int nRigidBodies = tracker->getNumberOfRigidBodies();
	LOG(INFO) << "Number of rigid bodies: " << nRigidBodies;
	for (int i = 0; i < nRigidBodies; ++i) {
		LOG(INFO) << "Rigid body name (" << i << "): " << tracker->getNameOfRigidBody(i);
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

	thread t1(streamRigidBodies, tracker, oscStreamer);
	thread t2(printRigidBodies);

	t1.join();
	t2.join();

	delete tracker;
	delete oscStreamer;
	return 0;
}
