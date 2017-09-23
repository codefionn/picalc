export CC=cc
export SRC=./src
export BUILD=./build

$CC $SRC/calcpi.c -o $BUILD/calcpi -lm
