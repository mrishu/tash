#include "command.c"

int main() {

    Command *currCmd = NewCmd();
    SimpleCommand *currSimCmd = NewSimCmd();

    // add arguments to current simple command
    insertArgument(currSimCmd, "ls");
    insertArgument(currSimCmd, "-l");
    insertArgument(currSimCmd, NULL);
    // add current simple command to current command
    insertSimpleCommand(currCmd, currSimCmd);
    
    // initialise new current simple command
    currSimCmd = NewSimCmd();
    // add arguments to current simple command
    insertArgument(currSimCmd, "wc");
    insertArgument(currSimCmd, NULL);
    // add current simple command to current command
    insertSimpleCommand(currCmd, currSimCmd);

    // execute current command
    execute(currCmd);

    // Free allocated memory
    free(currCmd);

    return 0;
}
