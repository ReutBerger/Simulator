#include <vector>
#include <unordered_map>
#include <unistd.h>

#include "Parser.h"

using namespace std;

Parser fileParser;

int main(int argc, char *argv[]) {


    // read file and initialize the vector
    vector<string> arrayVector = fileParser.lexer(argv[1]);
for (auto i = arrayVector.begin(); i != arrayVector.end(); i++) {
    cout << *i << ',';
}
    // Execute all commands from the vector
    fileParser.parser(arrayVector);

sleep(3600);

    return 0;
}