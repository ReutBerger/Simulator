#include <vector>
#include <unordered_map>

#include "Parser.h"

using namespace std;

Parser fileParser;

int main(int argc, char *argv[]) {
    try {
        ignore = argc;

        // Read the file and initialize the vector
        vector<string> arrayVector = fileParser.lexer(argv[1]);

        // Execute all commands from the vector
        fileParser.parser(arrayVector);
    } catch (const char * e) {
        cout << e << endl;
    }
    return 0;
}