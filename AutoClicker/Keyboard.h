#pragma once

#include <vector>
#include <windows.h>
#include <string>

class Keyboard
{
public:
	void PressKeysAtOnce (std::vector<WORD> const& keys);
	void PressKey (WORD const& key);
	void Type (std::string str);
	void HoldKey (WORD const& key, DWORD const& duration = 1000.);
};

