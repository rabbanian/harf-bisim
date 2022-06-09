# Harf-bisim

## Build Instructions

- First clone the submodules
``` bash
$ git submoduele init
$ git submoduele update
```

- Create a build directory (in source builds are prevented)
``` bash
$ mkdir build
```

- Generate build scripts with CMake
``` bash
$ cmake ..
```

- Build it (if you are in linux)
``` bash
$ make
```
