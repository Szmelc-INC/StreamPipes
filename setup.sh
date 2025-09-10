#!/bin/bash
set -e

# Ensure running on Arch-like system
if ! command -v pacman >/dev/null 2>&1; then
  echo "This script targets Arch Linux with pacman." >&2
  exit 1
fi

sudo pacman -Syu --needed --noconfirm base-devel fuse3

for dir in asciibuffer shortlog syspeek gpt; do
  make -C "$dir"
done

sudo modprobe fuse
sudo mkdir -p /dev/szmelc

sudo ./asciibuffer/asciibuffer /dev/szmelc/asciibuffer -f &
sudo ./shortlog/shortlog /dev/szmelc/shortlog -f &
sudo ./syspeek/syspeek /dev/szmelc/syspeek -f &
sudo ./gpt/gpt /dev/szmelc/gpt -f &

cat <<MSG
All pseudo devices mounted under /dev/szmelc.
Examples:
  cat /dev/szmelc/syspeek
  echo hello > /dev/szmelc/shortlog
To unmount:
  sudo fusermount3 -u /dev/szmelc/asciibuffer
  sudo fusermount3 -u /dev/szmelc/shortlog
  sudo fusermount3 -u /dev/szmelc/syspeek
  sudo fusermount3 -u /dev/szmelc/gpt
MSG

