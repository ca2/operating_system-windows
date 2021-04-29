cd /d "C:\xcore\platform\app" &msbuild "app.vcxproj" /t:sdvViewer /p:configuration="basis" /p:platform=x64
exit %errorlevel% 