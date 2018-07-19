#include <cstdio>
#include <gtest/gtest.h>
#include "../XMLReader.hpp"
#include "../XMLParcer.cpp"

static const char* correctOutput = "<root>\n    <primes>1 2 3 5 7 11 13</primes>\n</root>\n";

class TestXMLParcer: public ::testing::Test
{
protected:
	void SetUp()
	{
	    xmlParcer = new XMLParcer();
	    xmlReader = new XMLReader();
	}
	void TearDown()
	{
	    delete xmlReader;
	    delete xmlParcer;
	}
	XMLReader* xmlReader;
	XMLParcer* xmlParcer;
};

TEST_F(TestXMLParcer, Empty_input_list)
{
    longList empty = {};

    remove("Primes.xml");
    xmlParcer->parcePrimes(empty);
    xmlReader->readXMLFile("Primes.xml");

    ASSERT_STREQ(xmlReader->getFileString(), nullptr);
}

TEST_F(TestXMLParcer, Correct_input_list)
{
    longList correct = {1, 2, 3, 5, 7, 11, 13};

    remove("Primes.xml");
    xmlParcer->parcePrimes(correct);
    xmlReader->readXMLFile("Primes.xml");

    ASSERT_STREQ(xmlReader->getFileString(), correctOutput);
}


