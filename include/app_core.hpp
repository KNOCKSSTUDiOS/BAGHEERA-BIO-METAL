#ifndef APP_CORE_HPP
#define APP_CORE_HPP

#include <string>
#include <vector>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include "config_parser.hpp"

// Performance Variables
#define SYSTEM_SAMPLE_RATE 48000
#define CORE_SUB_FREQUENCY 30.0f
#define CORE_GAIN_DB 12.0f
#define MEMORY_POOL_BYTES (10 * 1024 * 1024) // 10MB

struct AudioLevelReport {
    float rms;
    float peak;
    size_t sampleCount;
};

class AppAudioProcessor {
private:
    float b0, b1, b2, a1, a2;
    float x1, x2, y1, y2;

public:
    AppAudioProcessor();
    void ConfigureHardwareFilters(float freq, float sampleRate, float gainDb);
    float ProcessAudioSample(float input);
    AudioLevelReport ProcessAudioBuffer(const float* samples, size_t count);
};

class KnocksAppEngine {
private:
    std::atomic<bool> isRunning;
    std::vector<uint8_t> localMemoryPool;
    AppAudioProcessor audioProcessor;
    ConfigParser config;

    void InitializeLocalStorage();
    void AllocateHardwareBuffers();

public:
    KnocksAppEngine();
    ~KnocksAppEngine();

    void BootApplication();
    void ShutdownApplication();
    void TriggerHardwareDiagnostics();

    const ConfigParser& GetConfig() const;
    size_t GetAllocatedMemorySize() const;
};

#endif // APP_CORE_HPP
