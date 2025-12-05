#include <iostream>
#include <string>
#include <cstring>
#include <climits>
#include <algorithm>

using std::cout;
using std::endl;
using std::reverse;
using std::string;

using namespace std;

string get_largest_subnumber(const string& num_str, int digits) {
    int len = num_str.length();
    int k = len - digits;

    if (k <= 0) return num_str;

    string result;
    for (char c : num_str) {
        while (!result.empty() && c > result.back() && k > 0) {
            result.pop_back();
            k--;
        }
        result.push_back(c);
    }

    // Ensure exactly 'digits' length
    result = result.substr(0, digits);
    return result;
}

string string_add(const string& a, const string& b) {
    string result;
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
    }

    reverse(result.begin(), result.end());
    return result;
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

    string sum_str;
    while (!feof(infile)) {
        char* ptr = fgets(buffer, 2048, infile);
        if (!ptr) {
            break;
        }
        buffer[strlen(buffer) - 1] = 0;

        string num_str = string(buffer);
        string largest = get_largest_subnumber(num_str, 12);

        // Store sum as string to avoid overflow
        if (sum_str.empty()) {
            sum_str = largest;
        } else {
            sum_str = string_add(sum_str, largest);
        }
    }
    fclose(infile);

    cout << sum_str << endl;

    return 0;
}
