
#Delete any existing CMake Build tree
if [ -d "Build" ]; then
    rm -rf Build
fi

#Create Build Tree
if [ ! -d "Build" ]; then
    mkdir Build
    mkdir Build/Debug
    mkdir Build/Release
fi

#Generate out-of-source CMake build trees for MSYS2
cd Build/Debug
cmake -DCMAKE_BUILD_TYPE=Debug -G "MSYS Makefiles" ../..
cd ../Release
cmake -DCMAKE_BUILD_TYPE=Release -G "MSYS Makefiles" ../..