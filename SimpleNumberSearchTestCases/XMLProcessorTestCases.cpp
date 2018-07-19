#include <gtest/gtest.h>
#include "../XMLProcessor.cpp"

const char* correctString = "<root>\n"
			    "<intervals>\n"
			    "<interval>\n"
			    "<low>100</low>\n"
			    "<high>500</high>/n"
			    "</interval>\n"
			    "</intervals>\n"
			    "</root>\n";
const char* nonNumberIntervalString = "<root>\n"
				      "<intervals>\n"
				      "<interval>\n"
				      "<low>a</low>\n"
				      "<high>%</high>/n"
				      "</interval>\n"
				      "</intervals>\n"
				      "</root>\n";
const char* doubleRootString =  "<root>\n"
				"<intervals>\n"
				"<interval>\n"
				"<low>100</low>\n"
				"<high>500</high>/n"
				"</interval>\n"
				"</intervals>\n"
				"</root>\n"
				"<root>\n"
				"<intervals>\n"
				"<interval>\n"
				"<low>200</low>\n"
				"<high>400</high>/n"
				"</interval>\n"
				"</intervals>\n"
				"</root>\n";
const char* incompleteString = "<root>\n"
			       "<intervals>\n"
			       "<interval>\n"
			       "<low>100</low>\n"
			       "<high>500</high>/n"
			       "</interval>\n"
			       "</intervals>\n";

class TestXMLProcessor: public ::testing::Test
{
protected:
	void SetUp()
	{
	    xmlProcessor = new XMLProcessor();
	}
	void TearDown()
	{
	    delete xmlProcessor;
	}
	XMLProcessor* xmlProcessor;
};

TEST_F(TestXMLProcessor, Process_correct_string)
{
    pairList example, result;
    example.push_back(std::make_pair(100l,500l));
    xmlProcessor->processXMLData(correctString);
    result = xmlProcessor->getIntervalList();
    ASSERT_EQ(result, example);
}
TEST_F(TestXMLProcessor, Process_non_number_interval_string)
{
    pairList example, result;
    xmlProcessor->processXMLData(nonNumberIntervalString);
    result = xmlProcessor->getIntervalList();
    ASSERT_EQ(result, example);
}
TEST_F(TestXMLProcessor, Process_double_root_string)
{
    pairList example, result;
    example.push_back(std::make_pair(100l,500l));
    example.push_back(std::make_pair(200l,400l));
    xmlProcessor->processXMLData(doubleRootString);
    result = xmlProcessor->getIntervalList();
    ASSERT_EQ(result, example);
}
TEST_F(TestXMLProcessor, Process_incomplete_string)
{
    pairList example, result;
    xmlProcessor->processXMLData(incompleteString);
    result = xmlProcessor->getIntervalList();
    ASSERT_EQ(result, example);
}

