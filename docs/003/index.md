---
layout: default
title: "GNU/Linux Legends"
description: "History and information about GNU/Linux legends"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/003/thumb.png
---

### Linux is an open source kernel made by Linus Torvalds. 
This is already "being known" for most of you guys, the question is how that kernel operates? Well busybox is the core utility of original linux and there wasn't any init system , users had to configure /etc/rc for init system. After a long time GNOME was founded, they made their own toolkit, own softwares and more. The term GNU/Linux means it's running glibc (GNU C library) at its core using GNU coreutils (a package that contains cat, grep, touch command's binary) ,  it's installed besides busybox in every GNU/Linux OSes. Because of Debian, Arch and many more user-friendly distros use GNU at its core, it's easy to say that other alternatives wouldn't work without recompiling against a custom libc. Same for systemd init system (non-GNU) , it's hard to create an alternative because all of them are just straight up using compatibility layers which makes sense, but this is the common problem of Linux: there is no shell, you have to create one.

---

Most GNU apps you should know are:
Because most of these are pre-installed into any GNU/Linux or there aren't any better alternatives

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
# gpg (GNU PG verifier)
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

<details>
<summary><strong>File System Hacks and Regex</strong> <sub>(click to expand)</sub></summary>

## Permissions and Ownership

### chmod (change file mode/permissions)

**Understanding Linux Permissions:**
Every file has three permission sets: Owner (u), Group (g), Others (o)
Each set has three permissions: Read (r=4), Write (w=2), Execute (x=1)

**Numeric (Octal) Method:**
```bash
chmod 755 script.sh             # rwxr-xr-x (owner: all, group: rx, others: rx)
chmod 644 file.txt              # rw-r--r-- (owner: rw, group: r, others: r)
chmod 700 private.sh            # rwx------ (owner only)
chmod 666 shared.txt            # rw-rw-rw- (all can read/write)
chmod 400 secret.key            # r-------- (owner read-only)
```

**Common Permission Numbers:**
- `777` - rwxrwxrwx (everyone can do everything - dangerous!)
- `755` - rwxr-xr-x (standard for executables/directories)
- `644` - rw-r--r-- (standard for regular files)
- `600` - rw------- (private files, like SSH keys)
- `400` - r-------- (read-only secrets)

**Symbolic Method:**
```bash
chmod u+x script.sh             # add execute for owner (user)
chmod g+w file.txt              # add write for group
chmod o-r private.txt           # remove read for others
chmod a+x program               # add execute for all (a=all)
chmod u=rwx,g=rx,o=r file       # set exact permissions
chmod +x script.sh              # add execute for all
chmod -R 755 directory/         # recursive permission change
```

**Special Permissions:**
```bash
chmod 4755 program              # setuid (runs as file owner)
chmod 2755 directory            # setgid (new files inherit group)
chmod 1777 /tmp                 # sticky bit (only owner can delete)
chmod u+s binary                # add setuid
chmod g+s directory             # add setgid
chmod +t directory              # add sticky bit
```

### chown (change owner)

**Syntax:** `chown [user][:group] file`

```bash
chown alice file.txt            # change owner to alice
chown alice:developers file.txt # change owner and group
chown :developers file.txt      # change group only
chown -R alice:staff /home/alice # recursive ownership change
chown --from=bob alice file.txt # change only if current owner is bob
```

### chgrp (change group)

```bash
chgrp developers project.txt    # change group to developers
chgrp -R staff /shared/folder   # recursive group change
chgrp --reference=file1 file2   # copy group from file1 to file2
```

## User and Group Management

### useradd / adduser (create user)

```bash
# useradd (low-level)
sudo useradd john               # create basic user
sudo useradd -m john            # create user with home directory
sudo useradd -m -s /bin/bash john # specify shell
sudo useradd -m -G sudo,developers john # add to groups
sudo useradd -m -u 1500 john    # specify UID
sudo useradd -m -e 2025-12-31 john # expiration date

# adduser (high-level, interactive - Debian/Ubuntu)
sudo adduser john               # interactive user creation
```

### usermod (modify user)

```bash
sudo usermod -aG sudo john      # add user to sudo group (append)
sudo usermod -aG docker,www-data john # add to multiple groups
sudo usermod -l newname oldname # rename user
sudo usermod -s /bin/zsh john   # change shell
sudo usermod -d /new/home john  # change home directory
sudo usermod -L john            # lock account
sudo usermod -U john            # unlock account
sudo usermod -e 2025-12-31 john # set expiration date
```

### userdel (delete user)

```bash
sudo userdel john               # delete user (keeps home directory)
sudo userdel -r john            # delete user and home directory
sudo userdel -f john            # force delete (even if logged in)
```

### passwd (change password)

```bash
passwd                          # change your own password
sudo passwd john                # change another user's password
sudo passwd -l john             # lock user account
sudo passwd -u john             # unlock user account
sudo passwd -d john             # delete password (passwordless login)
sudo passwd -e john             # expire password (force change on next login)
```

### groupadd / groupdel (manage groups)

```bash
sudo groupadd developers        # create group
sudo groupadd -g 1500 developers # create with specific GID
sudo groupdel developers        # delete group
sudo groupmod -n newname oldname # rename group
```

### User Information Commands

```bash
whoami                          # show current username
id                              # show user ID, group IDs
id john                         # show IDs for specific user
groups                          # show current user's groups
groups john                     # show groups for specific user
who                             # show logged-in users
w                               # show who's logged in and what they're doing
last                            # show login history
lastlog                         # show last login for all users
finger john                     # detailed user information (if installed)
```

### su and sudo (switch user / superuser do)

```bash
su                              # switch to root (requires root password)
su john                         # switch to john (requires john's password)
su - john                       # switch and load john's environment
sudo command                    # run command as root
sudo -u john command            # run command as john
sudo -i                         # interactive root shell
sudo -s                         # shell as root
sudo -l                         # list allowed sudo commands
```

## Account and System Information Files

### Important System Files

```bash
/etc/passwd                     # user account information
/etc/shadow                     # encrypted passwords (root only)
/etc/group                      # group information
/etc/gshadow                    # secure group information
/etc/sudoers                    # sudo permissions (edit with visudo)
/etc/skel/                      # skeleton directory for new users
```

**View user info:**
```bash
cat /etc/passwd | grep john     # find user entry
getent passwd john              # get user info (better method)
getent group developers         # get group info
```

**Format of /etc/passwd:**
```
username:x:UID:GID:comment:home_directory:shell
john:x:1001:1001:John Doe:/home/john:/bin/bash
```

### Managing sudo access

```bash
sudo visudo                     # edit sudoers file safely
sudo usermod -aG sudo john      # add to sudo group (Debian/Ubuntu)
sudo usermod -aG wheel john     # add to wheel group (RHEL/CentOS)
```

**Example /etc/sudoers entries:**
```
john ALL=(ALL:ALL) ALL          # john can run any command
%developers ALL=(ALL) NOPASSWD: ALL # group developers, no password
alice ALL=(ALL) /usr/bin/systemctl  # alice can only run systemctl
```

## File Ownership in Action

**Check permissions:**
```bash
ls -l file.txt
# -rw-r--r-- 1 alice developers 1024 Jan 23 10:00 file.txt
# |         |   |     |         
# |         |   owner group     
# permissions links
```

**Practical examples:**
```bash
# Make a script executable for everyone
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
sudo find /var/www/html -type f -exec chmod 644 {} \;
```

</details>

