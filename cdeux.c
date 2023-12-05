#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ansi.h"
#define USER_INPUT_BUFFER_SIZE 10000 // that many characters & bytes

bool closeApp = 0;
const char promptSymbol = '>';
char userInputBuffer[USER_INPUT_BUFFER_SIZE];



void readUserInput() {
    memset(userInputBuffer, ' ', USER_INPUT_BUFFER_SIZE); // Clears the input buffer
    printf("%c", promptSymbol);
    scanf("%s", userInputBuffer); // unsafe code (3 for some reason it doesnt work with fgets.
    printf("\n");
}

void executeUserCommand() {
    // Convert the input buffer to lowercase
    for (int i=0; i<strlen(userInputBuffer); i++) {
        userInputBuffer[i] = tolower(userInputBuffer[i]);
    }
    
    if (strcmp(userInputBuffer, "help")==0) {
        printf(ACLR_FG_YELLOW "Commands:");
        printf("\n> add \"<context>\" <progress> ('context' is a string, the actual message. put it inside the \"\"! 'progress' is a number from 0 to 2. 0 is none 1 is complete and 2 is halted/paused.)");
        printf("\n> modify <line_number> \"<context>\" <progress> ('line_number' is the number of the entry which you want to edit. 'context' is a string, the actual message. put it inside the \"\"! 'progress' is a number from 0 to 2. 0 is none 1 is complete and 2 is halted/paused.)");
        printf("\n> remove <line_number> ('line_number' is the number of the entry which you want to edit.)");
        printf("\n> gtfo (aka: exit, quit. You can also Ctrl+C)");
        printf("\n  CDEUX autosaves! There is no save/load command. One database. If you don't like it the project is open source :)");
        printf(ACLR_RESET "\n");
    } else if (strcmp(userInputBuffer, "gtfo")==0) {
        closeApp=1;
    }
}

int main() {

    printf(ANSI_CLEAR ANSI_HOME);
    printf("CDEUX - list of thy ideas.\n==========================\n\n");

    while (!closeApp) {
        readUserInput();
        executeUserCommand();
    }


    printf(ANSI_CLEAR ANSI_HOME);
    return 0;
}