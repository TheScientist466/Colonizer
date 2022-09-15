# Colonizer

**Try to colonize the whole star system before the enemy does!**

## Build
Clone the repository
```
git clone https://github.com/TheScientist466/Colonizer.git
cd Colonizer
```

### Windows
##### Visual Studio (MSVC)
The project is pretty much set up, with the `.sln` file present in the root of the repository.

### Linux
##### Prerequisites:
+ SFML library
    - Install from your distribution's package repository
    - Get [source code](https://github.com/SFML/SFML), build it and intall it
    - Download the precompiled SDK and manually copy the files
+ CMake
+ A C/C++ compiler which CMake can generate build file for (eg:- GNU g++)

##### Installing library from distribution's package repositories (preffered)
Most big distribution will have sfml in their official repositories.

###### For Debian/Ubuntu based distributions it would be:

```
sudo apt-get update
sudo apt-get install libsfml-dev
```

###### For Arch based distributions it would be:
```
sudo pacman -Sy sfml
```

###### For Fedora based distributions it would be:
```
sudo dnf makecache --refresh
sudo dnf install SFML
```

##### Building
Continue from **Building anywhere with CMake**

### Building anywhere with CMake
##### Prerequisites:
+ SFML library from the [official website](https://www.sfml-dev.org/)
    - [Prebuilt binaries](https://www.sfml-dev.org/download/sfml/2.5.1/)
    - [Source code](https://github.com/SFML/SFML) with [build instructions](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php)
+ CMake
+ A C/C++ compiler which CMake can generate build file for (eg:- MinGW)

##### Building 
Below are some examples to generate build files with CMake and building them with a compiler. CMake envionment variables and options should be set according to **your system**

##### Building Examples
###### Arch linux with SFML installed from official repos and compiler set to GNU g++
```
mkdir build && cd build
cmake -G "Unix Makefiles" ..
make
./Colonizer
```

