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


bool CompareStringCaseInsensitive(const std::string& lhs, const std::string& rhs) {

	std::string::size_type common_length = std::min(lhs.length(), rhs.length());

	for (std::string::size_type i = 0; i<common_length; ++i) {
		if (toupper(lhs[i]) < toupper(rhs[i]))return true;
		if (toupper(lhs[i]) > toupper(rhs[i]))return false;
	}

	if (lhs.length()<rhs.length())return true;
	if (lhs.length()>rhs.length())return false;

	return false;
}


bool sort::process(Order order, Filter filter, Case compare, std::istream & input, std::ostream & output)
{
	std::vector<std::string> lines { std::istream_iterator<Line>(input), std::istream_iterator<Line>() };

	// implementation of sorting

	if (compare == Case::ignore) {
		std::sort(lines.begin(), lines.end(), CompareStringCaseInsensitive);
	}

	else {
		std::sort(lines.begin(), lines.end());
	}

	if (order == Order::descending) {
		std::reverse(lines.begin(), lines.end());
	}

	if (filter == Filter::unique) {
			lines.erase(std::unique(lines.begin(), lines.end()), lines.end());	
	}

	for (int i = 0; i < lines.size(); i++) {
		output << lines[i] << std::endl;
	}
	
	return true;
}