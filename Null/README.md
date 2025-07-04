## Null

**Null** is a shell emulator (or terminal call it however you like) that is beginer friendly as it can be (in my opinion). I have desinged the commands to feel easier and guide you trough the commands and stuff for now there is none commands like this where you do command --help and for now its not even in my to-do list or sm like that. I made it long time ago to make my life easier now its part of this NullOS so its pretty cool. You could install it like every folder in this ecosystem (sadly for now without iso image) with oppenng the NullOS.sh its generaly the file you need it makes your day easier and mine too. As in mos of those README.md's I gotta notife you about the challange Im doing its a veryfing if you are human and if you really care about this all so go into the main README.md and read it you will learn about the challange to ge to my discord. And if you wanna install the Null like the Null not a thing else you will need to put this folder to ~/NullOS/Null to it work properly than to make sure it works fine you need to make sure its in ~/.bashrc so nano into it and than check if this is on the end of the file.


```bash
export PATH="$HOME/Documents/NullOS/Null:$PATH"
```


If it is make sure you do the next command, if it isnt than add it there and continue.


```bash
source ~/.bashrc
```


After that try to run the null in your bash terminal if it doesent work try re-compiling everything like this.


```bash
g++ ~/Documents/NullOS/Null/null.cpp -o ~/Documents/NullOS/Null/null
g++ ~/Documents/NullOS/Null/cpp/apps.cpp -o ~/Documents/NullOS/Null/cpp/apps
g++ ~/Documents/NullOS/Null/cpp/ssh_connect.cpp -o ~/Documents/NullOS/Null/cpp/ssh_connect
g++ ~/Documents/NullOS/Null/cpp/vnc_connect.cpp -o ~/Documents/NullOS/Null/cpp/vnc_connect
g++ ~/Documents/NullOS/Null/cpp/Nullc.cpp -o ~/Documents/NullOS/Null/cpp/Nullc
g++ ~/Documents/NullOS/Null/cpp/rpg.cpp -o ~/Documents/NullOS/Null/cpp/rpg
g++ ~/Documents/NullOS/Null/cpp/idek.cpp -o ~/Documents/NullOS/Null/cpp/idek
gcc ~/Documents/NullOS/Null/c/nmap_check.c -o ~/Documents/NullOS/Null/c/nmap_check
gcc ~/Documents/NullOS/Null/c/ip_check.c -o ~/Documents/NullOS/Null/c/ip_check
```


After all that you should be able to run null in your terminal and it should start if it still doesent than start from the begining or something or if you have more questions you can e-mail me on ---> nulldecode@gmail.com I should respond.

After all the null is just a shell-emulator for new or beginer users if you like the idea and want to check out my discord or join dev team make the challenge I mentioned before if you dont know how than you are cooked you can try on reatching out to me with the email maybye I will give you a hint.
