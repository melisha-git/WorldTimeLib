@echo off
vcpkg/bootstrap-vcpkg.bat
vcpkg/vcpkg.exe install curl jsoncpp
vcpkg/vcpkg.exe integrate install