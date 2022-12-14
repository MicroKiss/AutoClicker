#pragma once

#include <vector>
#include <windows.h>

class Keyboard
{
public:
	void PressKeysAtOnce (std::vector<WORD> const& keys);
	void PressKey (WORD const& key);
	void HoldKey (WORD const& key, DWORD const& duration = 1000.);
};

