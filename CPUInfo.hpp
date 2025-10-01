#pragma once
#include <string>
#include <Windows.h>
#include <intrin.h>
#include "Config.hpp"

class CPUInfo {
private:
    std::string cpu_name;
    int core_count;
    bool initialized;
    
    void initializeCPUInfo();
    
public:
    CPUInfo();
    const std::string& getCPUName() const;
    int getCoreCount() const;
    bool isValid() const;
};