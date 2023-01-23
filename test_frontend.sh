cd DoIt/frontend/Test;

cmake -B ./build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON;

cmake --build build;

cd build && ctest;
