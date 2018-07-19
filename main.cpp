#include <stdio.h>
#include "XMLReader.hpp"
#include "XMLProcessor.hpp"
#include "PrimeNumberSearchEngine.hpp"
#include "XMLParcer.hpp"

int main(int argc, char **argv)
{

    XMLReader reader;
    XMLProcessor processor;
    PrimeNumberSearchEngine engine;
    XMLParcer parcer;
    bool isSuccess = true;

    // Utilize use of optional console arguments.
    // Read of input file with default of provided filename.
    if (argc > 1)
    {
        printf("Used provided input filename: %s\n", *(argv + 1));
        isSuccess = reader.readXMLFile(*(argv + 1));
    }
    else
    {
        printf("Used default input file name: %s\n", reader.getDefaultFileName());
        isSuccess = reader.readXMLFile();
    }

    printf("Start prime number search process:\n");

    if (isSuccess)
    {
        // Process received XML data. Get numeric ranges.
        processor.processXMLData(reader.getFileString());
        // Calculate prime numbers from received ranges.
        engine.findPrimeNumbers(processor.getIntervalList());
        // Parce all found prime numbers into output file with default or provided filename.
        if (argc > 2)
        {
            printf("Used provided output filename: %s\n", *(argv + 2));
            isSuccess = parcer.parcePrimes(engine.getPrimeNumbersList(), *(argv + 2));
        }
        else
        {
            printf("Used default output file name: %s\n", parcer.getDefaultFileName());
            isSuccess = parcer.parcePrimes(engine.getPrimeNumbersList());
        }
        if (isSuccess)
        {
            printf( "Process ended successfully. Results provided in %s file\n",
                    ( (argc > 2) ? *(argv + 2) : parcer.getDefaultFileName() ) );
        }
        else
        {
            printf( "Process failed. Check input file: %s\n",
                    ( (argc > 1) ? *(argv + 1) : parcer.getDefaultFileName() ) );
        }
    }
    else
    {
        isSuccess = false;
        printf("File reading failed\n");
    }

    return 0;
}
