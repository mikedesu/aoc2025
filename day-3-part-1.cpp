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


//void read_chars_into_vector(string n, vector<int>& v) {
//    for (int i = 0; i < n.length(); i++) {
//        char c = n[i];
//        int num = c - 48;
//        v.push_back(num);
//    }
//}


//int largest_digit(vector<int>& v) {
//    int largest = -1;
//    int largest_index = -1;
//    for (int i = 0; i < v.size(); i++) {
//        int num = v[i];
//        if (num > largest) {
//            largest = num;
//            largest_index = i;
//        }
//    }
//    v.erase(v.begin() + largest_index);
//    return largest;
//}


//int get_charge(string n, vector<int>& v) {
//    read_chars_into_vector(n, v);
//    int tens = largest_digit(v);
//    int ones = largest_digit(v);
//    int num = tens * 10 + ones;
//    v.clear();
//    return num;
//}


int get_largest(string n) {
    int largest = -1;
    for (int i = 0; i < n.length() - 1; i++) {
        char c = n[i];
        int cn = c - 48;
        for (int j = i + 1; j < n.length(); j++) {
            char d = n[j];
            int dn = d - 48;

            int combined = 10 * cn + dn;

            if (combined > largest) {
                largest = combined;
            }
        }
    }
    return largest;
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

    int sum = 0;
    while (!feof(infile)) {
        char* ptr = fgets(buffer, 2048, infile);
        if (!ptr) {
            break;
        }
        buffer[strlen(buffer) - 1] = 0;

        string n = string(buffer);

        //printf("%s\n", buffer);
        int largest = get_largest(n);
        //printf("%d\n", get_largest(n));
        sum += largest;
    }
    fclose(infile);

    printf("Sum: %d\n", sum);

    //string n1 = "987654321111111";
    //string n2 = "811111111111119";
    //string n3 = "234234234234278";
    //string n4 = "818181911112111";

    //printf("Largest: %d\n", get_largest(n2));
    //printf("Largest: %d\n", get_largest(n3));
    //printf("Largest: %d\n", get_largest(n4));


    return 0;
}
