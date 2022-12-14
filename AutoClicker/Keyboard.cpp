#include "Keyboard.h"

void Keyboard::PressKeysAtOnce (std::vector<WORD> const& keys)
{
	std::vector<INPUT> inputs;
	inputs.resize (keys.size () * 2);

	for (auto& key : keys) {
		INPUT input = {};
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = key;
		inputs.push_back (std::move(input));
	}

	for (auto& key : keys) {
		INPUT input = {};
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = key;
		input.ki.dwFlags = KEYEVENTF_KEYUP;
		inputs.push_back (std::move (input));
	}

	UINT uSent = SendInput (inputs.size (), inputs.data(), sizeof (INPUT));

	if (uSent != inputs.size ()) {
		throw;
	}
}


//maybe these are needed for apps to catch the event ?
//UINT PressKeyScan (WORD scanCode)
//{
//	INPUT input[1] = {0};
//	input[0].type = INPUT_KEYBOARD;
//	input[0].ki.wVk = NULL;
//	input[0].ki.wScan = scanCode;
//	input[0].ki.dwFlags = KEYEVENTF_SCANCODE;
//
//	UINT ret = SendInput (1, input, sizeof (INPUT));
//
//	return ret;
//}
//
//UINT ReleaseKeyScan (WORD scanCode)
//{
//	INPUT input[1] = {0};
//	input[0].type = INPUT_KEYBOARD;
//	input[0].ki.wVk = NULL;
//	input[0].ki.wScan = scanCode;
//	input[0].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
//
//
//	UINT ret = SendInput (1, input, sizeof (INPUT));
//
//	return ret;
//}


void Keyboard::PressKey (WORD const& key)
{
	INPUT inputs[2] = {};
	
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = key;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = key;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	UINT uSent = SendInput (ARRAYSIZE (inputs), inputs, sizeof (INPUT));
	if (uSent != ARRAYSIZE (inputs)) {
		throw;
	}
}


void Keyboard::HoldKey (WORD const& key, DWORD const& duration)
{
	INPUT inputs[2] = {};

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = key;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = key;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	UINT uSent = SendInput (1, &inputs[0], sizeof (INPUT));

	Sleep (duration);
	uSent += SendInput (1, &inputs[1], sizeof (INPUT));
	if (uSent != ARRAYSIZE (inputs)) {
		throw;
	}
}
