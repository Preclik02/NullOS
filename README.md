## ArcOS 

**ArcOS** is a full eco-system of Arc builded by solo myself (preclik02) and no one else only my job.
I have plan on maintain it for some time or even full time. I plan on some commits every week or two.
The .iso image (for ArcOS-1.0.0 - witch is 1st public release) can be found there: https://www.dropbox.com/scl/fi/wrrroev2pr2z9v0nvx6q9/ArcOS-1.0.0.iso?e=2&rlkey=xpgk4gwn66bgavfbvmmf4e0vt&st=4yzwjg4m&dl=0
When you download the iso file and use tools like rufus or balenaEtcher to flash it on like USB stick it can be injected into pretty mutch any machine.
I just downloaded the .iso image for the linux mint cinnamon and got it into cubic and copied reops of this whole repo in there Im not sure if it has the files included in ~/.bsahrc so after booting the system up please check if it is there at the end a line like this
--
export PATH="$HOME/Documents/ArcOS/ArcNull:$PATH"
--
if its not there add it at the end of the ~/.bashrc file and than run
--
source ~/.bashrc
--
so that the system uses this file for bash if you want to just copy the files from this repo you can clone them by using
--
git clone https://github.com/Preclik02/ArcOS.git ~/Documents/ArcOS
--
The Arc-ecosystem is made from for now 3 programms. 1st the ArcNull - its a shell (or a terminal-emulator call it however you want) it is a optional shell and its bash-based is beginer friendly has a help command witch doesent have that for every feature but it lists down all for now 23 programs. 2nd programm is ArcC - this isnt a program but kinda is cuz it is a freamework for C witch isnt really a framework its a chipper witch basicly converts your C program to this .arc thing or not convert but like you write it in .arc file and write it in custom characters (If you wanna understand it look on he end of this readme) and compiles using 3rd program Arcc - Arcc is a compiler for .arc files and basicly its a gcc pipeline here is how it works - It starts when you tell the ArcNull arcc input than the cpp file starts a python progam that asks for the filename wihout the .arc witch it than makes a filename.txt in ~/Documents than the python program converts the .arc script to normal .c program than it ends now the cpp program compiles the generated .c file and removes it and now you have the compilde .arc file. It is a wierd language but it works (not for complex projects... yet) I made it for fun and here is the main part.

--

If you wanna become a discord user or potencionaly a dev that works on this project too and helps to improve or maintain this OS you need to look at the docs and create me 2 files. 1st file is the full alfabeth from A to Z no missing letters than 2nd file file with .arc that contains a basic script using this chipper and prints out the Hello world text. Your tries or quesion you can send me to - arcdecode@gmail.com
