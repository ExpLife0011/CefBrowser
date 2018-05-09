REM comenv
REM vc2017
@echo off
set VERSION=3.3359.1772.gd1df190

bash -c "wget -c http://opensource.spotify.com/cefbuilds/cef_binary_%VERSION%_windows32.tar.bz2"
bash -c "bsdtar -xvf cef_binary_%VERSION%_windows32.tar.bz2"
move cef_binary_*_windows32 CEF_WIN

REM Need cmake
cd CEF_WIN
cmake -Bbuild -H.

cd build
msbuild /m /p:configuration=release cef.sln

cd ..\..

copy CEF_WIN\Release\libcef.lib .
copy CEF_WIN\build\libcef_dll_wrapper\Release\libcef_dll_wrapper.lib .
xcopy /y /s /i CEF_WIN\include include

msbuild /m /p:configuration=release

copy /y release\QCefBrowser.exe CEF_WIN\build\tests\cefclient\Release\
CEF_WIN\build\tests\cefclient\Release\QCefBrowser.exe
