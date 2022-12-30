#include "InputBot.h"
#include <math.h>

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
	std::cout << "point added: x: " << pos.x << " y: " << pos.y << "\n";
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
		if (false){
			DrawCircle (cursor.GetPosition (), 100);
			started = false;
			return;
		}

		POINT lastLocation = cursor.GetPosition ();
		if (GetElapsedTime () > clickInterval) {
			lastTick = GetTickCount64 ();
			if (positions.empty ()) { // click at mouse position
				cursor.LeftClick ();
			} else {
				POINT lastLocation = cursor.GetPosition ();
				cursor.LeftClick (positions[positionIndex]);
				//Drag (lastLocation, positions[positionIndex]);
				positionIndex = (positionIndex + 1) % positions.size ();
				cursor.SetPosition (lastLocation);
			}
		}
	}
}


void InputBot::Drag (POINT const& pos1, POINT const& pos2, DWORD const interval /*1000*/, unsigned int const parts /*50*/)
{
	float xDif = pos2.x - pos1.x;
	float yDif = pos2.y - pos1.y;

	cursor.SetPosition (pos1);
	cursor.LeftDown ();

	for (unsigned int i = 0; i < parts; ++i) {
		cursor.SetPosition ({long (pos1.x + xDif / parts * i), long (pos1.y + yDif / parts * i)});
		Sleep (interval / parts);
	}

	cursor.LeftUp ();
}


void InputBot::DrawCircle (const POINT& pos, double r,size_t sections /* 100 */, unsigned long period /* =0 */)
{
	static const double PI = 3.141593;
	POINT lastLocation = cursor.GetPosition ();

	auto GetCirclePoint = [pos, r](double part)-> POINT {
		return {long (pos.x + r * cos (part)), long (pos.y + r * sin (part))};
	};

	cursor.SetPosition (GetCirclePoint (0));
	cursor.LeftDown ();

	for (unsigned int i = 0; i < sections + 1; ++i) {
		cursor.SetPosition (GetCirclePoint (2*PI*i / sections));
		Sleep (period/ sections);
	}

	cursor.LeftUp ();
	cursor.SetPosition (lastLocation);
	
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
