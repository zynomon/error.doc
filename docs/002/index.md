---
layout: default
title: "Installation and setup"
description: "Step-by-step installation and setup instructions"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/002/thumb.png
---


# Booting Up
[Booting up is easy](./items/anim.webp)

## Boot Order.
By default we have two bootloader for the ISO, this function is known as hybrid booting it supports BIOS and UEFI
BIOS is the abbrivation of basic input output system it's what stays in your cmos battery of your motherboard.

UEFI stays in the same place of BIOS but more modern  UEFI tends to have mouse input output recognition running in it. 

the key distinction of both is in booting up something. and configuring in them.

Both has one thing in common that is editing the boot configuration after inserting the error.os ISO containing ventoy device spamm click  f10 f12 f1 or del key of your keyboard ( it changes according to the motherboard vendor )  it will open you to a place called BIOS look for boot options and add one entry starting with "UEFI:<sub>...</sub>" to the "boot #1" or at the first order by  clicking space enter and up and down keys of your keyboard. after than  press `f10` or look for save changes and reboot or similar and listen DO NOT Change other options in BIOS/UEFI Unless you are familiar with the environment. 

## Boot Options
For BIOS we used the good old isolinux
![BIOS](./items/bios.png)

and as for the modern UEFI we used grub bootloader.
![alt text](./items/uefi.png)

( it looks wierd in Virtualization, so dont get it wrong )

we tried our best to keep ISO Linux menu and grub menu similar.
so here are the options we added here
__`Live (amd64) (English)`__ : it means it will boot into ISO for Preview and let you install it in friendly  and easy manner. that amd64 means cpu with 64 bit arch.  also recommended to click on thats why we put it on first everything except this is kind-of risky for newcomer. 

> IF YOU GET STUCK TRY TO PRESS THE RESTART KEY OF YOUR CHASSIS in these options below.
__`HDT`__: it's for detecting hardware and showing information about it, useful before booting up any OS for installation.

__`Memory Diagnostic Tool (memtest86+)`__: it's explainable through its name it shows informations about Random access memory 

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


