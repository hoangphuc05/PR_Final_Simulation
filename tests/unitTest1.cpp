#include "Hospital.h"
#include "gtest/gtest.h"

using namespace std;



//TEST(TestCase, FirstCase) {
    //ASSERT_EQ(0, read_int("My Prompt: ", -3, 3));
//}

int main (int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}