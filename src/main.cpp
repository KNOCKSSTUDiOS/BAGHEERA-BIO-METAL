#include "app_core.hpp"
#include "platform_bridge.hpp"
#include "system_diag.hpp"
#include <iostream>
#include <thread>
#include <chrono>

static const char* eventToString(InputEvent event) {
    switch (event) {
        case InputEvent::TOUCH_DOWN:  return "TOUCH_DOWN";
        case InputEvent::TOUCH_UP:    return "TOUCH_UP";
        case InputEvent::BACK_BUTTON: return "BACK_BUTTON";
    }
    return "UNKNOWN";
}

int main() {
    std::cout << "=== KNOCKSSTUDiOS // NATIVE APPLICATION BUILD ===" << std::endl;

    // --- Boot the engine ---
    KnocksAppEngine appInstance;
    appInstance.BootApplication();

    // --- Report loaded config values ---
    const ConfigParser& cfg = appInstance.GetConfig();
    int bugCount = cfg.GetIntValue("bugCount", 200);
    float reflectivity = cfg.GetFloatValue("reflectivity", 0.85f);
    int sampleRate = cfg.GetIntValue("sample_rate", SYSTEM_SAMPLE_RATE);
    std::cout << "[MAIN] Config -> bugCount=" << bugCount
              << " | reflectivity=" << reflectivity
              << " | sample_rate=" << sampleRate << std::endl;

    // --- Audio diagnostic (biquad filter + sine sweep) ---
    appInstance.TriggerHardwareDiagnostics();

    // --- Diagnostics: run a few frames and measure timing ---
    SystemDiagnostics diag;

    // Simulate frame work for a few frames.
    const int numFrames = 5;
    for (int i = 0; i < numFrames; ++i) {
        diag.MarkFrameStart();

        // Simulate some per-frame work (yield to scheduler for a short sleep).
        std::this_thread::sleep_for(std::chrono::microseconds(100 + i * 50));

        diag.MarkFrameEnd("RenderFrame_" + std::to_string(i));
    }

    double avgFrame = diag.GetAverageFrameTime(numFrames);
    std::cout << "[TELEMETRY] Average frame time over " << numFrames
              << " frames: " << avgFrame << " microseconds." << std::endl;

    // --- Memory usage ---
    diag.LogMemoryUsage(appInstance.GetAllocatedMemorySize());

    // --- Platform bridge: attach handler, broadcast state, dispatch events ---
    PlatformBridge bridge;
    bridge.AttachInputHandler([](InputEvent event) {
        std::cout << "[BRIDGE EVENT] Input handler received: "
                  << eventToString(event) << std::endl;
    });

    bridge.BroadcastSystemState(EngineState::RUNNING);
    bridge.SendHardwareRenderCommand("LOAD_SHADER:liquid_metal");
    bridge.SendHardwareRenderCommand("SPAWN_PARTICLES:" + std::to_string(bugCount));
    bridge.SendHardwareRenderCommand("RENDER_FRAME:wordmark_chrome");

    // Dispatch a real touch event through the attached callback.
    bridge.DispatchInputEvent(InputEvent::TOUCH_DOWN);

    // --- Clean shutdown ---
    bridge.BroadcastSystemState(EngineState::TERMINATED);
    std::cout << "[BRIDGE] Total render commands issued: "
              << bridge.GetCommandCount() << std::endl;

    appInstance.ShutdownApplication();

    std::cout << "=== BUILD LIFECYCLE COMPLETED CLEANLY ===" << std::endl;
    return 0;
}
