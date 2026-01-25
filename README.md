# Core Gaming

An

- SDL-2
- C++ 20 
- Cross Platform

game (engine) being used heavily as a learning tool.

# Development

You will need CMake installed on the system to generate the builds.
Follow the preferred installation for your platform, checking here for the latest version: https://cmake.org/download/

If you want to interact with the GitHub repo, pulling changes or pushing branches, you'd need Git as well. 
Check here for the preferred method on your platform: https://git-scm.com/install/

You will need to install SDL-2 differently based on your platform:

- Linux: sudo apt install libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev
- macOS: brew install sdl2
- Windows: vcpkg install sdl2

After that you should be able to configure and build the game.
If make is available, then from a command line perspective, you should be able to:

```shell
cd /path/to/CoreGaming
mkdir build
cd build
ccmake ..
make -j N (where N is the number of processors you want to use)
```

Of course, this is made quite a bit easier with an IDE.
For example with Clion, just open the repo root and it will automatically configure and be ready to go.
On Windows, you will want to generate a Visual Studio project.

# Testing

I want to add lots of testing on GHA.
One rule is that any SDL inclusion should only happen in the src/platform/ directory source.
That will make all the rest of the source easy to test.
