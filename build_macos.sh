VERSION=3.3359.1772.gd1df190
echo $VERSION
wget -c "http://opensource.spotify.com/cefbuilds/cef_binary_"$VERSION"_macosx64.tar.bz2"
bsdtar -xvf "cef_binary_"$VERSION"_macosx64.tar.bz2"
mv "cef_binary_"$VERSION"_macosx64" CEF_MAC
cp -R CEF_MAC/include .
cd CEF_MAC
cmake -Bbuild -H.
cd build
make cefclient -j8
cd ../..
cp CEF_MAC/build/libcef_dll_wrapper/libcef_dll_wrapper.a .
cp -R CEF_MAC/build/tests/cefclient/Release/cefclient\ Helper.app .
mv cefclient\ Helper.app/Contents/MacOS/cefclient\ Helper cefclient\ Helper.app/Contents/MacOS/QCefBrowser\ Helper
mv cefclient\ Helper.app QCefBrowser\ Helper.app

mv "CEF_MAC/Release/Chromium Embedded Framework.framework" .

qmake
make -j8

macdeployqt QCefBrowser.app

install_name_tool -change @rpath/Frameworks/Chromium\ Embedded\ Framework.framework/Chromium\ Embedded\ Framework @rpath/../Frameworks/Chromium\ Embedded\ Framework.framework/Chromium\ Embedded\ Framework QCefBrowser.app/Contents/MacOS/QCefBrowser

mv "Chromium Embedded Framework.framework" QCefBrowser.app/Contents/Frameworks
mv "QCefBrowser Helper.app" QCefBrowser.app/Contents/Frameworks

./QCefBrowser.app/Contents/MacOS/QCefBrowser