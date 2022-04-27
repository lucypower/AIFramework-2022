#pragma once

#include "DrawableGameObject.h"
#include "WaypointManager.h"
#include "Vector2D.h"
#include "Collidable.h"


enum class carColour
{
	redCar,
	blueCar,
};

enum CarStates
{
	SEEK,
	ARRIVE,
	WANDER,
	PURSUIT,
	FLEE,
	OBSTACLEAVOIDANCE
};

class Vehicle : public DrawableGameObject, public Collidable
{
public:
	virtual HRESULT initMesh(ID3D11Device* pd3dDevice, carColour colour);
	virtual void update(const float deltaTime);

	void setMaxSpeed(const float maxSpeed) { m_maxSpeed = maxSpeed; }
	void setCurrentSpeed(const float speed); // a ratio: a value between 0 and 1 (1 being max speed)
	void setPositionTo(Vector2D positionTo); // a position to move to
	void setVehiclePosition(Vector2D position); // the current position - this resets positionTo
	void setWaypointManager(WaypointManager* wpm);
	void hasCollided() {}

	void Velocity(const float deltaTime);

	void Seek(Vector2D position);
	void Wander();
	void Arrive(Vector2D position);
	Vector2D Flee(Vector2D targetPosition);
	void Pursuit();
	void Evade();

protected: // protected methods


protected: // preotected properties
	float m_maxSpeed;
	float m_currentSpeed;
	
	Vector2D m_currentPosition;
	Vector2D m_startPosition;
	Vector2D m_positionTo;
	Vector2D m_lastPosition;
	Vector2D m_velocity;
	WaypointManager* m_waypointManager;

	CarStates state;
};

