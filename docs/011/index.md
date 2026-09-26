---
layout: default
title: "Advanced easy Linux guide"
description: "Advanced but easy-to-follow Linux guide"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/011/thumb.png
---

## Table of Contents

- [Introduction](#introduction)
- [Bootloader](#bootloader)
- [Init](#init)
- [Shell: sh vs Bash](#shell-sh-vs-bash)
- [TTY and PTY](#tty-and-pty)
- [Display Manager: SDDM](#display-manager-sddm)
- [Display Server](#display-server)
- [Desktop Environment](#desktop-environment)
- [The Filesystem](#the-filesystem)
- [Character Devices: the "c" Files](#character-devices)

## Introduction

This is the same chain of hand-offs from [power button to desktop](./../001), just followed one layer deeper each time. Bootloader, init, shell, terminal, login screen, display server, desktop, filesystem, and the dotfiles that quietly configure all of it. Nothing here needs memorizing, it's context for when something in that chain breaks and you want to know which layer you're actually looking at.

It's more of preview of what things in error.os are called instead of the typical guide.

## Bootloader

GRUB is the thing that shows up before anything looks like an operating system, already covered in [booting the ISO](./../001#making-the-iso-boot) and [changing boot order](./../002). Its whole job is picking a kernel, loading it into memory along with an initramfs, and getting out of the way.

## Init

The kernel hands off to **init**, always the first real process, always PID 1. On error.os that's **systemd**. Everything else on the system is a descendant of it, directly or indirectly, `pstree -p` shows the whole family tree if you're curious. systemd also starts services in a dependency order (`systemctl status <name>` for any of them) and eventually reaches the point where it starts the login screen.

## Shell: sh vs Bash

`/bin/sh` and `/bin/bash` aren't the same thing, even though `sh` often feels like a shorter name for the same shell. On Debian (and error.os), `/bin/sh` is actually a symlink to **dash**, a smaller, faster shell that only implements the POSIX standard, nothing extra. **Bash** is the interactive shell you actually type into day to day, and it adds a pile of conveniences dash doesn't have: arrays, `[[ ]]` test syntax, command history, tab completion.

This matters because a script starting with `#!/bin/sh` is not guaranteed bash features, even if you wrote and tested it in a bash terminal. If a script uses bash-only syntax, its shebang should say `#!/bin/bash` explicitly.

## TTY and PTY

A **TTY** (teletype, historically an actual physical terminal) is what `Ctrl+Alt+F2` through `F6` switch you into, a real virtual console the kernel manages directly, no graphics involved.

A **PTY** (pseudo-terminal) is the software equivalent: a kernel-emulated pair that terminal emulators, SSH sessions, and anything running inside Konsole or xterm actually use. It behaves like a TTY to whatever program is running inside it, without there being real hardware underneath. Every terminal window you open on your desktop is a PTY, not a TTY.

## Display Manager: SDDM

Once init reaches the graphical target, something needs to draw a login screen and start a session once you authenticate, that's the **display manager**. error.os uses **SDDM** specifically. It's what you saw covered under [entering your password](./../002#entering-password), and it's also what autologin quietly skips past on a fresh install.

## Display Server

The display server is the layer underneath your desktop that actually manages drawing windows, input, and screen output. Linux has two in active use: the older **X11**, and the newer **Wayland**, which error.os's KDE Plasma session uses by default. Wayland handles input and compositing more directly and has better security isolation between apps; X11 is still around mainly for compatibility with older applications that haven't been updated to speak Wayland's protocol.

## Desktop Environment

The desktop environment is everything you actually see and click, panels, the application menu, window decorations, system settings. error.os ships **Minimal KDE Plasma**, as mentioned back in the [introduction](./../000#what-is-erroros), stripped down to what's actually needed rather than every KDE application bundled by default.

## The Filesystem

[Doc 002](./../002#what-do-these-directories-mean) already covers the directories most people actually touch. Here's the fuller picture, including the ones that usually go unmentioned:

| Path | What's actually there |
|---|---|
| `/bin`, `/sbin` | now just symlinks into `/usr/bin`, `/usr/sbin` on modern Debian, kept for compatibility |
| `/lib`, `/lib64` | same deal, symlinked into `/usr/lib`, `/usr/lib64` |
| `/root` | root's home directory, separate from `/home` so it's still reachable if `/home` is a separate, unmounted partition |
| `/run` | runtime data that shouldn't survive a reboot, PIDs, sockets, lock files |
| `/tmp` | temporary files, usually cleared on reboot |
| `/sys` | a virtual filesystem exposing kernel and device internals, similar in spirit to `/proc` but organized around devices and drivers instead of processes |

## Character Devices

That leading letter in `ls -l` output isn't part of the permissions, it's the file type. `-` is a regular file, `d` is a directory, and `c` is a **character device**, a file that represents hardware or a kernel-provided data stream, one byte at a time rather than in blocks. Most of `/dev` is full of them:

```bash
ls -l /dev/null /dev/zero /dev/random /dev/kvm
```

A few that actually show up in everyday scripts:

- **`/dev/null`**: the universal trash can. `command > /dev/null 2>&1` throws away both normal output and errors.
- **`/dev/zero`**: an endless stream of zero bytes. `dd if=/dev/zero of=file bs=1M count=100` creates a 100MB file of nothing, useful for quick test files or wiping a drive.
- **`/dev/random`** and **`/dev/urandom`**: sources of random bytes, used constantly for generating tokens or passwords: `head -c 16 /dev/urandom | base64`.
- **`/dev/tty`**: always refers to whatever terminal the current process is attached to, handy in a script that needs to talk to the user even when its normal input/output is redirected elsewhere.

And for a fun addition, **`/dev/kvm`**: your CPU's hardware virtualization extensions, exposed as a device file. It shows up on its own once the `kvm` kernel module loads (assuming virtualization is enabled in your BIOS/UEFI), but the device alone doesn't do anything by itself. To actually use it:

```bash
sudo apt install qemu-kvm virt-manager
```

`qemu-kvm` is the actual emulator that talks to `/dev/kvm` for hardware-accelerated virtual machines, `virt-manager` is the GUI on top of it for creating and managing those VMs without hand-writing QEMU command lines.

<blockquote class="note">
<span class="title">NOTE</span><br>
The other files in that same <code>/dev</code> listing (<code>cpu_dma_latency</code>, <code>cuse</code>, <code>drm_dp_aux0</code>, <code>nvram</code>, <code>port</code>, <code>ppp</code>) are all real character devices too, just ones you'd only ever touch while writing a driver or debugging specific hardware, not day-to-day scripting.
</blockquote>

<hr>

#### Next steps,
<div style="text-align:center; font-size:3rem;">
011 -> <a href="./../012">012</a>
</div>

## Related pages

- [000 - Introduction](./../000)

- [001 - Downloading and checksum](./../001)

- [002 - Installation and setup](./../002)