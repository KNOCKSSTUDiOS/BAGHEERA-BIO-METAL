#ifndef SYSTEM_DIAG_HPP
#define SYSTEM_DIAG_HPP

#include <chrono>
#include <string>

class SystemDiagnostics {
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point frameTime;
    uint64_t processedBytes;

public:
    SystemDiagnostics();
    ~SystemDiagnostics() = default;

    void MarkFrameStart();
    void MarkFrameEnd(const std::string& processName);
    void LogMemoryUsage(size_t allocatedBytes);
};

#endif // SYSTEM_DIAG_HPP
