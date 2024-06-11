int ex_cd(char *rel_path)  // Returns 1 if everything done correctly, -1 if the given directory does not exist, 2 if directory exists but not reachable
{
    // If the user types 'cd ~' or 'cd' then change the directory to home directory
    if((rel_path == NULL) || (*rel_path == '~')){
        rel_path = getenv("HOME");
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

void ex_exit(void)
{
    printf("Bye bye tash!\n");
    exit(0);
}
