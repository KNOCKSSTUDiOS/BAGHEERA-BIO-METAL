#include "system_diag.hpp"
#include <iostream>

SystemDiagnostics::SystemDiagnostics() : processedBytes(0) {
    startTime = std::chrono::high_resolution_clock::now();
}

void SystemDiagnostics::MarkFrameStart() {
    frameTime = std::chrono::high_resolution_clock::now();
}

void SystemDiagnostics::MarkFrameEnd(const std::string& processName) {
    auto current = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(current - frameTime).count();
    
    std::cout << "[TELEMETRY] Process [" << processName << "] execution sweep completed in: " 
              << duration << " microseconds." << std::endl;
}

void SystemDiagnostics::LogMemoryUsage(size_t allocatedBytes) {
    processedBytes += allocatedBytes;
    double megabytes = static_cast<double>(allocatedBytes) / (1024.0 * 1024.0);
    
    std::cout << "[MEMORY] Local buffer check: " << megabytes 
              << " MB locked dynamically in active heap space." << std::endl;
}
