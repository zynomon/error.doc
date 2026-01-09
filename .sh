#!/bin/bash

mkdir -p /docs

folders=("000" "001" "002" "003" "004" "005" "006" "007" "008" "009" "010" "011" "012")

titles=(
    "Introduction"
    "Downloading and checksum"
    "Installation and setup"
    "GNU/Linux Legends"
    "Our default apps"
    "Customizing The distro"
    "Gaming on Linux"
    "Programming on Linux"
    "Driver management and Nvidia drivers"
    "Troubleshooting"
    "What you can Do and don'ts"
    "Advanced easy Linux guide"
    "The story of the distro"
)

descriptions=(
    "Introduction to the guide and getting started"
    "Guide for downloading files and verifying checksums"
    "Step-by-step installation and setup instructions"
    "History and information about GNU/Linux legends"
    "Overview of default applications included"
    "Guide for customizing your Linux distribution"
    "Complete guide for gaming on Linux systems"
    "Programming setup and tools for Linux development"
    "Managing drivers and installing Nvidia drivers"
    "Common troubleshooting steps and solutions"
    "Best practices and things to avoid on Linux"
    "Advanced but easy-to-follow Linux guide"
    "The history and story behind the distribution"
)

for i in {0..12}; do
    folder_num=$(printf "%03d" $i)
    folder_path="docs/${folder_num}"
    mkdir -p "$folder_path"
    cat > "$folder_path/index.md" << EOF
---
layout: default
title: "${titles[i]}"
description: "${descriptions[i]}"
embed-thumbnail: https://zynomon.github.io/error.doc/docs/${folder_num}/thumb.png
---
EOF

    echo "Created: $folder_path/index.md"
done

echo "done"
