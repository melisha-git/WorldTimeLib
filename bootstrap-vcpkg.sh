#!/bin/bash
set -e

# Установить путь к vcpkg
VCPKG_ROOT="$(dirname "$(realpath "$0")")/vcpkg"

# Инициализация vcpkg
if [ ! -f "$VCPKG_ROOT/vcpkg" ]; then
    echo "Bootstrapping vcpkg..."
    "$VCPKG_ROOT/bootstrap-vcpkg.sh"
fi

# Установка пакетов
echo "Installing dependencies..."
"$VCPKG_ROOT/vcpkg" install curl jsoncpp

echo
echo "vcpkg setup completed."
echo

read -p "Press any key to continue..." -n1 -s
echo
