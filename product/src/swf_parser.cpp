#include "swf_parser.h"
#include <fstream>
#include <cstring>

namespace swf {

bool SWFParser::parse_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        error_ = "Failed to open file";
        return false;
    }
    
    // Read signature
    char sig[3];
    file.read(sig, 3);
    if (file.gcount() != 3) {
        error_ = "Invalid file";
        return false;
    }
    
    if (sig[0] != 'F' || sig[1] != 'W' || sig[2] != 'S') {
        if (!(sig[0] == 'C' && sig[1] == 'W' && sig[2] == 'S') &&
            !(sig[0] == 'Z' && sig[1] == 'W' && sig[2] == 'S')) {
            error_ = "Invalid SWF signature";
            return false;
        }
    }
    
    header_.signature[0] = sig[0];
    header_.signature[1] = sig[1];
    header_.signature[2] = sig[2];
    
    // Read version
    file.read(reinterpret_cast<char*>(&header_.version), 1);
    
    // Read file length
    file.read(reinterpret_cast<char*>(&header_.file_length), 4);
    
    // Skip frame info for simplicity (RECT is complex, but we need basic structure)
    header_.frame_count = 1;
    header_.frame_rate = 12.0f;
    
    // Try to read some tags
    while (file.good()) {
        uint16_t tag_header;
        file.read(reinterpret_cast<char*>(&tag_header), 2);
        if (file.gcount() != 2) break;
        
        uint16_t tag_code = tag_header >> 6;
        uint32_t tag_length = tag_header & 0x3F;
        
        if (tag_length == 0x3F) {
            file.read(reinterpret_cast<char*>(&tag_length), 4);
        }
        
        SWFTag tag;
        tag.code = tag_code;
        tag.length = tag_length;
        tags_.push_back(tag);
        
        // Skip tag data
        file.seekg(tag_length, std::ios::cur);
    }
    
    return true;
}

const SWFHeader& SWFParser::get_header() const {
    return header_;
}

const std::vector<SWFTag>& SWFParser::get_tags() const {
    return tags_;
}

std::string SWFParser::get_error() const {
    return error_;
}

} // namespace swf
