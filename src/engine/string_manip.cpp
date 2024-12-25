#include "engine/string_manip.h"

std::wstring utf8ToUtf32(const std::string& utf8) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(utf8);
}