#include <uefi.h>

// This example shows how to bypass automatical exit
// from application after 5 minutes
int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    ST->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
}
