#include <vector>
#include <string>
#include <regex>
#include <fstream>

#include "helpers/utils.hpp"

std::regex IS_INPUT_LINE("\s*].+\s*");
std::regex MATCH_VARIABLES("{[^{}]+}");

// This will become the inbuilt function to add an input
std::string INPUT_FUNCTION_NAME = "ADD_INPUT";
std::string FOR_FUNCTION_NAME = "FOR";

std::string CoverLangConstructs(std::string stringToParse) {
  // First and only for now, FOR
  if (stringToParse.find((FOR_FUNCTION_NAME + "(") != std::string::npos) {
    // This is a for loop
    int beginForLoopInternal = stringToParse.find_first_of("(");
    int endForLoopInternal = stringToParse.find_last_of(")");
    std::string forLoopInternal = stringToParse.substr(beginForLoopInternal, endForLoopInternal);
    // Send one big line
    std::string result = "for(const i=0;i<" + forLoopInternal + ";i++){";
    return result;
  }
  return stringToParse;
}

std::string ConvertInputLinesIfNeeded(std::string stringToParse) {
  std::smatch matches;
  if (std::regex_match(&stringToParse, matches, IS_INPUT_LINE) {
    // There is a match
    std::string match = matches[0].str();
    //Build string
    std::string parsedText = INPUT_FUNCTION_NAME + "('" + UTILS::trim(match).substr(1) + "');";
    std::smatch variableMatches;
    if (std::regex_match(&parsedText, variableMatches, MATCH_VARIABLES)) {
      for (int i = 0; i < variableMatches.size(); i++) {
        std::string thisMatch = variableMatches[i].str();
        // Removes first and last char
        UTILS::replace(parsedText, thisMatch, "'+" + thisMatch.substr(1, thisMatch.size() - 2) + "+'");
      }
    }
    return parsedText;
  }
  // This is not an input line
  returnstringToParse;
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
    file.close();
  }
  return scriptLines;
}
