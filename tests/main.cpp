#include <iostream>
#include <unittest++/UnitTest++.h>

int main()
{
    std::cout << "Hi, tests!" << std::endl;
    return UnitTest::RunAllTests();
}
