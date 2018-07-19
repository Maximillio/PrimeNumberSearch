#include <gtest/gtest.h>
#include "../PrimeNumberSearchEngine.cpp"


class TestPrimeNumberSearchEngine: public ::testing::Test
{
protected:
	void SetUp()
	{
	    primeNumberSearchEngine = new PrimeNumberSearchEngine();
	}
	void TearDown()
	{
	    delete primeNumberSearchEngine;
	}
	PrimeNumberSearchEngine* primeNumberSearchEngine;
};

TEST_F(TestPrimeNumberSearchEngine, Valid_single_range)
{
    pairList input = { {1, 10} };
    longList output, example = {1, 2, 3, 5, 7};
    primeNumberSearchEngine->findPrimeNumbers(input);
    output = primeNumberSearchEngine->getPrimeNumbersList();
    ASSERT_EQ(output, example);
}

TEST_F(TestPrimeNumberSearchEngine, Disconected_ranges)
{
    pairList input = { {1, 10}, {15, 20} };
    longList output, example = {1, 2, 3, 5, 7, 17, 19};
    primeNumberSearchEngine->findPrimeNumbers(input);
    output = primeNumberSearchEngine->getPrimeNumbersList();
    ASSERT_EQ(output, example);
}
TEST_F(TestPrimeNumberSearchEngine, Interconected_ranges)
{
    pairList input = { {1, 15}, {10, 20} };
    longList output, example = {1, 2, 3, 5, 7, 11, 13, 17, 19};
    primeNumberSearchEngine->findPrimeNumbers(input);
    output = primeNumberSearchEngine->getPrimeNumbersList();
    ASSERT_EQ(output, example);
}
TEST_F(TestPrimeNumberSearchEngine, Multiple_ranges)
{
    pairList input = { {1, 15}, {30, 50}, {60, 80}, {120, 125},
                       {190, 200}, {630, 640}, {1204, 1231}, {81, 99}, };
    longList output, example = {1, 2, 3, 5,
                                7, 11, 13, 31,
                                37, 41, 43, 47,
                                61, 67, 71, 73,
                                79, 83, 89, 97,
                                191, 193, 197, 199,
                                631, 1213, 1217, 1223,
                                1229};
    primeNumberSearchEngine->findPrimeNumbers(input);
    output = primeNumberSearchEngine->getPrimeNumbersList();
    ASSERT_EQ(output, example);
}
