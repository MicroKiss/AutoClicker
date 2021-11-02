#pragma once

#include <chrono>
#include <vector>
#include <iostream>

#include "Cursor.h"




enum HOTKEYS : UINT
{
	START = VK_F9,
	ADDPOINT = int ('D'), //+alt
	RESET = int ('C'), //+alt
	EXIT = VK_ESCAPE,
};


class AutoClicker
{
public:
	AutoClicker ();
	virtual ~AutoClicker ();
	void StartButton ();
	void Start ();
	void Stop ();
	void AddPoint (const POINT& pos);
	void AddCurrentPoint ();
	void ClearPoints ();
	bool IsAlive () const;
	std::vector<POINT> positions;
	void MainLoop ();
	double GetElapsedTime () const;
private:

	void Run ();
	void HandleEvents ();
	void SetupHotkeys ();
	Cursor cursor;
	double lastTick; //ms
	double clickInterval;
	bool alive;
	bool started;
	u_int positionIndex;
};

