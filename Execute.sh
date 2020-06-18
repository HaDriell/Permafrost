WorkspacePath=`pwd`

#Check for Build Profile (Debug, Release)
if [ -z "$1" ]; then
    BuildFolder=Debug
else
    BuildFolder="$1"
fi

BuildPath=${WorkspacePath}/${BuildFolder}

${BuildPath}/Sandbox/Sandbox.exe