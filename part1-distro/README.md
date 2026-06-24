
# Part 1 — Custom Ubuntu distro with Cubic

## Overview
Custom Ubuntu 26.04 ISO built using Cubic (Custom Ubuntu ISO Creator), including:
- Firefox replaced with LibreWolf
- Neovim installed with custom default config (deployed via /etc/skel)
- Custom .bashrc aliases deployed via /etc/skel
- Yaru-dark theme set as system default (via gschema override)
- htop and apache2 installed
- Verified bootable by creating a second VM using the generated ISO as boot media

## Steps (summary)
1. Created a VirtualBox VM (4GB RAM, 4 CPUs, 80GB disk) to host the build environment.
2. Installed Cubic via PPA:
   sudo apt-add-repository universe
   sudo apt-add-repository ppa:cubic-wizard/release
   sudo apt update
   sudo apt install --no-install-recommends cubic
3. Opened Cubic, selected the base Ubuntu ISO, and entered the customization chroot environment.
4. Inside the chroot:
   - Removed Firefox, installed LibreWolf via extrepo
   - Installed Neovim from PPA, created default config under /etc/skel/.config/nvim
   - Added custom aliases to /etc/skel/.bashrc
   - Installed and set Yaru-dark as default theme via gschema override
   - Installed htop and apache2
5. Generated the final custom ISO via Cubic.
6. Verified the ISO boots correctly by creating a new VM using it as the optical disk.

## Evidence
See evidencias.pdf in this folder - contains step-by-step screenshots of the VM setup, Cubic installation, package customization, and the boot verification of the final ISO.

## Reproduce
1. Create a VM with Ubuntu installed (or use an existing one) with at least 4GB RAM and 40GB+ disk.
2. Follow the steps above using the original Ubuntu ISO as the source image in Cubic.
3. The resulting custom ISO can be used to boot a new VM for verification.
