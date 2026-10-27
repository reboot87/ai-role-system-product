# SWF 解析器设计契约

## 概述
SWF 文件解析器，支持解析文件头和标签结构。

## 模块划分
- swf_parser: 核心解析逻辑
- swf_io: 文件读取
- swf_tags: 标签解析

## 接口契约（C++）

### swf_parser.h
```cpp
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
    // Frame info simplified
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
```

## 错误处理
- 文件不存在或无法打开 -> 返回 false，设置错误信息
- 无效签名 -> 返回 false
- 解析错误 -> 返回 false

## 非功能
- 跨平台（Windows/Linux/macOS）
- 使用 C++11
- 无第三方依赖（仅标准库）
