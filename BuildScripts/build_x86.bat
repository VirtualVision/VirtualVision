set BACKUP_PATH=%PATH%
set PATH=%PATH%;C:\ThirdParty\opencv\build\x86\vc12\bin
set PATH=%PATH%;C:\ThirdParty\ZeroMQ 4.0.4_x86\bin

cd /d c:\build

cmake -DCMAKE_TOOLCHAIN_FILE=C:\VirtualVision\ToolChains\toolchain_x86.cmake ..\VirtualVision

devenv VirtualVision.sln
