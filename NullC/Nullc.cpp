#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

int main() {
    
    system("python Nullc.py");

    string path = "~/Documents/filenames.txt";

    if (!path.empty() && path[0] == '~') {
        const char* home = getenv("HOME");
        if (home) {
            path = string(home) + path.substr(1);
        }
    }

    ifstream file(path);
    if (!file) {
        cerr << "Failed to open file: " << path << "\n";
        return 1;
    }

    string filename;
    file >> filename;
    
    file.close();
    
    string command = "gcc program.c -o " + filename;
    system(command.c_str());
    system("rm program.c");

    return 0;
}

