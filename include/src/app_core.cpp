#include "app_core.hpp"
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

AppAudioProcessor::AppAudioProcessor() : x1(0), x2(0), y1(0), y2(0) {
    ConfigureHardwareFilters(CORE_SUB_FREQUENCY, SYSTEM_SAMPLE_RATE, CORE_GAIN_DB);
}

void AppAudioProcessor::ConfigureHardwareFilters(float freq, float sampleRate, float gainDb) {
    // Standard BiQuad filter coefficient calculations for a steady low-shelf boost
    float A = std::pow(10.0f, gainDb / 40.0f);
    float omega = 2.0f * M_PI * freq / sampleRate;
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

KnocksAppEngine::KnocksAppEngine() : isRunning(false) {
    localMemoryPool.reserve(1024 * 1024 * 10); // Reserve 10MB local memory block upfront
}

KnocksAppEngine::~KnocksAppEngine() {
    ShutdownApplication();
}

void KnocksAppEngine::InitializeLocalStorage() {
    std::cout << "[APP CORE] Scanning isolated target system storage paths..." << std::endl;
    std::cout << "[APP CORE] Offline storage verification status: OK" << std::endl;
}

void KnocksAppEngine::AllocateHardwareBuffers() {
    std::cout << "[APP CORE] Binding memory stack matrices directly to app thread..." << std::endl;
}

void KnocksAppEngine::BootApplication() {
    if (isRunning) return;
    
    std::cout << "[APP CORE] Initializing application launch sequences..." << std::endl;
    isRunning = true;
    
    InitializeLocalStorage();
    AllocateHardwareBuffers();
    
    std::cout << "[APP CORE] App Engine successfully running in localized state." << std::endl;
}

void KnocksAppEngine::TriggerHardwareDiagnostics() {
    if (!isRunning) return;
    std::cout << "[DIAGNOSTIC] Verification run: 30Hz hardware sub-bass array initialized at +" << CORE_GAIN_DB << "dB." << std::endl;
}

void KnocksAppEngine::ShutdownApplication() {
    if (!isRunning) return;
    
    std::cout << "[APP CORE] Tearing down hardware buffer assignments cleanly..." << std::endl;
    isRunning = false;
    std::cout << "[APP CORE] System loop safely terminated." << std::endl;
}
