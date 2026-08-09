---
layout: default
title: "Downloading, Checksum Verification And Booting The ISO"
description: "Guide for downloading files, Verifying checksums and Booting the ISO"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/001/thumb.png
icon: https://zynomon.github.io/error/icons/doc/doc.svg
---

# Downloading, Checksum Verification And Booting The ISO

## Table of Contents

- [Downloading](#downloading)
- [Checksum](#checksum)
  - [MD5](#md5)
  - [SHA Verifications](#sha-verifications)
  - [GPG Verifications](#gpg-verifications)
- [Making the ISO Boot](#making-the-iso-boot)
  - [Prerequisites](#prerequisites)
  - [1. Flashing a Medium](#1-flashing-a-medium)
    - [Step 1. Install balenaEtcher](#step-1-install-balenaetcher)
    - [Step 2. Insert the Medium](#step-2-insert-the-medium)
    - [Step 3. Flash](#step-3-flash)
    - [Final Step. Change the Boot Order](#final-step-change-the-boot-order)
  - [2. Setting Up with Ventoy](#2-setting-up-with-ventoy)
    - [How to Use Ventoy](#how-to-use-ventoy)
      - [1. Install Ventoy on the USB drive](#1-install-ventoy-on-the-usb-drive)
      - [2. Copy to "Ventoy" Partition](#2-copy-to-ventoy-partition)
      - [3. Boot from the Ventoy Drive](#3-boot-from-the-ventoy-drive)
  - [3. Virtualization](#3-virtualization)

# Downloading

For downloading the ISO, go to the [Main Website](https://zynomon.github.io/error/downloads).<br>

We recommend you use the latest version since this guide follows the latest one. If you are not a novice at using Linux, you could try out other versions, but they have known issues.<br>

For information about the naming, see [this](../000/).<br>

# Checksum

Checksum verification ensures that the ISO file is intact and detects if something is missing. It's not necessary to check unless you have the time and tools to do so.<br>

**[Click here to skip this boring part](#making-the-iso-boot)**

As for NeoSpace26 (NS26), we have [sums.7z](https://archive.org/download/error.os_Neospace_2026/sums.7z).<br>
Extract it by using `7z x sums.7z` (in any Windows/macOS/Linux terminal) OR if missing, visit [7z_Website](https://7-zip.org/download.html).

Even though the verification tutorial is already given on the NeoSpace 2026 page, let's make it more clear in a way that works with other ISOs.

Since our ISO file name changes on each update, we couldn't just give you a command for a certain version or use wildcards (wildcards could pull in two ISO files). We are referring to your downloaded ISO filename as `x`, and `x.iso`, `x.md5`... are the files derived from it.

> [!NOTE]
> `x` is a placeholder, not the actual filename.

### MD5

**What MD5 is:**  
MD5 produces a 128-bit hash (32 hex characters) for file integrity verification.

> [!WARNING]
> MD5 is cryptographically broken. Use only for basic integrity checks.

**Verify `x.iso` against `x.md5`:**

Linux/macOS:
```bash
md5sum -c x.md5
```
macOS alternative:
```bash
md5 x.iso
```
Windows (PowerShell):
```powershell
Get-FileHash x.iso -Algorithm MD5
```
> For Windows and macOS, manually compare with `x.md5`

---

### SHA Verifications

**What SHA is:**  
SHA is a cryptographic hash family by NIST, more secure than MD5.

**SHA256 vs SHA512:**

| Feature | SHA256 | SHA512 |
|--------|--------|--------|
| Output | 256 bits (64 hex) | 512 bits (128 hex) |
| Security | Very strong | Stronger |
| Speed | Faster on 32-bit | Faster on 64-bit |

> [!NOTE]
> Both are secure. SHA256 is more common.

**To verify `x.iso` against checksum files:** First, open your terminal.

Linux/macOS:
```bash
sha256sum -c x.sha256
sha512sum -c x.sha512
```

Windows (PowerShell):
```powershell
Get-FileHash x.iso -Algorithm SHA256
# manually compare with x.sha256
Get-FileHash x.iso -Algorithm SHA512
# manually compare with x.sha512
```

> For Windows and macOS, manually compare with `x.sha512` or `x.sha256`

<br>

> [!TIP]
> The `-c` flag checks the ISO against the hash stored in the `.sha256` or `.sha512` file. It outputs "OK" if matches.

### GPG Verifications

**What GPG is:**  
GPG (GNU Privacy Guard) uses public-key cryptography to verify file authenticity and integrity, ensuring the file came from the claimed source.

**Verify `x.iso` against `x.asc`:**
```bash
gpg --verify x.asc x.iso
```

> [!NOTE]
> The `.asc` file name could be different; follow the extension, not the name.

---

**Setting up GPG:**

Generate a new key pair:
```bash
gpg --full-generate-key
```

List your keys:
```bash
gpg --list-keys
```

# Making the ISO Boot

There are a few ways to boot error.os:

1. [In hardware using an error.os-flashed medium](#1-flashing-a-medium)
2. [In hardware using a Ventoy USB medium](#2-setting-up-with-ventoy)
3. [Through a VM: VMware/QEMU/VirtualBox](#3-virtualization)


> [!tip]
> Anything outside of that is not mainstream. Options 2 and 3, in experience, come in the same category for error.os since it doesn't try to save anything in the live system.
> **If you followed any of those 3 JUMP to Next Page [..002](../002/)**

## Prerequisites

Firstly, your device needs to fulfill the requirements of running error.os. You may fall into problems caused by you. Instead of blaming yourself for this matter, move on.

Secondly, you need a bootable medium: a USB drive or a MicroSD card + SD card reader combination. This is called a bootable medium, and throughout this guide, we will refer to it as the "medium."

Thirdly, the device you are currently using to read this guide, or any other, may work.

## 1. Flashing a Medium

Flashing an ISO into a USB simply means extracting the ISO into a wiped-out (formatted) medium. So, to do this, we will only cover balenaEtcher. Rufus (Windows) and other flashing applications cover this in the same way, so you could choose whatever you feel familiar with.

### Step 1. Install balenaEtcher

For Windows/macOS/Linux, [visit this](https://etcher.balena.io/#download-etcher).<br>
For Android, [visit this](https://f-droid.org/packages/eu.depau.etchdroid/).<br>
Download and try to open them.
Once it starts up,

### Step 2. Insert the Medium

Could be a USB thumb drive or "MicroSD Card + SD Card Reader combo" as mentioned earlier.
Now, the application should pick up that medium.

### Step 3. Flash

> [!WARNING]
> This process formats the USB drive and erases all existing data.

Now, select the ISO you just downloaded and let it flash into the medium. Wait for it to flash the `.iso` file. It may take a while since it's extracting 2 GB and formatting your medium.


### Final Step. Change the Boot Order

After flashing the ISO to your medium, you need to tell your computer to boot from it instead of your hard drive.

**For UEFI systems (most modern computers):**

1. Restart your computer
2. During startup, press the boot menu key:
   - **Dell/Alienware:** F12
   - **HP:** F9 or Esc
   - **Lenovo:** F12 or Novo button
   - **Acer:** F12
   - **Asus:** F8 or Esc
   - **MSI:** F11
   - **Samsung:** F12 or Esc
   - **Sony:** F11 or Assist button
   - **Toshiba:** F12
   - **Apple Mac:** Hold Option (⌥) key

3. From the boot menu, select your USB drive (usually labeled with the vendor name, e.g., "USB Flash Drive" or "UEFI: [Vendor Name]")
4. The system will boot from the USB drive and load error.os

**For Legacy BIOS systems (older computers):**

1. Restart your computer
2. During startup, press the setup key (usually **Del**, **F2**, or **F10**) to enter BIOS/UEFI settings
3. Navigate to the **Boot** tab
4. Change the boot order so your USB drive is first
5. Save changes and exit (usually **F10**)
6. The system will reboot and boot from the USB drive

**If the ISO doesn't boot:**

- **Secure Boot:** Some systems have Secure Boot enabled, which may prevent booting. Disable it in BIOS/UEFI settings under the **Security** or **Boot** tab.
- **Wrong port:** Try using a USB 2.0 port instead of USB 3.0 (some older systems have issues with USB 3.0)
- **Corrupted flash:** Re-flash the ISO using balenaEtcher or try a different USB drive
- **Fast Boot:** Disable Fast Boot in BIOS/UEFI if the system skips the boot menu

> [!TIP]
> If you're unsure which key to press, watch the screen during startup. Most computers display a message like "Press F12 for Boot Menu" or "Press Del to enter Setup."

## 2. Setting Up with Ventoy

Supports Windows and Linux. There may be some third-party software for Android and macOS as well.
Ventoy is an open-source tool that creates a bootable USB drive capable of booting multiple ISO files without reformatting. Unlike traditional tools that require burning one ISO at a time, Ventoy installs a bootloader once, then lets you copy ISO files directly to the drive.
To download it, visit: [Ventoy](https://www.ventoy.net/en/download.html).

### How to Use Ventoy

**1. Install Ventoy on the USB drive**

Insert the USB drive and run the Ventoy installer (Ventoy2Disk.exe on Windows, Ventoy2Disk.sh or VentoyGUI on Linux).

As for Linux, run it from the terminal to get information about any issues in stdout.
```bash
chmod +x ./VentoyGUI.x86_64 && sudo ./VentoyGUI.x86_64 
```

Select the correct USB device from the list and click Install.

> [!WARNING]
> This process formats the USB drive and erases all existing data.

**2. Copy to "Ventoy" Partition**

After installation, Ventoy creates two partitions: a small system partition and a visible data partition (exFAT by default).

Simply copy the ISO you just downloaded into the visible partition. You can place them in the root directory of that partition or in subfolders.

**3. Boot from the Ventoy Drive**

Insert the USB drive into the target computer and restart.

Enter the boot menu (usually F12, Esc, or F8) and select the USB drive. Usually, it starts with UEFI: on UEFI devices, it's usually the other option in the bootloader menu beside your SSD vendor's name and your currently installed OS's name.

Ventoy displays a menu listing all ISO files on the drive. Select the desired ISO and press Enter to boot.

> [!TIP]
> You can add, delete, or rename ISO files at any time without reinstalling Ventoy or reformatting the drive. The drive remains usable for regular file storage alongside bootable ISOs.

## 3. Virtualization

Since error.os is Debian-based, there are few known issues. On advanced applications like [Oracle VirtualBox](https://www.virtualbox.org/) and [VMware](https://www.vmware.com/products/desktop-hypervisor/workstation-and-fusion), they tend to auto-detect that error.os is Debian 64-bit. On some applications like [virt-manager](https://virt-manager.org/download), you have to manually do that.<br>

**The specifications to always set in a VM:** Select the live medium/bootable medium as the ISO file, OS as Debian 13 64-bit/amd64/x86_64 or Linux 64/GNU Linux 64, RAM: 1.5GB minimum, Storage: more than 8GB (error.os installations are typically 3GB or close to 4GB).

Alternatively, you could enable display graphics and more; they won't interfere with the system. It also works with UEFI and BIOS.

> [!TIP]
> You can try installing error.os inside a virtualization layer or emulation environment, where everything is saved in a single image file. This allows you to delete it once you're done.


#### Next steps,
<div style="text-align:center; font-size:3rem;">
001 -> <a href="./../002">002</a>
</div>

## Related pages

- [008 - Hardware Driver management in linux](./../008)

- [009 - Troubleshooting in linux](./../009)

- [010 - What to do and don'ts , in linux](./../010)