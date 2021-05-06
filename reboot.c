#include <uefi.h>

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    ST->RuntimeServices->ResetSystem(EfiResetCold, 0, 0, NULL);
}
