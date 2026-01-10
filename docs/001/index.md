---
layout: default
title: "Downloading and checksum"
description: "Guide for downloading files and verifying checksums"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/001/thumb.png
---

# Downloading and checksum
---
### Downloading
you can find latest Neospace 2025 release in the following Internet archive: 
[details/error.os_Neospace_2025](https://archive.org/details/error.os_Neospace_2025)

alternatively, you can directly fetch it using ia cli tool:
```bash
ia download error.os_Neospace_2025
```
Please wait while downloading the file it may take a while.


### Checksum
> as if now in neospace we deliver 2 ways to verify the integrity of the downloaded file.


#### manual
you can manually download from the internet archive website and we showed you how to verify the checksums.

#### sums.7z
sums.7z contains all checksums in a single file. so if you extract the file make sure to have a zip file extractor or 7z it's also free to download from [here](https://www.7-zip.org/download.html). next step is to verify using these tools , if you are on windows you can use these commands to just skip the headache of using a browser following command directly installs iso and verifies it :

### Scripts to automate the process
<details>
    <summary>
        <img src="https://custom-icon-badges.demolab.com/badge/-5391FE?logo=powershell-white&logoColor=fff" alt="pwsh badge" />
        <b>Windows (pwsh) version</b> <span style="font-size:14px;">(click to expand)</span>
    </summary>
<pre><code>

New-Item -ItemType Directory -Force -Path "$HOME/downloads/iso"
Set-Location "$HOME/downloads/iso"

Invoke-WebRequest -Uri "https://archive.org/download/error.os_Neospace_2025/error.os_Neospace_2025.iso" -OutFile "error.os_Neospace_2025.iso"
Invoke-WebRequest -Uri "https://archive.org/download/error.os_Neospace_2025/sums.7z" -OutFile "sums.7z"

& 7z x sums.7z
& gpg --verify iso_verification.gpg error.os_Neospace_2025.iso

$expectedSha512 = (Get-Content "iso_verification.sha512.txt").Split(" ")[0]
$actualSha512   = (Get-FileHash -Algorithm SHA512 -Path "error.os_Neospace_2025.iso").Hash
if ($expectedSha512.ToUpper() -eq $actualSha512.ToUpper()) { "SHA512 verification passed" } else { "SHA512 verification FAILED" }

$expectedSha256 = (Get-Content "sha256sum.txt").Split(" ")[0]
$actualSha256   = (Get-FileHash -Algorithm SHA256 -Path "error.os_Neospace_2025.iso").Hash
if ($expectedSha256.ToUpper() -eq $actualSha256.ToUpper()) { "SHA256 verification passed" } else { "SHA256 verification FAILED" }

$expectedMd5 = (Get-Content "md5sum.txt").Split(" ")[0]
$actualMd5   = (Get-FileHash -Algorithm MD5 -Path "error.os_Neospace_2025.iso").Hash
if ($expectedMd5.ToUpper() -eq $actualMd5.ToUpper()) { "MD5 verification passed" } else { "MD5 verification FAILED" }

</code></pre>
</details>

<details>
    <summary>
        <img src="https://img.shields.io/badge/-black?logo=gnu-bash" alt="bash badge" />
        <b>Linux (bash) version</b> <span style="font-size:14px;">(click to expand)</span>
    </summary>
<pre><code>

mkdir -p ~/downloads/iso
cd ~/downloads/iso
wget https://archive.org/download/error.os_Neospace_2025/error.os_Neospace_2025.iso
wget https://archive.org/download/error.os_Neospace_2025/sums.7z
7z x sums.7z
gpg --verify iso_verification.gpg error.os_Neospace_2025.iso
sha512sum -c iso_verification.sha512.txt
sha256sum -c sha256sum.txt
md5sum -c md5sum.txt

</code></pre>
</details>


# Booting up 
here are few ways to boot up the iso file:
1. Virtualization
2. Bootable USB drive

> our following guide covers both of them
> .

### 1. Setting up a bootable USB drive

Here are few ways ways to setup a bootable USB drive in different operating systems:
---

- [![Linux](https://img.shields.io/badge/-FCC624?logo=linux&logoColor=black)](./linux.html) [Linux](./linux.html)
- [![Windows](https://custom-icon-badges.demolab.com/badge/-0078D6?logo=windows11&logoColor=white)](./windows.html) [Windows](./windows.html)
- [![Android](https://img.shields.io/badge/-3DDC84?logo=android&logoColor=white)](./android.html) [Android](./android.html)


### 2. Virtualization
For virtualization, you can use tools like VirtualBox or VMware to create a virtual machine and boot from the ISO file. Here are some guides for setting up virtual machines with different operating systems:
download a virtualization software like VirtualBox or VMware and follow the instructions to create a virtual machine and boot from the ISO file.
- [VirtualBox](https://www.virtualbox.org/wiki/Downloads)
- [VMware](https://www.vmware.com/products/workstation-pro.html)

After that setup the virtual machine and boot from the ISO file.
- Debian 13 64x bit
- ram 1500 mb
- cpu 1 cores
- disk 10 gb
- for the rest keep as your liking,

--
# TO BE CONTINUED
