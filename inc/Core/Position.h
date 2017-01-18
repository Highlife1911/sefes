#pragma once
#include "RobotinoExtension.h"

/** \class RobotinoExtension::Position
 *	\brief Position class for Navigation.
 *
 *	This object is immutable after its construction. It holds
 *	the basic cartesic Position data but not an angle.
 */

namespace RobotinoExtension
{
class
	EXPORT_CLASS Position
{
public:
	/**
	 *  Constructs a default Position object that can be used as a dummy.
	 */
	Position();


	/**
	 *  Constructs a Position object from coordinates.
	 *
	 *	\param x	X position in m;
	 *	\param y	Y position in m;
	 */
	Position(float x, float y);


	/**
	 *  Destroys the position object.
	 */
	virtual ~Position() = default;


	/**
	 *  Returns the X position in m.
	 */
	float x() const;


	/**
	 *  Returns the Y position in m.
	 */
	float y() const;


	/**
	 *  Computes the catesian distance in meters between 2 instances.
	 */
	float distanceTo(const Position &pos) const;

protected:

	/**
	 *  Raw X position in m.
	 */
	float mX;

	/**
	 *  Raw Y position in m.
	 */
	float mY;
};
}
