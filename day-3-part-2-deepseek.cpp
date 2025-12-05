#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <climits>

using std::cout;
using std::endl;
using std::max;
using std::string;
using std::vector;

vector<int> nums;
string n = "";

using namespace std;

unsigned long long dp[105][15]; // dp[i][j] = max number with j digits starting at position i

unsigned long long power10(int exp) {
    unsigned long long result = 1;
    while(exp-- > 0) {
        result *= 10;
    }
    return result;
}

string get_largest_12_digits() {
    string num_str;
    for (int d : nums) {
        num_str += to_string(d);
    }
    int len = num_str.length();
    const int k = len - 12;
    
    if (k <= 0) return num_str;
    
    string result;
    for (char c : num_str) {
        while (!result.empty() && c > result.back() && k > 0) {
            result.pop_back();
            k--;
        }
        result.push_back(c);
    }
    
    // Truncate to exactly 12 digits if needed
    if (result.length() > 12) {
        result = result.substr(0, 12);
    }
    
    return result;
}
    
    return dp[0][desired_count];
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

    unsigned long long sum = 0;
    while (!feof(infile)) {
        char* ptr = fgets(buffer, 2048, infile);
        if (!ptr) {
            break;
        }
        buffer[strlen(buffer) - 1] = 0;
        string input_num = string(buffer);
        if (input_num.empty()) continue;

        cout << input_num << ": ";

        nums.clear();
        for (char c : input_num) {
            if (c >= '0' && c <= '9') {
                nums.push_back(c - '0');
            }
        }

        string largest = get_largest_12_digits();
        cout << largest << endl;
        sum += stoull(largest);
    }
    fclose(infile);

    cout << sum << endl;


    return 0;
}
