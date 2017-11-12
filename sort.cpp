#include "sort.h"

#include <string>
#include <iterator>
#include <vector>
#include <cctype>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <set>


namespace
{
	struct Line : public std::string {};

	std::istream & operator >> (std::istream & is, Line & line)
	{
		return std::getline(is, line);
	}
}

bool LessCaseInSensitive(const std::string & a, const std::string & b) {
	
	for (const char *ptrA = a.c_str(), *ptrB = b.c_str(); ; ++ptrA, ++ptrB) {

		if (tolower(*ptrA) != tolower(*ptrB) || !*ptrA || !*ptrB) return tolower(*ptrA) < tolower(*ptrB);

	}

	return false;
}

bool sort::LessCaseSensitive(const std::string & a, const std::string & b) {

	for (const char *ptrA = a.c_str(), *ptrB = b.c_str(); ; ++ptrA, ++ptrB) {

		if (*ptrA != *ptrB || !*ptrA || !*ptrB) return *ptrA < *ptrB;

	}

	return false;
}

void Remove_ws(std::vector<std::string> & line) {

	for (std::vector<std::string>::iterator i = line.begin(); i != line.end(); ) {

		int pom = 0;

		for (size_t j = 0; j < (*i).length(); ++j)
			if (std::isspace((*i)[j])) pom++;

		if (pom == (*i).size()) i = line.erase(i);
		else ++i;

	}
}

bool Compare(const std::string & a, const std::string & b) {

	if (a.size() != b.size())
		return false;

	for (unsigned int i = 0; i < a.size(); ++i)
		if (tolower(a[i]) != tolower(b[i])) return false;

	return true;
}


bool sort::process(Order order, Filter filter, Case compare, Filtere space, std::istream & input, std::ostream & output)
{
	std::vector<std::string> lines { std::istream_iterator<Line>(input), std::istream_iterator<Line>() };

	// implementation of sorting

	if (space == Filtere::empty) {
		//lines.erase(std::remove_if(lines.begin(), lines.end(),  ::isspace), lines.end());
		Remove_ws(lines);
	}

	if (compare == Case::ignore) {
		std::sort(lines.begin(), lines.end(), LessCaseInSensitive);
	}

	else {
		std::sort(lines.begin(), lines.end(), sort::LessCaseSensitive);
	}

	if (order == Order::descending) {
		std::reverse(lines.begin(), lines.end());
	}

	if (filter == Filter::unique && compare == Case::ignore) {
		lines.erase(std::unique(lines.begin(), lines.end(), Compare), lines.end());
	}

	else if (filter == Filter::unique && compare == Case::sensitive) {
		lines.erase(std::unique(lines.begin(), lines.end()), lines.end());
	}
	
	for (int i = 0; i < lines.size(); i++) {
		output << lines[i] << std::endl;
	}
	
	return true;
}