#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

namespace UTILS {
	const std::string WHITESPACE = " \n\r\t\f\v";

	std::string ltrim(const std::string& s) {
		size_t start = s.find_first_not_of(UTILS::WHITESPACE);
		return (start == std::string::npos) ? "" : s.substr(start);
	}

	std::string rtrim(const std::string& s) {
		size_t end = s.find_last_not_of(UTILS::WHITESPACE);
		return (end == std::string::npos) ? "" : s.substr(0, end + 1);
	}

	std::string trim(const std::string& s) {
		return UTILS::rtrim(UTILS::ltrim(s));
	}

	bool replace(std::string& str, const std::string& from, const std::string& to) {
		size_t start_pos = str.find(from);
		if (start_pos == std::string::npos)
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}

	std::string joinVectorOfStrings(std::vector<std::string> thing, std::string delimiter) {
		std::string result;
		int size = thing.size();
		for (int i = 0; i < size; i++) {
			if (i != size) {
				result += (thing[i] + delimiter);
			} else {
				// This is the last line, so don't add unneccessary delimiter
				result += thing[i];
			}
		}
		return result;
	}

	char separator() {
#ifdef _WIN32
		return '\\';
#else
		return '/';
#endif
	}

	std::string getcwd_string() {
		char buff[PATH_MAX];
		getcwd(buff, PATH_MAX);
		std::string cwd(buff);
		return cwd;
	}
}
