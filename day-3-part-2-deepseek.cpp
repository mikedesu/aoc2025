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

unsigned long long get_largest_dp() {
    int len = n.length();
    int desired_count = 12;
    
    // Initialize DP table
    for(int i=0; i<=len; i++) {
        for(int j=0; j<=desired_count; j++) {
            dp[i][j] = 0;
        }
    }
    
    // Base case: single digit
    for(int i=0; i<len; i++) {
        dp[i][1] = nums[i];
    }
    
    // Fill table bottom-up
    for(int j=2; j<=desired_count; j++) {
        for(int i=0; i<=len-j; i++) {
            // Option 1: Take current digit and take j-1 more digits from remaining
            unsigned long long take = nums[i] * power10(j-1) + dp[i+1][j-1];
            // Option 2: Skip current digit and take j digits from remaining
            unsigned long long skip = dp[i+1][j];
            
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

    unsigned long long sum = 0;
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

        unsigned long long largest = get_largest_dp();
        cout << largest << endl;
        sum += largest;
    }
    fclose(infile);

    cout << sum << endl;


    return 0;
}
