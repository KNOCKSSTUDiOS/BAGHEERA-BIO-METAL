#ifndef PLATFORM_BRIDGE_HPP
#define PLATFORM_BRIDGE_HPP

#include <string>
#include <functional>

enum class EngineState { INITIALIZED, RUNNING, SUSPENDED, TERMINATED };
enum class InputEvent { TOUCH_DOWN, TOUCH_UP, BACK_BUTTON };

class PlatformBridge {
private:
    EngineState currentState;
    std::function<void(InputEvent)> inputCallback;

public:
    PlatformBridge();
    ~PlatformBridge() = default;

    void AttachInputHandler(std::function<void(InputEvent)> callback);
    void BroadcastSystemState(EngineState state);
    void SendHardwareRenderCommand(const std::string& commandType);
};

#endif // PLATFORM_BRIDGE_HPP
