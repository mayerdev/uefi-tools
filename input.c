#include <uefi.h>

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    efi_status_t input_status = ST->ConIn->Reset(ST->ConIn, 0);
    if(EFI_ERROR(input_status)) {
        return input_status;
    }

    efi_input_key_t current_key;

    // Waiting input initialization
    while((input_status = ST->ConIn->ReadKeyStroke(ST->ConIn, &current_key)) == EFI_NOT_READY);

    while(1) {
        ST->ConOut->OutputString(ST->ConOut, &current_key.UnicodeChar);
        input_status = ST->ConIn->ReadKeyStroke(ST->ConIn, &current_key);

        // Preventing cursor blinking and useless CPU ticks
        usleep(50 * 1000);
    }
}
