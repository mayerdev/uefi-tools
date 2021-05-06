#include <uefi.h>

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    ST->ConOut->OutputString(ST->ConOut, L"Hello world!");

    // "Pausing" application for 10 seconds to keep our message visible
    sleep(10);
    // Returning status code. Zero means "OK".
    return 0;
}
