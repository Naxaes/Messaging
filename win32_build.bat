@echo off

if not exist build mkdir build
pushd build


set DISABLED_WARNINGS=-wd4100 -wd4710 -wd4700
set BUILD_CLIENT=cl -Od -Zi -WX -Wall -nologo %DISABLED_WARNINGS%  ..\client.cpp  -link -out:client.exe

set BUILD_SERVER=cl -Od -Zi -WX -Wall -nologo %DISABLED_WARNINGS%  ..\server.cpp  -link -out:server.exe


if "%1"=="" (
	%BUILD_CLIENT%
	%BUILD_SERVER%
)
if "%1"=="client" (
	%BUILD_CLIENT%
)
if "%1"=="server" (
	%BUILD_SERVER%
)

popd build
