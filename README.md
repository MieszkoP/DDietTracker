# DDietTracker Desktop Diet Tracker
A desktop application for counting calories and nutrients.

## How to download application?
Go to website - 

## How to compile app from source code?
First, download source code from github:

The dependencies you needed include:

- Qt (I used 5.15.2 and GCC compiler g++ 11.4.0)
- Cmake (I used 3.24.2)
- Jsoncpp

After downloading the [jsoncpp](https://github.com/open-source-parsers/jsoncpp) library, you need to edit the CmakeLists.txt file by replacing the path to this library:

```set(CMAKE_PREFIX_PATH "~/vcpkg/packages/jsoncpp_x64-linux" ${CMAKE_PREFIX_PATH})```

Next, open project in Qt Creator:

Click "Debug as 

## How to create standalone app after compilation?
...
ss 
## Unit tests
Unit tests are present in a separate project:
