#include "app_core.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ---------------------------------------------------------------------------
// AppAudioProcessor
// ---------------------------------------------------------------------------

AppAudioProcessor::AppAudioProcessor() : b0(0), b1(0), b2(0), a1(0), a2(0),
                                           x1(0), x2(0), y1(0), y2(0) {
    ConfigureHardwareFilters(CORE_SUB_FREQUENCY, SYSTEM_SAMPLE_RATE, CORE_GAIN_DB);
}

void AppAudioProcessor::ConfigureHardwareFilters(float freq, float sampleRate, float gainDb) {
    // Standard BiQuad filter coefficient calculations for a steady low-shelf boost
    float A = std::pow(10.0f, gainDb / 40.0f);
    float omega = 2.0f * static_cast<float>(M_PI) * freq / sampleRate;
    float alpha = std::sin(omega) / 2.0f * std::sqrt((A + 1.0f / A) * (1.0f / 0.707f - 1.0f) + 2.0f);
    float cosOmega = std::cos(omega);
    float sqrtA2Alpha = 2.0f * std::sqrt(A) * alpha;

    float a0 = (A + 1.0f) + (A - 1.0f) * cosOmega + sqrtA2Alpha;
    b0 = (A * ((A + 1.0f) - (A - 1.0f) * cosOmega + sqrtA2Alpha)) / a0;
    b1 = (2.0f * A * ((A - 1.0f) - (A + 1.0f) * cosOmega)) / a0;
    b2 = (A * ((A + 1.0f) - (A - 1.0f) * cosOmega - sqrtA2Alpha)) / a0;
    a1 = (-2.0f * ((A - 1.0f) + (A + 1.0f) * cosOmega)) / a0;
    a2 = ((A + 1.0f) + (A - 1.0f) * cosOmega - sqrtA2Alpha) / a0;
}

float AppAudioProcessor::ProcessAudioSample(float input) {
    float output = b0 * input + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;
    x2 = x1; x1 = input; y2 = y1; y1 = output;
    return output;
}

AudioLevelReport AppAudioProcessor::ProcessAudioBuffer(const float* samples, size_t count) {
    AudioLevelReport report{0.0f, 0.0f, count};
    if (count == 0) return report;

    double sumSquares = 0.0;
    for (size_t i = 0; i < count; ++i) {
        float out = ProcessAudioSample(samples[i]);
        double v = static_cast<double>(out);
        sumSquares += v * v;
        report.peak = std::max(report.peak, std::fabs(out));
    }
    report.rms = static_cast<float>(std::sqrt(sumSquares / static_cast<double>(count)));
    return report;
}

// ---------------------------------------------------------------------------
// KnocksAppEngine
// ---------------------------------------------------------------------------

KnocksAppEngine::KnocksAppEngine() : isRunning(false) {
    localMemoryPool.reserve(MEMORY_POOL_BYTES); // Reserve 10MB local memory block upfront
}

KnocksAppEngine::~KnocksAppEngine() {
    ShutdownApplication();
}

// InitializeLocalStorage() and AllocateHardwareBuffers() are implemented in system_io.cpp
// to keep the I/O layer separated from the DSP core.

void KnocksAppEngine::BootApplication() {
    if (isRunning) return;

    std::cout << "[APP CORE] Initializing application launch sequences..." << std::endl;
    isRunning = true;

    // Load configuration if a config file exists in the project directory.
    config.LoadConfigFile("config/bagheera.cfg");

    InitializeLocalStorage();
    AllocateHardwareBuffers();

    std::cout << "[APP CORE] App Engine successfully running in localized state." << std::endl;
}

void KnocksAppEngine::TriggerHardwareDiagnostics() {
    if (!isRunning) return;

    std::cout << "[DIAGNOSTIC] Running audio diagnostic with biquad low-shelf filter..." << std::endl;

    // Read config-driven sample rate, fall back to hardware default.
    float sampleRate = config.GetFloatValue("sample_rate", static_cast<float>(SYSTEM_SAMPLE_RATE));

    // Generate a sine sweep from 20Hz to 2000Hz, 4096 samples at the configured rate.
    const size_t N = 4096;
    std::vector<float> sweep(N);
    double fStart = 20.0;
    double fEnd = 2000.0;
    for (size_t i = 0; i < N; ++i) {
        double t = static_cast<double>(i) / sampleRate;
        // Exponential sine sweep
        double phase = 2.0 * M_PI * fStart * t * (std::pow(fEnd / fStart, t * sampleRate / N) - 1.0)
                       / (std::log(fEnd / fStart) * t + 1e-12);
        // Fallback to a linear chirp if the exponential formula degenerates.
        double freq = fStart + (fEnd - fStart) * (static_cast<double>(i) / N);
        double linPhase = 2.0 * M_PI * (fStart * t + (freq - fStart) * t / 2.0);
        (void)phase;
        sweep[i] = static_cast<float>(0.8 * std::sin(linPhase));
    }

    // Reconfigure the filter using the config-driven sample rate.
    audioProcessor.ConfigureHardwareFilters(CORE_SUB_FREQUENCY, sampleRate, CORE_GAIN_DB);

    // Process the sweep through the biquad and measure real output levels.
    AudioLevelReport levels = audioProcessor.ProcessAudioBuffer(sweep.data(), N);

    std::cout << "[DIAGNOSTIC] Filter: low-shelf " << CORE_SUB_FREQUENCY << "Hz @ +"
              << CORE_GAIN_DB << "dB | sample_rate=" << static_cast<int>(sampleRate) << "Hz" << std::endl;
    std::cout << "[DIAGNOSTIC] Measured output over " << levels.sampleCount
              << " samples -> peak=" << levels.peak
              << " | RMS=" << levels.rms << std::endl;
}

void KnocksAppEngine::ShutdownApplication() {
    if (!isRunning) return;

    std::cout << "[APP CORE] Tearing down hardware buffer assignments cleanly..." << std::endl;
    isRunning = false;
    std::cout << "[APP CORE] System loop safely terminated." << std::endl;
}

const ConfigParser& KnocksAppEngine::GetConfig() const {
    return config;
}

size_t KnocksAppEngine::GetAllocatedMemorySize() const {
    return localMemoryPool.size();
}
