//-----------------------------------------------------------------------------
// Torque Shader Engine
// Copyright (C) GarageGames.com, Inc.
//-----------------------------------------------------------------------------

#include "marble.h"

//----------------------------------------------------------------------------

Point3D Marble::getVelocityD() const
{
    // TODO: Implement getVelocityD
    return Point3D();
}

void Marble::setVelocityD(const Point3D&)
{
    // TODO: Implement setVelocityD
}

void Marble::setVelocityRotD(const Point3D&)
{
    // TODO: Implement setVelocityRotD
}

void Marble::applyImpulse(const Point3F& pos, const Point3F& vec)
{
    // TODO: Implement applyImpulse
    Parent::applyImpulse(pos, vec);
}

void Marble::clearMarbleAxis()
{
    // TODO: Implement clearMarbleAxis
}

void Marble::applyContactForces(const Move*, bool, Point3D&, const Point3D&, double, Point3D&, Point3D&, float&)
{
    // TODO: Implement applyContactForces
}

void Marble::getMarbleAxis(Point3D&, Point3D&, Point3D&)
{
    // TODO: Implement getMarbleAxis
}

const Point3F& Marble::getMotionDir()
{
    // TODO: Implement getMotionDir
    return Point3F();
}

bool Marble::computeMoveForces(Point3D&, Point3D&, const Move*)
{
    // TODO: Implement computeMoveForces
    return false;
}

void Marble::velocityCancel(bool, bool, bool&, bool&, Vector<PathedInterior*>&)
{
    // TODO: Implement velocityCancel
}

Point3D Marble::getExternalForces(const Move*, double)
{
    // TODO: Implement getExternalForces
    return Point3D();
}

void Marble::advancePhysics(const Move*, U32)
{
    // TODO: Implement advancePhysics
}