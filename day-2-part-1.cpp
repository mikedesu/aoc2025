#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>


using std::string;
using std::vector;


vector<string> split_str(string& str, char delimiter) {
    vector<string> tokens;
    string cur_tok;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != string::npos) {
        cur_tok = str.substr(start, end - start);
        tokens.push_back(cur_tok);
        start = end + 1;
        end = str.find(delimiter, start);
    }
    cur_tok = str.substr(start);
    tokens.push_back(cur_tok);
    return tokens;
}


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

    printf("buffer: %s\n", buffer);

    string buf_str = string(buffer);

    vector<string> tokens = split_str(buf_str, ',');

    for (auto token : tokens) {
        printf("token: %s\n", token.c_str());
    }


    return 0;
}
