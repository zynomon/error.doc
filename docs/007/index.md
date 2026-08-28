---
layout: default
title: "Programming on Linux"
description: "Programming setup and tools for Linux development"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/007/thumb.png
---

## Table of Contents

- [Programming or Coding](#programming-or-coding)
- [Getting the Toolchain in Place](#getting-the-toolchain-in-place)
- [Picking an Editor or IDE](#picking-an-editor-or-ide)
- [Interpreted Languages](#interpreted-languages)
  - [Python](#python)
  - [Node.js](#nodejs)
  - [Shell Scripting](#shell-scripting)
- [Compiling From Source](#compiling-from-source)
- [Serving Things Locally](#serving-things-locally)
  - [Web Development Basics](#web-development-basics)
  - [Quick Static Testing](#quick-static-testing)
  - [Nginx](#nginx)
  - [Apache](#apache)
- [SSH](#ssh)
  - [Installing and Connecting](#installing-and-connecting)
  - [Key-Based Login](#key-based-login)
- [Containers](#containers)

## Programming or Coding

Programming on Linux feels native, because for most languages, it is. C/C++ toolchains, headers, and libraries live in standard, well-known locations (`/usr/include`, `/usr/lib`), package managers install dev libraries directly, and most languages ship a working interpreter or compiler through `apt`. Setting up a working environment is usually a couple of commands, not a multi-step installer with sandbox and more headaches.

## Getting the Toolchain in Place

Almost everything on this page depends on one system package:

```bash
sudo apt update
sudo apt install build-essential
```

`build-essential` pulls in `gcc`, `g++`, `make`, and the core C/C++ headers. Without it, compiling almost anything from source fails with missing header errors. This one does need root, there's no meaningful way around installing a compiler toolchain system-wide.

## Picking an Editor or IDE

error.os ships [Vex](./../004#vex) by default, a Qt-based editor with a plugin-driven syntax engine. If you'd rather use something else, these are common picks, most available as Flatpaks so they install and update independently of the base system:

| Editor | Flatpak ID | Best for |
|---|---|---|
| VS Code | `com.visualstudio.code` | General purpose, huge extension library |
| VSCodium | `com.vscodium.codium` | Same as VS Code, without Microsoft's telemetry/branding |
| Kate | `org.kde.kate` | Lightweight, KDE-native, built-in LSP support |
| Geany | `org.geany.Geany` | Very lightweight, fast to open |
| GNOME Builder | `org.gnome.Builder` | Best fit for GTK/GNOME native app development |

```bash
flatpak install flathub com.visualstudio.code
```
( you could also visit `err_` to do that for you )
<blockquote class="note">
<span class="title">NOTE</span><br>
JetBrains IDEs (PyCharm, IntelliJ IDEA, WebStorm) used to have official Community Edition Flatpaks, but those listings on Flathub are no longer maintained. The current supported route is the <a href="https://www.jetbrains.com/toolbox-app/">JetBrains Toolbox App</a>, installed via their own script rather than Flatpak.
</blockquote>

## Interpreted Languages 
( we would be using flatpak for sandbox )

### Python

Python 3 is already part of Debian's base system, and by extension error.os, so there's nothing to install just to get `python3` on your `PATH`.

For a friendly, beginner-oriented editor that stays entirely in user space, install **Thonny** as a Flatpak rather than through `apt`:

```bash
flatpak install --user flathub org.thonny.Thonny
```

The `--user` flag keeps the install scoped to your account, no root involved at any point. For installing Python packages without touching the system interpreter, keep using `pip install --user`, or better, `pipx` for isolating command-line tools:

```bash
python3 -m pip install --user pipx
pipx install black
```

### Node.js

Skip the NodeSource setup script (it needs `sudo` and modifies system package sources). `nvm` (Node Version Manager) installs entirely into your home directory instead:

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.1/install.sh | bash
nvm install --lts
```

No root access is requested at any point, and switching Node versions later is just `nvm use <version>`.

### Shell Scripting

Bash is already your default shell on error.os. A script only needs a shebang line and execute permission, both entirely user-level:

```bash
#!/bin/bash
echo "Hello from a script"
```

```bash
chmod +x script.sh
./script.sh
```

## Compiling From Source

Once `build-essential` is in place, compiling a single C file is one command:

```bash
gcc hello.c -o hello
./hello
```

For anything with multiple source files, a `Makefile` or CMake handles the build graph:

```bash
# Makefile-based project
make

# CMake-based project
mkdir build && cd build
cmake ..
make
```

If a project fails to build with missing library errors, you're usually missing a `-dev` package. A project depending on Qt6, for example, needs:

```bash
sudo apt install qt6-base-dev
```

Check the project's README for its exact dependency list before compiling, most name their required `-dev` packages directly.

dev headers just add the .h/.c/.cpp files that will get read and linked with the program that you would be compiling. and normal libraries are just the binary compiled `.so` ( shared object ) made to connect with the compiled file.

## Serving Things Locally

### Web Development Basics

A typical local setup needs a runtime (already covered above), a database, and a way to serve files:

```bash
# PostgreSQL
sudo apt install postgresql postgresql-contrib

# MySQL/MariaDB
sudo apt install mariadb-server

# SQLite (file-based, no server needed)
sudo apt install sqlite3

# PHP
sudo apt install php php-cli php-mysql
```

Most modern frameworks (Django, Flask, Express, Laravel) include their own local development server, so a full web server like Nginx usually isn't needed until you're ready to deploy.

### Quick Static Testing

For quickly serving a static folder with nothing extra installed:

```bash
python3 -m http.server 8000
```

Visit `http://localhost:8000`, it serves the current directory. Fine for local testing, not for production.

### Nginx

```bash
sudo apt install nginx
sudo systemctl enable --now nginx
```

Site configs live in `/etc/nginx/sites-available/`, symlinked into `/etc/nginx/sites-enabled/` to activate them. Test a config before reloading:

```bash
sudo nginx -t
sudo systemctl reload nginx
```

### Apache

```bash
sudo apt install apache2
sudo systemctl enable --now apache2
```

Site configs live in `/etc/apache2/sites-available/`, enabled with `a2ensite`, reloaded with:

```bash
sudo systemctl reload apache2
```

<blockquote class="warning">
<span class="title">WARNING</span><br>
Don't run Nginx and Apache at the same time unless you know exactly why, they'll fight over port 80.
</blockquote>

## SSH

### Installing and Connecting

To let other machines connect to yours:

```bash
sudo apt install openssh-server
sudo systemctl enable --now ssh
```

To connect out to another machine, no install is needed, the `ssh` client ships by default:

```bash
ssh username@remote-host
```

### Key-Based Login

Password logins work, but a key pair is faster and safer:

```bash
ssh-keygen -t ed25519
ssh-copy-id username@remote-host
```

After that, `ssh username@remote-host` logs in without a password prompt. For hosts you use often, `~/.ssh/config` saves typing:

```
Host myserver
    HostName 192.168.1.50
    User username
    IdentityFile ~/.ssh/id_ed25519
```

Then just `ssh myserver` connects.

## Containers

Everything above installs directly onto the host, most of it with root access. If you'd rather keep the base system clean, **Podman** runs containers without ever needing root for the containers themselves, only its own install needs `sudo`, same as any other package:

```bash
sudo apt install podman
```

Most tooling, tutorials, and Compose files still say `docker`. `podman-docker` provides a real `/usr/bin/docker` that forwards to Podman, so those commands work unmodified:

```bash
sudo apt install podman-docker
```

From here, the web server setup earlier in this page can run inside a container instead of directly on the host, no `apt install nginx` on the system at all:

```bash
podman run -d -p 8080:80 -v ./site:/usr/share/nginx/html:ro nginx
```

That command needs no `sudo`, the container itself runs rootless. Visit `http://localhost:8080` and it's serving whatever's in `./site`, isolated from the rest of the system.

<hr>

#### Next steps,
<div style="text-align:center; font-size:3rem;">
007 -> <a href="./../008">008</a>
</div>

## Related pages

- [003 - GNU/Linux Legends](./../003)

- [004 - Our default apps](./../004)

- [011 - Advanced easy guide to linux](./../011)
