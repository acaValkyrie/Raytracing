#!/bin/bash
chmod +rwx *
echo "compling"
cc animate.c img.c td.c td_func.c ray.c -lm
rm -r ppm
mkdir ppm
cd ppm
echo "executing"
../a.out
filename="anim_`date '+%m_%d_%T'`"
echo "converting"
convert -delay 5 img*.ppm ${filename}.gif
mv ${filename}.gif ../gif
eog ../gif/${filename}.gif
