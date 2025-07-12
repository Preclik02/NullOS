#include <iostream>
using namespace std;

int main() {
  system("clear");
  
  int x;
  while (true) {
    cout << "[0] Quit" << endl;
    cout << "[1] Google Chrome" << endl;
    cout << "[2] Explorer" << endl;
    cout << "[3] Spotify" << endl;
    cout << "[4] Steam" << endl;
  
    cout << "\n\n>> ";
    cin >> x;
    
    if (x == 0) {
      break;
    }
    else if (x == 1) {
      system("/opt/google/chrome/chrome");
    }
    else if (x == 2) {
      system("xdg-open .");
    }
    else if (x == 3) {
      system("spotify");
    }
    else if (x == 4) {
      system("steam");
    }
  }


  return 0;
}
