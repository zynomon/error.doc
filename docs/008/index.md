---
layout: default
title: "Driver management and Nvidia drivers"
description: "Managing drivers in linux and brief look into linux kernel how it handles the drivers"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/008/thumb.png
---

## Table of Contents

- [GUI Options](#gui-options)
- [How the Kernel Handles Drivers](#how-the-kernel-handles-drivers)
- [Checking Your Hardware](#checking-your-hardware)
- [When err_'s Driver Manager Isn't Enough](#when-errs-driver-manager-isnt-enough)
- [NVIDIA: Nouveau vs the Proprietary Driver](#nvidia-nouveau-vs-the-proprietary-driver)
- [Installing the Proprietary NVIDIA Driver by Hand](#installing-the-proprietary-nvidia-driver-by-hand)
- [32-bit Libraries for Steam and Wine](#32-bit-libraries-for-steam-and-wine)
- [Checking Mesa, OpenGL, and Vulkan](#checking-mesa-opengl-and-vulkan)
- [Verifying the Install](#verifying-the-install)
- [Secure Boot and DKMS](#secure-boot-and-dkms)
- [Switching Back to Nouveau](#switching-back-to-nouveau)
- [If the Screen Goes Black](#if-the-screen-goes-black)

## GUI Options

If you'd rather not touch a terminal at all, try these before scrolling further:

- **[err_'s Drivers tab](./../004#err_)** - detects your GPU automatically and installs with one click. Fastest option when it works, but it isn't always reliable, hence this page.
- **Synaptic Package Manager** - the standard graphical front-end for `apt` on Debian. Search for `nvidia-driver` and `nvidia-kernel-dkms`, tick both, and apply, no typed commands needed.
  ```bash
  sudo apt install synaptic
  ```
- **NVIDIA Settings** - not an installer, but the official control panel for a driver that's already installed: resolution, PRIME (hybrid GPU) profiles, and basic GPU info in a window.
  ```bash
  sudo apt install nvidia-settings
  ```

<blockquote class="note">
<span class="title">NOTE</span><br>
Unlike Ubuntu-family distros, plain Debian's Discover and GNOME Software generally don't auto-detect and offer proprietary drivers out of the box, that "Additional Drivers" style panel relies on Ubuntu-specific plumbing. If you're coming from Ubuntu or Mint, don't go looking for it here, Synaptic is the closer equivalent on Debian.
</blockquote>

If none of these get you a working driver, the rest of this page walks through the same steps by hand.

## How the Kernel Handles Drivers

On Linux, most drivers are kernel modules, small pieces of code that plug into the running kernel rather than getting compiled into it directly. Some drivers are built directly into the kernel image itself and are always active; the rest live as `.ko` files under `/lib/modules/$(uname -r)/` and load only when needed.

A few commands that matter here:

```bash
lsmod                  # list currently loaded modules
modprobe module_name   # load a module manually
modprobe -r module_name # unload a module
dmesg | grep -i module_name # check kernel messages related to a module
```

`udev` detects hardware as it's plugged in (or at boot) and loads the matching module automatically. For most hardware, that's the entire story. NVIDIA GPUs are the main exception, since the best-performing driver for them isn't open source and doesn't ship with the kernel.

## Checking Your Hardware

Before installing anything, confirm what you actually have and which driver is currently handling it:

```bash
lspci -k | grep -A 3 -i vga
```

The `Kernel driver in use:` line tells you what's active right now. On a fresh error.os install with an NVIDIA GPU, that's usually `nouveau`, the open-source driver that ships with the kernel by default.

## When err_'s Driver Manager Isn't Enough

If none of the GUI options above worked, everything from here on is the same process done by hand, with enough detail to see exactly where it's breaking.

## NVIDIA: Nouveau vs the Proprietary Driver

**Nouveau** is reverse-engineered, open-source, and installed automatically, no extra steps needed. It handles basic display output fine, but it doesn't support CUDA, has weaker 3D performance, and generally isn't what you want for gaming or GPU compute work.

**The proprietary NVIDIA driver** comes straight from NVIDIA, supports CUDA, and performs far better for gaming and compute, at the cost of being closed-source and needing a manual install.

<blockquote class="tip">
<span class="title">TIP</span><br>
If your GPU is only driving a desktop with no gaming or GPU compute involved, nouveau is often good enough, and skipping the proprietary driver means one less thing to break on a kernel update.
</blockquote>

## Installing the Proprietary NVIDIA Driver by Hand

Debian splits proprietary and firmware packages out of the default repositories, so `contrib`, `non-free`, and `non-free-firmware` need to be enabled first. Edit `/etc/apt/sources.list` (or the relevant file under `/etc/apt/sources.list.d/`) so each line's component list includes them, then update:

```bash
sudo apt update
```

Two package sets exist, and which one you want depends on your GPU generation:

```bash
# Maxwell through Ada/Hopper GPUs (most GTX/RTX cards up to the 40-series)
sudo apt install nvidia-kernel-dkms nvidia-driver

# Turing and newer (RTX 20-series onward), using NVIDIA's open-source kernel module
sudo apt install nvidia-open-kernel-dkms nvidia-driver
```

Both flavors need `nvidia-driver` explicitly alongside the DKMS package, `nvidia-driver` on its own doesn't pull in the kernel module. Blackwell (RTX 50-series) isn't covered by either of these branches yet in Debian's stable repository; if that's your card, check NVIDIA's own driver documentation for current packaging options rather than following this page.

Reboot once the install finishes:

```bash
sudo reboot
```

## 32-bit Libraries for Steam and Wine

Steam and most Wine-based setups need 32-bit NVIDIA libraries, even for 64-bit games, since parts of Steam's runtime and many older titles are still 32-bit binaries. Enable the i386 architecture before installing the driver so the matching 32-bit packages get pulled in automatically:

```bash
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install nvidia-driver-libs:i386
```

<blockquote class="warning">
<span class="title">WARNING</span><br>
The package is <code>nvidia-driver-libs:i386</code> with a colon, not <code>nvidia-driver-libs-i386</code>. The hyphenated version doesn't exist and <code>apt</code> will reject it.
</blockquote>

## Checking Mesa, OpenGL, and Vulkan

Even outside of NVIDIA-specific issues, a broken or missing Mesa install causes the same symptoms: no desktop effects, apps refusing to start with a GL-related error, or a blank window where 3D content should render. This applies whether you're using nouveau, the open-source AMD/Intel drivers, or just running an app in software rendering. Confirm the pieces are actually installed:

```bash
sudo apt install mesa-utils vulkan-tools
```

Then check what's actually being used:

```bash
glxinfo | grep "OpenGL renderer"
vulkaninfo --summary
```

If `glxinfo` reports `llvmpipe` instead of your GPU's name, rendering has fallen back to software, meaning the real driver isn't loading, worth revisiting the [hardware check](#checking-your-hardware) above. If either command isn't found at all, the underlying libraries are missing and can be reinstalled directly:

```bash
sudo apt install --reinstall libgl1-mesa-dri libglx-mesa0 mesa-vulkan-drivers
```

## Verifying the Install

For the NVIDIA proprietary driver specifically, after rebooting:

```bash
nvidia-smi
```

If the driver loaded correctly, this prints your GPU model, driver version, and current VRAM/utilization. If the command isn't found or errors out, see [If the Screen Goes Black](#if-the-screen-goes-black) below.

## Secure Boot and DKMS

The proprietary driver builds a kernel module via **DKMS** (Dynamic Kernel Module Support), which automatically rebuilds that module every time your kernel updates, instead of breaking on the next `apt upgrade`. Check its status with:

```bash
dkms status
```

If Secure Boot is enabled in your UEFI settings, an unsigned, DKMS-built module can fail to load, since Secure Boot only allows modules signed with a trusted key. The simplest fix is disabling Secure Boot in your BIOS/UEFI settings (covered in [boot order changes](./../001#final-step-change-the-boot-order)); the alternative is enrolling a Machine Owner Key (MOK) to sign the module yourself, which is more involved and out of scope here.

## Switching Back to Nouveau

If the proprietary driver causes more problems than it solves:

```bash
sudo apt purge '^nvidia-.*'
sudo reboot
```

Nouveau takes back over automatically, no reinstall needed since it's part of the kernel.

## If the Screen Goes Black

A black screen after installing or updating the NVIDIA driver usually means the display server can't talk to it. Drop to a TTY with `Ctrl+Alt+F2` through `Ctrl+Alt+F6` (same combination used in the [live ISO](./../002#entering-password)), log in, and either purge the driver as shown above or reinstall it cleanly:

```bash
sudo apt install --reinstall nvidia-driver nvidia-kernel-dkms
```

<blockquote class="note">
<span class="title">NOTE</span><br>
Booting once with the <code>nomodeset</code> kernel parameter can also get you to a usable console if a TTY switch alone doesn't work, add it temporarily from the GRUB boot menu without editing any files permanently.
</blockquote>

<hr>

#### Next steps,
<div style="text-align:center; font-size:3rem;">
008 -> <a href="./../009">009</a>
</div>

## Related pages

- [002 - Installation and setup](./../002)

- [004 - Our default apps](./../004)

- [009 - Troubleshooting in linux](./../009)