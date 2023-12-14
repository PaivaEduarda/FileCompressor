#include "Point.h"

inline int  Point::Y() 
{ 
	return y; 
}
inline int Point::X() 
{ 
	return x; 
}

void Point::MoveTo(int px, int py)
{
	x = px;
	y = py;
}

void Point::Translate(int dx, int dy)
{
	x += dx;
	y += dy;
}