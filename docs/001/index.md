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
        <img align="left" size="16" src="https://custom-icon-badges.demolab.com/badge/-5391FE?logo=powershell-white&logoColor=fff" alt="pwsh badge" />
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
        <img align="left" size="16" src="https://img.shields.io/badge/-black?logo=gnu-bash" alt="bash badge" />
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

our following guide covers both of them, however, it is recommended to use a virtual machine for a quick look at the operating system before installing it on your computer, and we don't recommend using a bootable USB drive for this purpose, it is because IF **YOU ARE NEW IN LINUX AND FEAR TO TAKE RISKS WE CAN'T ASSURE YOU WILL SUCCEED**. However, if you are confident and want to try it, you can follow the instructions below.

---

### 1. Virtualization
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

### 2. Setting up a bootable USB drive

Here are few ways ways to setup a bootable USB drive in different operating systems:
---

<style>
.download-cards{display:grid;grid-template-columns:repeat(auto-fit,minmax(220px,1fr));gap:12px;margin-bottom:8px}
.download-card{display:flex;align-items:center;padding:12px;border-radius:8px;background:#fff;border:1px solid #e6e6e6;text-decoration:none;color:inherit;box-shadow:0 2px 6px rgba(0,0,0,0.06);transition:transform .12s ease,box-shadow .12s ease}
.download-card:hover{transform:translateY(-4px);box-shadow:0 6px 18px rgba(0,0,0,0.12)}
.card-icon{width:48px;height:48px;flex:0 0 48px;margin-right:12px}
.card-title{font-weight:600;font-size:1rem;margin:0 0 4px}
.card-desc{font-size:0.86rem;color:#555;margin:0}
</style>

<div class="download-cards">
  <a class="download-card" href="./linux.html" role="button" aria-label="Linux instructions">
    <img class="card-icon" src="https://img.shields.io/badge/-FCC624?logo=linux&logoColor=black" alt="Linux badge" />
    <div>
      <div class="card-title">Linux</div>
      <div class="card-desc">Instructions for creating a bootable USB or using common Linux tools.</div>
    </div>
  </a>

  <a class="download-card" href="./windows.html" role="button" aria-label="Windows instructions">
    <img class="card-icon" src="https://custom-icon-badges.demolab.com/badge/-0078D6?logo=windows11&logoColor=white" alt="Windows badge" />
    <div>
      <div class="card-title">Windows</div>
      <div class="card-desc">Tools and steps for writing the ISO to USB on Windows.</div>
    </div>
  </a>

  <a class="download-card" href="./android.html" role="button" aria-label="Android instructions">
    <img class="card-icon" src="https://img.shields.io/badge/-3DDC84?logo=android&logoColor=white" alt="Android badge" />
    <div>
      <div class="card-title">Android</div>
      <div class="card-desc">Guide for flashing or mounting the ISO on Android devices.</div>
    </div>
  </a>
</div>

---


#### Next steps,
<div style="text-align:center; font-size:3rem;">
001 -> <a href="./../002">002</a>
</div>

## Related pages
[008 - Hardware Driver management in linux](./../008)
[009 - Troubleshooting in linux](./../009)
[010 - What to do and don'ts , in linux](./../010)

---
