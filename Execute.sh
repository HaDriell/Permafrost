WorkspacePath=`pwd`

#Check for Build Profile (Debug, Release)
if [ -z "$1" ]; then
    BuildFolder=Debug
else
    BuildFolder="$1"
fi

#Check for Build Target (Any executable Project)
if [ -z "$2"]; then
    BuildTarget=Sandbox
else
    BuildTarget="$2"
fi

BuildPath="${WorkspacePath}/${BuildFolder}/${BuildTarget}"
ProjectPath="${WorkspacePath}/${BuildTarget}"

if [ -d "${ProjectPath}/res" ]; then
    ln -fs "${ProjectPath}/res" "${BuildPath}/res"
fi

cd ${BuildPath}
./${BuildTarget}