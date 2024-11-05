//
// Created by Jonathan on 05/11/2024.
//

#ifndef BRE_UTILS_HPP
#define BRE_UTILS_HPP

#include <iostream>

class Utils {

public:
    /**
     * Converts an integer to a string.
     * WARNING: The returned string must be deleted after use.
     * @param number the integer to convert.
     * @return the string representation of the integer.
     */
    static char* toString(int number) {
        char* str = new char[10];
        sprintf(str, "%d", number);
        return str;
    }

};

#endif //BRE_UTILS_HPP
