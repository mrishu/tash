char* cwd_home_tilde(char *cwd) {
    char *cwd_orig = cwd;
    char *home = getenv("HOME");
    while (*home != '\0') {
        if (*home++ != *cwd++) {
            return cwd_orig;
        }
    }
    char* cwd_final = (char *)malloc((MAX_PATH_LEN + 1) * sizeof(char));
    *cwd_final = '~'; *(cwd_final + 1) = '\0';
    strcat(cwd_final, cwd);
    free(cwd_orig);
    return cwd_final;
}

void print_prompt(){
    char* cwd = (char *)malloc((MAX_PATH_LEN + 1) * sizeof(char));
    getcwd(cwd, MAX_PATH_LEN);
    char *username = getenv("USER");
    char hostname[HOST_NAME_MAX + 1];
    gethostname(hostname, sizeof(hostname));
    
    cwd = cwd_home_tilde(cwd);

    printf("\e[1m%c[%dm%s@%s\e[m", 0x1B, 32, username, hostname);
    printf("\e[1m%c[%dm:\e[m", 0x1B, 0);
    printf("\e[1m%c[%dm%s\e[m", 0x1B, 34, cwd);
    printf("\e[1m%c[%dm$ \e[m", 0x1B, 0);
    free(cwd);
}
