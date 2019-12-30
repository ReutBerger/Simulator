#include <vector>
#include <unordered_map>
#include <unistd.h>

#include "Parser.h"

using namespace std;


int main(int argc, char *argv[]) {

    Parser fileParser;

    // read file and initialize the vector
    vector<string> arrayVector = fileParser.lexer(argv[1]);

    // Execute all commands from the vector
    fileParser.parser(arrayVector);

sleep(3600);

    return 0;
}