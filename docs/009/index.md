---
layout: default
title: "Troubleshooting"
description: "Common troubleshooting steps and solutions"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/009/thumb.png
---

## Table of Contents

- [Introduction](#introduction)
- [1. Identify the Issue](#1-identify-the-issue)
- [2. Read the Error, Not Just the Symptom](#2-read-the-error-not-just-the-symptom)
- [3. Search With the Right Words](#3-search-with-the-right-words)
- [4. Check the Logs](#4-check-the-logs)
- [5. Make One Change at a Time](#5-make-one-change-at-a-time)
- [6. Know When to Ask for Help](#6-know-when-to-ask-for-help)

## Introduction

Linux is an open-source kernel, and GNU is the base built around it (GNU stands for "GNU's Not Unix", a recursive joke that doesn't fully make sense until you've been in Linux long enough to find it funny). GNU packages the bootloader, shell, and other essentials needed to make the Linux kernel usable as the core of an actual operating system.

Yet no system is perfect. Nothing that complex runs without the occasional failure.

So instead of blaming the system, this page teaches you how to resolve issues with what you already have. Linux has a huge open-source community and mountains of documentation, but its biggest flaw is that both tend to be hard to read. Articles and project docs are often written for people who already half-understand the problem. This page isn't about how to deal with every open-source project's documentation style, it's a friendly walkthrough of the everyday troubleshooting process itself.

## 1. Identify the Issue

Every outcome has a cause. Sometimes that cause is a bug in the program you're using, sometimes it's a setting you changed without realizing what it affected, and sometimes it's just a missing dependency. Before touching anything, think back to the moment right before it happened:

- What were you doing right before it broke?
- Did you just install, update, or remove something?
- Does it happen every time, or only sometimes?
- Does it happen for every user on the system, or just you?

Answering these narrows down where to even start looking. "My browser crashed" is a symptom. "My browser crashed after I enabled a new extension" is the start of an actual diagnosis.

## 2. Read the Error, Not Just the Symptom

The most common troubleshooting mistake is skimming past the actual error message and jumping straight to guessing. If a program prints an error to the terminal, that text is almost always more specific than whatever you'd search for based on the symptom alone.

```bash
some-program
# Error: could not find libexample.so.2
```

That single line tells you exactly what's missing, a shared library, not "why is some-program broken." Run a failing GUI app from a terminal instead of clicking its icon whenever possible, GUI launchers often swallow the exact error a terminal would show you.

## 3. Search With the Right Words

Once you have the actual error text, search for that, not your own paraphrase of the problem. Quote the specific error message, drop anything unique to your machine (usernames, exact file paths, timestamps), and include the program name.

<blockquote class="tip">
<span class="title">TIP</span><br>
Searching the literal error string in quotes almost always beats a vague description. "could not find libexample.so.2" finds people who hit your exact problem. "my program won't open" finds everyone else's unrelated problem.
</blockquote>

## 4. Check the Logs

When a program fails silently, without printing anything useful, the system logs usually have more detail than the program itself gave you:

```bash
journalctl -xe                  # recent systemd logs, most relevant first
journalctl -u service-name      # logs for one specific service
dmesg | tail -50                # recent kernel messages
```

For a crash that happens right at login or during boot, `journalctl -b` shows the logs from the current boot session specifically, which cuts out days of unrelated history.

## 5. Make One Change at a Time

When trying a fix, change exactly one thing, then test. Changing three settings at once and having the problem disappear tells you it's fixed, not which of the three fixed it, so the next time it happens, you're back to guessing from scratch.

This matters even more when a fix involves anything destructive or hard to undo (removing a package, editing a config file, purging a driver). Keep a copy of what you changed:

```bash
cp /etc/some-config.conf /etc/some-config.conf.bak
```

If the change doesn't help, put it back before trying the next one.

## 6. Know When to Ask for Help

Not everything needs to be solved alone, and asking well gets better answers faster. When you do ask, on a forum, Discord, or an issue tracker, include:

- What you were trying to do
- The exact error message or log output (as text, not a screenshot, so it's searchable and copyable)
- What you already tried
- Your distro, kernel version (`uname -r`), and relevant package versions

<blockquote class="note">
<span class="title">NOTE</span><br>
"It doesn't work" with no other detail is the single hardest kind of question to answer. The five points above turn a guessing game into something someone else can actually diagnose.
</blockquote>

<hr>

#### Next steps,
<div style="text-align:center; font-size:3rem;">
009 -> <a href="./../010">010</a>
</div>

## Related pages

- [008 - Driver management and Nvidia drivers](./../008)

- [010 - What to do and don'ts, in linux](./../010)

- [011 - Advanced easy guide to linux](./../011)