void print_prompt(){
    char cwd[MAX_PATH_LEN];
    getcwd(cwd, MAX_PATH_LEN);
    char *username = getenv("USER");
    char hostname[HOST_NAME_MAX + 1];
    gethostname(hostname, sizeof(hostname));
    
    char *home = getenv("HOME");
    if (strcmp(cwd, home) == 0) strcpy(cwd, "~");

    printf("\e[1m%c[%dm%s@%s\e[m", 0x1B, 32, username, hostname);
    printf("\e[1m%c[%dm:\e[m", 0x1B, 0);
    printf("\e[1m%c[%dm%s\e[m", 0x1B, 34, cwd);
    printf("\e[1m%c[%dm$ \e[m", 0x1B, 0);
}
