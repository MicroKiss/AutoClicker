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


void InputBot::ClearPoints ()
{
	Stop ();
	actions.clear ();
	std::cout << "actions cleared\n";
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
		if (started)
			Run ();
	}
}


double InputBot::GetElapsedTime () const
{
	return GetTickCount64 () - lastTick;
}


void InputBot::Run ()
{
		if (false) {
			std::cout << "here\n";
			//example keyboard event
			std::vector<WORD> keyInputs = {VK_LWIN,'R'};
			keyboard.PressKeysAtOnce (keyInputs);
			Sleep (200);
			keyboard.Type ("notepad");
			keyboard.PressKey (VK_RETURN);
			Sleep (200);
			keyboard.Type ("almafa");
			keyboard.PressKey (VK_RETURN);
			Stop ();
			return;
		}

		if (false) {
			DrawCircle (cursor.GetPosition (), 100);
			Stop ();
			return;
		}

		POINT lastLocation = cursor.GetPosition ();
		if (GetElapsedTime () > clickInterval) {
			lastTick = GetTickCount64 ();
			if (actions.empty ()) { // click at mouse position
				cursor.LeftClick ();
			} else {
				//POINT lastLocation = cursor.GetPosition ();
				HandleAction (actions[positionIndex]);
				//cursor.LeftClick ();
				//Drag (lastLocation, actions[positionIndex]);
				positionIndex = (positionIndex + 1) % actions.size ();
				//cursor.SetPosition (lastLocation);
			}
		}
}

void InputBot::HandleAction (Action const& action)
{
	switch (action.type) {
		case LeftClick:
			cursor.SetPosition ({action.data[0], action.data[1]});
			cursor.LeftClick (); 
			break;
		case RightClick:
			cursor.SetPosition ({action.data[0], action.data[1]});
			cursor.RightClick ();
			break;
		case Write:
			keyboard.Type (std::string (action.data.begin (), action.data.end ()));
			break;
		default:
			break;
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


void InputBot::DrawCircle (const POINT& pos, double r, size_t sections /* 100 */, unsigned long period /* =0 */)
{
	static const double PI = 3.141593;
	POINT lastLocation = cursor.GetPosition ();

	auto GetCirclePoint = [pos, r](double part)-> POINT {
		return {long (pos.x + r * cos (part)), long (pos.y + r * sin (part))};
	};

	cursor.SetPosition (GetCirclePoint (0));
	cursor.LeftDown ();

	for (unsigned int i = 0; i < sections + 1; ++i) {
		cursor.SetPosition (GetCirclePoint (2 * PI * i / sections));
		Sleep (period / sections);
	}

	cursor.LeftUp ();
	cursor.SetPosition (lastLocation);

}


void InputBot::AddLeftClick ()
{
	POINT cursorPosition = cursor.GetPosition ();
	Action action;
	action.type = LeftClick;
	action.data = {cursorPosition.x, cursorPosition.y};
	actions.push_back (action);
	std::cout << "added LeftClick action: " << cursorPosition.x << " " << cursorPosition.y << "\n";
}


void InputBot::AddRightClick ()
{
	POINT cursorPosition = cursor.GetPosition ();
	Action action;
	action.type = RightClick;
	action.data = {cursorPosition.x, cursorPosition.y};
	actions.push_back (action);
	std::cout << "added RightClick action: " << cursorPosition.x << " " << cursorPosition.y << "\n";
}


void InputBot::AddMessageWrite ()
{
	std::string message;
	std::cin >> message;
	Action action;
	action.type = Write;
	for (auto& c : message) {
		action.data.push_back (c);
	}
	actions.push_back (action);
	std::cout << "added Write action: " << message << '\n';
}


void InputBot::HandleEvents ()
{
	MSG msg;
	//PeekMessage doesn't block the thread
	if (PeekMessage (&msg, nullptr, 0, 0, PM_REMOVE)) { 
		if (msg.message == WM_HOTKEY) {
			switch (msg.wParam) {
				case START:
					StartButton ();
					break;
				case ADDLEFTCLICK:
					AddLeftClick ();
					break;
				case ADDRIGHTCLICK:
					AddRightClick ();
					break;
				case RESET:
					ClearPoints ();
					break;
				case CHANGEINTERVAL:
					ChangeInterval ();
					break;
				case ADDMESSAGE:
					AddMessageWrite ();
					break;
				case EXIT:
					Stop ();
					alive = false;
					break;
			}
		}
	}
}


void InputBot::SetupHotkeys ()
{
	RegisterHotKey (nullptr, START, MOD_NOREPEAT, VK_F9);
	RegisterHotKey (nullptr, ADDLEFTCLICK, MOD_CONTROL | MOD_NOREPEAT, 'D');
	RegisterHotKey (nullptr, ADDRIGHTCLICK, MOD_CONTROL | MOD_NOREPEAT, 'F');
	RegisterHotKey (nullptr, RESET, MOD_CONTROL | MOD_NOREPEAT, 'C');
	RegisterHotKey (nullptr, EXIT, MOD_CONTROL | MOD_NOREPEAT, VK_ESCAPE);
	RegisterHotKey (nullptr, CHANGEINTERVAL, MOD_CONTROL | MOD_NOREPEAT, 'G');
	RegisterHotKey (nullptr, ADDMESSAGE, MOD_CONTROL | MOD_NOREPEAT, 'R');
}