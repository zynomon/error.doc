---
layout: default
title: "What you can Do and don'ts"
description: "Best practices and things to avoid on Linux"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/010/thumb.png
---

## Table of Contents

- [Introduction](#introduction)
- [Do](#do)
- [Don't](#dont)
- [If You Already Did One of the Don'ts](#if-you-already-did-one-of-the-donts)

## Introduction

None of this is a strict rulebook, error.os's whole philosophy is that you own the machine and can break it however you like. This page is closer to a list of habits that save you time later, and a few that reliably cost you time later. Ignore any of it once you understand the trade-off you're making.

## Do

**Update regularly.**
```bash
sudo apt update && sudo apt upgrade
```
Small, frequent updates are far less likely to break something than one giant update after months of putting it off.

**Read a command before running it**, especially anything piped straight into a shell:
```bash
curl https://example.com/install.sh | sudo bash
```
That line runs whatever's at that URL with root access, no review, no chance to say no partway through. Download it, open it, read what it actually does, then run it yourself if it looks reasonable.

**Back up before anything destructive.** A driver reinstall, a partition resize, a config file you're about to hand-edit, all worth a copy first:
```bash
cp /etc/some-config.conf /etc/some-config.conf.bak
```
Covered in more detail in [troubleshooting](./../009#5-make-one-change-at-a-time).

**Keep a bootable USB around.** If a kernel update or driver change leaves the system unbootable, a spare live medium (see [downloading and booting](./../001)) is the fastest way back to a usable terminal.

**Learn to read the actual error**, not just the symptom. [Doc 009](./../009#2-read-the-error-not-just-the-symptom) covers this in depth, it's the single highest-leverage troubleshooting habit there is.

**Understand a permission before setting it.** `chmod 755` and `chmod 777` look similarly harmless typed out, they aren't. [Doc 003](./../003#chmod-change-file-modepermissions) covers what each digit actually means.

<blockquote class="tip">
<span class="title">TIP</span><br>
None of these take longer than the mistake they prevent. Reading a script takes thirty seconds; recovering from running an unread one can take an afternoon.
</blockquote>

## Don't

**Don't run `rm -rf` on a path you haven't double-checked**, especially as root. There's no trash bin to recover from, and a stray space turns `rm -rf ~/old-project` into `rm -rf ~ /old-project`, two commands instead of one.

**Don't `chmod 777` to make a permission error go away.** It works because it removes all restrictions, not because it fixes anything. Find the actual owner/group mismatch instead (`ls -l` shows it) and fix that specifically.

**Don't interrupt a package manager mid-operation.** Force-closing a terminal or losing power during `apt install` or `dpkg` can leave the package database in a broken, half-configured state. Let it finish, or if it's truly stuck, see the recovery step below.

**Don't mix package managers for the same app without a reason.** Installing the same program via `apt` and Flatpak isn't dangerous, but it does mean two separate copies to update and two separate places configuration might live, confusing when you're troubleshooting later and forget which one you're actually running.

**Don't ignore free disk space.** A nearly full `/` can cause package installs to fail halfway through, sometimes in ways that look like an unrelated bug. Check with:
```bash
df -h /
```

**Don't disable Secure Boot or similar protections without knowing why you're doing it.** Sometimes it's the correct fix (an unsigned DKMS module, as covered in [driver troubleshooting](./../008#secure-boot-and-dkms)), sometimes it's not needed at all for the actual problem in front of you.

**Don't treat `sudo` as a default habit.** Running everyday applications as root doesn't make them work better, it just means a mistake or a compromised app has full system access instead of just your user's, any small mistakes can bring tension.

## If You Already Did One of the Don'ts

A package manager interrupted mid-install is the most common one, and it's recoverable:

```bash
sudo dpkg --configure -a
sudo apt install -f
```

The first line finishes configuring anything left half-done; the second fixes broken dependencies left over from the interruption. Run `apt update` again afterward to make sure everything's back in a consistent state.

<hr>

#### Next steps,
<div style="text-align:center; font-size:3rem;">
010 -> <a href="./../011">011</a>
</div>

## Related pages

- [003 - GNU/Linux Legends](./../003)

- [008 - Driver management and Nvidia drivers](./../008)

- [009 - Troubleshooting in linux](./../009)