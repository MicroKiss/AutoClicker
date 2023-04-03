#pragma once

#include <chrono>
#include <vector>
#include <iostream>
#include <thread>

#include "Cursor.h"
#include "Keyboard.h"
#include "Action.h"

enum HOTKEYS
{
	START,
	ADDLEFTCLICK,
	ADDRIGHTCLICK,
	ADDMESSAGE,
	RESET,
	EXIT ,
	CHANGEINTERVAL
};


class InputBot
{
public:
	InputBot ();
	virtual ~InputBot ();
	void StartButton ();
	void Start ();
	void Stop ();
	void ClearPoints ();
	void ChangeInterval ();
	bool IsAlive () const;
	std::vector<Action> actions;
	void MainLoop ();
	double GetElapsedTime () const;

private:
	void Run ();
	void Drag (POINT const& pos1, POINT const& pos2, DWORD const interval = 1000, unsigned int const parts = 50);
	void DrawCircle (const POINT& pos, double r, size_t sections = 100, unsigned long period = 0);
	void HandleEvents ();
	void HandleAction (Action const& action);
	void AddLeftClick ();
	void AddMessageWrite ();
	void AddRightClick ();
	void SetupHotkeys ();
	Cursor cursor;
	Keyboard keyboard;
	double lastTick; //ms
	double clickInterval;
	bool alive;
	bool started;
	u_int positionIndex;
};

