---
layout: default
title: "Downloading and checksum : Android"
description: "Guide for downloading files and verifying checksums. This branch follows making a bootable solution in Android."
embed-thumbnail: https://zynomon.github.io/error.doc/docs/001/thumb.png
icon: https://zynomon.github.io/error/icons/doc/android.svg
---

# ![Android Icon](https://zynomon.github.io/error/icons/doc/android.svg) Android.

<div align="left">
  <p>
    This guide is for Android users who want to create a Bootable USB drive from an ISO file,
    useful when a system is bricked or does not have any Bootable OS yet.
  </p>
  <table>
    <thead>
      <tr>
        <th>Stuff</th>
        <th>Why?</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>USB Drive or SD card reader</td>
        <td>Needed to create a bootable USB drive.</td>
      </tr>
      <tr>
        <td>ISO File Downloaded</td>
        <td>Without the ISO, there is nothing to flash.</td>
      </tr>
      <tr>
        <td>USB OTG</td>
        <td>Required to connect the USB drive to the Android device.</td>
      </tr>
      <tr>
        <td>Charge</td>
        <td>More than 40% battery ensures stability during the process.</td>
      </tr>
    </tbody>
  </table>
</div>

---

<h3 style="font-size:4rem;">Elaborated;</h3>

<hr style="border: 1px solid #fff;">
    
<div align="left">
  <img src="https://images.teamgroupinc.com/products/usb/usb-3/c211/32gb_02.jpg" width="150" height="150" alt="USB Flash Drive" align="left" />
  <div>
    Yes, people do brick their systems by booting in a corrupted operating system or if the user is new in this field. This guide will help you to prevent that and make a bootable USB drive.
    First, ensure that you have a USB Thumbdrive, also known as a USB Flash Drive or pendrive.
  </div>
  <sub>
    Img: A USB Flash Drive , source:
    <a href="https://www.teamgroupinc.com/en/product-detail/usb/TEAMGROUP/c211/c211-TC211332GL01/">teamgroupinc.com</a>
  </sub>
</div>

<br clear="all">

<div align="right">
  <img src="https://cdn.discordapp.com/attachments/1274694365100642414/1461015690600382586/IMG_20260114_211347.png?ex=69690464&is=6967b2e4&hm=ac19c619e1571b52f3928c27f28d83660377716ebef4ba093afb2404123207c7" width="150" height="150" alt="SD Card Reader" align="right" />
  <div>
    You can do it in the cheapest way possible by using an SD Card with an SD card reader. Because you don't need 128+ GB of pendrive just to flash a 3 GB ISO file. It's recommended you have it instead. So go to a store nearby, pick up a good SD card, then buy an SD card reader and insert the SD card into the reader and it will be done.
  </div>
  <sub>
    Img: A SD card reader with SD card inserted
  </sub>
</div>

<h4>OTG</h4>
<img=>
<sub>A standard USB OTG converter</sub>
OTG is the next step since maximum android device doesn't comes with a big usb port
you have to get an USB OTG <sub>Universal Serial Bus On The Go</sub>, buy it according to your charger port if your charger uses USB-C then get that kind of OTG with USB-C if micro usb ( older port ) then get micro usb OTG 

---

### NOW YOU ARE READY,
follow this steps,

#### 1. install from playstore
<img>
<sub>Well for now we have to compromise these ads, soon we will make our own flashing app,</sub>
    
#### 2. Connect your OTG , then The bootable device

<img>
<sub>By looking at OTG you may get it where to connect , make sure to not move it a little bit</sub>

#### 3. Now go to <App>
 - first you will see your SD card or pendrive device,  
<sub> if not then either your OTG got disconnected or your USB device is corrupted </sub>
 - then open the iso file ( assuming you are coming from (here)[https://zynomon.github.io/error.doc/docs/001] )
 - then click at flash to start flashing the usb
 - wait it may take a while do not touch your android device if it has weaker IO ports,
<sub> weak charging port disconnects anytime with fraction of touch</sub>
 - after finishing, plugin that usb to your computer or laptop device
 - now turn it on by power button and start spamming the f12 key ( del key if asus motherboard / f10 key for dell motherboard )
 - you will enter in bios,
 - locate boot configuration and set your USB device as #1 ( first )
 - press f10 , save and leave

 ### Congratulations you just booted up error.os , 
 still the path ahead is more time catching check the 
 
<div style="text-align:center; font-size:3rem;">
001 -> <a href="./../002">002</a>
</div>
 
 instead of installing your own, because the bootloader shows all kinds of options dont worry everything will be fixed in NS26
