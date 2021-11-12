#pragma once

struct FormatKey {
    int id = -1;
    bool option1 = false;
    bool option2 = false;
};

inline bool operator< (const FormatKey& lhs, const FormatKey& rhs) {
    if (lhs.id < rhs.id) return true;
    if (lhs.id == rhs.id) {
        if (lhs.option1 < rhs.option1) return true;
        if (lhs.option1 == rhs.option1 && lhs.option1 < rhs.option1) return true;
    }
    return false;
}
