mkdir build
cd build
cmake ..
make
if [ $? = 0 ]
then
    ctest --output-on-failure
fi