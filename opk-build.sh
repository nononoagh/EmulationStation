#!/bin/sh
cp $1 resources/$1
mksquashfs resources/* ./$1.opk -all-root -noappend -no-exports -no-xattrs
rm resources/$1

if [ -z ${2+x} ]; then
  echo "'$2' is unset, please provide the GCW0's IP";
else
  echo "Uploading OPK...";
  scp $1.opk od@$2:/media/data/apps/
fi