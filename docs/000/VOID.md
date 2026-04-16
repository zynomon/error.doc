---
title: "VOID"
description: "VOID is a branch of error.os which could be called testing but it is not. These are ISOs that boot but have some issues. We ship them regardless so users can preview upcoming features."
embed-thumbnail: https://github.com/zynomon/error/raw/web-side/icons/void.jpg
icon: https://github.com/zynomon/error/raw/web-side/icons/void.jpg
---

### VOID is a branch of error.os

VOID releases can look different or behave differently across versions. VOID v1 and v2 were beta releases of Neospace 2025. VOID v3 is a beta release of Neospace 2026.

# VOID v3

VOID v3 is the third version of VOID. In other words it is NS26β1. It contains advanced fixes and customizations along with the faults and fixes from Neospace 2025. It was released on March 26, 2026.

This version includes Vex Cytoplasm which is the text editor at version 4.1 with an added plugin architecture. Onu is at version 0.6 with many fixes applied. err_ is at version 3.0 and now includes a wine optimizer. error.doc is at version 4.0 and is now offline based with man page support and additional changes. error.base received minimal changes. Calamares settings error received some fixes tied to installing error.os but there are still issues tied to apt run live which is why this remains in the VOID section.

#### Known Issues

- Issues with apt run live
- Calamares installation still has problems

# VOID v2

VOID v2 is the second version of VOID. It was made one month after VOID v1. We built several applications such as Vex and Onu instead of using Featherpad or Falkon. This should have made the ISO smaller but this time it was built using the Debian live build command line tool.

In this version we made a full system that boots and shows our own theme. However Onu as a browser was still experimental. I (zynomon aelius) added Calamares but it did not install correctly.

#### Known Issues

- No Calamares installer (you can install it manually)

# VOID v1

VOID v1 is the first version of VOID. It was an experimental build of what would become Neospace 2025. It was released in September 2025, the same month the project started. It was built using Penguin's Egg on Debian 13.

At the time I (zynomon aelius) did not know that `/etc/skel` existed. This was unfortunate because I made configuration files but they did not save globally. However it did retrieve the application sets which at least made it feel like a part of error.os.

#### Known Issues

- No error.os theming
- No error.os repository
- Contains bloat from Penguin's Egg

---

## Download links

<table>
<tr>
<th>VOID v3</th>
<th>VOID v2</th>
<th>VOID v1</th>
</tr>
<tr>
<td><a href="https://archive.org/download/error.os-neospace-2026/NS_26%20VOID%20%28%20boots%20but%20has%20issues%20%29/NS26_VOID_3.0.iso">Download VOID v3</a></td>
<td><a href="https://archive.org/details/error.os-void-0.2">Download VOID v2</a></td>
<td><a href="https://archive.org/details/error.os-Neospace-64bit">Download VOID v1</a></td>
</tr>
</table>