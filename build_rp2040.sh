#!/bin/bash
# run this with `curl -fsSL <github raw URL> | sh`

# get QMK_HOME
 QMK_FIRMWARE=$(qmk env | grep QMK_FIRMWARE | cut -d '=' -f 2 | sed s.C:/./c/.g | tr -d \")

if [[ -z "$QMK_FIRMWARE" ]]; then
	# QMK has not been setup yet
	qmk setup -y
	QMK_FIRMWARE=$(qmk env | grep QMK_FIRMWARE | cut -d '=' -f 2 | sed s.C:/./c/.g | tr -d \")
fi

# go there
cd "$QMK_FIRMWARE"

# add the remote
git remote add nullbits https://github.com/jaygreco/qmk_firmware

# check if there are changes
if ! git diff --exit-code; then
	# there are unpushed changes
	echo "There are unpushed changes to your QMK firmware repo! The're going to be stashed. To get them back, use 'git stash pop'."
fi

git fetch nullbits

# checkout the nullbits repo rp2040_clean branch
git checkout nullbits/rp2040_clean

# reset submodules
git submodule update

# print a message
echo "Done! You now have the nullbits RP2040 repo checked out."
echo "Build RP2040 firmwares with 'qmk compile -kb nullbitsco/<keyboard>/rp2040 -km all'."
echo "To get the original QMK repository back, check it out with 'git checkout master'"