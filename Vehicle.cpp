#include "Vehicle.h"
#include "Waypoint.h"

#define NORMAL_MAX_SPEED 200




HRESULT	Vehicle::initMesh(ID3D11Device* pd3dDevice, carColour colour)
{
	m_scale = XMFLOAT3(30, 20, 1);

	if (colour == carColour::redCar)
	{
		setTextureName(L"Resources\\car_red.dds");
	}
	else if (colour == carColour::blueCar)
	{
		setTextureName(L"Resources\\car_blue.dds");
	}

	HRESULT hr = DrawableGameObject::initMesh(pd3dDevice);

	m_maxSpeed = NORMAL_MAX_SPEED;
	setMaxSpeed(m_maxSpeed);

	m_currentSpeed = m_maxSpeed;
	setVehiclePosition(Vector2D(0, 0));

	m_lastPosition = Vector2D(0, 0);

	return hr;
}

void Vehicle::update(const float deltaTime)
{
	// consider replacing with force based acceleration / velocity calculations
	Vector2D vecTo = m_positionTo - m_currentPosition;
	float velocity = deltaTime * m_currentSpeed;

	float length = (float)vecTo.Length();

	switch (state)
	{
	case SEEK:
		Seek(m_positionTo);
		break;
	case ARRIVE:
		Arrive(m_positionTo);
		break;
	case WANDER:
		Wander();
		break;
	case PURSUIT:
		Pursuit(m_positionTo);
		break;
	case FLEE:
		Flee(m_positionTo);
		break;
	case OBSTACLEAVOIDANCE:

		break;
	default:
		break;
	}
	
	// if the distance to the end point is less than the car would move, then only move that distance. 
	if (length > 0) {
		vecTo.Normalize();
		if(length > velocity)
			vecTo *= velocity;
		else
			vecTo *= length;

		m_currentPosition += vecTo;
	}


	// rotate the object based on its last & current position
	Vector2D diff = m_currentPosition - m_lastPosition;
	if (diff.Length() > 0) { // if zero then don't update rotation
		diff.Normalize();
		m_radianRotation = atan2f((float)diff.y, (float)diff.x); // this is used by DrawableGameObject to set the rotation
	}
	m_lastPosition = m_currentPosition;

	// set the current poistion for the drawablegameobject
	setPosition(Vector2D(m_currentPosition));

	DrawableGameObject::update(deltaTime);
}


// a ratio: a value between 0 and 1 (1 being max speed)
void Vehicle::setCurrentSpeed(const float speed)
{
	m_currentSpeed = m_maxSpeed * speed;
	m_currentSpeed = max(0, m_currentSpeed);
	m_currentSpeed = min(1, m_currentSpeed);
}

// set a position to move to
void Vehicle::setPositionTo(Vector2D position)
{
	m_startPosition = m_currentPosition;
	
	m_positionTo = position;
}

// set the current position
void Vehicle::setVehiclePosition(Vector2D position)
{
	m_currentPosition = position;
	m_positionTo = position;
	m_startPosition = position;
	setPosition(position);
}

void Vehicle::setWaypointManager(WaypointManager* wpm)
{
	m_waypointManager = wpm;
}

//void Vehicle::Velocity(const float deltaTime)
//{
//	m_velocity.x = deltaTime * m_currentSpeed;
//	m_velocity.y = deltaTime * m_currentSpeed;
//}

void Vehicle::Seek(Vector2D position)
{
	state = CarStates::SEEK;

	Waypoint* wp = m_waypointManager->getNearestWaypoint(position);
	m_positionTo = wp->getPosition();
}

void Vehicle::Arrive(Vector2D position) // TODO : General concept present, code not actually applying a speed decrease currently
{
	state = CarStates::ARRIVE;

	Vector2D vecTo = position - m_currentPosition;
	float length = (float)vecTo.Length();

	float speed = length * 0.3;
	Vector2D desiredVelocity = position * speed / length;	

	if (length > 0)
	{
		Waypoint* wp = m_waypointManager->getNearestWaypoint(position);
		// apply speed/desiredVelocity/force here
		m_positionTo = wp->getPosition();
		vecTo = m_positionTo - m_currentPosition;
		length = (float)vecTo.Length();
	}
}

void Vehicle::Wander()
{
	state = CarStates::WANDER;

	Vector2D vecTo = m_positionTo - m_currentPosition;
	float length = (float)vecTo.Length();

	if (length < 5)
	{
		Waypoint* wp = m_waypointManager->getRandomWaypoint();
		m_positionTo = wp->getPosition();
		vecTo = m_positionTo - m_currentPosition;
		length = (float)vecTo.Length();
	}	
}

void Vehicle::Flee(Vector2D targetPosition) // TODO : Not working // drawable game object? // find direction of red car, find inverse for blue car and length to go to mag 1 and then subtract length
{
	state = CarStates::FLEE;

	Vector2D vecTo = m_currentPosition - targetPosition;
	float length = (float)vecTo.Length();

	if (length < 2)
	{
		Waypoint* wp = m_waypointManager->getRandomWaypoint();
		m_positionTo = wp->getPosition();
	}
	else
	{
		m_positionTo = m_currentPosition;
	}

	//Vector2D desiredVelocity = Vec2DNormalize(m_currentPosition - m_positionTo * m_maxSpeed);
	//return (desiredVelocity - m_velocity);

	//Waypoint* wp = m_waypointManager->getRandomWaypoint();
	//m_positionTo = wp->getPosition();
}

void Vehicle::Pursuit(Vector2D targetPosition) // not working but concept is there, find position of red car and move towards position
{
	state = CarStates::PURSUIT;

	Vector2D vecTo = m_positionTo - m_currentPosition;
	float length = (float)vecTo.Length();

	if (length < 10)
	{
		Waypoint* wp = m_waypointManager->getNearestWaypoint(targetPosition);
		m_positionTo = wp->getPosition();
		vecTo = m_positionTo - m_currentPosition;
		length = (float)vecTo.Length();
	}
}