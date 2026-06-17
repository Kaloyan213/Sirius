@echo off
pushd %~dp0\..\
call Vendor\premake\binaries\premake5.exe vs2022
popd
PAUSE
