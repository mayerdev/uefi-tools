#include <uefi.h>

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    
    time_t current = time(0);
    printf("Time[h:m:s]: %d:%d:%d \r\n", current / 3600 % 24, current / 60 % 60, current % 60);
}