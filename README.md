# DDietTracker - Desktop Diet Tracker
A desktop application for counting calories and nutrients.
![Zrzut ekranu z 2023-10-09 01-45-17](https://github.com/MieszkoP/DDietTracker/assets/78937784/07f4f9fa-b416-4a08-8f71-c5a6014904c1)

## How to download application? (Linux only)
Go to link - https://drive.google.com/drive/folders/1S50IIiUawC67S_nicYw3XFzsEaP3zWvk?usp=drive_link
1. Download all directory,
2. Allow  file "DDietTracker" to be executed as a program

## How to compile app from source code?
First, download source code from github:

```git clone https://github.com/MieszkoP/DDietTracker.git```

The dependencies you needed include:

- Qt (I used version 5.15.2 Qt)
- Cmake (I used 3.24.2)
- Jsoncpp
- C++ 20 (so, You need to make sure you use the correct compiler - I used g++ 11.4.0)

After downloading the [jsoncpp](https://github.com/open-source-parsers/jsoncpp) library, you need to edit the CmakeLists.txt file by replacing the path to this library:

```set(CMAKE_PREFIX_PATH "~/vcpkg/packages/jsoncpp_x64-linux" ${CMAKE_PREFIX_PATH})```
and delete 
```set(CMAKE_PREFIX_PATH "/home/mieszko/Qt/5.15.2/gcc_64/lib/cmake/Qt5" ${CMAKE_PREFIX_PATH})``` or change path to installed Qt, if you want to build and run project from command line. 

Next, open project in Qt Creator:

Set Build option to "Release" and click "Run".

If you want to build the program from the command line, enter the following into the terminal:

```cmake -S <source_code_address> -B <built_program_folder_address>```

```cmake --build <built_program_folder_address> --config Release --target all --```

## How to create standalone app after compilation?

To turn the built version into a standalone application, you need the linuxdeployqt (for Linux) or windeployqt (for Windows) tool. They copy the libraries and plugins used by the built version to the program folder, making the program standalone.

Since I use Linux, I will tell you how to create a standalone application for Linux:
1. Make sure you are using the correct version of Ubuntu - compatible with linuxdeployqt
As we read in the tool's Readme:
> linuxdeployqt refuses to work on systems any newer than the oldest currently still-supported Ubuntu LTS release
This means you can't use Ubuntu 22.04, but you can use Ubuntu 20.04.
2. Make sure you have the appropriate compiler and the jsoncpp library downloaded. You can add compiler information to the CmakeLists.txt file
3. Build the application
4. Add to the environment variable the path where the binary files corresponding to the Qt version are located (for me it was the libQt5Core.so.5 file)
  ```export PATH=/.../Qt/5.15.2/gcc_64/bin/:$PATH```
5. Run linuxdeployqt:
  ```/linuxdeployqt-continuous-x86_64.AppImage '/.../build-nienazwany11-Desktop_Qt_5_15_2_GCC_64bit-Release/DDietTracker' -verbose=3 -appimages```

## Unit tests
Unit tests are present in a separate project.
[DDietTracker Tests](https://github.com/MieszkoP/DDietTrackerUnitTests)
