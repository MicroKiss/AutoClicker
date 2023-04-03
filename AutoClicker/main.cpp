#include <iostream>
#include "InputBot.h"
#include <iostream>

void WriteHelp ()
{
	std::cout << R""""(
	Welcome to MicroKiss's InputBot.
Usage: 
	F9 
		To start, it will automatically click every interval in your all time mouse position
	ctrl + D
		To add a point where the autoclicker should click instead of your all time current  mouse pos
		Note: you can add more points and the clicker will click them in the given sequence
	ctrl + C
		clear points
	ctrl + G
		Set new clicking interval
	ESCAPE
		Shuts down the program
)"""";
}


void WriteGoodbye ()
{
	std::cout << R""""(
	Byeeee
                      (`.-,')
                    .-'     ;
                _.-'   , `,-
          _ _.-'     .'  /._
        .' `  _.-.  /  ,'._;)
       (       .  )-| (
        )`,_ ,'_,'  \_;)
('_  _,'.'  (___,))
 `-:;.-'
)"""";
}


int main ()
{
	WriteHelp ();
	InputBot IB;
	IB.MainLoop ();
	WriteGoodbye ();
}