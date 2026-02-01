---

layout: default
title: "Downloading and checksum - Make a bootable usb in Windows"
description: "Guide for downloading files and verifying checksums this branch follows making bootable solution in Windows"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/001/thumb.png
icon: https://zynomon.github.io/error/icons/doc/windows.svg
---

# THIS IS NOT THE FINAL
# [img] Windows 

--- 

Windows also known as Microsoft windows is another example of an operating system, so first of all we are going to talk about the accessories requirements and where to find them, 

## Physical Accessories. 
Indeed you need a usb device to flash "usb" isn't that self explanatory? 

### 1. USB
[Img]
Usb thumb drive or Pendrive is widely used and known we recommend you to have a good and new healthy pendrive . But recommendations doesn't matters if  it works. So you need minimum of **4GB** Usb pendrive which doesn't exist in 2026 you can see in market 32 GB is the least. 

### OR;
[Img]
Sd card reader is another great way and it's also cheaper but it can also give unstablity since the sd card and card reader is separate in this case get a good sd card reader. 

## Softwares, 
You also need some softwares, 

### Rufus 

### OR; 

---

## Steps
1. Download Rufus or ventoy and setup
2. Download the iso from [link]
##### Go to [link] and download the iso file it should be easy. Now move that file to your existing computer to flash if you haven't. 
3. Plug in the usb/sd card reader
##### plugin the thing that's going to be flashed ( converting to bootable usb) 
4. Check in the Rufus or ventoy if the device is showing
##### a device may show up . 
5. Flash
##### now open the usb flashing software and choose your  device that is going to be flashed 
>alert  
> this will remove existing data on that pendrive. 

6. Reboot 
##### now reboot the device and keep pressing F12 key of your keyboard every Miliseconds if possible , if it's 50% keyboard try numlock+[f2] when the device starts up in reboot ( known as restart) it will boot into BIOS
7. Bios
##### BIOS is the last stage, start finding the "Boot or Bootloader" related options change the first bootable system by changing the Microsoft/windows bootloader to your USB Device or Sd card reader name the most common name is vendor.co or if your device is branded it will show up as that name select it and save it  then  press  F10 key of your keyboard and save the changes **[** ***don't worry it won't do any harm to windows operating system currently*** **]** now the device should boot up into error.os 

Check  [Installing](. /../002) 
It covers from bootloader to installing and troubleshooting issues  do not attempt to install it on your own the experience might be worse 

---
