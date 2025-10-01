#include "CPUInfo.hpp"
#include <cstring>

CPUInfo::CPUInfo() : initialized(false), core_count(0) {
    initializeCPUInfo();
}

void CPUInfo::initializeCPUInfo() {
    try {
        int cpu_info[4] = {-1};
        char cpu_string[0x40];
        __cpuid(cpu_info, Config::CPUID_EXTENDED_FEATURES);
        unsigned int ex_ids = cpu_info[0];
        
        memset(cpu_string, 0, sizeof(cpu_string));
        
        for (int i = Config::CPUID_EXTENDED_FEATURES; i <= ex_ids; ++i) {
            __cpuid(cpu_info, i);
            if (i == Config::CPUID_BRAND_STRING_1)
                memcpy(cpu_string, cpu_info, sizeof(cpu_info));
            else if (i == Config::CPUID_BRAND_STRING_2)
                memcpy(cpu_string + 16, cpu_info, sizeof(cpu_info));
            else if (i == Config::CPUID_BRAND_STRING_3)
                memcpy(cpu_string + 32, cpu_info, sizeof(cpu_info));
        }
        
        cpu_name = cpu_string;
        
        SYSTEM_INFO system_info;
        GetSystemInfo(&system_info);
        core_count = system_info.dwNumberOfProcessors;
        
        initialized = true;
    } catch (...) {
        initialized = false;
        cpu_name = "Unknown CPU";
        core_count = 0;
    }
}

const std::string& CPUInfo::getCPUName() const {
    return cpu_name;
}

int CPUInfo::getCoreCount() const {
    return core_count;
}

bool CPUInfo::isValid() const {
    return initialized && core_count >= Config::MIN_CPU_CORES;
}