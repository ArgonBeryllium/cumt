# CUMT
the **C**ross-platform, **U**niversal game-**M**aking **T**ool.  
This is less of an engine, and more of a framework, as I wanted to try something new after writing multiple (terrible) ECS engines. I also felt that this kind of tool might be more suited to a game jam setting, as the process here is much more streamlined and straight-forward, with less relying on existing component types, which at times requires jumping around headers, awkward inheritance structures and whatnot.
*(Though most of these frustrations with the previous system were probably due to my poor implementations, rather than inherent design flaws.)*

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
- [ ] Replace AABB methods for v2fs and Things in order to increase accuracy
