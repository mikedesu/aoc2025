#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <cstdlib>


using std::string;
using std::strtol;
using std::to_string;
using std::vector;


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: missing input file\n");
        exit(-1);
    }

    string filename = string(argv[1]);
    printf("Filename: %s\n", filename.c_str());

    FILE* infile = fopen(filename.c_str(), "r");
    if (!infile) {
        fprintf(stderr, "Failed to open %s\n", filename.c_str());
        exit(-1);
    }

    char buffer[2048] = {0};
    fscanf(infile, "%s", buffer);
    fclose(infile);

    return 0;
}
