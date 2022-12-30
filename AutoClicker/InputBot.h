#pragma once

#include <chrono>
#include <vector>
#include <iostream>

#include "Cursor.h"
#include "Keyboard.h"




enum HOTKEYS : UINT
{
	START = VK_F9,
	ADDPOINT = int ('D'), //+alt
	RESET = int ('C'), //+alt
	EXIT = VK_ESCAPE,
	CHANGEINTERVAL = int ('G'), //+alt
};


class InputBot
{
public:
	InputBot ();
	virtual ~InputBot ();
	void StartButton ();
	void Start ();
	void Stop ();
	void AddPoint (const POINT& pos);
	void AddCurrentPoint ();
	void ClearPoints ();
	void ChangeInterval ();
	bool IsAlive () const;
	std::vector<POINT> positions;
	void MainLoop ();
	double GetElapsedTime () const;
private:

	void Run ();
	void DrawCircle (const POINT& pos, double r, size_t sections = 100, unsigned long period = 0);
	void HandleEvents ();
	void SetupHotkeys ();
	Cursor cursor;
	Keyboard keyboard;
	double lastTick; //ms
	double clickInterval;
	bool alive;
	bool started;
	u_int positionIndex;
};

