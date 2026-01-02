# DOCUMENTATION UNDER CONSTRUCTION 
error.doc is the documentary for error.os now it's in under development, the goal is to have a  manpage like cli  documentary viewer with a qt web view in gui that fetches data from  https://zynomon.github.io/error.doc which is also under construction
the gui will have --gui flag in the   .desktop  and if not used  --gui flag it will run in cli making it an universal documentary + manpage viewer


-------documentary begins from here -------------------------

___



error.os Neospace 2025 is debian based system, following doc readme contains information about this distribution as if now it's being made under 2 months yet it's typically lame,
in error.doc we are going to learn how to use error.os as if it's your playgrounduyt
we will discuss  about every chosen packages for error.os you will get idea about what to do
use ``gh repo view zynomon/error.doc``
if your minimal tty device supports github cli

---
# the philosophy?
there is no philosophy  we build we distroy, we make erros we correct them 
so why should we hide it.

here we begin..

---
# GRUB AND ISOLINUX USAGE IN error.os 

grub or gnu grub is an opensource software , it's more customizable and versatile 
when it comes to comparing it with other bootloaders like windows bootloader 
grub has a good reputation  for having a solid performance, 
and thus as debian it's being used on error.os too

for having a short set of time what we did was adding grub png instead of making our
own grub theme as if it may become slower on some older windows 98 used devices ( hilarious ik )
and we added a grub customizer in the err_ ( error.os dashboard which is not a tui app )
the grub is widely used for uefi devices but in error.os you have to unlock secure boot 

Isolinux is another bootloader specialized and widely used for running live iso on bios based older systems 

there are two images for error.os bootloaders 
# live iso 
<img width="640" height="480" alt="splash" src="https://github.com/user-attachments/assets/bd018795-3c26-4ba3-bff4-f3d4f5e98af4" />

# Base system 

<img width="1366" height="768" alt="grub" src="https://github.com/user-attachments/assets/74580b9b-0229-48fa-a448-9c7fb2ce6d4f" />

the packages that are mentioned are
`apt show grub-common grub-pc grub-themes grub-efi-amd64 grub-efi-ia32 grub2-common grub-pc-bin grub-efi-amd64-bin isolinux`
-# not all of them are installed in any error.os device

---

 > to be continued 
