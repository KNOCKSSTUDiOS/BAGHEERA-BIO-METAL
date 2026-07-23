#ifndef APP_CORE_HPP
#define APP_CORE_HPP

#include <string>
#include <vector>
#include <atomic>

// Performance Variables
#define SYSTEM_SAMPLE_RATE 48000
#define CORE_SUB_FREQUENCY 30.0f
#define CORE_GAIN_DB 12.0f

class AppAudioProcessor {
private:
    float b0, b1, b2, a1, a2;
    float x1, x2, y1, y2;
public:
    AppAudioProcessor();
    void ConfigureHardwareFilters(float freq, float sampleRate, float gainDb);
    float ProcessAudioSample(float input);
};

class KnocksAppEngine {
private:
    std::atomic<bool> isRunning;
    std::vector<uint8_t> localMemoryPool;
    AppAudioProcessor audioProcessor;

    void InitializeLocalStorage();
    void AllocateHardwareBuffers();

public:
    KnocksAppEngine();
    ~KnocksAppEngine();
    
    void BootApplication();
    void ShutdownApplication();
    void TriggerHardwareDiagnostics();
};

#endif // APP_CORE_HPP
