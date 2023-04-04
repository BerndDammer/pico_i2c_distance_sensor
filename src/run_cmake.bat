call ../../../SetEnv.bat

rd /s /q ..\.settings
rd /s /q ..\build
rd /s /q ..\CMakeFiles
rd /s /q ..\generated
rd /s /q ..\pico-sdk
rd /s /q ..\pioasm

del /s /q ..\.cproject
del /s /q ..\.project
del /s /q ..\Makefile
del /s /q ..\cmake_install.cmake
del /s /q ..\*.elf
del /s /q ..\*.uf2
del /s /q ..\CMakeCache.txt




set P=%PICO_ROOT%bin\python
set PATH=%P%;%PATH%
set P=%PICO_ROOT%bin\python\Scripts
set PATH=%P%;%PATH%


set P=%PICO_ROOT%bin\cmake\bin
set PATH=%P%;%PATH%

set P=%PICO_ROOT%bin\make
set PATH=%P%;%PATH%

set PICO_SDK_PATH=%PICO_ROOT%pico-sdk

set PICO_TOOLCHAIN_PATH=%PICO_ROOT%bin\gcc


rem ---------------------------------
set
pause
rem ---------------------------------


cd ..

call cmake -S src -B . -G "Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug
pause


