WorkspacePath=`pwd`

#Check for Build Profile (Debug, Release)
if [ -z "$1"]; then
    BuildType=Debug
else
    BuildType="$1"
fi

BuildPath=${WorkspacePath}/${BuildType}

#Wipe Existing Build Tree
if [ -d ${BuildPath} ]; then
    rm -rf ${BuildPath}
fi
#Create Build Tree
mkdir ${BuildPath}

#Generate out-of-source Build Tree for MSYS2
cd ${BuildPath}

export CC=gcc
export CXX=g++

cmake -DWIN32=1 -DCMAKE_BUILD_TYPE=${BuildType} -G "Ninja" ${WorkspacePath}