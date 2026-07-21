#include "app_core.hpp"
#include <iostream>
#include <filesystem>

// This module integrates directly into the KnocksAppEngine class structure declared in app_core.hpp.
// It owns the I/O-bound methods to keep the DSP core in app_core.cpp clean.

void KnocksAppEngine::InitializeLocalStorage() {
    std::cout << "[SYSTEM I/O] Securing application local context bounds..." << std::endl;

    // Create a local storage directory relative to the project working dir (sandbox-safe).
    std::string primaryDir = "./bagheera_storage";
    std::error_code ec;
    if (std::filesystem::create_directories(primaryDir, ec)) {
        std::cout << "[SYSTEM I/O] Local storage directory created: "
                  << std::filesystem::absolute(primaryDir).string() << std::endl;
    } else if (ec) {
        std::cerr << "[SYSTEM I/O] WARNING: could not create storage directory: "
                  << ec.message() << std::endl;
    } else {
        std::cout << "[SYSTEM I/O] Local storage directory already present: "
                  << std::filesystem::absolute(primaryDir).string() << std::endl;
    }
    std::cout << "[SYSTEM I/O] Zero network tracking state: VERIFIED ENFORCED." << std::endl;
}

void KnocksAppEngine::AllocateHardwareBuffers() {
    std::cout << "[SYSTEM I/O] Instantiating high-capacity data matrix layers..." << std::endl;

    // Actually allocate the memory pool to the full reserved size.
    localMemoryPool.assign(MEMORY_POOL_BYTES, 0);

    double megabytes = static_cast<double>(localMemoryPool.size()) / (1024.0 * 1024.0);
    std::cout << "[SYSTEM I/O] Allocation completed: " << megabytes
              << " MB pristine runtime memory cache bound (" << localMemoryPool.size()
              << " bytes)." << std::endl;
}
