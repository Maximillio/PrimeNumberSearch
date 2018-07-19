#include <cstdio>
#include "XMLParcer.hpp"

const char *XMLParcer::getDefaultFileName()
{
    return defaultOutputFileName;
}

bool XMLParcer::parcePrimes(const longList& _primeNumbers, const char* _fileName)
{
   bool isValid = true; // This variable will be returned as a result of parcing.
   std::fstream outputFile;

   // Is input list is empty, we do not create empty file
   if (_primeNumbers.size() == 0)
   {
       isValid = false;
       // It's required to remove possbile previously existing file with _fileName to
       // avoid confusion about programm process result.
       remove(_fileName);
       printf("Input container is empty\n");
   }
   // No need fo further actions if process failed at previous point.
   if (isValid)
   {
       try
       {
           // If there is existing file with same name as _fileName, it will be
           // completely overwrited.
           outputFile.open(_fileName, std::fstream::out | std::fstream::trunc);
       }
       catch (std::exception)
       {
           // Each error hangling block in this function does the same:
           // 1. Set result to false;
           // 2. Remove possibly existing file;
           // 3. Print info message to stdout.
           isValid = false;
           remove(_fileName);
           printf("Cannot access filename: %s\n", _fileName);
       }
       // No need fo further actions if process failed at previous point.
       if (isValid)
       {
           try
           {
               // Set basic XML tags before output of prime numbers.
               outputFile<<"<root>\n";
               outputFile<<"    <primes>";
               for (longList::const_iterator i = _primeNumbers.begin();
                    i != _primeNumbers.end();
                    ++i)
               {
                   // We output all prime numbers from input list _primeNumbers
                   // and put spaces between them.
                   outputFile<<*i;
                   // This construction prevent insert of odd space after last number.
                   if (*i != _primeNumbers.back())
                   {
                       outputFile<<" ";
                   }
               }
               // Closing XML tags
               outputFile<<"</primes>\n";
               outputFile<<"</root>\n";
               // Checking and closing file stream.
               if (outputFile.is_open())
               {
                   outputFile.close();
               }
           }
           catch (std::exception)
           {
               isValid = false;
               remove(_fileName);
               printf("An error occured while writing to the following file: %s\n", _fileName);
           }
       }
   }

   return isValid;
}

