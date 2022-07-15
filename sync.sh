#!/usr/bin/env bash
# This script is mainly used to sync REAME.md.
# git pull origin main:main

cat README_HEAD.md > README.md

dir="leetcode-solution"
ls $dir > temp

while IFS= read -r line; 
do 
    echo "- [${line%.*}]($dir/$line)" >> README.md; 
done < temp

rm temp
echo >> README.md
cat README_TAIL.md >> README.md