#include "QuickJS/quickjs.h"

#include "helpers/utils.hpp"

#include "parser.hpp"

JSRuntime* currentJSRuntime;
JSContext* currentJSContext;

std::vector<std::string> generatedScript;

JSValue AddLine(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) 

void RunScript(std::string filepath) {
  // Will be called recursively if the script does so
  std::vector<std::string> lines = ParseScript(filepath);
  // Parsed lines will now be executed
  // Join them together
  std::string script = UTILS::joinVectorOfStrings(lines, "\n");
  // Run the code in the context
  JS_Eval(currentJSContext, script.c_str(), script.size(), filepath, JS_EVAL_TYPE_GLOBAL);
}

void StartEvaluating(std::string filepath) {
  // Create runtime
  currentJSRuntime = JS_NewRuntime();
  // Create context
  currentJSContext = JS_NewContext(currentJSRuntime);
}
