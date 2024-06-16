#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_PATH_LEN 500

#define RESET "[0m"
#define BOLD "[1m"
#define ITALIC "[3m"
#define UNDERLINE "[4m"
#define RED "[31m"
#define GREEN "[32m"
#define YELLOW "[33m"
#define BLUE "[34m"
#define MAGENTA "[35m"
#define CYAN "[36m"
#define WHITE "[37m"
#define BRED "[91m"
#define BGREEN "[92m"
#define BYELLOW "[93m"
#define BBLUE "[94m"
#define BMAGENTA "[95m"
#define BCYAN "[96m"
#define AND 0x1B
