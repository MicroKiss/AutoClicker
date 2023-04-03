#pragma once
#include <iostream>
#include <vector>

enum ActionType
{
	LeftClick,
	RightClick,
	MoveCursor,
	LeftDrag,
	Press,
	Write
};


class Action
{
public:
	ActionType type;
	std::vector<long> data;
	void Write (std::ostream& os) const;
	void Read (std::istream& is);
};

