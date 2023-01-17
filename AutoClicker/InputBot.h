#pragma once

#include <chrono>
#include <vector>
#include <iostream>

#include "Cursor.h"
#include "Keyboard.h"

enum HOTKEYS
{
	START ,
	ADDPOINT,
	RESET,
	EXIT ,
	CHANGEINTERVAL,
	RECORDMESSAGE
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
	void RecordMessage ();
	bool IsAlive () const;
	std::vector<POINT> positions;
	void MainLoop ();
	double GetElapsedTime () const;

private:
	void Run ();
	void Drag (POINT const& pos1, POINT const& pos2, DWORD const interval = 1000, unsigned int const parts = 50);
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
	std::string message;
};

