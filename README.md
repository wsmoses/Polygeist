## Build instructions

### Requirements 
- Working C and C++ toolchains(compiler, linker, specailly a compiled Clang toolchain except you have a machine with 32GB or more memory)
- cmake
- make or ninja

### 1. Clone Polygeist
```sh
git clone --recursive https://github.com/llvm/Polygeist
cd Polygeist
```

### 2. Install LLVM, MLIR, Clang, and Polygeist

#### Option 1: Using pre-built LLVM, MLIR, and Clang

Polygeist can be built by providing paths to a pre-built MLIR and Clang toolchain.

1. Build LLVM, MLIR, and Clang:
```sh
mkdir llvm-project/build
cd llvm-project/build
cmake -G Ninja ../llvm \
  -DLLVM_ENABLE_PROJECTS="mlir;clang" \
  -DLLVM_TARGETS_TO_BUILD="host" \
  -DLLVM_ENABLE_ASSERTIONS=ON \
  -DCMAKE_BUILD_TYPE=DEBUG
# Use Clang toolchain may save memory and faster
# -DCMAKE_C_COMPILER=clang
# -DCMAKE_CXX_COMPILER=clang++
# -DLLVM_USE_LINKER=lld
ninja
ninja check-mlir
```

To enable compilation to cuda add `-DMLIR_ENABLE_CUDA_RUNNER=1` and remove `-DLLVM_TARGETS_TO_BUILD="host"` from the cmake arguments. (You may need to specify `CUDACXX`, `CUDA_PATH`, or `CMAKE_CUDA_COMPILER`)

2. Build Polygeist:
```sh
mkdir build
cd build
cmake -G Ninja .. \
  -DMLIR_DIR=$PWD/../llvm-project/build/lib/cmake/mlir \
  -DCLANG_DIR=$PWD/../llvm-project/build/lib/cmake/clang \
  -DLLVM_TARGETS_TO_BUILD="host" \
  -DLLVM_ENABLE_ASSERTIONS=ON \
  -DCMAKE_BUILD_TYPE=DEBUG
ninja
ninja check-polygeist-opt && ninja check-cgeist
```

To enable compilation to cuda add `-DPOLYGEIST_ENABLE_CUDA=1`

#### Option 2: Using unified LLVM, MLIR, Clang, and Polygeist build

Polygeist can also be built as an external LLVM project using [LLVM_EXTERNAL_PROJECTS](https://llvm.org/docs/CMake.html#llvm-related-variables).

1. Build LLVM, MLIR, Clang, and Polygeist:
```sh
mkdir build
cd build
cmake -G Ninja ../llvm-project/llvm \
  -DLLVM_ENABLE_PROJECTS="clang;mlir" \
  -DLLVM_EXTERNAL_PROJECTS="polygeist" \
  -DLLVM_EXTERNAL_POLYGEIST_SOURCE_DIR=.. \
  -DLLVM_TARGETS_TO_BUILD="host" \
  -DLLVM_ENABLE_ASSERTIONS=ON \
  -DCMAKE_BUILD_TYPE=DEBUG
# Use Clang toolchain may save memory and faster
# -DCMAKE_C_COMPILER=clang
# -DCMAKE_CXX_COMPILER=clang++
# -DLLVM_USE_LINKER=lld
ninja
ninja check-polygeist-opt && ninja check-cgeist
```

`ninja check-polygeist-opt` runs the tests in `Polygeist/test/polygeist-opt`
`ninja check-cgeist` runs the tests in `Polygeist/tools/cgeist/Test`
