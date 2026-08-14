---
layout: default
title: "GNU/Linux Legends"
description: "History and information about GNU/Linux legends"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/003/thumb.png
---

## Table of Contents

- [GNU/Linux: The Basics](#gnu-linux-the-basics)
- [GNU Coreutils Command Reference](#gnu-coreutils-command-reference)
  - [rm (remove)](#rm-remove)
  - [ls (list)](#ls-list)
  - [cp (copy)](#cp-copy)
  - [mv (move)](#mv-move)
  - [cat (concatenate)](#cat-concatenate)
  - [mkdir (make directory)](#mkdir-make-directory)
  - [touch](#touch)
- [File System Hacks and Regex](#file-system-hacks-and-regex)
  - [Permissions and Ownership](#permissions-and-ownership)
    - [chmod (change file mode/permissions)](#chmod-change-file-modepermissions)
    - [chown (change owner)](#chown-change-owner)
    - [chgrp (change group)](#chgrp-change-group)
  - [User and Group Management](#user-and-group-management)
    - [useradd / adduser (create user)](#useradd--adduser-create-user)
    - [usermod (modify user)](#usermod-modify-user)
    - [userdel (delete user)](#userdel-delete-user)
    - [passwd (change password)](#passwd-change-password)
    - [groupadd / groupdel (manage groups)](#groupadd--groupdel-manage-groups)
    - [User Information Commands](#user-information-commands)
    - [su and sudo](#su-and-sudo-switch-user--superuser-do)
  - [Account and System Information Files](#account-and-system-information-files)
    - [Important System Files](#important-system-files)
    - [Managing sudo access](#managing-sudo-access)
  - [File Ownership in Action](#file-ownership-in-action)
- [Bash Operators](#bash-operators)
- [Test Yourself](#test-yourself)

## GNU/Linux: The Basics

Linux is an open source kernel made by Linus Torvalds. This is already common knowledge for most of you, the real question is how that kernel operates. Busybox provides a minimal set of core utilities, and early Linux systems didn't ship with a full init system, users had to configure `/etc/rc` themselves. The GNU Project, started years earlier by Richard Stallman, already had its own toolchain and utilities ready to pair with the Linux kernel.

The term GNU/Linux refers to a system running glibc (the GNU C library) at its core, built with GNU coreutils (the package containing binaries like `cat`, `grep`, and `touch`), installed alongside busybox on most GNU/Linux systems. Because Debian, Arch, and most user-friendly distros build on GNU at their core, other libc alternatives generally can't run those binaries without recompiling against a different libc. The same applies to non-GNU init systems like systemd, building an alternative is hard, since most tooling assumes compatibility with it. This is the recurring theme in Linux: there's no single default shell or toolchain handed to you, you assemble one.

---

Most GNU apps you should know are, most of these come pre-installed on any GNU/Linux system, and for many of them there isn't a better alternative anyway:

```bash
# bash (GNU Bash) 
## grub (GNU bootloader) 
# gcc (GNU Compiler Collection) 
## coreutils (the everyday commands: ls cp mv rm mkdir cat etc)
# glibc (GNU C library, the heart most programs link to)
## binutils (assembler linker objdump readelf strip etc)
# make (GNU make, boss of building software)
## grep (search god-tier tool)
# sed (stream editor for text surgery from terminal)
## awk (GNU awk, the swiss army knife for text)
# findutils (find xargs locate)
## diffutils (diff cmp diff3 patch)
# tar (GNU tar, archiving king)
## gzip (compression classic + bzip2 xz helpers)
# wget (simple powerful downloader)
## nano (the forgiving text editor)
# gpg (GNU Privacy Guard, verifies signatures)
```

---

## GNU Coreutils Command Reference

### rm (remove)
- `-r` (recursive): removes directories and their contents
- `-f` (force): ignore nonexistent files, never prompt
- `-rf` (combined): dangerous - removes everything without confirmation
- `-i` (interactive): prompts before each removal (safer!)
- `-v` (verbose): shows what's being deleted

**Example:**
```bash
rm -rfv /tmp/*
```
Note: Combining `-f` with `-i` is contradictory - force will override interactive prompts, so the `-i` becomes useless.

> [!WARNING]
> `rm -rf` does not ask twice. There's no trash bin to recover from once it's run, especially as root. Double-check the path before you press enter.

### ls (list)
- `-l` (long): detailed file information
- `-a` (all): shows hidden files (starting with `.`)
- `-h` (human-readable): file sizes in KB, MB, GB
- `-R` (recursive): lists subdirectories too
- `-t` (time): sorts by modification time

**Examples:**
```bash
ls -lah        # long format, all files, human-readable sizes
ls -lt         # sorted by modification time
ls -lR /etc    # recursive listing of /etc
```

### cp (copy)
- `-r` (recursive): copies directories
- `-i` (interactive): prompts before overwrite
- `-v` (verbose): shows files being copied
- `-p` (preserve): keeps timestamps and permissions
- `-u` (update): only copy when source is newer

**Examples:**
```bash
cp -r source_dir/ dest_dir/     # copy entire directory
cp -rp /etc/config ~/backup/    # preserve attributes
cp -uv file1 file2              # update and verbose
```

### mv (move)
- `-i` (interactive): prompts before overwrite
- `-v` (verbose): shows what's being moved
- `-n` (no-clobber): doesn't overwrite existing files
- `-u` (update): move only when source is newer

**Examples:**
```bash
mv oldname newname              # rename file
mv -i file.txt /backup/         # move with prompt
mv *.txt documents/             # move multiple files
```

### cat (concatenate)
- Displays file contents
- `-n` (number): numbers all output lines
- `-b` (number-nonblank): numbers only non-empty lines
- `-s` (squeeze): suppresses repeated empty lines

**Examples:**
```bash
cat file.txt                    # display content
cat file1 file2 > combined      # merge files
cat -n script.sh                # show with line numbers
cat << EOF > newfile.txt        # here document
content here
EOF
```

### mkdir (make directory)
- `-p` (parents): creates nested directories
- `-v` (verbose): prints created directories
- `-m` (mode): set permissions directly

**Examples:**
```bash
mkdir -p ~/projects/web/css     # create nested dirs
mkdir -m 755 public_folder      # create with permissions
mkdir -pv one/two/three         # verbose nested creation
```

### touch
- Creates empty files or updates timestamps
- `-c` (no-create): don't create file if it doesn't exist
- `-t` (time): set specific timestamp
- `-a` (access): change only access time
- `-m` (modify): change only modification time

**Examples:**
```bash
touch newfile.txt               # create empty file
touch existing.txt              # update timestamp
touch -t 202401011200 old.txt   # set specific time
touch file{1..10}.txt           # create multiple files
```

---

<details><summary><strong>File System Hacks and Regex</strong> <sub>(click to expand)</sub></summary>

<h2>Permissions and Ownership</h2>

<h3>chmod (change file mode/permissions)</h3>

<p><strong>Understanding Linux Permissions:</strong><br>
Every file has three permission sets: Owner (u), Group (g), Others (o)<br>
Each set has three permissions: Read (r=4), Write (w=2), Execute (x=1)</p>

<p><strong>Numeric (Octal) Method:</strong></p>

<pre>chmod 755 script.sh             # rwxr-xr-x (owner: all, group: rx, others: rx)
chmod 644 file.txt              # rw-r--r-- (owner: rw, group: r, others: r)
chmod 700 private.sh            # rwx------ (owner only)
chmod 666 shared.txt            # rw-rw-rw- (all can read/write)
chmod 400 secret.key            # r-------- (owner read-only)</pre>

<p><strong>Common Permission Numbers:</strong></p>

<ul>
<li><code>777</code> - rwxrwxrwx (everyone can do everything - dangerous!)</li>
<li><code>755</code> - rwxr-xr-x (standard for executables/directories)</li>
<li><code>644</code> - rw-r--r-- (standard for regular files)</li>
<li><code>600</code> - rw------- (private files, like SSH keys)</li>
<li><code>400</code> - r-------- (read-only secrets)</li>
</ul>

<p><strong>Symbolic Method:</strong></p>

<pre>chmod u+x script.sh             # add execute for owner (user)
chmod g+w file.txt              # add write for group
chmod o-r private.txt           # remove read for others
chmod a+x program               # add execute for all (a=all)
chmod u=rwx,g=rx,o=r file       # set exact permissions
chmod +x script.sh              # add execute for all
chmod -R 755 directory/         # recursive permission change</pre>

<p><strong>Special Permissions:</strong></p>

<pre>chmod 4755 program              # setuid (runs as file owner)
chmod 2755 directory            # setgid (new files inherit group)
chmod 1777 /tmp                 # sticky bit (only owner can delete)
chmod u+s binary                # add setuid
chmod g+s directory             # add setgid
chmod +t directory              # add sticky bit</pre>

<h3>chown (change owner)</h3>

<p><strong>Syntax:</strong> <code>chown [user][:group] file</code></p>

<pre>chown alice file.txt            # change owner to alice
chown alice:developers file.txt # change owner and group
chown :developers file.txt      # change group only
chown -R alice:staff /home/alice # recursive ownership change
chown --from=bob alice file.txt # change only if current owner is bob</pre>

<h3>chgrp (change group)</h3>

<pre>chgrp developers project.txt    # change group to developers
chgrp -R staff /shared/folder   # recursive group change
chgrp --reference=file1 file2   # copy group from file1 to file2</pre>

<h2>User and Group Management</h2>

<h3>useradd / adduser (create user)</h3>

<pre># useradd (low-level)
sudo useradd john               # create basic user
sudo useradd -m john            # create user with home directory
sudo useradd -m -s /bin/bash john # specify shell
sudo useradd -m -G sudo,developers john # add to groups
sudo useradd -m -u 1500 john    # specify UID
sudo useradd -m -e 2025-12-31 john # expiration date

# adduser (high-level, interactive - Debian/Ubuntu)
sudo adduser john               # interactive user creation</pre>

<blockquote>
<p>[!TIP] <code>useradd</code> is the low-level tool and doesn't create a home directory or set a shell unless you tell it to. <code>adduser</code> wraps it in an interactive script and handles those defaults for you. On Debian-based systems like error.os, prefer <code>adduser</code> unless you're scripting.</p>
</blockquote>

<h3>usermod (modify user)</h3>

<pre>sudo usermod -aG sudo john      # add user to sudo group (append)
sudo usermod -aG docker,www-data john # add to multiple groups
sudo usermod -l newname oldname # rename user
sudo usermod -s /bin/zsh john   # change shell
sudo usermod -d /new/home john  # change home directory
sudo usermod -L john            # lock account
sudo usermod -U john            # unlock account
sudo usermod -e 2025-12-31 john # set expiration date</pre>

<h3>userdel (delete user)</h3>

<pre>sudo userdel john               # delete user (keeps home directory)
sudo userdel -r john            # delete user and home directory
sudo userdel -f john            # force delete (even if logged in)</pre>

<h3>passwd (change password)</h3>

<pre>passwd                          # change your own password
sudo passwd john                # change another user's password
sudo passwd -l john             # lock user account
sudo passwd -u john             # unlock user account
sudo passwd -d john             # delete password (passwordless login)
sudo passwd -e john             # expire password (force change on next login)</pre>

<h3>groupadd / groupdel (manage groups)</h3>

<pre>sudo groupadd developers        # create group
sudo groupadd -g 1500 developers # create with specific GID
sudo groupdel developers        # delete group
sudo groupmod -n newname oldname # rename group</pre>

<h3>User Information Commands</h3>

<pre>whoami                          # show current username
id                              # show user ID, group IDs
id john                         # show IDs for specific user
groups                          # show current user's groups
groups john                     # show groups for specific user
who                             # show logged-in users
w                               # show who's logged in and what they're doing
last                            # show login history
lastlog                         # show last login for all users
finger john                     # detailed user information (if installed)</pre>

<h3>su and sudo (switch user / superuser do)</h3>

<pre>su                              # switch to root (requires root password)
su john                         # switch to john (requires john's password)
su - john                       # switch and load john's environment
sudo command                    # run command as root
sudo -u john command            # run command as john
sudo -i                         # interactive root shell
sudo -s                         # shell as root
sudo -l                         # list allowed sudo commands</pre>

<h2>Account and System Information Files</h2>

<h3>Important System Files</h3>

<pre>/etc/passwd                     # user account information
/etc/shadow                     # encrypted passwords (root only)
/etc/group                      # group information
/etc/gshadow                    # secure group information
/etc/sudoers                    # sudo permissions (edit with visudo)
/etc/skel/                      # skeleton directory for new users</pre>

<p><strong>View user info:</strong></p>

<pre>cat /etc/passwd | grep john     # find user entry
getent passwd john              # get user info (better method)
getent group developers         # get group info</pre>

<p><strong>Format of /etc/passwd:</strong></p>

<pre>username:x:UID:GID:comment:home_directory:shell
john:x:1001:1001:John Doe:/home/john:/bin/bash</pre>

<h3>Managing sudo access</h3>

<pre>sudo visudo                     # edit sudoers file safely
sudo usermod -aG sudo john      # add to sudo group (Debian/Ubuntu)
sudo usermod -aG wheel john     # add to wheel group (RHEL/CentOS)</pre>

<p><strong>Example /etc/sudoers entries:</strong></p>

<pre>john ALL=(ALL:ALL) ALL          # john can run any command
%developers ALL=(ALL) NOPASSWD: ALL # group developers, no password
alice ALL=(ALL) /usr/bin/systemctl  # alice can only run systemctl</pre>

<h2>File Ownership in Action</h2>

<p><strong>Check permissions:</strong></p>

<pre>ls -l file.txt
# -rw-r--r-- 1 alice developers 1024 Jan 23 10:00 file.txt
# |         |   |     |         
# |         |   owner group     
# permissions links</pre>

<p><strong>Practical examples:</strong></p>

<pre># Make a script executable for everyone
chmod +x script.sh

# Secure a private SSH key
chmod 600 ~/.ssh/id_rsa
chown $USER:$USER ~/.ssh/id_rsa

# Set up a shared project directory
sudo mkdir /shared/project
sudo chgrp developers /shared/project
sudo chmod 2775 /shared/project  # setgid + rwxrwxr-x

# Fix web server permissions
sudo chown -R www-data:www-data /var/www/html
sudo find /var/www/html -type d -exec chmod 755 {} \;
sudo find /var/www/html -type f -exec chmod 644 {} \;</pre>

</details>

## Bash Operators

Bash chains commands together in a few different ways, and mixing these up is one of the most common daily-use mistakes.

### | (pipe)

```bash
cmd1 | cmd2
```
Sends cmd1's output directly into cmd2's input.

```bash
cat file.txt | grep "error"
```

### && (AND)

```bash
cmd1 && cmd2
```
Runs cmd2 only if cmd1 succeeds (exits with status 0). Useful for chaining steps that depend on each other.

```bash
sudo apt update && sudo apt install pipx
```

### || (OR)

```bash
cmd1 || cmd2
```
Runs cmd2 only if cmd1 fails. Useful as a fallback.

```bash
apt install alien || apt install human
```
(Runs the second install only if the first one fails.)

### ; (sequence)

```bash
cmd1 ; cmd2
```
Runs cmd1, then cmd2, regardless of whether cmd1 succeeded or failed. Useful when you don't care about the outcome of the first command.

```bash
apt search alien ; apt search human
```
(Checks for both, regardless of whether the first search finds anything.)

> [!NOTE]
> `&&`, `||`, and `;` all chain commands, but only `&&` and `||` care whether the first command succeeded. `;` doesn't check at all.

## Test Yourself

Whether you're coming from Windows, macOS, or another Linux distro, here's a quick self-test to make sure the essentials above actually stuck. Try to answer before expanding each one.

<details>
<summary>What does <code>chmod 755 script.sh</code> actually set?</summary>
Owner gets read, write, and execute (7). Group and others get read and execute (5 each), no write. Common for scripts and executables.
</details>

<details>
<summary>What's the difference between <code>useradd</code> and <code>adduser</code>?</summary>
<code>useradd</code> is the low-level tool and won't create a home directory or set a shell unless you pass flags for it. <code>adduser</code> is the interactive, Debian-friendly wrapper that handles those defaults automatically.
</details>

<details>
<summary>What happens if you run <code>cmd1 ; cmd2</code> and cmd1 fails?</summary>
cmd2 runs anyway. <code>;</code> doesn't check the exit status of the first command, it just runs both in sequence.
</details>

<details>
<summary>What's the safest way to preview an <code>rm -rf</code> before actually running it?</summary>
Run the same command with <code>ls</code> instead of <code>rm</code> first, to see exactly what would be affected. Or add <code>-i</code> for interactive prompts, though combining <code>-i</code> with <code>-f</code> cancels the prompt out.
</details>

<details>
<summary>Where does Linux store encrypted user passwords?</summary>
<code>/etc/shadow</code>, readable only by root. <code>/etc/passwd</code> stores account info but not the password hash itself.
</details>

<details>
<summary>What does <code>sudo -i</code> do differently from <code>sudo -s</code>?</summary>
<code>sudo -i</code> starts an interactive root login shell, loading root's own environment and profile. <code>sudo -s</code> starts a shell as root but keeps your current environment.
</details>

<details>
<summary>You want to update packages and only install something new if the update succeeds. Which operator do you use?</summary>
<code>&&</code>. For example: <code>sudo apt update && sudo apt install pipx</code>.
</details>

<details>
<summary>What does the sticky bit (<code>chmod 1777 /tmp</code>) actually do?</summary>
It lets anyone create files in the directory, but only the file's owner (or root) can delete or rename it, even though everyone has write access to the directory itself.
</details>

<hr>

> [!TIP] 
> For further study on this matter there are more easy to understand articles and youtube videos out there. and for daily basic usage these were enough.

#### Next steps,
<div style="text-align:center; font-size:3rem;">
003 -> <a href="./../004">004</a>
</div>

## Related pages

- [007 - Programming on Linux](./../007)

- [009 - Troubleshooting in linux](./../009)

- [011 - Advanced easy guide to linux](./../011)
