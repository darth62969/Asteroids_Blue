# Asteroids_Blue
Was a Project From Computer Graphics (CSC315) @Mercer Univercity is now made anew for for personal and commertial reasons. 

![](https://img.shields.io/discord/289585903771451392.svg?logo=discord&style=flat)

## About:
 A rebuild of the game Asteroids. Originally built as a group project for Computer Graphics @ Mercer University, it is now a Game Platform with Mod(plugin) Support with additional cool features. Build any mode you want and play though the Game engine for an easy and quick way to learn C++ and game development.

### How to Build

#### Windows
1. install WSL and your choice of distro from the Windows 10 Store
2. in your choice of WSL distro, install make, freeglut3-dev, git, a window manager and g++
3. set up display export, and install an windows x-server (Recomends vcxsrv)
4. clone the repository in a directory you can find.
5. in the project directory (the one with the makefile) run make.
6. type ./bin/Asteroids

#### Linux
1. same as Windows except forgo 1. and 3. 

#### Your Own Libraries/Game Modes
1. write a new library or game mode
2. add all your dependencies and source files to the make file as rules
3. add your target titled "(yourmode).mode"
4. build your mode with `make "(yourmode).mode"`
5. add your "(yourmode).mode" to the "libraries.txt" file
6. launch the game, and trouble shoot any errors loading your mode.
7. rage when it segfaults, and you don't know why.

### Credits:
 * Jonathan Oakes - Me, I did the asteroid class, odds and ends, and broke it plenty of times.
 * Braeden Brettin - The guy that explained my ideas better then I could. Also fixed what I broke
 * Ted Dorfeuille - The guy that did something think collisions
 * Chris Le - Maybe this guy did collisions and Ted did tesselations?
 * Emily Herron - She did stuff. like the scoreboard and things like that. probably more odds and ends.

### Dependencies:
 * FreeGlut3 - Yes I know this is old and needs improvements.
 * g++ - For compiling
 * Linux or Windows 10 w/ WSL - Will not run on windows without WSL. 
