#include "fs304.h"

int parseCommand(char inputBuffer[], char *args[]);

int main(void){
    char inputBuffer[50];
    char *args[50];	        /* buffer to hold the command entered */
    int shouldRun = 1;
    mountFS304();     /* mount command to open fs304.disk */
    
    while(shouldRun){
        shouldRun = parseCommand(inputBuffer, args);
        if (strncmp(inputBuffer, "exit", 4) == 0){
            shouldRun = 0;     /* sets*/
        }
        else if (strncmp(inputBuffer, "ls", 2) == 0){
            ls();
        }
        else if (strncmp(inputBuffer, "md", 2) == 0){
            md(args[1]);
        }
        else if (strncmp(inputBuffer, "cd", 2) == 0){
            cd(args[1]);
        }
        else if (strncmp(inputBuffer, "stats", 5) == 0){
            stats();
        }
        else if (strncmp(inputBuffer, "rd", 2) == 0){
            rd();
        }
        else if (strncmp(inputBuffer, "compare", 7) == 0){
            compare(args[1], args[2]);
        }
        else if (strncmp(inputBuffer, "copy", 4) == 0){
            copy(args[1], args[2]);
        }
        else if (strncmp(inputBuffer, "rname", 5) == 0){
            rname(args[1], args[2]);
        } else {
            if (args != NULL)
            {
                if (!open(args[0]))
                {
                    printf("File not found: %s\n", args[0]);
                }
            }
        }
    }
    return 0;
}






int parseCommand(char inputBuffer[], char *args[])
{
    int numChars,		/* # of chars in command line */
    i,          /* counter */
    start,		/* beginning of next command */
    ct,	        /* index of where to place the next parameter into args[] */
    command_number;	/* index of requested command number */
    
    ct = 0;
    
    /* input reader */
    do {
        printPrompt();
        fflush(stdout);
        numChars = read(STDIN_FILENO,inputBuffer,50); /* writes input from file to inputBuffer. numChars = # of bytes read */
    }
    while (inputBuffer[0] == '\n');
    
    start = -1;
    if (numChars == 0)
        exit(0);            /* end of user command */
    
    
    
    /* Parse the contents of inputBuffer into args buffer */
    
    for (i=0;i<numChars;i++) {
        switch (inputBuffer[i]){
            case ' ':
            case '\t' :               /* argument separators */
                if(start != -1){
                    args[ct] = &inputBuffer[start];    /* set up pointer */
                    ct++;
                }
                inputBuffer[i] = '\0'; /* add a null char; make a C string */
                start = -1;
                break;
                
            case '\n':                 /* should be the final char examined */
                if (start != -1){
                    args[ct] = &inputBuffer[start];
                    ct++;
                }
                inputBuffer[i] = '\0';
                args[ct] = NULL; /* no more arguments to this command */
                break;
                
            default :             /* some other character */
                if (start == -1)
                    start = i;
        } /* end of switch */
    }    /* end of for */
    
    return 1;
    
}
