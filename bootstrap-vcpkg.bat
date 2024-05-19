@echo off
setlocal

REM Установить путь к vcpkg
set VCPKG_ROOT=%~dp0vcpkg

REM Инициализация vcpkg
if not exist "%VCPKG_ROOT%\vcpkg.exe" (
    echo Bootstrapping vcpkg...
    call "%VCPKG_ROOT%\bootstrap-vcpkg.bat"
)

REM Установка пакетов
echo Installing dependencies...
"%VCPKG_ROOT%\vcpkg.exe" install curl jsoncpp

REM Интеграция vcpkg с Visual Studio
echo Integrating vcpkg with Visual Studio...
"%VCPKG_ROOT%\vcpkg.exe" integrate install

echo.
echo vcpkg setup completed.
echo.

endlocal
pause