#include <string>

#include "third_party/CLI11.hpp"

#include "parser.hpp"

int main(int argc, char** argv) {
    std::string description = "Zippy, a precompiling language to aid in the creation of TAS scripts";
    std::string fileExtension = "zpy";
    
    CLI::App app{description};

    std::string mainFileToParse = "main." + fileExtension;
    app.add_option("-f,--file", mainFileToParse, "Main file of Zippy script");

    CLI11_PARSE(app, argc, argv);
  
    return 0;
}
