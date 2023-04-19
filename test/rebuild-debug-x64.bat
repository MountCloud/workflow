rd /S/Q build
md build
rd /S/Q bin
md bin

cd build

SET TARGET_PLATFORM=x64

cmake -DCMAKE_BUILD_TYPE=Debug^
    -A %TARGET_PLATFORM% ..^
    && cmake --build . --config Debug

cd ..