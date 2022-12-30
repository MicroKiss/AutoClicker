#pragma once

#include <windows.h>

class Cursor
{
public:
	void SetPosition (POINT const& pos);
	void ClickAndDrag (POINT const& pos1, POINT const& pos2, DWORD const interval = 500.0, unsigned int const parts = 50);
	void LeftDown ();
	void LeftUp ();
	void LeftClick ();
	void LeftClick (POINT const& pos);
	void RightDown ();
	void RightUp ();
	void RightClick ();
	void RightClick (POINT const& pos);
	POINT GetPosition () const;
};

