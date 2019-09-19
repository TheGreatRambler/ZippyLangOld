#pragma once

#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include "helpers/utils.hpp"

// Basic might work
std::regex IS_INPUT_LINE("\\s*\\].+\\s*", std::regex::basic);
std::regex MATCH_VARIABLES("{[^{}]+}", std::regex::basic);

// This will become the inbuilt function to add an input
std::string INPUT_FUNCTION_NAME = "ADD_INPUT";
std::string FOR_FUNCTION_NAME = "FOR";

std::string CoverLangConstructs(std::string stringToParse) {
	// First and only for now, FOR
	if (stringToParse.find(FOR_FUNCTION_NAME + "(") != std::string::npos) {
		// This is a for loop
		int beginForLoopInternal = stringToParse.find_first_of("(");
		int endForLoopInternal = stringToParse.find_last_of(")");
		std::string forLoopInternal = stringToParse.substr(beginForLoopInternal + 1, endForLoopInternal - beginForLoopInternal);
		// Send one big line
		std::string result = "for(const i=0;i<" + forLoopInternal + ";i++){";
		return result;
	}
	return stringToParse;
}

std::string ConvertInputLinesIfNeeded(std::string stringToParse) {
	std::smatch returnedMatch;
	if (std::regex_search(stringToParse, returnedMatch, IS_INPUT_LINE)) {
		// There is a match
		std::string match = returnedMatch.str();
		// Build string
		std::string parsedText = INPUT_FUNCTION_NAME + "('" + UTILS::trim(match).substr(1) + "');";
		std::smatch variableMatch;
		while (std::regex_match(parsedText, variableMatch, MATCH_VARIABLES)) {
			std::string thisMatch = variableMatch.str();
			// Removes first and last char
			UTILS::replace(parsedText, thisMatch, "'+" + thisMatch.substr(1, thisMatch.size() - 2) + "+'");
		}

		return parsedText;
	}
	// This is not an input line
	return stringToParse;
}

// Parse the lines to account for input lines
std::vector<std::string> ParseScript(std::string filename) {
	// The lines
	std::vector<std::string> scriptLines;
	std::ifstream fileStream(filename);
	if (fileStream.is_open()) {
		std::string line;
		while (std::getline(fileStream, line)) {
			// `line` is the current line
			// Now it is converted
			std::string parsedLine = ConvertInputLinesIfNeeded(line);
			// Deal with lang contructs
			parsedLine = CoverLangConstructs(parsedLine);
			// Add to script lines
			scriptLines.push_back(parsedLine);
		}
		fileStream.close();
	}
	return scriptLines;
}
