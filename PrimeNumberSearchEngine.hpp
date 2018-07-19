#pragma once

#include <list>
#include <tuple>
#include <mutex>
#include <thread>
#include <math.h>

using longList   = std::list<long>;
using threadList = std::list<std::thread>;
using pairList   = std::list<std::pair<long, long> >;

static std::mutex containerMutex_; //Mutex to synchronize access to prime numbers container

struct ThreadInput  //Structure to pass multiple input values into thread without template issues.
{
    long      low_;          // Bottom range limit
    long      high_;         // Top range limit
    longList* primeNumbers_; // Pointer to the output container

    ThreadInput(long _low, long _high, longList* _primeNumbers) // Constructor of structure to get all values.
      : low_(_low), high_(_high), primeNumbers_(_primeNumbers)  // If pointer to output container didn't be set
    {if (_primeNumbers == nullptr) throw 0;}                    // an exception will be thrown to prevent further usage
};                                                              // of incomplete structure.

class PrimeNumberSearchEngine
{
public:
    void findPrimeNumbers(pairList& _ranges); // Main function to get all prime numbers from provided ranges
    const longList& getPrimeNumbersList();
private:
    static void findPrimeNumbersinRange(ThreadInput _input); // Function to call in separate thread to get all prime numbers from one range
private:
    longList   primeNumbers_;                 // An output container for prime numbers
    threadList threadList_;                   // A container for all prime number calculating threads, to join them afterwards.
};
