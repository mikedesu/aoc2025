#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <climits>
#include <algorithm>

using std::cout;
using std::endl;
using std::max;
using std::string;
using std::vector;
using std::reverse;

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
        string input_num = string(buffer);
        if (input_num.empty()) continue;

        cout << input_num << ": ";

        nums.clear();
        for (char c : input_num) {
            if (c >= '0' && c <= '9') {
                nums.push_back(c - '0');
            }
        }

        string num_str;
        for (int d : nums) {
            num_str += to_string(d);
        }

        string largest = get_largest_subnumber(num_str, 12);
        cout << largest << endl;

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
