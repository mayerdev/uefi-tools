#include <uefi.h>

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    // Reset current input state
    efi_status_t input_status = ST->ConIn->Reset(ST->ConIn, 0);
    if(EFI_ERROR(input_status)) return input_status;

    efi_input_key_t current_key;

    // Wait for input initialization
    while((input_status = ST->ConIn->ReadKeyStroke(ST->ConIn, &current_key)) == EFI_NOT_READY);

    while(1) {
        // Print previous typed character
        ST->ConOut->OutputString(ST->ConOut, &current_key.UnicodeChar);
        // Read new pressed key
        input_status = ST->ConIn->ReadKeyStroke(ST->ConIn, &current_key);

        // Exit if [ESC] pressed
        if (current_key.ScanCode == 0x17) return 0;

        // Sleep prevents cursor blinking and useless CPU usage
        usleep(50 * 1000);
    }
}
