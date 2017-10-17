#include "options.h"
#include<string>

using namespace std;

std::optional<std::tuple<Order, Filter, Case, char *>> options::parse(int argc, char * argv[])
{
	Order order { Order::ascending };
	Filter filter { Filter::all };
	Case compare { Case::sensitive };
	char * input { nullptr };

	// parse commandline options

	if (argc == 2) {

		//*input = nullptr;

		if (argv[1] == string("-r")) {
			order = { Order::descending };
		}

		else if (argv[1] == string("-u")) {
			filter = { Filter::unique };
		}

		else if (argv[1] == string("-i")) {
			compare = { Case::ignore };
		}
	}

	return std::make_tuple(order, filter, compare, input);
}
