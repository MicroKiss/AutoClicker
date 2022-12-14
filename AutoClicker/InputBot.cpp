#include "InputBot.h"

InputBot::InputBot ()
{
	alive = true;
	started = false;
	SetupHotkeys ();
	lastTick = GetTickCount64 ();
	clickInterval = 1000.;
}


InputBot::~InputBot ()
{
}

void InputBot::StartButton ()
{
	if (started)
		Stop ();
	else
		Start ();
}


void InputBot::Start ()
{
	std::cout << "Started\n";
	positionIndex = 0;
	started = true;
	lastTick = GetTickCount64 ();
}


void InputBot::Stop ()
{
	std::cout << "Stopped\n";
	started = false;
}


void InputBot::AddPoint (const POINT& pos)
{
	std::cout << "point added" << pos.x << " " << pos.y << "\n";
	positions.push_back (pos);
}


void InputBot::AddCurrentPoint ()
{
	AddPoint (cursor.GetPosition ());
}


void InputBot::ClearPoints ()
{
	std::cout << "points cleared\n";
	Stop ();
	positions.clear ();
}

void InputBot::ChangeInterval ()
{
	std::cout << "Enter new clickInterval value (ms) : ";
	std::cin >> clickInterval;
	std::cout << "\nNew clicking interval is set value : " << clickInterval << "\n";
}


bool InputBot::IsAlive () const
{
	return alive;
}


void InputBot::MainLoop ()
{
	while (IsAlive ()) {
		HandleEvents ();
		Run ();
	}
}


double InputBot::GetElapsedTime () const
{
	return GetTickCount64 () - lastTick;
}


void InputBot::Run ()
{
	if (started) {
		// example keyboard event
		////std::vector<WORD> keyInputs = {VK_RIGHT,VK_LEFT};
		////keyboard.PressKeysAtOnce (keyInputs);
		//keyboard.PressKey ('A');
		//Sleep (100);

		//return;
		
		if (GetElapsedTime () > clickInterval) {
			lastTick = GetTickCount64 ();
			if (positions.empty ()) { // click at mouse position
				cursor.LeftClick ();
			} else {
				POINT lastLocation = cursor.GetPosition ();
				cursor.LeftClick (positions[positionIndex]);
				positionIndex = (positionIndex + 1) % positions.size ();
				cursor.SetPosition (lastLocation);
			}
		}
	}
}


void InputBot::HandleEvents ()
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


void InputBot::SetupHotkeys ()
{
	RegisterHotKey (nullptr, HOTKEYS::START, MOD_NOREPEAT, HOTKEYS::START);
	RegisterHotKey (nullptr, HOTKEYS::ADDPOINT, MOD_ALT | MOD_NOREPEAT, HOTKEYS::ADDPOINT);
	RegisterHotKey (nullptr, HOTKEYS::RESET, MOD_ALT | MOD_NOREPEAT, HOTKEYS::RESET);
	RegisterHotKey (nullptr, HOTKEYS::EXIT, MOD_NOREPEAT, HOTKEYS::EXIT);
	RegisterHotKey (nullptr, HOTKEYS::CHANGEINTERVAL, MOD_ALT | MOD_NOREPEAT, HOTKEYS::CHANGEINTERVAL);
}
