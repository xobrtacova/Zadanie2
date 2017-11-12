#include "options.h"

#include <iostream>
#include <string>


std::optional<std::tuple<Order, Filter, Case, Filtere, char *>> options::parse(int argc, char * argv[])
{
	Order order { Order::ascending };
	Filter filter { Filter::all };
	Case compare { Case::sensitive };
	Filtere space { Filtere::nospace };
	char * input { nullptr };

	// parse commandline options

	if (argc == 1)
		return std::make_tuple(order, filter, compare, space, input);

	else {
		int pocet = argc, auxi = 0;
		std::string pom = argv[argc - 1], aux = "";
		if (pom.size() > 4) {
			for (size_t i = pom.size() - 4; i < pom.size(); i++)
				aux = aux + pom[i];
			if (aux == std::string(".txt"))
				auxi = 1;
		}

		for (int i = 0; i < argc; i++) {
			if (argv[i] == std::string("-r")) {
				order = Order::descending;
				pocet--;
			}

			else if (argv[i] == std::string("-u")) {
				filter = Filter::unique;
				pocet--;
			}

			else if (argv[i] == std::string("-i")) {
				compare = Case::ignore;
				pocet--;
			}

			else if (argv[i] == std::string("-e")) {
				space = Filtere::empty;
				pocet--;
			}
		}

		if (pocet == 2 && auxi == 1) {
			return std::make_tuple(order, filter, compare, space, argv[argc - 1]);
		}

		else if (pocet == 1)
			return std::make_tuple(order, filter, compare, space, input);

		else
			return {};
	}
}