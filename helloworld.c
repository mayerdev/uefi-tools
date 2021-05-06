#include <uefi.h>

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    
    ST->ConOut->OutputString(ST->ConOut, "Hello world!");
}