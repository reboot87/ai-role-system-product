#ifndef SWF_PARSER_H
#define SWF_PARSER_H

#include <string>
#include <vector>
#include <cstdint>

namespace swf {

struct SWFHeader {
    char signature[3];
    uint8_t version;
    uint32_t file_length;
    uint32_t frame_count;
    float frame_rate;
};

struct SWFTag {
    uint16_t code;
    uint32_t length;
};

class SWFParser {
public:
    SWFParser() = default;
    bool parse_file(const std::string& filename);
    const SWFHeader& get_header() const;
    const std::vector<SWFTag>& get_tags() const;
    std::string get_error() const;
    
private:
    SWFHeader header_;
    std::vector<SWFTag> tags_;
    std::string error_;
};

} // namespace swf

#endif
