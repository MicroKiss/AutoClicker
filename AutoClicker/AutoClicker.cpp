#include "AutoClicker.h"

AutoClicker::AutoClicker ()
{
	alive = true;
	started = false;
	SetupHotkeys ();
	lastTick = GetTickCount64 ();
	clickInterval = 1000;
}


AutoClicker::~AutoClicker ()
{
}

void AutoClicker::StartButton ()
{
	if (started)
		Stop ();
	else
		Start ();
}


void AutoClicker::Start ()
{
	std::cout << "Started\n";
	positionIndex = 0;
	started = true;
	lastTick = GetTickCount64 ();
}


void AutoClicker::Stop ()
{
	std::cout << "Stopped\n";
	started = false;
}


void AutoClicker::AddPoint (const POINT& pos)
{
	std::cout << "point added" << pos.x << " " << pos.y << "\n";
	positions.push_back (pos);
}


void AutoClicker::AddCurrentPoint ()
{
	AddPoint (cursor.GetPosition ());
}


void AutoClicker::ClearPoints ()
{
	std::cout << "points cleared\n";
	Stop ();
	positions.clear ();
}

void AutoClicker::ChangeInterval ()
{
	std::cout << "Enter new clickInterval value (ms) : ";
	std::cin >> clickInterval;
	std::cout << "\nNew clicking interval is set value : " << clickInterval << "\n";
}


bool AutoClicker::IsAlive () const
{
	return alive;
}


void AutoClicker::MainLoop ()
{
	while (IsAlive ()) {
		HandleEvents ();
		Run ();
	}
}


double AutoClicker::GetElapsedTime () const
{
	return GetTickCount64 () - lastTick;
}


void AutoClicker::Run ()
{
	if (started) {
		INPUT inputs[4] = {};
		ZeroMemory (inputs, sizeof (inputs));

		inputs[0].type = INPUT_KEYBOARD;
		inputs[0].ki.wVk = 'A';

		inputs[1].type = INPUT_KEYBOARD;
		inputs[1].ki.wVk = 'D';

		inputs[2].type = INPUT_KEYBOARD;
		inputs[2].ki.wVk = 'A';
		inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

		inputs[3].type = INPUT_KEYBOARD;
		inputs[3].ki.wVk = 'D';
		inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

		UINT uSent = SendInput (ARRAYSIZE (inputs), inputs, sizeof (INPUT));
		Sleep (10);
		return;
		if (GetElapsedTime () > clickInterval) {
			lastTick = GetTickCount64 ();
			if (positions.empty ())
				cursor.LeftClick ();
			else {
				if (false) {
					cursor.ClickAndDrag (positions[0], positions[1]);
				} else {
				POINT lastLocation = cursor.GetPosition ();
				cursor.LeftClick (positions[positionIndex]);
				positionIndex = (positionIndex + 1) % positions.size ();
				cursor.SetPosition (lastLocation);
				}
			}
		}
	}
}


void AutoClicker::HandleEvents ()
{
	MSG msg;
	while (PeekMessage (&msg, nullptr, 0, 0, PM_REMOVE)) { //get only the keyboard messages
		if (msg.message == WM_TIMER) {
			break;
		}
		TranslateMessage (&msg); // translates virtual-key codes 
		DispatchMessage (&msg);  // dispatches message to window 
		if (msg.message == WM_HOTKEY) {
			switch (msg.wParam) {
				case HOTKEYS::START:
					StartButton ();
					break;
				case HOTKEYS::ADDPOINT:
					AddCurrentPoint ();
					break;
				case HOTKEYS::RESET:
					ClearPoints ();
					break;
				case HOTKEYS::CHANGEINTERVAL:
					ChangeInterval ();
					break;
				case HOTKEYS::EXIT:
					Stop ();
					alive = false;
					break;
			}
		}
	}
}


void AutoClicker::SetupHotkeys ()
{
	RegisterHotKey (nullptr, HOTKEYS::START, MOD_NOREPEAT, HOTKEYS::START);
	RegisterHotKey (nullptr, HOTKEYS::ADDPOINT, MOD_ALT | MOD_NOREPEAT, HOTKEYS::ADDPOINT);
	RegisterHotKey (nullptr, HOTKEYS::RESET, MOD_ALT | MOD_NOREPEAT, HOTKEYS::RESET);
	RegisterHotKey (nullptr, HOTKEYS::EXIT, MOD_NOREPEAT, HOTKEYS::EXIT);
	RegisterHotKey (nullptr, HOTKEYS::CHANGEINTERVAL, MOD_ALT | MOD_NOREPEAT, HOTKEYS::CHANGEINTERVAL);
}
