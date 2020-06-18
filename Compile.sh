WorkspacePath=`pwd`

#Check for Build Profile (Debug, Release)
if [ -z "$1" ]; then
    BuildFolder=Debug
else
    BuildFolder="$1"
fi

BuildPath=${WorkspacePath}/${BuildFolder}

#Invoke Make if Build Folder exists
if [ -d ${BuildPath} ]; then
    cd ${BuildPath}
    make VERBOSE=1
fi