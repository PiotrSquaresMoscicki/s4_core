# compile, build, test

mkdir build
cd build
cmake ..
cmake --build . --config Release
if [ $? = 0 ]
then
    ctest --output-on-failure
fi