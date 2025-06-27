## ArcNull

**ArcNull** is basicly a shell (or a terminal emulator call it however you want) its writen entirely in C++ with one small python script for Arcc. Its a my try on making the most beginer friendly shell its bash-based and comes with the ArcOS iso image. You can easily copy it into the Documents folder just like the ArcOS witch its used to be in and if its not in the ~/Documents folder with the ArcOS entire script the ArcNull might not work becouse it has been set to be in those folders by me. If you want to make the ArcNull be accesable from anywhere you would need to make sure you have it in the ~/.bashrc and if you have the defalut instalation you need to make sure this line is there if its not there you need to put it in there.


```bash
export PATH="$HOME/Documents/ArcOS/ArcNull:$PATH"
```


and to make things apply you need to also run


```bash
source ~/.bashrc
```


than you can acces ArcNull from any folder by typing arcnull. If it doesent work you might need to use gcc and re-compile every file or you can just do


```bash
g++ ~/Documents/ArcOS/ArcNull/arcnull.cpp -o ~/Documents/ArcOS/ArcNull/arcnull
g++ ~/Documents/ArcOS/ArcNull/apps.cpp -o ~/Documents/ArcOS/ArcNull/apps
g++ ~/Documents/ArcOS/ArcNull/ssh_connect.cpp -o ~/Documents/ArcOS/ArcNull/ssh_connect
g++ ~/Documents/ArcOS/ArcNull/vnc_connect.cpp -o ~/Documents/ArcOS/ArcNull/vnc_connect
g++ ~/Documents/ArcOS/ArcNull/Arcc.cpp -o ~/Documents/ArcOS/ArcNull/Arcc
g++ ~/Documents/ArcOS/ArcNull/rpg.cpp -o ~/Documents/ArcOS/ArcNull/rpg
g++ ~/Documents/ArcOS/ArcNull/idek.cpp -o ~/Documents/ArcOS/ArcNull/idek
```


After running this you should be ready to go what this does is basicly that it compiles every src code of ArcNull to make it executable if they arent (just make sure you have the g++).


For any help you can do help command in the ArcNull and you should be able to see everythnig you need it has some basic things for now.
If you have any more detiled questions you can send them to arcdecode@gmail.com or join my discord server witch I said how in the README.md in the main folder of this repo
