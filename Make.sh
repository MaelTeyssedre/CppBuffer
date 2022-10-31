mkdir build
cd build
cmake ..
cmake --build . --config Release
mv libBuffer.a ..
cd ..
mkdir Include
cp sources/Buffer.hpp Include/.