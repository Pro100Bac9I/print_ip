#include <vector>
#include <list>
#include <tuple>
#include <string>

#include "PrintIP.h"


int main()
{
	print_ip(char(-1));
	print_ip(short(0));
	print_ip(int(2130706433));
	print_ip(long(8875824491850138409));
	print_ip(std::string("12.3.18.10"));
	print_ip(std::vector<int>{15, 13, 10, 255});
	print_ip(std::list<short>{123, 124, 30, 40});
	print_ip(std::make_tuple(1, 2, 3, 4, 5));

	return 0;
}

