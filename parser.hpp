#include <vector>
#include <string>
#include <regex>

std::regex IS_INPUT_LINE("\s*].+\s*");
std::regex MATCH_VARIABLES("{[^{}]+}");
/*
function convertInputLines(sourceCodeArray, index) {
  var inputText = sourceCodeArray[index].match(IS_INPUT_LINE);
  if (inputText) {
    // There are inputs in this line that need to be replaced
    // Remove whitespace and ] and turn into function
    var parsedText = INPUT_FUNCTION_NAME + "('" + inputText[0].trim().substr(1) + "');";
    var variables = parsedText.match(MATCH_VARIABLES);
    if (variables) {
      variables.forEach(function(variable) {
        parsedText = parsedText.replace(variable, "'+" + variable.slice(1,-1) + "+'");
      });
    }
    sourceCodeArray[index] = parsedText;
  }
}
*/

void ConvertInputLinesIfNeeded(std::vector<std::string>* 

std::vector<std::string> ParseScript(std::string filename) {

}
