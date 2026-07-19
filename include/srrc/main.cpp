#include "app_core.hpp"
#include <iostream>

int main() {
    std::cout << "=== KNOCKSSTUDiOS // NATIVE APPLICATION BUILD ===" << std::endl;

    // Instantiate and launch the structural framework
    KnocksAppEngine appInstance;
    appInstance.BootApplication();
    
    // Execute real-time verification pass
    appInstance.TriggerHardwareDiagnostics();

    // Terminate engine loop safely on close
    appInstance.ShutdownApplication();

    std::cout << "=== BUILD LIFECYCLE COMPLETED CLEANLY ===" << std::endl;
    return 0;
}
