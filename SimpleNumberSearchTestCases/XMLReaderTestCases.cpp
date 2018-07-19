#include <gtest/gtest.h>
#include "../XMLReader.cpp"

const char* correctFile =
    "Valid text with two\n"
    "lines of text.\n.xml";

class TestXMLReader: public ::testing::Test
{
protected:
	void SetUp()
	{
		xmlReader = new XMLReader();
	}
	void TearDown()
	{
		delete xmlReader;
	}
	XMLReader* xmlReader;
};

TEST_F(TestXMLReader, Read_non_exist_file)
{
    ASSERT_FALSE(xmlReader->readXMLFile("../SimpleNumberSearchTestCases/Fake.xml"));
    ASSERT_STREQ(xmlReader->getFileString(), nullptr);
}

TEST_F(TestXMLReader, Read_empty_file)
{
    ASSERT_FALSE(xmlReader->readXMLFile("../SimpleNumberSearchTestCases/Empty.xml"));
    ASSERT_STREQ(xmlReader->getFileString(), nullptr);
}
TEST_F(TestXMLReader, Read_correct_file)
{
    ASSERT_TRUE(xmlReader->readXMLFile("../SimpleNumberSearchTestCases/Source.xml"));
    ASSERT_STREQ(xmlReader->getFileString(), correctFile);
}
