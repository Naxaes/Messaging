@echo off

if not exist build mkdir build
pushd build


set DISABLED_WARNINGS=-wd4100 -wd4710 -wd4700

cl -Od -Zi -WX -Wall -nologo %DISABLED_WARNINGS%  ..\client.cpp  -link -out:client.exe
cl -Od -Zi -WX -Wall -nologo %DISABLED_WARNINGS%  ..\server.cpp  -link -out:server.exe


popd build
