# Building cpp projects with cmake and nix

This project is intended to serve as a template for cpp projects.
I will extend this readme throughout the work on this project and collect thoughts, goals and useful links here.
I will include some test cpp/hpp files to show how all of this works (and to test it). 

## Goals

### Structure

I think the following folder structure should work well with most projects:

```
.
+-- _app # the code of the app developed in this project
|   +-- _include
|   +-- _src
+-- _bin # binary files, content not uploaded to git
+-- _cmake # cmake related files
+-- _lib
|   +-- _<libname_1>
|       +-- _include
|   +-- _<libname_n>
|       +-- _include
+-- _nix # nix related files
+-- _test # testing related files
|   +-- _unit
|   +-- _fuzz
```

The `lib` folder should contain only libs that I have written myself for this project.
All the other libs should be managed by nix.

### CMake

I want CMake to
- [ ] build my application
- [ ] build my libs and link them correctly
- [ ] build my tests
  - [ ] unit tests
  - [ ] fuzz tests
  - [ ] maybe more
- [ ] run static analysis

### Nix

I will start working on nix when at least some CMake stuff works, but I will include a `shell.nix` file to be able to build all this in a nix-shell.
