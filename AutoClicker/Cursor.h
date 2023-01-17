#pragma once

#include <windows.h>

class Cursor
{
public:
	void SetPosition (POINT const& pos);
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

