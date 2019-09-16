var IS_INPUT_LINE = /\s*].+\s*/g;
var MATCH_VARIABLES = /{[^{}]+}/g;
var INPUT_FUNCTION_NAME = "___";

function convertLine(sourceCodeArray, index) {
  var inputText = sourceCodeArray[index].match(IS_INPUT_LINE);
  if (inputText) {
    // There are inputs in this line that need to be replaced
    // Remove whitespace on either side
    inputText.trim();
    // Remove ] and turn into function
    var parsedText = INPUT_FUNCTION_NAME + "('" + inputText.substr(1) + "');";
    var variables = parsedText.match(MATCH_VARIABLES);
    if (variables) {
      variables.forEach(function(variable) {
        parsedText = parsedText.replace(variable, "'+variable.slice(1,-1)+'");
      });
    }
    sourceCodeArray[index] = parsedText;
  }
}
