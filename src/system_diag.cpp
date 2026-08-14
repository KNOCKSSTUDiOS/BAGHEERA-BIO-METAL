#include "system_diag.hpp"
#include <iostream>
#include <algorithm>

SystemDiagnostics::SystemDiagnostics() : processedBytes(0) {
    startTime = std::chrono::high_resolution_clock::now();
}

void SystemDiagnostics::MarkFrameStart() {
    frameTime = std::chrono::high_resolution_clock::now();
}

void SystemDiagnostics::MarkFrameEnd(const std::string& processName) {
    auto current = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(current - frameTime).count();

    // Record this frame's duration for rolling-average computation.
    frameDurations.push_back(static_cast<double>(duration));
    // Cap the history to the last 1000 frames to bound memory.
    if (frameDurations.size() > 1000) {
        frameDurations.pop_front();
    }

    std::cout << "[TELEMETRY] Process [" << processName << "] execution sweep completed in: "
              << duration << " microseconds." << std::endl;
}

void SystemDiagnostics::LogMemoryUsage(size_t allocatedBytes) {
    processedBytes += allocatedBytes;
    double megabytes = static_cast<double>(allocatedBytes) / (1024.0 * 1024.0);

    double totalMB = static_cast<double>(processedBytes) / (1024.0 * 1024.0);
    std::cout << "[MEMORY] Buffer allocated: " << megabytes
              << " MB | running total tracked: " << totalMB << " MB ("
              << processedBytes << " bytes)." << std::endl;
}

double SystemDiagnostics::GetAverageFrameTime(size_t recentN) const {
    if (frameDurations.empty()) return 0.0;
    size_t count = std::min(recentN, frameDurations.size());
    double sum = 0.0;
    auto it = frameDurations.end() - static_cast<std::deque<double>::difference_type>(count);
    for (size_t i = 0; i < count; ++i) {
        sum += *it++;
    }
    return sum / static_cast<double>(count);
}

uint64_t SystemDiagnostics::GetTotalProcessedBytes() const {
    return processedBytes;
}
