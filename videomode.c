#include <uefi.h>

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    
    efi_gop_t *gop = NULL;
    efi_guid_t gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_gop_mode_info_t *info = NULL;
    
    BS->LocateProtocol(&gopGuid, NULL, (void**)&gop);
    gop->QueryMode(gop, gop->Mode ? gop->Mode->Mode : 0, &isiz, &info);

    // info->HorizontalResolution
    // info->VerticalResolution
}