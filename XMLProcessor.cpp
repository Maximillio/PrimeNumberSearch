#include "XMLProcessor.hpp"

void XMLProcessor::getTagDataFromString(const string& _inputString,
                                        stringList&   _outputStringList,
                                        const regex   _expression)
{
    smatch matches;

    // If string is empty, no need to process it.
    if (_inputString.length() > 0)
    {
        // Iterators to cycle through input string without changing it.
        string::const_iterator pos = _inputString.cbegin(), end = _inputString.cend();
        // Iterate through string, find matches by expression and put them into output list.
        // Insert only data between search tags. Tag itself is not present in pushed data.
        for ( ; std::regex_search(pos, end, matches, _expression); pos = matches.suffix().first)
        {
          _outputStringList.push_back(matches.str(1));
        }
    }
}
void XMLProcessor::getTagDataFromStringList(const stringList& _inputStringList,
                                            stringList&       _outputStringList,
                                            const regex       _expression)
{
    // If list is empty, no need to process it.
    if (_inputStringList.size() > 0)
    {
        // Iterate through all string in list and process them with getTagDataFromString function.
        for (auto s : _inputStringList)
        {
            getTagDataFromString(s, _outputStringList, _expression);
        }
    }
}
void XMLProcessor::getIntervalValues(const stringList& _inputStringList,
                                     pairList&         _outputPairList)
{
    smatch matches;
    static const regex expression("<low>(.+)</low>.*?<high>(.+)</high>"); // For this case, expression is stated in function,
    string::const_iterator pos, end;                                      // because it is used only for this specific case.
    long low, high;

    if (_inputStringList.size() > 0)
    {
        for (auto s : _inputStringList)
        {
            pos = s.cbegin();
            end = s.cend();
            for ( ; std::regex_search(pos, end, matches, expression); pos = matches.suffix().first)
            {
                //Cycle through all string inside _inputStringList (<interval> tag data) and write to valid ranges to outputPairs_
                try
                {
                    low  = stol(matches.str(1));  // If one of values is not a number
                    high = stol(matches.str(2));  // we handle invalid argument error
                                                  // and skip this pair.
                    if (low > high ? false : true)
                    {
                        _outputPairList.push_back( std::make_pair(low, high) );
                    }
                }
                // We have nothing to do in case of an exception.
                catch (std::invalid_argument) {}
            }
        }
      }
}

pairList& XMLProcessor::getIntervalList()
{
    return outputPairs_;
}

void XMLProcessor::processXMLData(const char* _inputString)
{
    string processable(_inputString);
    // Nested and intersepting tags are not handled. Such structure of XML file may cause data loss.
    regex regReplace ("[\r]?\n");                         // Expression for removing all newline and return charachters.
    regex regRoot("<root>(.+?)</root>");                  // Expression to get all data between <root> tag.
    regex regIntervals("<intervals>(.+?)</intervals>");   // Expression to get all data between <intervals> tag.
    regex regInterval("<interval>(.+?)</interval>");      // Expression to get all data between <interval> tag.

    stringList root;                                      // Container for data between <root> tag.
    stringList intervals;                                 // Container for data between <intervals> tag.
    stringList interval;                                  // Container for data between <interval> tag.

    outputPairs_.clear();                                       // Clear output list to avoid interference
    processable = regex_replace(processable, regReplace, "");   // Removing all newline and return charachters.

    getTagDataFromString(processable, root, regRoot);           // Get <root> data in initial input string.
    getTagDataFromStringList(root, intervals, regIntervals);    // Get <intervals> data in all <root> data string found on previous step.
    getTagDataFromStringList(intervals, interval, regInterval); // Get <interval> data in all <intervals> data string found on previous step.
    getIntervalValues(interval, outputPairs_);                  // Get final values from between <low> and <high> tags inside <interval> data strings.
}
