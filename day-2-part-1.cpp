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


size_t total_invalid_ids = 0;
long int sum_invalid_ids = 0;


bool all_repeating_digits(string& n) {
    char c = n[0];
    for (int i = 1; i < n.length(); i++) {
        if (n[i] != c) {
            return false;
        }
    }
    return true;
}


bool equal_halves(string& n) {
    size_t len = n.length() / 2;
    string sub_n0 = n.substr(0, len);
    string sub_n1 = n.substr(len, len);
    return sub_n0 == sub_n1;
}


bool is_valid_id(long int id) {
    string n = to_string(id);
    if (n.length() == 1) {
        // are single-digit ids valid?
        // we will assume yes
        return true;
    } else if (n.length() == 2) {
        if (n[0] == n[1]) {
            total_invalid_ids++;
            return false;
        }
        return true;
    } else if (n.length() == 3) {
        return true;
    }

    if (n.length() % 2 == 0) {
        for (long int i = 1; i <= n.length() / 2; i++) {
            if (equal_halves(n)) {
                total_invalid_ids++;
                return false;
            }
        }
    }
    return true;
}


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

    string buf_str = string(buffer);
    vector<string> tokens = split_str(buf_str, ',');

    for (auto token : tokens) {
        vector<string> params = split_str(token, '-');
        string top = params[0];
        string bottom = params[1];
        char* end_ptr = NULL;
        const long int top_n = strtol(top.c_str(), &end_ptr, 10);
        const long int bottom_n = strtol(bottom.c_str(), &end_ptr, 10);

        for (long int id = top_n; id <= bottom_n; id++) {
            if (!is_valid_id(id)) {
                sum_invalid_ids += id;
            }
        }
    }
    printf("Total invalid ids: %ld\n", total_invalid_ids);
    printf("Sum invalid ids: %ld\n", sum_invalid_ids);
    return 0;
}
