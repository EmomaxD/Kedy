@echo off

cd ..

call cmake -S . -B .
call cmake --build . --config Release

cd Demo
cd Release

copy Demo.exe ..\Demo.exe

cd ..

call Demo.exe

pause