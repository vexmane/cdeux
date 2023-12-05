// code is messy
// prone to crashes
// if you use it the way its meant to be used it will work
// i *MAY* fix the issues in the future
// if you dont like them all of the code is down below
// TODO: add commands to filter/sort the items

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "ansi.h"
#define USER_INPUT_BUFFER_SIZE 10000 // that many characters & bytes
#define DB_LINE_BUFFER_SIZE USER_INPUT_BUFFER_SIZE+1000 // just because.

bool closeApp = 0;
const char promptSymbol = '>';
char userInputBuffer[USER_INPUT_BUFFER_SIZE];
char dbLineBuffer[DB_LINE_BUFFER_SIZE];
FILE *db;



void loadDb() {
    db = fopen("thygemynd.db", "r+");
    
    // Check if the db exists. If not create it.
    if (db == NULL) {
        db = fopen("thygemynd.db", "w");
        // Check if it was created successfully. If not exit with 1.
        if (db == NULL) {
            perror(ACLR_FG_RED "Faileed to create the database file." ACLR_RESET);
            exit(1);
        }
    }
}


void listDb() {
    
    unsigned counter=0;

    while ( fgets(dbLineBuffer, DB_LINE_BUFFER_SIZE, db) ) {
        counter++;
        printf("%d: ", counter);

        switch ((int)(dbLineBuffer[0]-'0')) {
        case 0:
            printf(ACLR_RESET);
            break;
        case 1:
            printf(ACLR_FG_GREEN);
            break;
        case 2:
            printf(ACLR_FG_RED);
            break;
        default:
            printf(ACLR_RESET);
            break;
    }

        dbLineBuffer[0]=' ';
        printf("%s" ACLR_RESET, dbLineBuffer);
    }
    printf("\n\n");
    rewind(db);
    
}


void readUserInput() {
    memset(userInputBuffer, ' ', USER_INPUT_BUFFER_SIZE); // Clears the input buffer
    printf("%c", promptSymbol);
    fgets(userInputBuffer, USER_INPUT_BUFFER_SIZE, stdin); //scanf("%s", userInputBuffer); // unsafe code (3 for some reason it doesnt work with fgets.
    // Remove the trailing newline character, if present
    size_t len = strlen(userInputBuffer);
    if (len > 0 && userInputBuffer[len - 1] == '\n') {
        userInputBuffer[len - 1] = '\0';
    }
    printf("\n");
}

void refreshScreen() {
    printf(ANSI_CLEAR ANSI_HOME ACLR_RESET);
    printf("CDEUX - list of thy ideas.\n==========================\n\n");
    listDb();
}

void lowercaseInputBuffer() {
    for (int i=0; i<strlen(userInputBuffer); i++) {
        userInputBuffer[i] = tolower(userInputBuffer[i]);
    }
}

void executeUserCommand() {
    lowercaseInputBuffer();
    
    
    if (strcmp(userInputBuffer, "help")==0) {
        printf(ACLR_FG_YELLOW "Commands:");
        printf("\n> add <context> ('context' is a string, the actual message.)");
        printf("\n> modify <line_number> <progress> ('line_number' is the number of the entry which you want to edit. 'progress' can be either none, complete or halted.)");
        printf("\n> remove <line_number> ('line_number' is the number of the entry which you want to edit.)");
        printf("\n> cls (refreshes the screen and lists thy ideas.)");
        printf("\n> gtfo (aka: exit, quit. You can also Ctrl+C)");
        printf("\n  CDEUX autosaves! There is no save/load command. One database. If you don't like it the project is open source :)");
        printf(ACLR_RESET "\n");
    } else if (strcmp(userInputBuffer, "gtfo")==0) {
        closeApp=1;
    } else if (strcmp(userInputBuffer, "cls")==0) {
        refreshScreen();
    } else if (strcmp(userInputBuffer, "remove")==0) {
        
        printf("\nEnter line number ");
        readUserInput();

        int lineNumber = atoi(userInputBuffer);
        unsigned counter=0;

        FILE *tempDb = fopen("temp.db", "w");
        if (tempDb == NULL) {
            perror(ACLR_FG_RED "Failed to create temporary database file." ACLR_RESET);
            exit(1);
        }

        rewind(db); //just in case
        while ( fgets(dbLineBuffer, DB_LINE_BUFFER_SIZE, db) ) {
            counter++;
            if (lineNumber!=counter) {
                fputs(dbLineBuffer, tempDb);
            }
        }
        
        fclose(db); fclose(tempDb);
        remove("thygemynd.db");
        rename("temp.db", "thygemynd.db");
        loadDb(); //reload
        refreshScreen();
        

    } else if (strcmp(userInputBuffer, "modify")==0) {

        printf("\nEnter line number: ");
        readUserInput();
        int lineNumber = atoi(userInputBuffer);

        printf("\nEnter progress (none, complete, halted): ");
        readUserInput();
        lowercaseInputBuffer();

        unsigned counter=0;

        FILE *tempDb = fopen("temp.db", "w");
        if (tempDb == NULL) {
            perror(ACLR_FG_RED "Faileed to create temporary database file." ACLR_RESET);
            exit(1);
        }

        rewind(db); //just in case
        while ( fgets(dbLineBuffer, DB_LINE_BUFFER_SIZE, db) ) {
            counter++;
            if (lineNumber==counter) {
                if (strcmp(userInputBuffer, "none")==0) {
                    dbLineBuffer[0]='0';
                } else if (strcmp(userInputBuffer, "complete")==0) {
                    dbLineBuffer[0]='1';
                } else if (strcmp(userInputBuffer, "halted")==0) {
                    dbLineBuffer[0]='2';
                } else {
                    printf(ACLR_FG_YELLOW "Operation cancelled. You are supposed to enter either none, complete or halted." ACLR_RESET);
                    getchar();
                }
            }
            fputs(dbLineBuffer, tempDb);
        }
        
        fclose(db); fclose(tempDb);
        remove("thygemynd.db");
        rename("temp.db", "thygemynd.db");
        loadDb(); //reload
        refreshScreen();

        
    } else if (strcmp(userInputBuffer, "add")==0) {

        printf("\nEnter thy idea: ");
        readUserInput();

        // Go to the end of the file
        fseek(db, 0, SEEK_END);
        fprintf(db, "0%s\n", userInputBuffer);
        rewind(db);
        refreshScreen();

    }

}

int main() {

    loadDb();
    refreshScreen();

    while (!closeApp) {
        readUserInput();
        executeUserCommand();
    }

    fclose(db);
    printf(ANSI_CLEAR ANSI_HOME);
    return 0;
}