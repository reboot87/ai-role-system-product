# SWF 解析器

一个简单的 SWF（Shockwave Flash）文件解析器，用于解析 SWF 文件头和标签结构。

## 功能
- 解析 SWF 文件头（签名、版本、文件长度）
- 解析 SWF 标签列表
- 支持 FWS、CWS、ZWS 格式检测

## 使用方法
```bash
swf_parser <file.swf>
```

## 构建
```bash
cd product
mkdir build && cd build
cmake ..
make
```

## 测试
```bash
ctest
```
