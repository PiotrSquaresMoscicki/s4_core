#include <iostream>

#include <core/collections/tuple.hpp>

using namespace core::collections;

int main() {
    std::cout << "Hello World!" << std::endl;

    Tuple a = Tuple{1, "ASDAS", 3.2, 4.5f};
    Tuple b = Tuple(1, "ASDAS", 3.2, 4.5f);
    Tuple c(1, "ASDAS", 3.2, 4.5f);
    Tuple d{1, "ASDAS", 3.2, 4.5f};

    std::cout << a.has<int>() << std::endl;
    std::cout << a.at<1>() << std::endl;
    std::cout << a.get<float>() << std::endl;
}