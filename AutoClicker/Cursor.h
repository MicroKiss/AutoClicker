#pragma once

#include <windows.h>


class Cursor
{
public:
	void SetPosition (const POINT& pos);
	void LeftClick (const POINT& pos);
	void LeftClick ();
	void RightClick (const POINT& pos);
	void RightClick ();
	POINT GetPosition () const;

};

