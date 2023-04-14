#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime> // added
#include <cstdlib>// added 

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
    // Hash entry --> do second
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        // Create array and change values to 0
        unsigned long long w[5];
        for (size_t i = 0; i < 5; ++i) {
          w[i] = 0;
        }

        unsigned long long convUnit = 0;
        unsigned long long returnUnit = 0;
        int multiUnit = 0;
        size_t i = 0;
        int stringIncrement = k.size() - 1;
        int arrayIncrement = 4; // 1 indexing
        int sixIncrement = 0;
        
        while (i < k.size()) {
          
          // multiUnit == 0 --> multiply + increment
          if (multiUnit == 0) {
            ++i;
            convUnit += letterDigitToNumber(k[stringIncrement]);
            --stringIncrement;
            ++multiUnit;
            multiUnit *= 36;
          }

          // multiUnit --> 36
          else {
            ++i;
            convUnit += (multiUnit * (letterDigitToNumber(k[stringIncrement])));
            multiUnit *= 36;
            --stringIncrement;
          }

           ++sixIncrement; 

          // # --> 6, w.append, shift
          if (sixIncrement == 6) {
            w[arrayIncrement] = convUnit;
            --arrayIncrement;
            convUnit = 0;
            multiUnit = 0;
            sixIncrement = 0;
          }

          // ++sixIncrement; --> doesn't work here ? not sure why 
         
        }


        // # < 6 --> w.append
        if (sixIncrement < 6) {
          w[arrayIncrement] = convUnit;
        }

        // Random * w[]
        for (size_t i = 0; i < 5; ++i) {
          std::cout << "w[" << i << "] = " << w[i] << std::endl;
          returnUnit += (w[i] * rValues[i]);
        }

        return returnUnit;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    // helper function conversion --> do first
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        // Upper-case to lower-case
        if (letter > 64 && letter < 91) { 
          letter += 32;
        }

        int digit = 0;
        if (letter > 96 && letter < 123) {
          digit = letter - 97;
        }
        // character number --> digit
        else if (letter > 47 && letter < 58) {
          digit = letter - 22;
        }

      return digit;

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
