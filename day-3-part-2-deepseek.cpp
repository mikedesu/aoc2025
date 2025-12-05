#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <cstdlib>
//#include <unordered_map>


using std::cout;
using std::endl;
using std::max;
using std::string;
//using std::unordered_map;
using std::vector;


vector<int> nums;
string n = "";

//long** grid = NULL;


long get_largest(int i, long total, int desired_count) {
    if (i >= n.length()) {
        return total;
    }
    if (desired_count == 0) {
        return total;
    }
    return max(get_largest(i + 1, total * 10 + nums[i], desired_count - 1), get_largest(i + 1, total, desired_count));
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

    //unsigned long sum = 0;
    //while (!feof(infile)) {
    //    char* ptr = fgets(buffer, 2048, infile);
    //    if (!ptr) {
    //        break;
    //    }
    //    buffer[strlen(buffer) - 1] = 0;
    //    string n = string(buffer);
    //}
    //fclose(infile);

    //n = "987654321111111";
    //n = "987654321111111";
    //n = "811111111111119";
    //n = "234234234234278";
    //n = "818181911112111";
    n = "4346343235149456543445233353534244533333333343433259333326337334334333438332533343452433223352443324";

    const int desired_count = 12;

    // init grid
    //grid = new long*[n.length()];
    //for (int i = 0; i < n.length(); i++) {
    //    grid[i] = new long[desired_count];
    //    for (int j = 0; j < desired_count; j++) {
    //        grid[i][j] = -1;
    //    }
    //}

    // init vector
    nums.clear();
    for (int i = 0; i < n.length(); i++) {
        char c = n[i];
        int val = c - 48;
        nums.push_back(val);
    }

    cout << get_largest(0, 0, 12) << endl;


    // flip a switch on
    //flip_switch(0, n.length());
    //flip_switch(1, n.length());
    //flip_switch(2, n.length());
    //switches[0] = true;
    //switches[1] = true;
    //switches[2] = true;
    //switches[11] = true;

    // count switches on
    //int on_count = get_on_count(n.length());
    //for (int i = 0; i < n.length(); i++) {
    //    if (switches[i]) on_count++;
    //}
    //cout << "On: " << on_count << endl;

    //cout << get_num_from_switches(n.length()) << endl;

    //cout << get_largest(0, 0, n.length()) << endl;

    //for (int i = 0; i < n.length(); i++) {
    //    if (switches[i]) cout << nums[i];
    //}
    cout << endl;

    //vector<long> candidates;
    //if (n.length() == 13) {
    //}

    //vector<long> dropped = drop_all(n);

    //set<long> candidates;

    //get_candidates(n);

    //for (auto candidate : candidates)

    //for (auto it = candidates.rbegin(); it != candidates.rend(); it++) {
    //    auto first = it->first;
    //    auto second = it->second;
    //    cout << first << endl;
    //    cout << second << endl;
    //    break;
    //}

    //for (auto p : candidates) {
    //    cout << p.first << endl;
    //}

    //cout << *candidates.rbegin() << endl;

    //for (auto a : dropped) {
    //    cout << a << endl;
    //}

    //while (n.length() > 12) {
    //    n0 = drop_i(n, 0);
    //}


    //long largest_n = get_largest(n);

    //string n2 = "811111111111119";
    //string n3 = "234234234234278";
    //string n4 = "818181911112111";

    //for (auto c : candidates)
    //    cout << c << endl;
    //printf("Largest: %d\n", get_largest(n2));
    //printf("Largest: %d\n", get_largest(n3));
    //printf("Largest: %d\n", get_largest(n4));


    return 0;
}
