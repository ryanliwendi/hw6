#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        int digits[28];
        for (int i = 0; i < 28; i++)
        {
            digits[i] = 0;
        }
        for (int i = 0; i < k.size(); i++)
        {
            int pos = 28 - k.size() + i;
            digits[pos] = letterDigitToNumber(k[i]);
        }
        unsigned long long w[5];
        int start = 22, end = 27;
        int curpos = 4;
        while (end > 0)
        {
            int len = end - start + 1;
            unsigned long long num = 0;
            for (int i = 0; i < len; i++)
            {
                num *= 36;
                num += digits[start + i];
            }
            w[curpos] = num;
            curpos --;
            start -= 6;
            end -= 6;
            if (start < 0)
                start = 0;
        }
        unsigned long long ans = 0;
        for (int i = 0; i < 5; i++)
        {
            ans += w[i] * rValues[i];
        }
        return ans;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= '0' && letter <= '9')
        {
            return letter - '0' + 26;
        }
        letter = std::tolower(letter);
            return letter - 'a';
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
