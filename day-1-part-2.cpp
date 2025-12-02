#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>


using std::string;


class dial {
private:
    int pointing;
    int password;

public:
    dial() {
        pointing = 50;
    }

    int get_password() {
        return password;
    }

    void check_password() {
        if (pointing == 0) {
            password++;
        }
    }

    void turn_left(int n) {
        //pointing = pointing - n;
        //while (pointing < 0) {
        //    pointing = 100 - abs(pointing);
        //}
        //check_password();

        int m = n;
        while (m > 0) {
            pointing -= 1;

            if (pointing < 0) {
                pointing = 99;
            }

            if (pointing == 0) {
                password++;
            }

            m--;
        }
    }

    void turn_right(int n) {
        //pointing = pointing + n;
        //while (pointing >= 100) {
        //    pointing = pointing - 100;
        //}
        //check_password();

        int m = n;
        while (m > 0) {
            pointing += 1;

            if (pointing == 100) {
                pointing = 0;
            }

            if (pointing == 0) {
                password++;
            }

            m--;
        }
    }
};


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


    dial d;

    char buffer[1024] = {0};
    while (!feof(infile)) {
        char* ptr = fgets(buffer, 1024, infile);

        printf("buffer: %s\n", buffer);
        printf("ptr: %s\n", ptr);

        if (!ptr) {
            break;
        }

        buffer[strlen(buffer) - 1] = 0;


        int n = atoi(ptr + 1);

        if (buffer[0] == 'L') {
            printf("turning left %d\n", n);
            d.turn_left(n);
        } else if (buffer[0] == 'R') {
            printf("turning right %d\n", n);
            d.turn_right(n);
        }
    }


    fclose(infile);


    printf("Password: %d\n", d.get_password());


    return 0;
}
