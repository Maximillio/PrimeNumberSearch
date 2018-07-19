#pragma once

#include <string>
#include <fstream>
#include <list>

using longList = std::list<long>;

static const char* defaultOutputFileName = "Primes.xml"; // Default name will be used if no other is provided.

class XMLParcer
{
public:
  const char* getDefaultFileName();
  bool parcePrimes(const longList& _primeNumbers, const char*  _fileName = defaultOutputFileName);
};
