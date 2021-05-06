#include <uefi.h>

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    
    FILE *f;
    char buff[2048], fn[16];
    int i;

    for(i = 0; i < 64; i++) {
        sprintf(fn, "/dev/disk%d", i);
        if((f = fopen(fn, "r"))) {
            memset(buff, 0, sizeof(buff));
            fread(buff, sizeof(buff), 1, f);
            printf("%4D \r\n", (efi_physical_address_t) buff);
            fclose(f);
        }
    }
}