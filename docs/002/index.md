---
layout: default
title: "Installation and setup"
description: "Step-by-step installation and setup instructions"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/002/thumb.png
---


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
> **DO NOT change other settings in BIOS/UEFI unless you are familiar with them.** Changing incorrect settings can prevent your computer from booting properly.

The error.os ISO supports hybrid booting, which works with both BIOS and UEFI systems.


## Boot Options
For BIOS we used the good old isolinux
![BIOS](./items/bios.png)

and as for the modern UEFI we used grub bootloader.
![alt text](./items/uefi.png)

( it looks wierd in Virtualization, so dont get it wrong )

we tried our best to keep ISO Linux menu and grub menu similar.
so here are the options we added here

<br>
__`Live (amd64) (English)`__ : it means it will boot into ISO for Preview and let you install it in friendly  and easy manner. that amd64 means cpu with 64 bit arch.  also recommended to click on thats why we put it on first everything except this is kind-of risky for newcomer. 

<br>
> IF YOU GET STUCK TRY TO PRESS THE RESTART KEY OF YOUR CHASSIS in these options below.
<br>
__`HDT`__: it's for detecting hardware and showing information about it, useful before booting up any OS for installation.
<br>

__`Memory Diagnostic Tool (memtest86+)`__: it's explainable through its name it shows informations about Random access memory 
<br>

### Advanced Options
![!\[alt text\](image.png)](items/advanced-BIOS.png)

__`Live (amd64) (Bangla)`__ : Is the same thing as the english but with locale set to bn_BD, may break or may not.

__`Install`__ : installs it with debian's own installer its not recommended to use, as it just installs the Live ISO itself. DONT USE IT we put it for convinience.

__`Install (text mode)`__ : Is the same as __`Install`__  but in debian's text installer.

__`Live (amd64 failsafe)`__ : in this mode the system avoids GPU and boots up with the english locale.


> The installation guide below works with the GUI Based options eg. __`Live (amd64 failsafe)`__ , __`Live (amd64) (Bangla)`__  , __`Live (amd64) (English)`__ .


### entering password:
By default we added autologin to the sddm since in the last version it had issues,
but if you want to access tty or by some chance sddm comes up again use these credential,
username is error.user
and password  is user

and as for root user is root and password is toor alternatively you get those in the live tty through  using these key combination:
`crtl + alt + f2`   - tty2 ***to***  `crtl + alt + f6`  - tty6
it appears like that in Live ISO.

<img width="1023" height="672" alt="screen-08_08_13_55--2026" src="https://github.com/user-attachments/assets/d7d0c306-3506-4fa9-b8bc-c88638fd9587" />
>>>>>>> Coming more.
