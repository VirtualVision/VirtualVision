set BACKUP_PATH=%PATH%
set PATH=%PATH%;C:\ThirdParty\opencv\build\x64\vc12\bin;
set PATH=%PATH%;C:\ThirdParty\ZeroMQ 4.0.4_x64\bin

cd /d c:\build

cmake -G "Visual Studio 12 2013 Win64" -DCMAKE_TOOLCHAIN_FILE=C:\VirtualVision\ToolChains\toolchain_x64.cmake ..\VirtualVision

devenv VirtualVision.sln