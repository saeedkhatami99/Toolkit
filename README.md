# Toolkit

A comprehensive, production-ready C++ toolkit for advanced systems programming, featuring modern architecture and professional-grade implementations of low-level Windows operations.

## Overview

A sophisticated, modular system demonstrating advanced C++ and Windows API programming techniques. This toolkit provides educational and professional tools for process manipulation, memory operations, graphics overlays, and multi-threading with modern C++17 features, enhanced security, and 64-bit compatibility.

## Core Features

### Process Injection

- **Manual DLL Mapping**: Advanced PE injection with 64-bit support and relocation handling
- **LoadLibrary Injection**: Standard library injection methods
- **Shellcode Injection**: Direct assembly code execution
- **Process Hijacking**: Advanced process manipulation techniques

### Memory Operations

- **Process Attachment**: Safe handle management with RAII principles
- **Memory Read/Write**: Type-safe operations using uintptr_t addressing
- **Signature Scanning**: Optimized pattern matching with std::vector
- **Address Resolution**: Dynamic calculation with 64-bit compatibility

### Graphics Overlay

- **DirectX9 Integration**: Hardware-accelerated rendering
- **Window Hijacking**: Seamless overlay integration
- **Rendering Primitives**: Lines, rectangles, filled shapes
- **Multi-Monitor Support**: Fullscreen and windowed modes

### Threading System

- **CPU Affinity Control**: Intelligent core distribution
- **Workload Balancing**: Automatic thread pool management
- **Performance Monitoring**: Real-time thread statistics
- **Exception Safety**: Robust error handling in threaded environments

### Security Features

- **Anti-Debugging**: Continuous heartbeat monitoring for debugger detection
- **Runtime Security**: Automatic alerts and process termination on threats
- **Ethical Safeguards**: Built-in protections against malicious use

## Quick Start

### Prerequisites

- MinGW-w64 g++ compiler with C++17 support
- DirectX9 SDK (d3d9, d3dx9)
- Windows SDK for API access
- Windows 10/11 (64-bit recommended)

### Build

```powershell
# Clone and build
git clone https://github.com/saeedkhatami99/Toolkit.git
cd Toolkit

# Build manually
g++.exe -std=c++17 -fpermissive -o Toolkit.exe main.cpp SafeUtils.cpp CPUInfo.cpp injection/injection.cpp memory/memory_fn.cpp menu/menu.cpp overlay/overlay.cpp render/render.cpp simplified_fn/simplified_fn.cpp threadlib/threadlib.cpp workload/workload.cpp -luser32 -lgdi32 -ld3d9 -ld3dx9 -lshell32 -lpsapi -ldwmapi
```

### Usage

```powershell
# Run the toolkit
.\Toolkit.exe

# Interactive menu options:
# 1. Run workload testing
# 2. LoadLibrary injection
# 3. Manual PE injection
# 4. Shellcode injection
# 5. Graphics overlay hijacking
# 6. Exit
```

Do **NOT** use this toolkit for:

- **Cheating in online games** - Violates terms of service
- **Malicious software development** - Illegal and unethical
- **Unauthorized system access** - Potential legal violations
- **Bypassing security measures** - May violate applicable laws

## Learning Resources

Comprehensive examples of:

- Advanced C++ systems programming with modern standards
- Windows API integration with 64-bit compatibility
- DirectX graphics programming
- Process and memory manipulation techniques
- Multi-threaded application design
- Security-conscious programming practices

Perfect for computer science students and professional developers exploring low-level Windows programming.
