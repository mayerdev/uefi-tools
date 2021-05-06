#include <uefi.h>

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    
    ST->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
}