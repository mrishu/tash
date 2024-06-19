// if cwd starts with /home/user (or $HOME), then it replaces that with ~
char *cwd_home_tilde(char *cwd) {
    char *cwd_orig = cwd;
    char *home = getenv("HOME");
    while (*home != '\0') {
        if (*home++ != *cwd++) {
            return cwd_orig;
        }
    }
    char *cwd_final = (char *)malloc((MAX_PATH_LEN + 1) * sizeof(char));
    strcpy(cwd_final, "~");
    strcat(cwd_final, cwd);
    free(cwd_orig);
    return cwd_final;
}

// prints prompt in the format user@hostname:/path/to/cwd
void print_prompt(){
    char *cwd = (char *)malloc((MAX_PATH_LEN + 1) * sizeof(char));
    getcwd(cwd, MAX_PATH_LEN);
    char *username = getenv("USER");
    char hostname[HOST_NAME_MAX + 1];
    gethostname(hostname, sizeof(hostname));
    
    cwd = cwd_home_tilde(cwd);

    printf("\e%s%c%s%s@%s\e%s", BOLD, AND, GREEN, username, hostname, RESET);
    printf("\e%s:\e%s", BOLD, RESET);
    printf("\e%s%s\e%s", BLUE, cwd, RESET);
    printf("$ ");
    free(cwd);
}

void welcome_msg(void){
    printf("\e%s%c%sWelcome \e%s", BOLD, AND, RED, RESET);
    printf("\e%s%c%sto \e%s", BOLD, AND, YELLOW, RESET);
    printf("\e%s%c%sTash\e%s", BOLD, AND, GREEN, RESET);
    printf("\e%s%c%s!!\e%s\n", BOLD, AND, BLUE, RESET);
}
