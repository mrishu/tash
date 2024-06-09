#include <unistd.h>

int my_cd(const char *path) {
    if (chdir(path) == -1) {
        perror("my_cd");
        return 1; // Indicates failure
    }
    return 0; // Indicates success
}
