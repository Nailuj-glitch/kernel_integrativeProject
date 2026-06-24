
# Part 2 — 64-bit kernel from scratch

A minimal 64-bit x86 kernel built with NASM and C, booted via GRUB Multiboot2 inside a reproducible Docker build environment.

## What it does

1. GRUB loads the kernel as a Multiboot2 module.
2. The kernel boots in 32-bit protected mode and verifies:
   - It was loaded by a Multiboot2-compliant bootloader.
   - The CPU supports `cpuid`.
   - The CPU supports long mode (64-bit).
3. Sets up identity-mapped page tables (first 1GB, using 2MB huge pages) — paging is mandatory before entering long mode.
4. Builds a minimal 64-bit GDT and performs a far jump into long mode.
5. Calls into C code (`kernel_main`), which writes directly to VGA memory (`0xb8000`) to display "Welcome to 64-bit kernel" in green.

## Structure
## Build and run

One-liner build:
```bash
docker build -t kernel-dev . && docker run --rm -v $(pwd):/root/env kernel-dev make kernel.iso
```

Run in QEMU (text-mode display, no GUI needed):
```bash
docker run --rm -it -v $(pwd):/root/env kernel-dev qemu-system-x86_64 -cdrom kernel.iso -display curses
```
Exit QEMU curses mode with `Ctrl+A` then `x`.

## Notes

- Build environment is fully containerized for reproducibility (cross-compilation toolchain pinned via Dockerfile).
- All assembly objects are assembled as `elf64` (even the 32-bit boot code) so the linker can combine them with the 64-bit C objects into a single binary.
- `qemu-system-x86_64 -display curses` is used instead of the default GTK display since the build environment is headless (no X server in the container).
