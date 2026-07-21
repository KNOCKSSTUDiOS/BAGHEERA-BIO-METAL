#include "platform_bridge.hpp"
#include <iostream>

PlatformBridge::PlatformBridge() : currentState(EngineState::INITIALIZED) {}

void PlatformBridge::AttachInputHandler(std::function<void(InputEvent)> callback) {
    inputCallback = std::move(callback);
    std::cout << "[BRIDGE] Native hardware input hooks successfully attached." << std::endl;
}

static const char* stateName(EngineState s) {
    switch (s) {
        case EngineState::INITIALIZED: return "INITIALIZED";
        case EngineState::RUNNING:     return "RUNNING";
        case EngineState::SUSPENDED:   return "SUSPENDED";
        case EngineState::TERMINATED:  return "TERMINATED";
    }
    return "UNKNOWN";
}

void PlatformBridge::BroadcastSystemState(EngineState state) {
    currentState = state;
    std::cout << "[BRIDGE] Broadcasting lifecycle update: STATE_"
              << stateName(state) << std::endl;

    // When transitioning to TERMINATED, synthesize a BACK_BUTTON event
    // to notify any attached handler that the session is ending.
    if (state == EngineState::TERMINATED && inputCallback) {
        std::cout << "[BRIDGE] Dispatching BACK_BUTTON to input handler on TERMINATED." << std::endl;
        inputCallback(InputEvent::BACK_BUTTON);
    }
}

void PlatformBridge::SendHardwareRenderCommand(const std::string& commandType) {
    // Structured log entry so downstream systems can parse it.
    commandLog.push_back(commandType);
    std::cout << "[BRIDGE] render_cmd | seq=" << commandLog.size()
              << " | cmd=" << commandType << std::endl;
}

void PlatformBridge::DispatchInputEvent(InputEvent event) {
    if (inputCallback) {
        inputCallback(event);
    } else {
        std::cout << "[BRIDGE] No input handler attached; event dropped." << std::endl;
    }
}

size_t PlatformBridge::GetCommandCount() const {
    return commandLog.size();
}
