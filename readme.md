# CUMT
the **C**ross-platform, **U**niversal game-**M**aking **T**ool.  
This is less of an engine, and more of a framework, as I wanted to try something new after writing multiple (terrible) ECS engines. I also felt that this kind of tool might be more suited to a game jam setting, as the process here is much more streamlined and straight-forward, with less relying on existing component types, which at times requires jumping around headers, awkward inheritance structures and whatnot.
*(Though most of these frustrations with the previous system were probably due to my poor implementations, rather than inherent design flaws.)*

## Building
### Dependencies
Firstly, you're going to need to make sure you've cloned all the submodules along with the main repo.
There are 2 ways to do this:

- pass the `--recurse-submodules` flag to the initial clone command
- `git submodule init && git submodule update` in the project root after cloning

The remaining dependencies are external libraries, namely [SDL2](https://www.libsdl.org) 
as well as its 
[*mixer*](https://github.com/libsdl-org/SDL_mixer), 
[*image*](https://github.com/libsdl-org/SDL_image) and 
[*ttf*](https://github.com/libsdl-org/SDL_ttf) subprojects.
Make sure they're in your include path before continuing.

### Build tools
The makefile was written for Bash, but I don't see why it wouldn't work on any other vaguely POSIX-compliant shell.  
It uses `clang++` as the default compiler and `x86_64-w64-mingw32-g++` for windows cross-compilation, but replacing those defaults should prove trivial.

### Shipping Executables
If you read the makefile, you might've already noticed that all those delicious external libraries you went through so much trouble to install are being linked dynamically. This means it's possible for an end user to be unable to run your program if you don't provide them with the libraries -- `dll`s for Windows and `so`s for *nix.  
Here's a convenient checklist of what to include to make sure your GOTY competitor is playable on other machines(append `.so` or `.dll` to the filenames as needed)(indentation marks dependancy)(version numbers may vary, I have no idea what I'm doing):

- `SDL2`
- `SDL2_ttf`
	- `libfreetype-6`
		- `zlib1`
- `SDL2_image`
- `SDL2_mixer`


...and that should be it. When something inevitably breaks due to my poor dependancy management, please let me know.

## ToDo:
### Features
- [ ] Keymap system
- [ ] Controller support
- [ ] Thing serialisation
- [ ] Compile-time version check
- [ ] Cached text rendering
- [ ] Render masks
### Refactors
- [ ] Replace pointer types in functions with optional return values with Maybe monads
- [x] Replace AABB methods for v2fs and Things in order to increase accuracy
