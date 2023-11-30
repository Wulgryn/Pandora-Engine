#pragma once
#include <string>

namespace utils {
    
    namespace strings {
        
        /**
        * Replaces all occurrences of a substring in a string with another substring.
        * 
        * @param str The string in which to perform the replacement.
        * @param what The substring to be replaced.
        * @param to The substring to replace with.
        * @return The modified string after replacement.
        */
        std::string replace(std::string& str, std::string what, std::string to);
    }
}