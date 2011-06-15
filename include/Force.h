/*
 * May 29, 2005
 */

#pragma once

namespace traer { namespace physics {

/**
 * @author jeffrey traer bernstein
 *
 */
class Force
{
public:
	virtual void turnOn() = 0;
	virtual void turnOff() = 0;
	virtual bool isOn() = 0;
	virtual bool isOff() = 0;
	virtual void apply() = 0;
};

} } // namespace traer::physics