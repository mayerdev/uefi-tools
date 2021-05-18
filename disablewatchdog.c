#include <uefi.h>

// This example shows how to bypass automatical exit
// from application after 5 minutes
// USE ONLY IF THE BOOTLOADER IS FULLY INITIALIZED AND READY TO RUN THE OS

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    ST->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
}
