/* Command Data Structure */

// Describes a simple command and arguments
typedef struct _SimpleCommand {
    int num_args;   // Number of arguments
    char **args;    // Array of arguments
} SimpleCommand;

void insertArgument(SimpleCommand *simCmd, char *argument) {
    simCmd -> args = realloc(simCmd -> args, sizeof(char *) * (simCmd -> num_args + 1));
    if (!simCmd -> args) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    simCmd -> args[simCmd -> num_args++] = argument;
}

SimpleCommand *NewSimCmd(){
    SimpleCommand *SimCmd = malloc(sizeof(SimpleCommand));
    if (!SimCmd) {
        perror("malloc");
    }
    SimCmd -> num_args = 0;
    SimCmd -> args = NULL;
    return SimCmd;
}

// Describes a complete command with input/output redirection if any.
typedef struct _Command {
    int num_simCmds;  // Number of simple commands
    SimpleCommand **simCmds;  // Array of simple commands
    char *outFile;
    char *inFile;
    char *errFile;
    int background;
    int out_append;
    int err_append;
} Command;

void insertSimpleCommand(Command *Cmd, SimpleCommand *simCmd) {
    Cmd -> simCmds = realloc(Cmd -> simCmds, sizeof(SimpleCommand *) * (Cmd -> num_simCmds + 1));
    if (!Cmd -> simCmds) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    Cmd -> simCmds[Cmd -> num_simCmds++] = simCmd;
}

Command *NewCmd(){
    Command *Cmd = malloc(sizeof(Command));
    if (!Cmd) {
        perror("malloc");
    }
    Cmd -> num_simCmds = 0;
    Cmd -> simCmds = NULL;
    Cmd -> inFile = NULL;
    Cmd -> outFile = NULL;
    Cmd -> errFile = NULL;
    Cmd -> background = 0;
    Cmd -> out_append = 0;
    Cmd -> err_append = 0;
    return Cmd;
}

void execute(Command *Cmd) {
    int tmpin = dup(0); // Save stdin
    int tmpout = dup(1); // Save stdout
    int tmperr = dup(2); //Save stderr

    int numsimplecommands = Cmd -> num_simCmds;
    SimpleCommand **scmd = Cmd -> simCmds;
    char *inFile = Cmd -> inFile;
    char *outFile = Cmd -> outFile;
    char *errFile = Cmd -> errFile;
    int background = Cmd -> background;
    int out_append = Cmd -> out_append;
    int err_append = Cmd -> err_append;

    //implementing error redirection
    int fderr;
    if(errFile) {
        if(err_append) {
            fderr = open(errFile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        else {
            fderr = open(errFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }

        // Redirect stderr to error file
        if (dup2(fderr, STDERR_FILENO) == -1) {
            perror("Error redirecting stderr");
            exit(EXIT_FAILURE);
        }
    }

    //Implementing cd (change directory)
    SimpleCommand *first_scmd = scmd[0];
    if(strcmp(first_scmd -> args[0], "cd") == 0){
        int status = ex_cd(first_scmd -> args[1]);
        if (status == -1) {
            fprintf(stderr, "error: \"%s\" directory doesn't exist!\n", first_scmd -> args[1]);
        }
        else if(status == 2) {
            fprintf(stderr,"error: \"%s\" directory is not reachable!\n", first_scmd -> args[1]);
        }
        return;
    }
    // Implementing Exit
    if(strcmp(first_scmd -> args[0], "exit") == 0){
        ex_exit();
    }

    // Set up initial input
    int fdin;
    if (inFile) {
        fdin = open(inFile, O_RDONLY);
        if (fdin < 0) {
            perror("open input file");
            exit(EXIT_FAILURE);
        }
    } 
    else {
        // Use default input
        fdin = dup(tmpin);
    }

    int ret;
    int fdout;
    for (int i = 0; i < numsimplecommands; i++) {
        // Redirect input
        dup2(fdin, 0);
        close(fdin);

        // Setup output
        if (i == numsimplecommands - 1) {
            if (outFile)
            {
                if(out_append) {
                    fdout = open(outFile, O_WRONLY | O_CREAT | O_APPEND, 0644);
                }
                else {
                    fdout = open(outFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }
                if (fdout < 0) {
                    perror("open output file");
                    exit(EXIT_FAILURE);
                }
            }
            else {
                fdout = dup(tmpout);
            }
        }
        else {
            int fdpipe[2];
            if (pipe(fdpipe) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            fdout = fdpipe[1];
            fdin = fdpipe[0];
        }

        dup2(fdout, 1); // Redirect output
        close(fdout);

        ret = fork();
        if (ret == 0) {
            // Child process
            execvp(scmd[i] -> args[0], scmd[i] -> args);
            perror("execvp");
            _exit(EXIT_FAILURE);
        } 
        else if (ret < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    dup2(tmpin, 0);
    dup2(tmpout, 1);
    dup2(tmperr, 2);

    close(tmpin);
    close(tmpout);
    close(tmperr);

    if(errFile) {
        close(fderr);
    }

    if (!background) {
        waitpid(ret, NULL, 0);
    }
}

void freeCmd(Command *Cmd){
    if (!Cmd) {
        return;
    }
    for (int i = 0; i < Cmd -> num_simCmds; i++) {
        free(Cmd -> simCmds[i] -> args);
        free(Cmd -> simCmds[i]);
    }
    free(Cmd -> simCmds);
    free(Cmd->inFile);
    free(Cmd->outFile);
    free(Cmd->errFile);
    Cmd->out_append=0;
    Cmd->err_append=0;
    free(Cmd);
}

void freeSimCmd(SimpleCommand *simCmd){
    if (!simCmd) {
        return;
    }
    free(simCmd -> args);
    free(simCmd);
}
