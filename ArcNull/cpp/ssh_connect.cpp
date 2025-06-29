#include <iostream>
using namespace std;

int main() {

  int x;
  cout << "To what machine you wanna connect?\n[1] RPi zero (192.168.0.x)\n\n>> ";
  cin >> x;
  
  if (x == 1) {
    cout << "connecting . . ." << endl;
    system("ssh pi@192.168.0.x");
  }
  else {
    cout << "wrong input" << endl;
  }

  return 0;
}
