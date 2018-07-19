#pragma once

#include <list>
#include <tuple>
#include <regex>

using string       = std::string;
using stringList   = std::list<string>;
using pairList     = std::list<std::pair<long, long>>;
using regex        = std::regex;
using smatch	   = std::smatch;

class XMLProcessor
{
public:
    pairList& getIntervalList();
    void processXMLData(const char* _inputString);  // Process input string and stores result in outputPairs_ container.
private:
    void getTagDataFromString(const string& _inputString,       // Gets all parts of string(_inputString) that matches
                              stringList&   _outputStringList,  // regex expression(_expression) and stores it in
                              const regex   _expression);       // provided string container(_outputStringList).
    void getTagDataFromStringList(const stringList& _inputStringList,  // Does the same as getTagDataFromString, but
                                  stringList&       _outputStringList, // takes all strings from input container(_inputStringList)
                                  const regex       _expression);      // and stores all matches from all strings in output container(_outputStringList).
    void getIntervalValues(const stringList& _inputStringList, // Specific function. Takes numeric range values from input container(_inputStringList)
                           pairList&	     _outputPairList); // and stores all matches in output container(_outputPairList) as pairs with type (long int)
                                                               // in format {low, high}. Has inbuilt regular expression.
private:
    pairList outputPairs_;
};
