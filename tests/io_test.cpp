#include <iostream>
#include <vector>
#include <memory>
#include <unittest++/UnitTest++.h>

#include "utils/io.h"

TEST(matrix_of_csv_clean) {
    std::stringstream csvcontent;
    csvcontent << "1,2,3\n3,4.2,5\n8,6,2.718";
    auto M = matrix_of_csv<double>(csvcontent);
    CHECK(M(0, 0)==1);
    CHECK(M(1, 1)==4.2);
    CHECK(M(2, 2)==2.718);
}

TEST(matrix_of_csv_with_space) {
    std::stringstream csvcontent;
    csvcontent << "1,2, 3   \n3, 4.2,5\n8,6,  2.718";
    auto M = matrix_of_csv<double>(csvcontent);
    CHECK(M(0, 0)==1);
    CHECK(M(1, 1)==4.2);
    CHECK(M(2, 2)==2.718);
}
