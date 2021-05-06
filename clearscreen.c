#include <uefi.h>

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    // Clear screen
    ST->ConOut->ClearScreen(ST->ConOut);
}
