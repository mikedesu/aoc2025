#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <cstdlib>


using std::cout;
using std::endl;
using std::max;
using std::string;
using std::vector;


vector<int> nums;
string n = "";

// this var was declared by deepseek
unsigned long dp[100][13];


// this function was written by deepseek
unsigned long get_largest_dp() {
    int len = n.length();
    int desired_count = 12;
    // Initialize DP table
    for (int i = 0; i <= len; i++) {
        for (int j = 0; j <= desired_count; j++) {
            if (j == 0)
                dp[i][j] = 0;
            else
                dp[i][j] = -1;
        }
    }

    // Fill table bottom-up
    for (int i = len - 1; i >= 0; i--) {
        for (int j = 1; j <= desired_count; j++) {
            // Option 1: Take current digit
            unsigned long take = nums[i] * pow(10, j - 1) + (i + 1 <= len ? dp[i + 1][j - 1] : 0);
            // Option 2: Skip current digit
            unsigned long skip = (i + 1 <= len ? dp[i + 1][j] : 0);
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

    unsigned long sum = 0;
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

        unsigned long largest = get_largest_dp();
        cout << largest << endl;
        sum += largest;
    }
    fclose(infile);

    cout << sum << endl;


    return 0;
}
