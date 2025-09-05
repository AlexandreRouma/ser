#include "ser.h"
#include <stdexcept>

#ifdef _WIN32
#include <Windows.h>
#include <SetupAPI.h>
#else
#include <termios.h>
#include <filesystem>
#endif

namespace ser {
    Port::Port(Port::OSHandle port) {
        // Save the handle
        this->port = port;
    }

    void Port::close() {
        // TODO
    }

    bool Port::isOpen() {
        return port;
    }

    int Port::send(const uint8_t* data, size_t len) {
        // TODO
        return -1;
    }

    int Port::sendstr(const std::string& str) {
        // TODO
        return -1;
    }

    int Port::recv(uint8_t* data, size_t maxLen, bool forceLen, int timeout) {
        // TODO
        return -1;
    }

    int Port::recvline(std::string& str, int maxLen, int timeout) {
        // TODO
        return -1;
    }

    std::vector<std::string> list() {
        std::vector<std::string> ports;

#ifdef _WIN32
        // Open the COM port list
        HKEY serialcomm;
        LSTATUS ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_READ, &serialcomm);
        if (ret != ERROR_SUCCESS) { printf("%d\n", ret); throw std::runtime_error("Failed to access COM port list"); }

        // Iterate through each port
        for (int i = 0;; i++) {
            // Get a port
            char port[512];
            DWORD portLen = sizeof(port);
            ret = RegEnumValueA(serialcomm, i, port, &portLen, NULL, NULL, NULL, NULL);
            if (ret != ERROR_SUCCESS) { break; }

            // Get the name of the port
            char name[512];
            DWORD nameLen = sizeof(name);
            RegGetValueA(serialcomm, NULL, port, RRF_RT_ANY, NULL, name, &nameLen);

            // Add the port name to the list
            ports.push_back(name);
        }

        // Close the COM port list
        RegCloseKey(serialcomm);
#else
        // List all terminal devices
        auto sysTTY = std::filesystem::path("/sys/class/tty");
        auto ttys = std::filesystem::directory_iterator(sysTTY);
        for (const auto& tty : ttys) {
            // Skip if not a directory
            if (!tty.is_directory()) { continue; }

            // Skip if not linked with a device
            if (!std::filesystem::exists(sysTTY / tty / "device")) { continue; }

            // TODO: Do more checks to prove it's a serial port

            // Save to list
            ports.push_back(tty.path().filename());
        }
#endif

        return ports;
    }

    Port open(const std::string& name, int baudrate, int bits, int stopBits, ParityType parity) {
        return Port(0);
    }
}