---
layout: default
title: "Our default apps"
description: "Overview of default applications included"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/004/thumb.png
---

## Table of Contents

- [Introduction](#introduction)
- [Our Daily Graphical User Interface (GUI) Apps](#our-daily-graphical-user-interface-gui-apps)
  - [error.doc](#-errordoc)
  - [Vex](#vex)
  - [err_](#err_)
  - [Onu](#onu)
- [Pitfalls](#pitfalls)
- [Some Underlying error.os Applications](#some-underlying-erroros-applications)
  - [error.base](#errorbase)
  - [error.os installer (calamares-settings-error)](#erroros-installer-calamares-settings-error)
  - [libtrigonometry](#libtrigonometry)
  - [once](#once)

# Introduction

After installation, you get a set of applications built by the error.os team as lighter alternatives to the usual storage-heavy defaults. This page also covers the packages that build error.os itself behind the scenes.

# Our Daily Graphical User Interface (GUI) Apps

- error.doc
- err_
- vex
- onu

<h3>
<img width="48" height="48" src="https://github.com/zynomon/error.doc/raw/main/.deb/install/error.doc.svg" alt="error.doc logo"> <b>e</b>rror<i>.doc</i>
</h3> 
error.doc is the Qt-based viewer behind this documentation. It browses three URL schemes: `:/err/` for pages like this one, `:/man/` for your system's manpages, and `:/doc/` for its own settings, bookmarks, and about page. It supports tabs, bookmarks, `Ctrl+F` find-in-page, text highlighting, and text-to-speech for reading selected text aloud. The manpage viewer, previously listed as a to-do, is now fully implemented.

### Vex
<img width="887" height="645" alt="image" src="https://github.com/user-attachments/assets/805d4c93-c19c-492f-95c7-6bde655e0ce9" />

Vex is a cross-platform C++ text editor, currently on version 4.1 ("Cytoplasm"). It's built on Qt and runs on Windows, Linux, and FreeBSD (no macOS support yet). Since version 4.0 it's plugin-based: core features load in three tiers (structural "Xylem" plugins first, enhancement "Phloem" plugins second, standalone "Simple" plugins last). It ships with Find & Replace, an "Open by name" feature that works like `vi ~/.bashrc` (creates the file if it doesn't exist, with path autocompletion), and a custom syntax-highlighting engine driven by `.vxsyn` definition files. Downloads are available as a Windows installer, Linux AppImage/deb/rpm/tar.zst, and a FreeBSD package.

### err_

<img width="870" height="597" alt="image" src="https://github.com/user-attachments/assets/6beb5f72-d919-4143-a1e9-77faa993488f" />
<img width="813" height="580" alt="image" src="https://github.com/user-attachments/assets/5e6593bc-ae66-44c5-959a-4d1236075a38" />

err_ can be pronounced "E.R.R. Dashboard." Now on version 3.0, it's the closest thing error.os has to a control panel: a System Info tab (CPU, RAM, storage, uptime, hostname), a Driver Manager (detects your GPU/CPU vendor, installs NVIDIA or printer drivers, offers to remove unused microcode or GPU drivers for other vendors), an App Installer split into dpkg, Flatpak, and wget tabs with curated app lists, an App Remover, and an Extra Settings tab with a Wine configuration/optimizer tool, a shortcut to system settings, and links to its GitHub repo and wallpaper gallery.
> [!TIP]
> Dont click too much on the logo.


### Onu

Onu is a small Qt6 WebEngine-based browser, currently on version 0.6 (beta), licensed Apache 2.0. On KDE, most of its packages are under 1MB, though non-KDE desktops can pull in up to 200MB of dependencies; its AppImage build is typically under 100MB. From version 0.5 onward it depends on the crash-handling part of libtrigonometry. It has dockable, floating toolbars (URL/search, Favorites, Navigation, Tabs, Recents), a customizable `onu://home` dashboard with widgets like a clock and rotating quotes, a multi-segment download manager with pause/resume, QSS-based theming, a Qt-plugin extension system, and a hosts-file style adblocker.

# Pitfalls

All the applications above share common issues: they're in beta, can be laggy, and are still buggy in places, since they haven't had much real-world user feedback yet.

# Some Underlying error.os Applications

This list contains the following packages:

- calamares-settings-error
- error.base
- libtrigonometry
- once

<div align="right">
<img src="https://github.com/user-attachments/assets/66384ead-09a9-4e6e-ac8d-3c546e004ec5" width="350" height="350" alt="error.base" align="right" />
<h1>error.base</h1>
<div>
Think of <code>error.base</code> as the "soul" of error.os. It's the package that makes a plain Debian system actually <em>feel</em> like error.os.<br><br>
When it installs, it runs a script (called <code>postinst</code>) that customizes the system. This is where the OS gets its personality, the error.os branding, settings, and identity.<br><br>
Normally, when you install a package, this setup script runs automatically. But when Calamares just unpacks files (like copying a bunch of folders to a new disk), it doesn't always run those scripts. That's why we sometimes have to "trigger" it manually after installation.<br><br>
If error.os were a car, <code>error.base</code> would be the paint job, the logo on the steering wheel, and the seat covers. The car still drives without them, but it doesn't feel like <em>your</em> car.
</div>
</div>
<p><br clear="all" /></p>
<div align="left">
<img src="https://github.com/user-attachments/assets/d6266dd1-a55f-49e4-8c6d-46383641481b" width="520" height="300" alt="calamares" align="left" />
<h1>error.os installer (calamares-settings-error)</h1>
<div>
This is the package that tells Calamares (the installer program) how to install error.os. It's like a set of instructions and a theme for the installer.<br><br>
It controls how the installer looks (the slideshow, branding, colors) and what steps it takes during installation, like partitioning disks, copying files, setting up users, installing the bootloader, and cleaning up.<br><br>
It doesn't install the system itself, it just <em>guides</em> Calamares. It tells Calamares: "Use this branding, remove these packages after installing, and run this script to set up error.os properly."<br><br>
If error.os is a car being assembled, <code>calamares-settings-error</code> is the instruction manual and the paint booth.
</div>
</div>
<p><br clear="all" /></p>

### libtrigonometry

libtrigonometry is a small C++ library for Qt applications. Right now it ships two working headers, both focused on crash handling:

- **COS** (Character Output Streambuffer): captures an application's stdout/stderr and writes it to a timestamped log file, while also setting up signal handlers for crashes (`SIGSEGV`, `SIGABRT`, and similar) and capturing a stack trace when one happens.
- **COSEC** (Crash Output Stream Executor): builds on COS with a Qt6 GUI crash reporter, so a crash shows a window instead of just a log file.

> [!NOTE]
> Earlier drafts of this page described `sin.h` as a "system information fetcher" and `cot.h` as a "translation system." Neither exists in the library yet, the project's own README lists only COS and COSEC as implemented, with more headers planned.

### once
<img width="1225" height="786" alt="image" src="https://github.com/user-attachments/assets/6fff8e0b-5339-4a9d-8f03-d78806822a63" />

`once` used to be a separate onboarding script paired with a systemd-driven cleanup component. As of Neospace 2026, it's been rebuilt as a single Qt binary: the external scripts and the systemd piece are gone, and only the onboarding wizard remains.
<img width="1011" height="463" alt="image" src="https://github.com/user-attachments/assets/1909f78a-ba5b-404e-9dca-11387f3bcbd8" />

On first login, it walks through a short setup: a welcome screen, a nudge to press the Windows/Super key to open your app launcher, a license screen (it types out both a short philosophy statement and the Apache 2.0 license text), and a package selection screen. That screen offers profiles like Minimal, Essential, Gaming, Developer, Digital Art, Graphic Designer, File Server, Student, and Cyber Security, each mapped to a curated `apt` package list. Picking one or more profiles builds an `apt install` command live in a small terminal-style preview. Finishing the wizard opens a real terminal to run that command, then removes its own autostart entry, true to the name: it only runs once.

<hr>


> [!TIP]
> MORE INFORMATION ABOUT THESE COULD BE FOUND ON The [Github Repo Tab](https://github.com/zynomon?tab=repositories)
> you could find source code as well as the readme about some.

#### Next steps,
<div style="text-align:center; font-size:3rem;">
004 -> <a href="./../005">005</a>
</div>

## Related pages

- [002 - Installation and setup](./../002)

- [005 - Customizing the distro](./../005)

- [010 - What to do and don'ts, in linux](./../010)
