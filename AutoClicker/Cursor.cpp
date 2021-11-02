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
