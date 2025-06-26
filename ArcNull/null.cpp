#include <iostream>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <cstdlib>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

void listDirectory(const string& path) {
    DIR* dir = opendir(path.c_str());
    if (!dir) {
        cout << "Directory not found." << endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        cout << entry->d_name << endl;
    }
    closedir(dir);
}

int main() {
  
    cout << R"(  _   _       _ _ 
 | \ | |     | | |
 |  \| |_   _| | |
 | . ` | | | | | |
 | |\  | |_| | | |
 |_| \_|\__,_|_|_|)";
    cout << "\n\n";
    string command;

    while (true) {
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));
        cout << cwd << " > ";

        cin >> command;

        if (command == "quit") {
            break;
        } else if (command == "cls") {
            system("clear");
        } else if (command == "color") {
            // Terminal color is usually managed by ANSI escape codes in Linux
            cout << "\033[1;32m"; // Bright green
        } else if (command == "./") {
            string filename;
            cout << "filename >> ";
            cin >> filename;
            system((string("./") + filename).c_str());  // Or use xdg-open if it’s a file
        } else if (command == "help") {
            cout << "All commands:\n\n[1] quit\n[2] cls\n[3] color\n[4] help\n[5] rpg\n[6] idek\n[7] ls\n[8] mkdir\n[9] touch\n[10] explorer\n[11] cd\n[12] rm\n[13] tab\n[14] shutdown\n[15] ./\n[16] ssh\n[17] sl\n[18] apps\n[19] vnc\n[20] arcc\n\n";
        } else if (command == "ls") {
            cout << "\n";
            system("ls");
            cout << "\n";
        } else if (command == "idek") {
            system("~/Documents/null/idek");
        } else if (command == "rpg") {
            system("~/Documents/null/rpg");
        } else if (command == "mkdir") {
            string filename;
            cout << "filename >> ";
            cin >> filename;
            mkdir(filename.c_str(), 0755);
        } else if (command == "touch") {
            string filename;
            cout << "filename >> ";
            cin >> filename;
            system(("touch " + filename).c_str());
        } else if (command == "explorer") {
            system("xdg-open .");
        } else if (command == "cd") {
            string dirname;
            cout << "directory name >> ";
            cin >> dirname;
            if (chdir(dirname.c_str()) != 0) {
                perror("cd failed");
            }
        } else if (command == "rm") {
            string filename;
            cout << "filename >> ";
            cin >> filename;
            system(("rm " + filename).c_str());
        } else if (command == "tab") {
            listDirectory(".");
        } else if (command == "shutdown") {
	    system("shutdown 0");
	    }
        else if (command == "ssh") {
          system("~/Documents/ArcOS/ArcNull/ssh_connect");
        }
        else if (command == "sl") {
          system("sl");
        }
        else if (command == "apps") {
          system("~/Documents/ArcOS/ArcNull/apps");
        }
        else if (command == "vnc") {
          system("~/Documents/ArcOS/ArcNull/vnc_connect");
        }
        else if (command == "arcc") {
            system("~/Documents/ArcOS/ArcNull/Arcc");
        }
      
    }

    return 0;
}

