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

long long dp[105][15]; // dp[i][j] = max number with j digits starting at position i

long long power10(int exp) {
    long long result = 1;
    while(exp-- > 0) {
        result *= 10;
    }
    return result;
}

long long get_largest_dp() {
    int len = n.length();
    int desired_count = 12;
    
    // If number is 12 digits or shorter, just return the number itself
    if (len <= desired_count) {
        long long result = 0;
        for (int d : nums) {
            result = result * 10 + d;
        }
        return result;
    }

    // Initialize DP table
    for(int i=0; i<=len; i++) {
        for(int j=0; j<=desired_count; j++) {
            dp[i][j] = (j == 0) ? 0 : -1;
        }
    }
    
    // Fill table bottom-up
    for(int i=len-1; i>=0; i--) {
        for(int j=1; j<=desired_count; j++) {
            // Option 1: Take current digit
            long long take = -1;
            if (i+1 <= len && dp[i+1][j-1] != -1) {
                take = nums[i] * power10(j-1) + dp[i+1][j-1];
            }
            
            // Option 2: Skip current digit
            long long skip = (i+1 <= len) ? dp[i+1][j] : -1;
            
            dp[i][j] = max(take, skip);
        }
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

    long long sum = 0;
    while (!feof(infile)) {
        char* ptr = fgets(buffer, 2048, infile);
        if (!ptr) {
            break;
        }
        buffer[strlen(buffer) - 1] = 0;
        string n = string(buffer);

        cout << n << ": ";

        nums.clear();
        for (int i = 0; i < n.length(); i++) {
            char c = n[i];
            int val = c - 48;
            nums.push_back(val);
        }

        long long largest = get_largest_dp();
        cout << largest << endl;
        sum += largest;
    }
    fclose(infile);

    cout << sum << endl;


    return 0;
}
