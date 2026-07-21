#ifndef SYSTEM_DIAG_HPP
#define SYSTEM_DIAG_HPP

#include <chrono>
#include <string>
#include <deque>
#include <cstdint>

class SystemDiagnostics {
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point frameTime;
    uint64_t processedBytes;
    std::deque<double> frameDurations; // microseconds per frame

public:
    SystemDiagnostics();
    ~SystemDiagnostics() = default;

    void MarkFrameStart();
    void MarkFrameEnd(const std::string& processName);
    void LogMemoryUsage(size_t allocatedBytes);

    // Returns average frame time in microseconds over the last N recorded frames.
    double GetAverageFrameTime(size_t recentN) const;

    // Returns total bytes tracked across all LogMemoryUsage calls.
    uint64_t GetTotalProcessedBytes() const;
};

#endif // SYSTEM_DIAG_HPP
