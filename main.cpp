#include <string>

#include "helpers/utils.hpp"

#include "third_party/CLI11.hpp"

#include "runScript.hpp"

int main(int argc, char** argv) {
	std::string description = "Zippy, a precompiling language to aid in the creation of TAS scripts";
	std::string fileExtension = "zpy";

	CLI::App app { description };

	std::string mainFileToParse = "main." + fileExtension;
	app.add_option("-f,--file", mainFileToParse, "Main file of Zippy script");

	std::string nameOfGeneratedFile = "generated.txt";
	app.add_option("-n,--name", nameOfGeneratedFile, "Name to give to generated script");

	std::string folder = UTILS::getcwd_string();
	app.add_option("-d,--dir", folder, "Directory to run from and cwd otherwise");

	CLI11_PARSE(app, argc, argv);

	// Start running the function
	// Will block entire program while compiling
	StartEvaluating(mainFileToParse, folder);
	// Write generated file because parsing is done
	WriteGeneratedFile(nameOfGeneratedFile);

	return 0;
}
