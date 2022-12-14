#include "Cursor.h"
#include <iostream>

void Cursor::SetPosition (const POINT& pos)
{
	SetCursorPos (pos.x, pos.y);
}


void Cursor::LeftClick (const POINT& pos)
{
	SetPosition (pos);
	LeftClick ();
}


void Cursor::ClickAndDrag (POINT const& pos1, POINT const& pos2, DWORD const interval, unsigned int const parts)
{
	float xDif = pos2.x - pos1.x;
	float yDif = pos2.y - pos1.y;

	SetPosition (pos1);
	mouse_event (MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

	for (unsigned int i = 0; i < parts; ++i) {
		SetPosition ({long (pos1.x + xDif / parts * i), long (pos1.y + yDif / parts * i)});
		Sleep (interval / parts);
	}

	mouse_event (MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}


void Cursor::LeftClick ()
{
	std::cout << "leftClick\n";
	mouse_event (MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event (MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}


void Cursor::RightClick (const POINT& pos)
{
	SetPosition (pos);
	RightClick ();
}


void Cursor::RightClick ()
{
	mouse_event (MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	mouse_event (MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}


POINT Cursor::GetPosition () const
{
	POINT p;
	GetCursorPos (&p);
	return p;
}
