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

CMAKE_ARGS="${CMAKE_ARGS} -DWIN32=1"
CMAKE_ARGS="${CMAKE_ARGS} -DCMAKE_BUILD_TYPE=${BuildType}"
CMAKE_ARGS="${CMAKE_ARGS} -DCMAKE_CXX_LINK_EXECUTABLE=\"<CMAKE_LINKER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>\""
CMAKE_ARGS="${CMAKE_ARGS} -DCMAKE_C_COMPILER=gcc"
CMAKE_ARGS="${CMAKE_ARGS} -DCMAKE_CXX_COMPILER=g++"

cmake ${CMAKE_ARGS} -G "Ninja" ${WorkspacePath}