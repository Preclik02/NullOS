#include <iostream>
using namespace std;

int main() {
  
  int x;
  
  cout << "To what machine you wanna vnc-connect\n\n[1] RPi zero (192.168.0.x)\n\n>> ";
  cin >> x;
  
  if (x == 1) {
    cout << "conecting . . . " << endl;
    system("vncviewer 192.168.0.x");
  }


  return 0;
}
