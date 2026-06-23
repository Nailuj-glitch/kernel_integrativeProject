# kernel_integrativeProject

## Build instructions

To build the kernel ISO from scratch:

```bash
docker build -t kernel-dev . && docker run --rm -v $(pwd):/root/env kernel-dev make kernel.iso
```

To run it in QEMU:

```bash
docker run --rm -v $(pwd):/root/env kernel-dev qemu-system-x86_64 -cdrom kernel.iso -display curses
```
