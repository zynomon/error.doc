---
layout: default
title: "Gaming on Linux"
description: "Complete guide for gaming on Linux systems"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/006/thumb.png
---

## Table of Contents

- [A Short History](#a-short-history)
- [Wine-Based Game Launchers](#wine-based-game-launchers)
  - [Lutris](#lutris)
  - [Heroic Games Launcher](#heroic-games-launcher)
  - [Bottles](#bottles)
  - [Faugus Launcher](#faugus-launcher)
  - [PortProton](#portproton)
- [Steam and Proton](#steam-and-proton)
- [Retro Emulation](#retro-emulation)
  - [Libretro and RetroArch](#libretro-and-retroarch)
  - [Standalone Emulators](#standalone-emulators)
  - [A Note on Switch Emulation](#a-note-on-switch-emulation)

## A Short History

Since Valve made SteamOS, gaming on Linux has become native, or at least close to playable, for a huge chunk of the Windows library. Before that era, Linux had a handful of notable games: Cave Story, the Tux series, KDE/GNOME's own game collections, and Xonotic. These games had one thing in common: they were all open source, with nothing gatekept behind a premium paywall.

But for safety always use [Flatpak](https://flathub.org/en/setup/Debian) <sub>click to get download instruction</sub> for the games since they could access entire file system if downloaded with apt. also use [Flatseal](https://flathub.org/en/apps/com.github.tchx84.Flatseal) to manage permissions and [Flatsweep](https://flathub.org/en/apps/io.github.giantpinkrobots.flatsweep) for erasing junk data. also some games could be found [here too](https://flathub.org/en/apps/category/game/1)

> [!NOTE]
> One another thing for you to keep in mind on troubleshooting  error.os is basically "debian" 

## Wine-Based Game Launchers

Wine translates Windows API calls into something Linux can run. Most people don't configure Wine by hand anymore, they use a launcher that manages Wine prefixes and versions for them.

### Lutris

Lutris is the oldest and most widely used of the bunch. It's less a single tool and more a platform: community-maintained install scripts cover thousands of games across Steam, GOG, Epic, Battle.net, and standalone installers, and it wraps Wine, Proton-GE, and native Linux builds under one interface.

### Heroic Games Launcher

Heroic is a native, open-source launcher built specifically for Epic Games Store and GOG. It uses Legendary and gogdl as backends to talk to those storefronts, then runs Windows titles through Wine or Proton-GE.

### Bottles

Bottles focuses on isolation: every application or game gets its own sandboxed Wine prefix ("bottle"), so a broken dependency in one game can't affect another. It's less game-store-focused than Lutris or Heroic and more of a general-purpose Wine prefix manager.

### Faugus Launcher

Faugus Launcher is a small, lightweight launcher built around UMU-Launcher. It runs native Linux games and Windows games through Proton, and bundles Winetricks, Winecfg, MangoHud, and Feral GameMode as one-click tools. It also includes a Proton Manager for downloading and removing GE-Proton builds directly.

### PortProton

PortProton (formerly PortWINE) automates Wine prefix setup and library installation (DirectX, Visual C++, .NET) so a Windows installer can usually just be pointed at and run. It bundles Proton and Proton-GE, and its Autoinstall tab can fetch popular launchers like Epic Games, Battle.net, and Ubisoft Connect on its own.

<blockquote class="tip">
<span class="title">TIP</span><br>
All five of these do roughly the same job. Lutris and Heroic lean toward storefront integration, Bottles and PortProton lean toward general Wine management, and Faugus stays deliberately minimal. Try one, don't feel obligated to install all of them.
</blockquote>

## Steam and Proton

Steam is still the most common way to game on Linux, mainly because of Proton: Valve's Wine-based compatibility layer, built into Steam as "Steam Play." Enable it in Steam's settings under Compatibility, and most Windows-only games on your library will show a Play button like any native title.

Valve's official Proton builds prioritize stability and broad compatibility. For games that don't run well on stock Proton, the community fork **Proton-GE** (GloriousEggroll) adds extra patches, codecs, and fixes, and can be installed alongside official Proton through most of the launchers above, or manually via ProtonUp-Qt.

## Retro Emulation

### Libretro and RetroArch

Libretro is an API, not an emulator by itself. Individual emulators get compiled into "cores" that plug into a libretro frontend, most commonly **RetroArch**, giving you one interface, one set of shaders and save-state handling, and one controller config for dozens of systems instead of a separate app per console.

### Standalone Emulators

Some emulators are better used on their own rather than as a libretro core, usually because they need more system-specific tuning:

- **Dolphin** - GameCube and Wii
- **PCSX2** - PlayStation 2
- **RPCS3** - PlayStation 3
- **DuckStation** - PlayStation 1
- **PPSSPP** - PSP
- **DOS-Box-x** - MS-DOS  (early .exe programs) & NEC PC-98
  
> [!WARNING]
> Emulation and it's legal authority is the concern of the developer and the user {YOU - if you use it} so make sure to double check their TOS ( terms of service ) and Licenses.
> Not all emulation is legal, 


<
  hr>

#### Next steps,
<div style="text-align:center; font-size:3rem;">
006 -> <a href="./../007">007</a>
</div>

## Related pages

- [004 - Our default apps](./../004)

- [005 - Customizing the distro](./../005)

- [009 - Troubleshooting in linux](./../009)
