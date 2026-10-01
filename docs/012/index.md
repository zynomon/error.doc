---
layout: default
title: "The story of the distro"
description: "The story behind the distribution"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/012/thumb.png
---

### September 2025

**zynomon aelius, the main dev:** That day it all began. It was a strange day; I was scratching an itch with Porteus Linux.

2025 was the year I started using Linux. I daily drove Debian 12 for a while, but then distro-hopping syndrome got me. The idea occurred to me to start my own operating system instead, so I began working on it.

After a few days of nonstop digging into Debian and its ecosystem, the first ISO was completed by the end of September. At the time, I made the mistake of not having a Debian repo and instead used Penguins' Eggs to build it. It was tagged Void v1, even though my intention was to make a Neospace version; every Void version since has received the same treatment. err_ was created around this time.

### October 2025

This period represented both the peak and the baseline for error.os. We used live-build to create a Debian derivative, "error.os". Within roughly one or two sleepless nights, Vex and Onu were created. This update also brought calamares-settings-error and error.base, and the first concept for the error.os repo was established on GitHub Pages.

A dpkg repo on GitHub Pages? See for yourself: error.os never spent any money, nor did it earn any. We currently do not have a domain name of our own.

### November 2025

This release was later called Void v2. It was the update worked on throughout October.

### December 2025

The first version of error.doc was also created, though it was rushed and functioned only as a Chromium site opener (opening this very website).

This was the first real debugging period for error.os. The goal was simple: make it small, fast, and user-friendly, while maintaining the vibe that makes it "error.os". Instead of tedious debugging, we moved to a bash script for the live-build setup, and for other programs, we focused on providing the most stable experience possible.

We moved drastically from raster to vector graphics and began using system icon themes, which reduced the web browser's size to under 500 KB.

At the end of the month, the first stable release of error.os's Neospace was released, tagged NS25 (Neospace 2025). It was published on the last day of 2025 on the [Internet Archive](https://archive.org).

### January 2026

The start of a new journey toward a more stable version. Work on error.doc (this documentation) continued throughout the month.

Around this time, and again in March and April, work was done on Onu to make it an extension-based, toolbar-based web browser.

### March 2026

Work on Vex continued throughout this period.

Vex is a text editor, loosely inspired by Vim and FeatherPad, with an extra layer of extensibility. Three things set it apart:

1. **A syntax system that can define itself using its own syntax.** As of now, it doesn't have an official name, so we call it "vxsyn" after its temporary file extension. It defines itself by highlighting colors and interpreting the definition directly inside the same binary.
2. **A plugin system** that loads Xylem, Phloem, and Simple types of plugins, each with its own priority order.
3. **A tiny base.** The application was under 100 KB, which made the editor easy to build upon.

```
/bin/vex: ELF 64-bit LSB pie executable, x86-64, version 1 (GNU/Linux), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=0f8cd2bedc43c9d12d0e749abbcdf2a4c063f4cf, for GNU/Linux 3.2.0, not stripped 89K
```

On March 18, version 4.0 introduced this new "extensive" system. It was refined in version 4.1 on March 20, which added Windows executables and an NSIS installer. Later versions have some gaps on Windows, which should be resolved in the next stable release of Vex, 4.5.

<<<<<<< HEAD
Also void V3 ( Neospace 2026 beta ) was released by this time.

=======
>>>>>>> cfde602 (git commit commit more)
### April 2026

Development of Vex began to evolve drastically. Release 4.2 fixed several issues.

Neospace 2026 (NS26) was released around this time. It had minor bugs, but fewer and smaller than previous versions.

### May 2026

Vex added Uplugin, a system where Vex plugins communicate with another plugin system called Uplugin (short for "user plugin"). I also developed several plugins to improve Vex and its use of the plugin system. The admin-based plugin system became a safe user-plugin system with a friendly GUI for management. Since then, no new Windows release has been issued.

The first alpha version of the Onu web browser was also released at this time.

### June and July 2026

Some wallpapers were created during this time. Although they were intended for error.os, the decision was later reconsidered.

### August 2026

I started turning the unfinished error.doc into a stable, TTS-based manpage reader and more, featuring a friendly URL-scheme system that primarily uses XDG icons.

### September 2026

error.os NS26+1 arrived, along with improvements to "once" (the onboarder), "err_", error.doc, "libtrigonometry", and other unfocused packages. The previous attempt at running most things through terminal execution was replaced by libterm (tan), the part of libtrigonometry that executes commands in a terminal live.

<<<<<<< HEAD
This release specifically addressed the minor bugs found in version NS26. after that Neospace 2026 has been declared as Void V4.
=======
This release specifically addressed the minor bugs found in version NS26.
>>>>>>> cfde602 (git commit commit more)

This marked one year with error.os.
<hr>


### TL;DR
<<<<<<< HEAD
Even though there have been no users up until now, this entire ecosystem of projects has continued for the fun of development. With each update, stability has been redefined.

## Related pages

- [000 - Introduction](./../000)

- [004 - Our default apps](./../004)

- [011 - Advanced easy guide to linux](./../011)
=======
Even though there have been no users up until now, this project has continued for the fun of development. With each update, stability has been redefined.
>>>>>>> cfde602 (git commit commit more)
