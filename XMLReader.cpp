#include "XMLReader.hpp"

XMLReader::XMLReader() : fileContent_(nullptr) {} // Initiate file info container with nullptr to prevent confusion.

XMLReader::~XMLReader()
{
    if (fileContent_)
    {
        delete[] fileContent_;
    }
}

bool XMLReader::readXMLFile(string _filepath)
{
	std::fstream inputFile;
	// Result value will be retruned to indicate if file reading process went fine or not.
	bool result = false;
	// Incapsulate file read process ing try-catch block to avoid crashes from incorrect reading.
	try
	{
	    inputFile.open(_filepath, std::ifstream::in);
	    if ( inputFile.is_open() )
	    {
		inputFile.seekg (0, inputFile.end); // Getting file length. We put file pointer
		long length = inputFile.tellg();    // to the end of file and measue distance
		inputFile.seekg (0, inputFile.beg); // between the beggining and the end.

		//Check if file content has some data already. If it has - we delete it to prevent memory leak.
		if (fileContent_)
		{
		    delete[] fileContent_;
		}
		//Check is file is not empty or bigger than maxFileLength.
		if ( (length != 0) && (length <= maxFileLength) )
		{
		    fileContent_ = new char[length];
		    inputFile.read(fileContent_, length);
		    result = true;
		    inputFile.close();
		}
	    }
	}
	// If we got an exception, that file reading process was unsuccessful.
	catch (std::exception)
	{
	    result = false;
	    // If we allocated memory for file string, we have to free it.
	    if (fileContent_)
	    {
		delete[] fileContent_;
	    }
	    //If file stream is still open, we have to close it.
	    if (inputFile.is_open())
	    {
		inputFile.close();
	    }
	}
	// Output to console if reading failed.
	if (!result)
	{
	   printf("Unable to open file\n");
	}

	return result;
}
const char* XMLReader::getFileString()
{
    return fileContent_;
}

const char* XMLReader::getDefaultFileName()
{
    return defaultInputFilename;
}
