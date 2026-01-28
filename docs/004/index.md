---
layout: default
title: "Our default apps"
description: "Overview of default applications included"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/004/thumb.png
---

# Introduction

After installation, you will have a set of applications in your device as alternatives to more storage space eating ones. These applications are made by error.os team.
These are the applications included:

- error.doc
- err_
- vex
- onu

### error.doc

<img width="512" height="512" src="https://github.com/zynomon/error/tree/web-side/icons/doc/doc.svg" alt="error.doc logo">
error.doc is a documentation viewer qt wrapper for this page  *and also a manpage viewer ( to do ).*

### Vex
vex is a simple text editor that has a lot of features that are very useful in daily life, it's designed to be small fast and usable for small text editing, like editing smaller files or testing code snippets or just simply search and replace terms instantly. that takes a lot of time on IDEs or editors like vscode or sublime text.

### err_
err_ can be pronounced as *E. R. R. Dashboard* its like the root of error.os, this application serves as a settings, setup manager, application installer, application remover , wine configuration manager, and more. all in one place.

### Onu
onu is a web browser that weights less than 300kb yet it has all features like modern javascript support, css support, html support, and more. it's designed to be fast and lightweight.

# Pitfalls
all of this application above has common issues like , they are in beta , laggy , buggish because of no user experiencing thier feedbacks

# Some underlaying error.os applications

This list contains the following applications:
calamares-settings-error
error.base
libtrigonometry
once

### calamares-settings-error
calamares settings error is a calamares configuration for error.os scheme , you will see this working behind in an error.os live system.

### error.base
error.base is a base application for any debian/ubuntu system to patch it to make it error.os it has a long postinst script that will configure the system to be error.os, it contains the kde system theme provided by error.os ( credits to kde monochrome theme) and  it also contains a small version of bibata cursor theme, openemoji font theme, kora icon theme and last of all few error.os tweaks you will see your kde system change in few minutes if you used this script. 
<sub>a little notice that error.base doesnt contains everything made by error.os its a mixture of picking up a good theme and packing it up, because minimal kde looks ugly</sub>

> alert
> this is beta the postrm script isnt configured to make the system state ( core information ) back to what it was before


### libtrigonometry
this is a library it contains header called cos.h cosec.h , sin.h , cot.h and more coming soon.
What this does?
this works as a non redundant multiple definition of simple stuff like cos+cosec **crash and basic /tmp logger** cot **translation system** sin **system information fetcher**

so in conclusion if you want to know more check it in [here](https://github.com/zynomon/libtrigonometry)

### once
once is a clean up script and also a gui onboarder that will be there in an installed system. it just self distructs itself after it's done cleaning up.
