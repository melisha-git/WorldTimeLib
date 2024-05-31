# WorldTimeLib
Library for convenient access to worldtimeapi.org
## Installing

### Step 1: Cloning repo

```sh
git clone --recurse-submodules git@github.com:melisha-git/WorldTimeLib.git
cd WorldTimeLib
```

### Step 2: build vcpkg

* Windows
```sh
bootstrap-vcpkg.bat
```
* Linux
```sh
chmod +x bootstrap-vcpkg.sh
bootstrap-vcpkg.sh
```

### Step 3: build project

* Windows
Open the project in MS Visual Studio and build it as a dll or lib. <a href="https://learn.microsoft.com/ru-ru/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170#to-add-the-dll-header-to-your-include-path">Connect</a> to your project and use

* Linux
Use libWorldTimeLib.a in your project.

```sh
cmake .
make
```

