//======================================================================================================-----
// Copyright 2014, NaturalPoint Inc.
//======================================================================================================-----
#pragma once
#ifndef _RIGID_BODY_SOLVER_RIGID_BODY_SETTINGS_H
#define _RIGID_BODY_SOLVER_RIGID_BODY_SETTINGS_H

namespace Core
{
    class cIReader;
    class cIWriter;
}

namespace RigidBodySolver
{
    const int kRigidBodyNameMaxLen = 32;
    const int kRigidBodyModelNameMaxLen = 256;

    class cRigidBodySettings
    {
    public:
        cRigidBodySettings();

        void  Save( Core::cIWriter *serial ) const;
        void  Load( Core::cIReader *serial );

        wchar_t  mName     [kRigidBodyNameMaxLen];
        wchar_t  mModelName[kRigidBodyModelNameMaxLen];

        int   UserData;
        float ColorR;
        float ColorG;
        float ColorB;

        float MaxFrameRotation;             //== deprecated
        float MaxFrameTranslation;          //== deprecated

        bool  DynamicRotationConstraint;    //== deprecated
        bool  DynamicTranslationConstraint; //== deprecated
        int   DynamicConstraintFrames;

        double Smoothing;                   // in the range [0,1]
        double PredictionTime;              // the amount of time to predict the solution forward, in fractional frames

        bool   Visible;
        bool   DisplayUntracked;
        bool   DisplayPivot;
        bool   DisplayUntrackedMarkers;
        bool   DisplayMarkerQuality;
        bool   DisplayQuality;
        bool   DisplayTracked;
        bool   DisplayLabel;
        bool   DisplayOrientation;
        bool   DisplayModelReplace;

        float  ModelYaw;
        float  ModelPitch;
        float  ModelRoll;
        float  ModelX;
        float  ModelY;
        float  ModelZ;
        float  ModelScale;

        bool   DisplayPositionHistory;
        bool   DisplayOrientationHistory;
        int    DisplayHistoryLength;
        int    DisplayOrientationSpread;
        int    DisplayOrientationSize;

        //== Static constraint ==--

        bool    StaticOrientationConstraint;
        double  StaticConstraintX;
        double  StaticConstraintY;
        double  StaticConstraintZ;
        double  StaticConstraintAngle;

        // Solver settings
        bool    Enabled;
        float   MaxMarkerDeflection;
        int     MinimumMarkerCount;
        int     MinimumHitCount;         //== deprecated
        float   Flexibility;
        bool    ShareMarkers;
        bool    Unique;
        double  MaxCalculationTime;
        int     AcquisitionFrames;

        enum eTrackingAlgorithms
        {
            Algorithm_Auto = 0,
            Algorithm_MarkerBased,
            Algorithm_RayBased,
            Algorithm_RayBasedPlus,
            Algorithm_RayBasedUltimate
        };

        eTrackingAlgorithms TrackingAlgorithmLevel;
    };
}

#endif // _RIGID_BODY_SOLVER_RIGID_BODY_SETTINGS_H
