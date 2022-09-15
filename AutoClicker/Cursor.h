#pragma once

#include <windows.h>


class Cursor
{
public:
	void SetPosition (const POINT& pos);
	void LeftClick (const POINT& pos);
	void ClickAndDrag (const POINT& pos1, const POINT& pos2);
	void LeftClick ();
	void RightClick (const POINT& pos);
	void RightClick ();
	POINT GetPosition () const;

};

