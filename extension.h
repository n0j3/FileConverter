#ifndef EXTENSION_H
#define EXTENSION_H

#include <string>
#include <unordered_map>

enum class Extension {
    STEP,
    STL,
    INVALID // Added INVALID as a default return value for unsupported extensions
};

inline const std::unordered_map<Extension, std::string> extensionToStringMap = {
    { Extension::STEP, "step" },
    { Extension::STL, "stl" }
};

inline const std::unordered_map<std::string, Extension> stringToExtensionMap = {
    { "step", Extension::STEP },
    { "stl", Extension::STL },
    { "stp", Extension::STEP }
};

inline std::string toString(Extension extension) {
    return extensionToStringMap.at(extension);
}

inline Extension toExtension(const std::string& str) {
    auto it = stringToExtensionMap.find(str);
    if (it != stringToExtensionMap.end()) {
        return it->second;
    }
    return Extension::INVALID; // Return INVALID if the string does not match any extension
}

#endif // EXTENSION_H
