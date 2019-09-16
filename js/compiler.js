var IS_INPUT_LINE = /\s*].+\s*/g;
var MATCH_VARIABLES = /{[^{}]+}/g;

var INPUT_FUNCTION_NAME = "___";
var IMPORT_FUNCTION_NAME = "IMPORT(";

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

function convertImportLines(sourceCodeArray, index) {
  var importStatement = sourceCodeArray[index].match(IMPORT_FUNCTION_NAME);
  if (importStatement) {
    var newText = sourceCodeArray[index].replace("IMPORT", "self.importScripts");
    // Extensions arent required, so add them in here
    newText = newText.replace(")", "+'.js')");
    sourceCodeArray[index] = newText;
  }
}

// The compiler function runs in a webworker
