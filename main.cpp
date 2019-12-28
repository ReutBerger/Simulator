#include <vector>
#include <unordered_map>
#include <unistd.h>

#include "FileParser.h"

using namespace std;


int main(int argc, char *argv[]) {

    FileParser fp;

    // read file and initialize the vector
    vector<string> arrayVector = fp.lexer(argv[1]);

    // Execute all commands from the vector
    fp.parser(arrayVector);

sleep(3600);

    return 0;
}