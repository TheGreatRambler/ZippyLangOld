#include <string.h>
#include <vector>
#include <string>

#include "QuickJS/quickjs.h"

#include "helpers/utils.hpp"

#include "parser.hpp"

JSRuntime* currentJSRuntime;
JSContext* currentJSContext;

std::string currentFolder;

std::vector<std::string> generatedScript;

const std::string INPUT_NAME = "ADD_INPUT";
const std::string BLANK_NAME = "BLANK";
const std::string IMPORT_NAME = "IMPORT";

unsigned int frameNum = 0;

void RunScript(std::string filepath) {
  // Will be called recursively if the script does so
  std::vector<std::string> lines = ParseScript(filepath);
  // Parsed lines will now be executed
  // Join them together
  std::string script = UTILS::joinVectorOfStrings(lines, "\n");
  // Run the code in the context
  JS_Eval(currentJSContext, script.c_str(), script.size(), filepath, JS_EVAL_TYPE_GLOBAL);
}

void StartEvaluating(std::string fileName, std::string folder) {
  // Create runtime
  currentJSRuntime = JS_NewRuntime();
  // Create context
  currentJSContext = JS_NewContext(currentJSRuntime);
  // Set current folder
  currentFolder = folder;
  // Add built-in functions
  AddAllCFunctions();
  // Start running
  RunScript(folder + UTILS::separator() + fileName);
}

void WriteGeneratedFile(std::string fileName) {
  std::string generatedString = UTILS::joinVectorOfStrings(generatedScript, "\n");
  // Write file
  std::ofstream out(currentFolder + UTILS::separator() + fileName);
  // Write all the text at once
    out << generatedString;
  // Close the file
    out.close();
}

void AddAllCFunctions() {
  // Global object
  JSValue global_obj = JS_GetGlobalObject(currentJSContext);
  
  // Add all the functions
  JSValue inputFunc = JS_NewCFunction(currentJSContext, AddLine, INPUT_NAME, 1);
  JSValue blankFunc = JS_NewCFunction(currentJSContext, AddBlank, BLANK_NAME, 1);
  JSValue importFunc = JS_NewCFunction(currentJSContext, ImportFile, IMPORT_NAME, 1);
  
  // Add to global object
  JS_SetPropertyStr(ctx, global_obj, INPUT_NAME, inputFunc);
  JS_SetPropertyStr(ctx, global_obj, BLANK_NAME, blankFunc);
  JS_SetPropertyStr(ctx, global_obj, IMPORT_NAME, importFunc);
}

JSValue AddLine(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  const char *str = JS_ToCString(currentJSContext, argv[0]);
  std::string input = std::string(str);
  // Current frame: frameNum
  // The input needs to be parsed, but I don't know how to do that yet
  generatedScript.push_back(std::to_string(frameNum) + " " + input);
  // Increment frame
  frameNum++;
  // Should free string
  JS_FreeCString(currentJSContext, str);
  return JS_UNDEFINED;
}

JSValue AddBlank(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  unsigned int timeToDelay;
  JS_ToInt32(currentJSContext, &timeToDelay, argv[0]);
  // Delay the frame that much
  frameNum += timeToDelay;
  return JS_UNDEFINED;
}

JSValue ImportFile(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  const char *str = JS_ToCString(currentJSContext, argv[0]);
  std::string fileName = std::string(str);
  std::string filePath = currentFolder + UTILS::separator() + fileName;
  // Run this script recursively
  RunScript(filePath);
  // Should free string
  JS_FreeCString(currentJSContext, str);
  return JS_UNDEFINED;
}
