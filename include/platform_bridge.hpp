#ifndef PLATFORM_BRIDGE_HPP
#define PLATFORM_BRIDGE_HPP

#include <string>
#include <functional>
#include <vector>

enum class EngineState { INITIALIZED, RUNNING, SUSPENDED, TERMINATED };
enum class InputEvent { TOUCH_DOWN, TOUCH_UP, BACK_BUTTON };

class PlatformBridge {
private:
    EngineState currentState;
    std::function<void(InputEvent)> inputCallback;
    std::vector<std::string> commandLog;

public:
    PlatformBridge();
    ~PlatformBridge() = default;

    void AttachInputHandler(std::function<void(InputEvent)> callback);
    void BroadcastSystemState(EngineState state);
    void SendHardwareRenderCommand(const std::string& commandType);

    // Dispatch an input event to the attached handler (if any).
    void DispatchInputEvent(InputEvent event);

    // Return the number of render commands logged so far.
    size_t GetCommandCount() const;
};

#endif // PLATFORM_BRIDGE_HPP
