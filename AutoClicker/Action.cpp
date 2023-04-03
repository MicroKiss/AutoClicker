#include "Action.h"
#include "string"
#include <sstream>

void Action::Write (std::ostream& os) const
{
	os << type;
	for (auto& i : data) {
		os << " " << i;
	}
	os << "\n";
}

void Action::Read (std::istream& is)
{
	std::string line;
	std::getline (is, line);
	std::stringstream ss (line);
	long tmp;
	is >> tmp;
	type = static_cast<ActionType>(tmp);
	std::copy (std::istream_iterator<long> (ss), std::istream_iterator<long> (),
			   std::back_inserter (data));
}