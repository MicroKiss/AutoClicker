#include "Cursor.h"
#include <iostream>

void Cursor::SetPosition (const POINT& pos)
{
	LONG x = pos.x * (65536.0f / GetSystemMetrics (SM_CXSCREEN));
	LONG y = pos.y * (65536.0f / GetSystemMetrics (SM_CYSCREEN));
	INPUT Input = {};
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = x;
	Input.mi.dy = y;
	SendInput (1, &Input, sizeof (INPUT));
}


void Cursor::LeftClick (const POINT& pos)
{
	SetPosition (pos);
	LeftClick ();
}

void Cursor::RightDown ()
{
	INPUT input = {};
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

	SendInput (1, &input, sizeof (INPUT));
}

void Cursor::RightUp ()
{
	INPUT input = {};
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

	SendInput (1, &input, sizeof (INPUT));
}


void Cursor::ClickAndDrag (POINT const& pos1, POINT const& pos2, DWORD const interval, unsigned int const parts)
{
	float xDif = pos2.x - pos1.x;
	float yDif = pos2.y - pos1.y;

	SetPosition (pos1);
	LeftDown ();

	for (unsigned int i = 0; i < parts; ++i) {
		SetPosition ({long (pos1.x + xDif / parts * i), long (pos1.y + yDif / parts * i)});
		Sleep (interval / parts);
	}

	LeftUp ();
}

void Cursor::LeftUp ()
{
	INPUT input = {};
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;

	SendInput (1, &input, sizeof (INPUT));
}

void Cursor::LeftDown ()
{
	INPUT input = {};
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	SendInput (1, &input, sizeof (INPUT));
}


void Cursor::LeftClick ()
{
	LeftDown ();
	LeftUp ();
}


void Cursor::RightClick (const POINT& pos)
{
	SetPosition (pos);
	RightClick ();
}


void Cursor::RightClick ()
{
	INPUT inputs[2] = {};
	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

	inputs[1].type = INPUT_MOUSE;
	inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

	SendInput (2, inputs, sizeof (INPUT));
}


POINT Cursor::GetPosition () const
{
	POINT p;
	GetCursorPos (&p);
	return p;
}
