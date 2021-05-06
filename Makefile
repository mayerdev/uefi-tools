# Output file
TARGET = BOOTX64.efi
# ./uefi - POSIX UEFI files
include uefi/Makefile

build_image:
	mkdir -p image/EFI/BOOT
	rm -f image/EFI/BOOT/*.efi
	mv ${TARGET} image/EFI/BOOT
# Building CD image on macOS
	hdiutil create -fs fat32 -ov -size 48m -volname EFIBOOT -format UDTO -srcfolder image uefi.cdr

start:
	qemu-system-x86_64 -cpu qemu64 -bios bios.fd -drive file=uefi.cdr,format=raw,if=ide -device VGA,vgamem_mb=128 -m 256

test: build_image start

# Use `make watch` to build new image and restart QEMU on *.C file changes
watch:
# `nodemon` can be replaced with any file watching utility
	nodemon -e c -x "clear; make && make test"
