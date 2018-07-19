#pragma once

#include <string>
#include <list>
#include <fstream>

using string = std::string;

static const char* defaultInputFilename = "Source.xml";  // Default filename is used when no other is provided.
const long         maxFileLength   = (1l)<<32;		 // 2^32 bytes is max file size that can be read (which is 4 294 967 296 bytes).
							 // It's introduced to prevent programm to hang up on big files.
class XMLReader
{
public:
	XMLReader();
	~XMLReader();
	
	const char* getFileString();
	const char* getDefaultFileName();
	bool readXMLFile(string _filepath = defaultInputFilename);	//Initiate file reading process.
private:
	char* fileContent_; // File content storage.
};

