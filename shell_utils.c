char *cwd_home_tilde(char *cwd) {
    char *cwd_orig = cwd;
    char *home = getenv("HOME");
    while (*home != '\0') {
        if (*home++ != *cwd++) {
            return cwd_orig;
        }
    }
    char *cwd_final = (char *)malloc((MAX_PATH_LEN + 1) * sizeof(char));
    *cwd_final = '~'; *(cwd_final + 1) = '\0';
    strcat(cwd_final, cwd);
    free(cwd_orig);
    return cwd_final;
}

void print_prompt(){
    char *cwd = (char *)malloc((MAX_PATH_LEN + 1) * sizeof(char));
    getcwd(cwd, MAX_PATH_LEN);
    char *username = getenv("USER");
    char hostname[HOST_NAME_MAX + 1];
    gethostname(hostname, sizeof(hostname));
    
    cwd = cwd_home_tilde(cwd);

    printf("\e%s%c%s%s@%s\e%s", BOLD, AND, GREEN, username, hostname, ENDF);
    printf("\e%s:\e%s", BOLD, ENDF);
    printf("\e%s%c%s%s\e%s", BOLD, AND, BLUE, cwd, ENDF);
    printf("$ ", BOLD, AND, WHITE, ENDF);
    free(cwd);
}

void welcome_msg(void){
    printf("\e%s%c%sWelcome \e%s", BOLD, AND, RED, ENDF);
    printf("\e%s%c%sto \e%s", BOLD, AND, YELLOW, ENDF);
    printf("\e%s%c%sTash \e%s", BOLD, AND, GREEN, ENDF);
    printf("\e%s%c%s!!\e%s\n", BOLD, AND, BLUE, ENDF);
}
