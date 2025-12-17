cd /d %~dp0
call "%VS100COMNTOOLS%\vsvars32.bat"

devenv "..\Projects\Win32\Msvc10\SDK\GFx 4.2 SDK.sln" /BUILD "D3D9_Debug_Static|Win32"
if not "%ERRORLEVEL%" == "0" pause
devenv "..\Projects\Win32\Msvc10\SDK\GFx 4.2 SDK.sln" /BUILD "D3D9_Release_Static|Win32"
if not "%ERRORLEVEL%" == "0" pause
devenv "..\Projects\Win32\Msvc10\SDK\GFx 4.2 SDK.sln" /BUILD "D3D9_Shipping|Win32"
if not "%ERRORLEVEL%" == "0" pause

devenv "..\Projects\Win32\Msvc10\SDK\GFx 4.2 SDK.sln" /BUILD "D3D9_Debug_Static|x64"
if not "%ERRORLEVEL%" == "0" pause
devenv "..\Projects\Win32\Msvc10\SDK\GFx 4.2 SDK.sln" /BUILD "D3D9_Release_Static|x64"
if not "%ERRORLEVEL%" == "0" pause
devenv "..\Projects\Win32\Msvc10\SDK\GFx 4.2 SDK.sln" /BUILD "D3D9_Shipping|x64"
if not "%ERRORLEVEL%" == "0" pause

devenv "..\Projects\Xbox360\Msvc10\SDK\GFx 4.2 Xbox 360 SDK.sln" /BUILD "Debug|Xbox 360"
if not "%ERRORLEVEL%" == "0" pause
devenv "..\Projects\Xbox360\Msvc10\SDK\GFx 4.2 Xbox 360 SDK.sln" /BUILD "Release|Xbox 360"
if not "%ERRORLEVEL%" == "0" pause
devenv "..\Projects\Xbox360\Msvc10\SDK\GFx 4.2 Xbox 360 SDK.sln" /BUILD "Shipping|Xbox 360"
if not "%ERRORLEVEL%" == "0" pause

devenv "..\Projects\PS3\Msvc10\SDK\GFx 4.2 PS3 SDK.sln" /BUILD "Debug_NoRTTI|PS3"
if not "%ERRORLEVEL%" == "0" pause
devenv "..\Projects\PS3\Msvc10\SDK\GFx 4.2 PS3 SDK.sln" /BUILD "Release_NoRTTI|PS3"
if not "%ERRORLEVEL%" == "0" pause
devenv "..\Projects\PS3\Msvc10\SDK\GFx 4.2 PS3 SDK.sln" /BUILD "Shipping_NoRTTI|PS3"
if not "%ERRORLEVEL%" == "0" pause

start BuildCafe.bat
start BuildWii.bat