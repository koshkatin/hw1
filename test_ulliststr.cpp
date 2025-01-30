#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "ulliststr.h"

// Use this file to test your ulliststr implementation before running the test suite

int main(int argc, char* argv[])
{
    ULListStr dat;

    // Push front strings "0" to "10"
    for (int i = 0; i <= 21; ++i) {
        dat.push_front(std::to_string(i));
    }

    // Print the list
    ULListStr::Item* current = dat.get_head();
    while (current != nullptr) {
        for (size_t i = current->first; i < current->last; ++i) {
            std::cout << current->val[i] << " ";
        }
        current = current->next;
        std::cout << "  ";
    }
    std::cout << std::endl;

    return 0;
}
