#include "QuickJS/quickjs.h"

#include "parser.hpp"

JSRuntime* currentJSRuntime = JS_NewRuntime();
JSContext* currentJSContext = JS_NewContext(currentJSRuntime);

void startRunning(std::string filename) {
  std::vector<std::string> lines = 
}
