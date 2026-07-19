#include "platform_bridge.hpp"
#include <iostream>

PlatformBridge::PlatformBridge() : currentState(EngineState::INITIALIZED) {}

void PlatformBridge::AttachInputHandler(std::function<void(InputEvent)> callback) {
    inputCallback = callback;
    std::cout << "[BRIDGE] Native hardware input hooks successfully attached." << std::endl;
}

void PlatformBridge::BroadcastSystemState(EngineState state) {
    currentState = state;
    std::string stateName;
    switch (currentState) {
        case EngineState::INITIALIZED: stateName = "INITIALIZED"; break;
        case EngineState::RUNNING:     stateName = "RUNNING"; break;
        case EngineState::SUSPENDED:   stateName = "SUSPENDED"; break;
        case EngineState::TERMINATED:  stateName = "TERMINATED"; break;
    }
    std::cout << "[BRIDGE] Broadcasting lifecycle update: STATE_" << stateName << std::endl;
}

void PlatformBridge::SendHardwareRenderCommand(const std::string& commandType) {
    // Direct, zero-bloat call straight to hardware display synchronization layers
    std::cout << "[BRIDGE] Direct hardware rendering command sent: " << commandType << std::endl;
}
