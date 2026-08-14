---
layout: default
title: "Installation and setup"
description: "Step-by-step installation and setup instructions"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/002/thumb.png
---

## Table of Contents

- [Booting Up](#booting-up)
  - [Boot Order](#boot-order)
  - [Boot Options](#boot-options)
    - [Advanced Options](#advanced-options)
    - [Entering password](#entering-password)
- [Calamares: GUI Installer](#calamares-gui-installer)
  - [Step 1: Welcome](#step-1-welcome)
  - [Step 2: Locale](#step-2-locale)
  - [Step 3: Keyboard Mapping](#step-3-keyboard-mapping)
  - [Step 4: Partitioning](#step-4-partitioning)
    - [What Is Partitioning?](#what-is-partitioning)
    - [Option #1: Install Along Side](#option-1-install-along-side)
    - [Option #2: Replace A Partition](#option-2-replace-a-partition)
    - [Option #3: Wipe Out Entire Disk](#option-3-wipe-out-entire-disk)
    - [Option #4: Manual Partition](#option-4-manual-partition)
  - [Step 5: Setting Up User Password](#step-5-setting-up-user-password)
  - [Step 6: Confirmation](#step-6-confirmation)
  - [Step 7: The Moment Of Truth](#step-7-the-moment-of-truth)
  - [Step 8: Finish](#step-8-finish)
- [Things After Installation](#things-after-installation)
  - [1. Grub](#1-grub)
  - [2. Date & Time](#2-date-time)
  - [3. Onboarder (`once`)](#3-onboarder-once)

# Booting Up
<img width="1408" height="1152" alt="e" src="https://github.com/user-attachments/assets/733a9f71-73d7-4265-9652-ec5d451ae408" />

### Boot Order

After inserting your bootable medium, you need to tell your computer to boot from it.

1. Restart your computer
2. Immediately press the boot menu key repeatedly:
   - Common keys: **F10**, **F12**, **F1**, **Del**, **Esc**, or **F2**
   - The exact key depends on your motherboard manufacturer
   - Watch the screen for a message like "Press F12 for Boot Menu"

3. From the boot menu, select your USB drive (look for "UEFI:" followed by your USB name)

4. If the boot menu doesn't appear, enter BIOS/UEFI settings:
   - Press the setup key (usually **Del**, **F2**, or **F10**) during startup
   - Navigate to the **Boot** tab
   - Move your USB drive to the first position (Boot #1)
   - Press **F10** to save and exit

> [!WARNING]
> **Do not change other settings in BIOS/UEFI unless you are familiar with them.** Changing the wrong setting can prevent your computer from booting properly.

The error.os ISO supports hybrid booting, which works with both BIOS and UEFI systems.

## Boot Options

For BIOS, we use the classic isolinux bootloader.

![BIOS](./items/bios.png)

For modern UEFI systems, we use the GRUB bootloader.

![UEFI](./items/uefi.png)

(It may look different inside a VM, that's expected.)

We've tried to keep the isolinux and GRUB menus visually similar, so here are the options available:

<br>

**`Live (amd64) (English)`**: Boots into the live ISO for a preview and lets you install error.os afterward if you like it. "amd64" refers to a 64-bit CPU architecture. This is the recommended, default option. Everything else below is riskier for newcomers.

<br>

> If you get stuck in any of the options below, press your chassis's restart button.

<br>

**`HDT`**: Detects your hardware and shows information about it, useful before installing any OS.

<br>

**`Memory Diagnostic Tool (memtest86+)`**: Tests your RAM for errors, as the name suggests.

### Advanced Options
![Advanced boot options menu](items/advanced-BIOS.png)

**`Live (amd64) (Bangla)`**: Same as the English live option, but with the locale set to `bn_BD`. This may have rough edges.

**`Install`**: Installs using Debian's own installer. Not recommended, it just installs the live ISO as-is. We include it only for convenience; avoid it unless you know what you're doing.

**`Install (text mode)`**: Same as **`Install`**, but using Debian's text-based installer.

**`Live (amd64 failsafe)`**: Boots without GPU acceleration and defaults to the English locale. Useful if the normal live mode fails to start.

> The installation guide below works with the GUI-based options, e.g. **`Live (amd64 failsafe)`**, **`Live (amd64) (Bangla)`**, **`Live (amd64) (English)`**.

### Entering password:

By default, autologin is enabled for SDDM, since the previous version had login issues. If you need to access a TTY, or if SDDM asks for a password anyway, use these credentials:

username: `error.user`
password: `user`

<img width="1114" height="707" alt="screen-08_10_20_45--2026" src="https://github.com/user-attachments/assets/a26598ae-ff47-4063-a541-25c61631e2dd" />
<br><br>

The root user's username is `root` and password is `toor`. You can reach a TTY using this key combination:

`Ctrl + Alt + F2` through `Ctrl + Alt + F6` (TTY2 through TTY6). This works the same way in the live ISO.

<img width="1023" height="672" alt="screen-08_08_13_55--2026" src="https://github.com/user-attachments/assets/d7d0c306-3506-4fa9-b8bc-c88638fd9587" />

# Calamares: GUI Installer
<img width="330" height="255" alt="image" src="https://github.com/user-attachments/assets/a6234ab2-89e4-4163-ae9c-5b53d7b1b32f" />

Calamares is an open-source installer project maintained mostly by KDE developers. It's the default installer for several distros, including Debian, Zorin OS, and KDE Neon. While alternatives exist, none are as widely adopted as Calamares. What you're seeing here is our own [calamares-settings-error](https://zynomon.github.io/error/dists/stable/main/binary-all/e.html) package, you can inspect the package at that link. It's roughly 80% based on the original calamares-settings-debian.

<hr />

## Step 1: Welcome

Click Next. (The UI has some rough edges, suggestions for improving it are welcome.)

<img width="1055" height="577" alt="Screenshot_20260810_112346" src="https://github.com/user-attachments/assets/d6266dd1-a55f-49e4-8c6d-46383641481b" />

<hr />

## Step 2: Locale
<img width="1050" height="577" alt="Screenshot_20260810_112436" src="https://github.com/user-attachments/assets/99ef34ec-96e5-4bf6-98ec-a01b60bded71" />

If you don't want quirks like numerals changing to match your selected language, leave this untouched to keep your system and UI entirely in English. To make the system clock auto-update after installation, run this in a terminal:

```bash
sudo apt install systemd-timesyncd
```

> [!TIP]
> Don't confuse this with your physical location. This step is really about locale (language and regional formatting), not a VPN or GPS setting.

<hr />

## Step 3: Keyboard Mapping
<img width="1047" height="570" alt="Screenshot_20260810_112558" src="https://github.com/user-attachments/assets/96f3a472-809e-41e9-886e-9e67b4f63883" />

Keyboards vary by region and manufacturer, so this step defaults to the most common QWERTY layout. Change it if yours is different.

> [!TIP]
> Search for your keyboard model to find out which layout it uses. This may not work for lesser-known or generic keyboard brands.

<hr />

## Step 4: Partitioning
<img width="1048" height="562" alt="Screenshot_20260810_113919" src="https://github.com/user-attachments/assets/c9e267cf-affb-43ff-8ee4-ceac46d331f8" />

This is the step where new Linux users most often make mistakes, so pay close attention.

### What Is Partitioning?

<details><summary>It's simply dividing the storage you have (HDD / SATA SSD / NVMe SSD, etc.) into sections so the OS can be installed and boot from one of them.</summary>

<br>

Linux uses the Unix file hierarchy (also used by Android, macOS, BSD, and more):

```text
                                                       /
                                                       |
   -------------------------------------------------------------------------------------------------
   |    |     |    |    |     |    |      |     |    |    |      |    |    |     |    |    |    |    |
  bin  boot  dev  etc  home  lib  lib64 media  mnt  opt  proc  root  run  sbin  srv  sys  tmp  usr  var
```

That's why file paths are written starting with `/`, e.g. `/usr`, `/run`, `/sbin`, `/bin`, `/sys`.

#### What do these directories mean?

<b>/usr</b> - User system resources. Contains programs, libraries, documentation.<br>
<b>/usr/lib &rarr; /lib &amp; /usr/lib64 &rarr; /lib64</b> - Shared libraries and kernel modules.<br>
<b>/usr/bin &rarr; /bin &amp; /usr/sbin &rarr; /sbin</b> - Essential and system administration binaries.<br>
<b>/home</b> - User home directories. Personal files and settings for each user.<br>
<b>/etc</b> - System-wide configuration files. Contains settings for OS, services, and applications.<br>
<b>/proc &amp; /var &amp; /srv</b><br>
&nbsp;&nbsp;/proc - Virtual filesystem. Runtime process and kernel information (CPU, memory, processes).<br>
&nbsp;&nbsp;/var - Variable data. Logs, caches, spools, mail, databases that change frequently.<br>
&nbsp;&nbsp;/srv - Service data. Data for system services like web servers (/srv/www/) or FTP.<br>
<b>/boot</b> - Boot loader files. Contains the Linux kernel (vmlinuz), initrd.img, and GRUB bootloader configuration.<br>
<b>/dev</b> - Device files. Represents hardware devices (hard drives, USB, terminals, null, random).<br>
<b>/media &amp; /mnt &amp; /opt</b><br>
&nbsp;&nbsp;/media - Mount point for removable media (USB drives, CDs, DVDs). Auto-mounts here.<br>
&nbsp;&nbsp;/mnt - Temporary mount point for manually mounted filesystems.<br>
&nbsp;&nbsp;/opt - Optional third-party software packages (add-on applications).<br>

For more information, see <a href="https://zynomon.github.io/error.doc/docs/011/">011</a>, check it out once you're done here.

This section installs the OS into your storage and erases the space you selected for installation.

</details>

Normally, this step shows four options if your system meets the requirements. If there's a problem with automatic partition detection, only Manual Partition will show. Always double-check your setup, you can restart, or create a new partition from unallocated space using the KDE Partition Manager.

### Option: #1 [Install Along Side]
<img width="1048" height="562" alt="Screenshot_20260810_113955" src="https://github.com/user-attachments/assets/94317b56-9fdf-4a3e-b979-831bba48d2de" />

Installs error.os into a partition with more than 5GB of free space, creating a new partition alongside your existing ones without touching them. Best when you have plenty of free space on another OS's partition, or for dual-booting.<br>

### Option: #2 [Replace A Partition]
<img width="1043" height="565" alt="Screenshot_20260810_114028" src="https://github.com/user-attachments/assets/a72f13da-a7f7-4c17-8fa3-e1e07f4f88f7" />

Replaces the selected partition with error.os. Best for dual-booting.<br><br>

### Option: #3 [Wipe Out Entire Disk]
<img width="877" height="532" alt="image" src="https://github.com/user-attachments/assets/eefa8aa7-c9ac-43e5-8f32-17967f5b6c98" />

Wipes the entire selected disk and installs error.os alone. Best if you plan to use error.os as your daily driver.<br><br>

### Option: #4 [Manual Partition]

Now for manual partitioning.

<img width="900" height="579" alt="Screenshot_20260810_114107" src="https://github.com/user-attachments/assets/7983c6ed-0b52-4c6a-ba06-fbc0f42229bb" />

Here's a rough guide:

- `/boot`: 500MB
- swap: match your RAM size (in GB)
- root (`/`): use Btrfs if you want built-in snapshots/backups, or ext4 to keep things simple

You can customize further, but only if you know why you need to.<br><br>

<hr />

## Step 5: [Setting Up User Password]
<img width="684" height="335" alt="Screenshot_20260810_111909" src="https://github.com/user-attachments/assets/e81a2074-4467-414b-a7c9-425888ae183b" />

This step is fairly self-explanatory, but here's what each field does. Your **username** is what you'll see in the terminal. Your **display name** only shows up on the SDDM login screen, lock screen, and the Kicker (application) menu. The **hostname** appears as `[username@hostname]` in some terminal prompts.

**first field** -> Display name ( keep it long and accurate, doesn't matter much )
**second field** -> username ( keep it short )
**third field** -> hostname ( keep it short and memorable )
**fourth field** -> password ( you'll type it frequently, so keep it memorable to you )
**tick ( autologin )** -> SDDM autologin ( logs in automatically on startup instead of asking for a password, good for single-user devices, not for security-conscious setups )

<br>

## Step 6: [Confirmation]
<img width="1054" height="597" alt="Screenshot_20260810_112002" src="https://github.com/user-attachments/assets/d3be78bc-eccb-4fa1-9979-b6d52187e386" />

Review your choices for mistakes, then click Next if everything looks correct.

> [!WARNING]
> This action deletes the existing data on the device you are installing to.

## Step 7: [The Moment Of Truth]
<img width="1920" height="1080" alt="install" src="https://github.com/user-attachments/assets/f70d7fa1-53a7-46c8-9459-4d28556477ee" />

The actual installation now begins. It usually takes 3-8 minutes, but can take up to 30 depending on your hardware. If it freezes (more common in VMs) try increasing the VM's allocated RAM and restart the installation.

## Step 8: [Finish]

The system restarts automatically once installation finishes.

# Things After Installation
<img width="730" height="655" alt="screen-08_10_21_51--2026-01" src="https://github.com/user-attachments/assets/631b1cc4-6a43-4a48-b975-8d89cc061917" />

Everything should work well after installation. You'll see an onboarding prompt, once you're through it, you're in error.os.

There are a few known issues on the installed system:

### 1. Grub
<img width="1060" height="659" alt="screen-08_10_21_51--2026" src="https://github.com/user-attachments/assets/1442124f-7fd7-4298-bd94-69a1ccbac4fa" />

Run this in a terminal to update the bootloader (this will be automated in a future patch):

```bash
sudo update-grub
```

<img width="1036" height="651" alt="screen-08_10_21_55--2026" src="https://github.com/user-attachments/assets/543b2a9a-4c92-439f-ad66-6965d2c67809" />
<br><br>
<img width="1005" height="756" alt="screen-08_10_22_42--2026" src="https://github.com/user-attachments/assets/51116e5f-bf19-4f43-a34e-81e4a0e50390" />

This is the real error.os grub theme.

### 2. Date & Time

If you run into time-sync issues, install and configure `ntp`. It fetches accurate time data over the internet based on your location.

### 3. Onboarder (`once`)

The onboarding app is called `once`, it walks you through installing recommended apps. Currently there's a typo (`firefox` instead of `firefox-esr`) that causes a package-not-found error, so the preselected app bundle won't install. This will be fixed in the next update.

<hr>

#### Next steps,
<div style="text-align:center; font-size:3rem;">
002 -> <a href="./../003">003</a>
</div>

## Related pages

- [004 - Our default apps](./../004)

- [005 - Customizing](./../005)

- [011 - Advanced easy guide to linux](./../011)
