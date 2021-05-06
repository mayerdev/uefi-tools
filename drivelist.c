#include <uefi.h>

// Printing list of all (64 at least) connected drives
int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    FILE *drive_file;
    char buffer[2048], drive_path[16];

    for(int i = 0; i < 64; i++) {
        sprintf(drive_path, "/dev/disk%d", i);
        if((drive_file = fopen(drive_path, "r"))) {
            memset(buffer, 0, sizeof(buffer));
            fread(buffer, sizeof(buffer), 1, drive_file);
            // Printing HEX view of first 2 kB stored on drive
            printf("%s:\r\n%4D\r\n", drive_path, buffer);
            fclose(drive_file);
        }
    }

    // Freeing up used memory to make it safe to reuse
    free(buffer);
    free(drive_path);
    // `drive_file` is already free, because `fclose` cleanups `fopen` allocation

    sleep(10);
    return 0;
}
