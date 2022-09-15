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

void Cursor::ClickAndDrag (const POINT& pos1, const POINT& pos2)
{
	static int counter = 0;
	counter++;

	POINT poss1, poss2;
	poss1.x = -970;
	poss1.y = 445;
	if (counter > 4)
		poss1.y -= 50;
	poss2.x = poss1.x;
	poss2.y = poss1.y + 200;

	float xDif = poss2.x - poss1.x;
	float yDif = poss2.y - poss1.y;
	SetPosition (poss1);
	Sleep (30);
	SetPosition ({poss1.x , poss1.y + 10});
	Sleep (1000);
	mouse_event (MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

	for (int i = 0; i < 50; ++i) {
		SetPosition ({long (poss1.x + xDif / 50.0 * i), long (poss1.y + yDif / 50.0 * i)});
		Sleep (60);
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
