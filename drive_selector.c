#include <uefi.h>

// boolean_t RtStrCmp (wchar_t *s1, wchar_t *s2) {
//     while (*s1) {
//         if (*s1 != *s2) {
//             break;
//         }

//         s1 += 1;
//         s2 += 1;
//     }

//     return *s1 - *s2;
// }

efi_gop_mode_info_t *video_info = NULL;
void init_video () {
    efi_gop_t *gop = NULL;
    efi_guid_t gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    uintn_t isiz = sizeof(efi_gop_mode_info_t), currentMode;

    BS->LocateProtocol(&gopGuid, NULL, (void**)&gop);
    gop->QueryMode(gop, gop->Mode ? gop->Mode->Mode : 0, &isiz, &video_info);
    free(gop);
    free(&gopGuid);
    free(&isiz);
}

inline void cout (wchar_t* str) {
    ST->ConOut->OutputString(ST->ConOut, str);
}

void redner_box (char lines[], int step, int length) {
    length *= step;
    int i, j;

    int width = video_info->HorizontalResolution / 10 - 2;
    char row[width];
    for (i = 0; i < width; i++) row[i] = '-';
    printf("*%s*", row);

    for (i = 0; i < length; i += step) {
        memcpy(row, lines + i, step);
        printf("| %s %s ", i == 0 ? ">" : " ", row);
        for (j = strlen(row); j < width - 4; j++) {
            printf(" ");
        }
        printf("|");
    }

    for (i = 0; i < width; i++) row[i] = '-';
    printf("*%s*", row);

    free(&i);
    free(&j);
    free(row);
}

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    init_video();

    efi_status_t input_status = ST->ConIn->Reset(ST->ConIn, 0);
    if (EFI_ERROR(input_status)) {
        return input_status;
    }

    BS->SetWatchdogTimer(0, 0, 0, NULL);

    char device_path[16];
    FILE *device_file;
    int i;

    // Tryint to initialize smth in UEFI
    device_file = fopen("/dev/disk", "r");
    if (device_file != 0) fclose(device_file);

    for(i = 0; ; i++) {
        sprintf(device_path, "/dev/disk%d", i);
        if((device_file = fopen(device_path, "r"))) {
            fclose(device_file);
        } else {
            break;
        }
    }
    free(device_file);

    int max_devices = i;
    char line_buffer[16 * max_devices];
    for (i = 0; i < max_devices; i++) {
        sprintf(device_path, "/dev/disk%d", i);
        memcpy(line_buffer + 16 * i, device_path, 16);
    }

    free(&i);
    free(device_path);
    ST->ConOut->EnableCursor(ST->ConOut, 0);

    efi_input_key_t current_key;
    int active = 0;
    boolean_t is_changed = 1;
    while (1) {
        if (is_changed) {
            ST->ConOut->ClearScreen(ST->ConOut);
            printf("   Select boot device:\n\n");
            redner_box(line_buffer, 16, max_devices);
            is_changed = 0;
        }

        input_status = ST->ConIn->ReadKeyStroke(ST->ConIn, &current_key);
        // ESC
        if (current_key.ScanCode == 23) {
            break;
        // Up
        } else if (current_key.ScanCode == 1) {
            ST->ConOut->SetCursorPosition(ST->ConOut, 2, 3 + active);
            cout(L" ");

            if (--active == -1) active = max_devices - 1;

            ST->ConOut->SetCursorPosition(ST->ConOut, 2, 3 + active);
            cout(L">");
        // Down
        } else if (current_key.ScanCode == 2) {
            ST->ConOut->SetCursorPosition(ST->ConOut, 2, 3 + active);
            cout(L" ");

            if (++active == max_devices) active = 0;

            ST->ConOut->SetCursorPosition(ST->ConOut, 2, 3 + active);
            cout(L">");
        // Enter
        } else if (current_key.UnicodeChar == 0xD) {
            printf("[Enter]");
        } else {
            usleep(50000);
        }
    }

    return 0;
}
// #include <uefi.h>

// // Printing list of all (64 at least) connected drives
// int main(int argc, char **argv) {
//     (void) argc;
//     (void) argv;

//     FILE *drive_file;
//     char buffer[2048], drive_path[16];

//     for(int i = 0; i < 64; i++) {
//         sprintf(drive_path, "/dev/disk%d", i);
//         if((drive_file = fopen(drive_path, "r"))) {
//             memset(buffer, 0, sizeof(buffer));
//             fread(buffer, sizeof(buffer), 1, drive_file);
//             // Printing HEX view of first 2 kB stored on drive
//             printf("%s:\r\n%4D\r\n", drive_path, buffer);
//             fclose(drive_file);
//         }
//     }

//     // Freeing up used memory to make it safe to reuse
//     free(buffer);
//     free(drive_path);

//     sleep(10);
//     return 0;
// }
