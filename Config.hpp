#pragma once
#include <cstdint>

class Config {
public:
    static constexpr size_t MAX_PATH_LENGTH = 260;
    static constexpr float MIN_MEMORY_GB = 0.512f;
    static constexpr int MIN_CPU_CORES = 2;
    static constexpr uint32_t CPUID_EXTENDED_FEATURES = 0x80000000;
    static constexpr uint32_t CPUID_BRAND_STRING_1 = 0x80000002;
    static constexpr uint32_t CPUID_BRAND_STRING_2 = 0x80000003;
    static constexpr uint32_t CPUID_BRAND_STRING_3 = 0x80000004;
    
    struct Memory {
        static constexpr size_t BUFFER_SIZE_SMALL = 256;
        static constexpr size_t BUFFER_SIZE_MEDIUM = 1024;
        static constexpr size_t BUFFER_SIZE_LARGE = 4096;
    };
    
    struct Threading {
        static constexpr int MAX_THREADS = 64;
        static constexpr int DEFAULT_SLEEP_MS = 1000;
    };
};