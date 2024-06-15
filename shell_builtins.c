// Returns 0 if everything done correctly,
// -1 if the given directory does not exist,
// 2 if directory exists but not reachable
int ex_cd(char *rel_path) {
    // If the user types 'cd ~' or 'cd' then change the directory to home directory
    if (rel_path == NULL){
        rel_path = getenv("HOME");
    }
    else if (*rel_path == '~') {
        char *home = (char *)malloc(sizeof(char) * (strlen(getenv("HOME")) + strlen(rel_path) + 1));
        strcpy(home, getenv("HOME"));
        strcat(home, rel_path+1);
        free(rel_path);
        rel_path = home;
    }

    // Check whether the directory exists or not
    DIR* dir = opendir(rel_path);
    if (dir) {
        // Directory exists
        closedir(dir);
    } else if (ENOENT == errno) {
        // Directory doesn't exist
        return -1;
    }
    else {
        // Directory exists but not reachable
        return 2;
    }
    chdir(rel_path);
    return 0;
}

void ex_exit(void) {
    printf("Bye bye Tash!\n");
    exit(0);
}
