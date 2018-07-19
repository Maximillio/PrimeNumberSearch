#include "PrimeNumberSearchEngine.hpp"

const longList& PrimeNumberSearchEngine::getPrimeNumbersList()
{
    return primeNumbers_;
}

void PrimeNumberSearchEngine::findPrimeNumbers(pairList& _ranges)
{
    // For each range we initiate separate thread, that will calculate prime numbers and store in
    // provided container(primeNumbers_).
    for (auto p : _ranges)
    {
        threadList_.push_back( std::thread( PrimeNumberSearchEngine::findPrimeNumbersinRange,
                                            ThreadInput( p.first, p.second, &primeNumbers_) ) );
    }
    // We have to wait for each thread to end it's calculations and join the main thread.
    for (std::thread& p : threadList_)
    {
        if (p.joinable())
        {
            p.join();
        }
    }
    // We sort and remove all duplicates. Sort is used before, because unique() function works only with sorted lists.
    primeNumbers_.sort();
    primeNumbers_.unique();
}

void PrimeNumberSearchEngine::findPrimeNumbersinRange(ThreadInput _input)
{
    bool isPrime;

    // Each number gets divided by numbers from 2 to square root from number itself:
    // If the result of division always had a reminder, than the number is simple.
    for (int i = _input.low_; i < _input.high_; ++i)
    {
        isPrime = true;
        for (int j = 2; j <= std::sqrt(i); ++j)
        {
            if (!(i % j))
            {
                isPrime = false;
            }
        }
        if (isPrime)
        {
            // Due to multithreaded approach, we have to
            // syncronize access to the result container.
            containerMutex_.lock();
            _input.primeNumbers_->push_back(i);
            containerMutex_.unlock();
        }
    }
}
