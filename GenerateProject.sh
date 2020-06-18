WorkspacePath=`pwd`

#Check for Build Profile (Debug, Release)
if [ -z "$1"]; then
    BuildFolder=Debug
else
    BuildFolder="$1"
fi

BuildPath=${WorkspacePath}/${BuildFolder}

#Wipe Existing Build Tree
if [ -d BuildPath ]; then
    rm -rf ${BuildPath}
fi
#Create Build Tree
mkdir ${BuildPath}
#Generate out-of-source Build Tree for MSYS2
cd ${BuildPath}
cmake -DCMAKE_BUILD_TYPE=Debug -G "MSYS Makefiles" ${WorkspacePath}