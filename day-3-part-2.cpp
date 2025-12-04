//#include <cstdio>
#include <algorithm>
#include <iostream>
//#include <memory>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <algorithm>
//#include <set>
#include <unordered_map>
#include <map>


//using std::shared_ptr;
//using std::make_shared;
//using std::copy;
using std::cout;
using std::endl;
using std::max;
//using std::set;
using std::string;
//using std::strtol;
using std::map;
using std::to_string;
using std::unordered_map;
using std::vector;


//int get_largest(string n) {
//    int largest = -1;
//    for (int i = 0; i < n.length() - 1; i++) {
//        char c = n[i];
//        int cn = c - 48;
//        for (int j = i + 1; j < n.length(); j++) {
//            char d = n[j];
//            int dn = d - 48;
//            int combined = 10 * cn + dn;
//            if (combined > largest) {
//                largest = combined;
//            }
//        }
//    }
//    return largest;
//}


void convert_str_to_vector(const string n, vector<long int>& v) {
    v.clear();
    for (int i = 0; i < n.length(); i++)
        v.push_back(n[i] - 48);
}


vector<long> drop_three(vector<long>& v, int i, int j, int k) {
    vector<long> cv(v);
    // erase elements starting with k
    cv.erase(cv.begin() + k);
    cv.erase(cv.begin() + j);
    cv.erase(cv.begin() + i);
    return cv;
}


string join_str(vector<long>& v) {
    string n = "";
    for (auto i : v) {
        n += to_string(i);
    }
    return n;
}


//long get_largest(string &n) {
//}


//void drop_i(string& n, string& target, size_t i) {
//if (n.length() <= 12) {
//    return n;
//}

//if (i < 0 || i >= n.length()) {
//    return "";
//}

//return n.substr(0, i) + n.substr(i + 1);
//return n.substr(0, i).append(n.substr(i + 1));
//    target = n.substr(0, i).append(n.substr(i + 1));
//}


//vector<long> drop_all(string n) {
//    vector<long> numbers;
//    // first num if n.len = 13
//    if (n.length() == 13) {
//        for (int i = 0; i < n.length(); i++) {
//            numbers.push_back(stol(drop_i(n, i)));
//        }
//    } else if (n.length() > 13) {
//        for (int i = 0; i < n.length(); i++) {
//            string n0 = drop_i(n, i);
//            vector<long> tmp = drop_all(n0);
//            numbers.insert(numbers.end(), tmp.begin(), tmp.end());
//        }
//    }
//
//    return numbers;
//}


//unordered_map<long, bool> candidates;

//long candidate = -1;


//void get_candidates(string& n) {
//if (n.length() == 12) {
//    candidates.insert(stol(n));
//    return;
//}

//string n0 = "";
//if (n.length() == 13) {
//    for (int i = 0; i < n.length(); i++) {
//        //candidates[stol(drop_i(n, i))] = true;
//        //n0 = "";
//        //drop_i(n, n0, i);
//        n0 = n.substr(0, i).append(n.substr(i + 1));
//        long potential = stol(n0);
//        //if (potential > candidate) {
//        candidates[potential] = true;
//        //}
//    }
//    return;
//}

//if (n.length() >= 14) {
//for (int i = 0; i < n.length(); i++) {
//drop_i(n, n0, i);
//    n0 = n.substr(0, i).append(n.substr(i + 1));
//    get_candidates(n0);
//}
//}
//}


long get_candidate(string& n, long total, int i, int count) {

    if (count == 12) {
        return total;
    }

    if (i >= n.length()) {
        return 0;
    }

    char c = n[i];
    long c_val = c - 48;

    long new_total = total * 10 + c_val;

    long candidate_0 = get_candidate(n, new_total, i + 1, count + 1);
    long candidate_1 = get_candidate(n, new_total, i + 2, count + 1);
    return max(candidate_0, candidate_1);

    //long max_candidate = -1;
    //for (int j = 1; i + j < n.length(); j++) {
    //    max_candidate = fmax(max_candidate, get_candidate(n, new_total, i + 1, count + 1));
    //}
    //return max_candidate;
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

        long max_candidate = -1;
        for (int i = 0; i < n.length() - 12; i++) {
            //cout << get_candidate(n, 0, i, 0) << endl;
            max_candidate = max(max_candidate, get_candidate(n, 0, i, 0));
        }
        cout << max_candidate << endl;


        //long candidate = -1;
        //for (int i = 0; i <= n.length() - 12; i++) {
        //long c = get_candidate(n, 0, i, 0);
        //candidate = fmax(candidate, c);
        //if (c > candidate) {
        //    candidate = c;
        //}
        //}
        //cout << candidate << endl;
        sum += max_candidate;
    }
    fclose(infile);

    cout << "sum: " << sum << endl;

    //string n = "4346343235149456543445233353534244533333333343433259333326337334334333438332533343452433223352443324";
    //string n   = "4346343235149456543445233353534244533333333343433259333326337334334333438332533343452433223352443324";
    //string n = "4346343935145555591111111111111199999999999999999999999999999";

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
