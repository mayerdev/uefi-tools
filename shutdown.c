#include <uefi.h>

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    ST->RuntimeServices->ResetSystem(EfiResetShutdown, 0, 0, NULL);
}