#include "swf_parser.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: swf_parser <file.swf>" << std::endl;
        return 1;
    }
    
    swf::SWFParser parser;
    if (parser.parse_file(argv[1])) {
        const auto& header = parser.get_header();
        std::cout << "SWF Version: " << (int)header.version << std::endl;
        std::cout << "File Length: " << header.file_length << std::endl;
        std::cout << "Tags found: " << parser.get_tags().size() << std::endl;
        return 0;
    } else {
        std::cout << "Error: " << parser.get_error() << std::endl;
        return 1;
    }
}
