/*
 * motive.h
 *
 * Copyright (c) 2015 Zhao He, Wieden+Kennedy
 * Copyright (c) 2014 Bjorn Blissing
 *
 */

#ifndef _MOTIVE_H_
#define _MOTIVE_H_

#include <string>
#include <NPTrackingTools.h>

struct RigidBody
{
	float x;
	float y;
	float z;
	float qx;
	float qy;
	float qz;
	float qw;
	float yaw;
	float pitch;
	float roll;
	RigidBody() : x(0.0), y(0.0), z(0.0), qx(0.0), qy(0.0), qz(0.0), yaw(0.0), pitch(0.0), roll(0.0) {}
};

class Motive 
{
	public:
		Motive() : m_projectFile(""), m_initialized(false) {};
		~Motive() { terminate(); }
		int init();
		int isInitialized() const { return m_initialized; }
		int terminate();
		void setProjectFile(std::string filename) { m_projectFile = filename; }
		bool loadRigidBodies(std::string filename);
		bool removeRigidBody(int index);
		bool update();
		bool updateSingleFrame();
		bool isRigidBodyTracked(int index) const;
		int getRigidBodyID(int index) const;
		void getPositionAndOrientation(int index, float& x, float& y, float& z, float& qx, float& qy, float& qz, float& qw, float& yaw, float& pitch, float& roll) const;
		double getTimeStamp() const;
		int getNumberofMarkers() const;
		int getNumberOfCameras() const;
		int getNumberOfRigidBodies() const;
		std::string getNameOfCamera(int id) const;
		std::string getNameOfRigidBody(int id) const;
	protected:
		int checkResult(int result);
		std::string m_projectFile;
	private:
		bool m_initialized;
};

#endif
