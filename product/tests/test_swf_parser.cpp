#include "swf_parser.h"
#include <iostream>

int main() {
    swf::SWFParser parser;
    // Test with non-existent file
    if (parser.parse_file("nonexistent.swf")) {
        std::cout << "FAIL: should fail on missing file" << std::endl;
        return 1;
    }
    std::cout << "PASS: missing file test" << std::endl;
    return 0;
}
