# SHXX

Simple string hash without magic for C++; Wraps [xxHash](https://github.com/Cyan4973/xxHash).

32bit only for a while.

## Build

    cd SHXX
    mkdir build
    cd build
    cmake ../SHXX/ [options]
    cmake --build .
    # optionaly
    cmake --build . --target install

Where possible options are:

- `-DCMAKE_INSTALL_PREFIX=<path/to/install/to>`
- `-DSHXX_USE_BUNDLED_XXHASH=<ON|OFF>` -- Set to ON to use xxHash from git submodule via add_subdirectory, set to OFF to use external xxHash; Default is ON.

.
