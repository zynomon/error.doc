---
layout: default
title: "Customizing The distro"
description: "Guide for customizing your Linux distribution"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/005/thumb.png
---

## Table of Contents

- [Customizing in the GUI](#customizing-in-the-gui)
- [KDE CLI Tools](#kde-cli-tools)
- [Grub](#grub)
- [Plymouth](#plymouth)
- [SDDM](#sddm)
- [Desktop Layout and Panel](#desktop-layout-and-panel)
- [Wallpaper](#wallpaper)
- [Lockscreen](#lockscreen)
- [Cursor](#cursor)
- [Icons](#icons)
- [Window Decoration](#window-decoration)
- [Ksplash](#ksplash)
- [Color Schemes](#color-schemes)
- [Desktop Theme](#desktop-theme)
- [Look and Feel](#look-and-feel)
- [Konsole Profiles](#konsole-profiles)
- [Bashrc](#bashrc)
- [Application Styles: Qt Style (Kvantum)](#application-styles-qt-style-kvantum)
- [Tips on Using External Assets](#tips-on-using-external-assets)

## Customizing in the GUI
<img width="266" height="455" align="left" alt="image" src="https://github.com/user-attachments/assets/dea93841-edd2-4426-a94c-68ce3d1639cf" />

Most customization assets are browsable straight from Plasma Discover's Addons page.

<img width="268" height="74" alt="image" src="https://github.com/user-attachments/assets/69d6686b-f88f-4eef-ab5a-dd0e7027eff5" />

Open Discover, go to **Addons**, and each category below (themes, cursors, icons, splash screens, and so on) has its own section there, same place, one search box. Go to **Settings** to edit them once installed.

<p><br clear="all" /></p>

## KDE CLI Tools

Everything below has a GUI path through System Settings or Discover, and most of it also has a direct command for setting it from a terminal or a script. Two packages cover almost all of it:

```bash
sudo apt install libkf6config-bin kpackagetool6
```

`libkf6config-bin` provides `kreadconfig6` and `kwriteconfig6`, the generic tools for reading and writing any KDE config file by key, used throughout this page. `kpackagetool6` installs and removes KPackage-format assets (Look and Feel packages, Plasma themes, splash screens) from the command line, covered in [Tips on Using External Assets](#tips-on-using-external-assets).

The `plasma-apply-*` family of commands (`plasma-apply-colorscheme`, `plasma-apply-desktoptheme`, `plasma-apply-lookandfeel`, `plasma-apply-cursortheme`, `plasma-apply-wallpaperimage`) ships as part of `plasma-workspace`, already installed with the desktop, nothing extra needed for those.

## Grub

GRUB isn't a KDE component, so none of the tools above apply here, it's edited directly. Theme folders live at `/boot/grub/themes/<theme-name>/`, referenced from `/etc/default/grub`:

```bash
GRUB_THEME="/boot/grub/themes/your-theme/theme.txt"
```

After editing that file:

```bash
sudo update-grub
```

## Plymouth

Plymouth (the boot splash) has its own dedicated CLI. You can also change it from System Settings, but that page is a bit janky, it doesn't show theme thumbnails.

<img width="916" height="612" alt="image" src="https://github.com/user-attachments/assets/11892978-269c-4e3a-a89b-d5e85217f99e" />

However you can still download a new Plymouth theme and switch to it with:

```bash
plymouth-set-default-theme your-theme-name
sudo update-initramfs -u
```

Theme folders live at `/usr/share/plymouth/themes/<theme-name>/`. System Settings' **Boot Splash Screen** page wraps this same command behind a GUI, it's just that GUI that lacks previews right now.

## SDDM

error.os uses SDDM specifically, no other display manager. Its config is a plain INI file, so `kwriteconfig6` works directly on it:

```bash
sudo kwriteconfig6 --file /etc/sddm.conf.d/kde_settings.conf --group Theme --key Current your-theme-name
```

Theme folders live at `/usr/share/sddm/themes/<theme-name>/`. System Settings' **Login Screen (SDDM)** page does the same thing through a picker, and can fetch new themes directly via its "Get New Login Screen Designs" button.

## Desktop Layout and Panel

Right-click the desktop and choose **Edit Mode** to add, remove, or rearrange widgets, and to add, resize, or configure panels (the taskbar being the default one). This is interactive by nature, there's no single command that represents "move this panel here."

The layout is technically stored in `~/.config/plasma-org.kde.plasma.desktop-appletsrc`, and `kwriteconfig6` can touch it, but hand-editing applet layouts is fragile and easy to break. Edit Mode is the practical way to do this one.

## Wallpaper

```bash
plasma-apply-wallpaperimage /path/to/image.jpg
```

Downloaded wallpaper packs land in `~/.local/share/wallpapers/`. The GUI path: right-click the desktop, **Configure Desktop and Wallpaper**, with a "Get New Wallpapers" button for browsing more.

## Lockscreen

The lock screen generally follows the active Look and Feel package (covered below), but its wallpaper can be set separately through System Settings' **Screen Locking** page, which also has its own "Get New Wallpapers" entry point.

## Cursor

```bash
plasma-apply-cursortheme your-cursor-theme
```

Cursor themes install to `~/.local/share/icons/`, same directory icon themes use, since cursors follow the same XCursor spec. GUI path: System Settings > **Cursors** > "Get New Cursors".

## Icons

```bash
kwriteconfig6 --file ~/.config/kdeglobals --group Icons --key Theme your-icon-theme
```

There's no dedicated `plasma-apply-icontheme`, icons are set through `kdeglobals` directly instead. Icon themes also install to `~/.local/share/icons/`. GUI path: System Settings > **Icons** > "Get New Icons".

## Window Decoration

```bash
kwriteconfig6 --file ~/.config/kwinrc --group org.kde.kdecoration2 --key theme your-decoration-theme
qdbus org.kde.KWin /KWin reconfigure
```

Window decorations (Aurorae themes) install to `~/.local/share/aurorae/themes/`. GUI path: System Settings > **Window Decorations** > "Get New Window Decorations".

## Ksplash

```bash
kwriteconfig6 --file ~/.config/ksplashrc --group KSplash --key Theme your-splash-theme
```

Not to be confused with Plymouth, Ksplash is the splash screen shown while logging into the Plasma session itself, after Plymouth has already finished. GUI path: System Settings > **Splash Screen**.

## Color Schemes

```bash
plasma-apply-colorscheme YourColorScheme
```

`.colors` files install to `~/.local/share/color-schemes/`. GUI path: System Settings > **Colors** > "Get New Color Schemes".

## Desktop Theme

```bash
plasma-apply-desktoptheme your-plasma-theme
```

This is the Plasma Style, panel and widget appearance specifically, not the Qt application style covered later. Themes install to `~/.local/share/plasma/desktoptheme/`. GUI path: System Settings > Appearance > **Plasma Style**.

<img width="929" height="491" alt="image" src="https://github.com/user-attachments/assets/711b311b-142b-4ab7-adfc-c80f7e456595" />

This same page also lets you configure the appearance of GTK applications.

## Look and Feel

```bash
plasma-apply-lookandfeel -a YourGlobalTheme
```

A Look and Feel package bundles several of the sections above together, color scheme, Plasma style, splash screen, sometimes SDDM theme, into one coherent set applied all at once. Packages install to `~/.local/share/plasma/look-and-feel/`. GUI path: System Settings > **Global Theme**.

## Konsole Profiles

<img width="848" height="599" alt="image" src="https://github.com/user-attachments/assets/b86a96c1-5916-47bf-b0a6-6f98d7f33eba" />

Konsole profiles don't have a dedicated CLI setter the way the Plasma-wide settings above do, they're managed from within Konsole itself: **Settings > Manage Profiles**. The underlying files are plain `.profile` files under `~/.local/share/konsole/`, along with separate `.colorscheme` files for color schemes specifically, both editable by hand or with `kwriteconfig6` if you want to script a profile rather than click through the dialog.

## Bashrc

`~/.bashrc` is just a shell script, manual editing is the only path. For per-user changes (aliases, prompt, `PATH` additions), edit `~/.bashrc` directly. New users get their starting `.bashrc` copied from `/etc/skel/.bashrc`, and `/etc/bash.bashrc` applies system-wide to every user's interactive shell.

You can cook up your own [bash PS1 prompt here](https://bash-prompt-generator.org/).

## Application Styles: Qt Style (Kvantum)

Kvantum comes preinstalled on error.os, error.os's own default theme is applied through it, set up by error.base during install (covered in [doc 004](./../004#errorbase)).

```bash
kvantummanager --set YourKvantumTheme
```

Theme folders live at `~/.config/Kvantum/<ThemeName>/`. For Kvantum's styling to actually apply, the active Qt style also needs to be set to Kvantum itself: System Settings > Appearance > **Application Style**, pick "Kvantum" from the list. Kvantum Manager (same `kvantummanager` binary, run without arguments) opens a GUI for browsing and previewing installed themes.

## Tips on Using External Assets

Most of what's covered above can also come from outside Discover, sites like the KDE Store (store.kde.org) or a plain GitHub repository. Two things decide whether something downloaded that way actually works:

1. **Folder structure.** Each category above has a specific install path (`~/.local/share/plasma/desktoptheme/`, `~/.local/share/color-schemes/`, and so on). An asset only gets picked up if it lands in the right one, matching the category it's for.
2. **A valid `metadata.json`** (or legacy `metadata.desktop`) inside the package, describing its name, type, and KPackage structure. This is what tells KDE's tooling, `kpackagetool6` specifically, what kind of asset it's looking at.

For something already in that proper KPackage format (most Look and Feel themes, Plasma styles, and splash screens downloaded as a `.zip` or `.tar.gz` from the KDE Store are), skip manually extracting into the right folder and let `kpackagetool6` do it correctly:

```bash
kpackagetool6 --type Plasma/LookAndFeel --install /path/to/downloaded-theme.tar.gz
kpackagetool6 --type Plasma/LookAndFeel --list    # confirm it installed
kpackagetool6 --type Plasma/LookAndFeel --remove your-theme-name
```

Swap `--type` for the matching category (`Plasma/Theme` for desktop themes, `KWin/Decoration` for window decorations, and so on).

For assets that are just loose files rather than a proper KPackage, cursor themes and icon themes most commonly, there's no installer tool involved at all: extract the archive directly into the matching `~/.local/share/` folder from the sections above, and it shows up in System Settings the next time that page is opened.

As for making Such Look And Feel Package It's Recommended to check `plasma-sdk` from apt
```bash
sudo apt install plasma-sdk
```

<blockquote class="note">
<span class="title">NOTE</span><br>
GRUB and Plymouth assets never go through <code>kpackagetool6</code> or the KPackage format at all, since neither is a KDE component. New themes for those two always mean placing files under <code>/boot/grub/themes/</code> or <code>/usr/share/plymouth/themes/</code> directly, as shown in their sections above, Plymouth's Settings page included, it's still just a GUI wrapper around the same file placement and <code>plymouth-set-default-theme</code> command, not KPackage underneath it.
</blockquote>

<hr>

#### Next steps,
<div style="text-align:center; font-size:3rem;">
005 -> <a href="./../006">006</a>
</div>

## Related pages

- [000 - Introduction](./../000)

- [004 - Our default apps](./../004)

- [011 - Advanced easy guide to linux](./../011)
