#!/bin/bash

function file_check() {
	if [ ! -f "$1" ]
	then
		echo "Error: file $1 not found"
		echo "       script must be run from the root of the repo"
		exit 1
	fi
}

file_check ./scripts/setup-merge-tools.sh
file_check CMakeLists.txt
file_check .git/config

ABS_PATH="$(cd "$(dirname "$0" || exit 1)"/ && pwd -P)"

read -r -d '' driver << EOF
[merge "ddnet-cmake"]
	name = Support for file conflicts in CMakeLists.txt
	driver = $ABS_PATH/ddnet-cmake-merge-tool.sh %O %A %B
EOF

if ! grep -qF '[merge "ddnet-cmake"]' .git/config
then
	echo -e "\n$driver" >> .git/config
fi

activate_driver=true

arg="$1"
if [ "$arg" == "--help" ] || [ "$arg" == "help" ] || [ "$arg" == "-h" ]
then
	echo "usage: ./scripts/setup-merge-tools.sh [ARG]"
	echo "arguments:"
	echo "  off | uninstall | deactivate     revert the activation of the merge driver"
	exit 0
elif [ "$arg" == "off" ] || [ "$arg" == "uninstall" ] || [ "$arg" == "deactivate" ]
then
	echo "[*] turning custom merge driver off ..."
	activate_driver=false
else
	echo "Error: unknown argument '$arg' see --help"
	exit 1
fi

# https://stackoverflow.com/a/14099431
# in the .gitattributes we say README.md merge=ours
# but the "ours" merge driver is off by default
git config merge.ours.driver "$activate_driver" 
git config merge.ours.ddnet-cmake "$activate_driver" 

