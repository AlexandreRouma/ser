#include "ser.h"
#include <stdexcept>

#ifdef _WIN32
#include <Windows.h>
#include <SetupAPI.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <filesystem>
#include <map>
#endif

namespace ser {
#ifndef _WIN32
    const std::map<uint32_t, speed_t> BAUDRATES = {
        { 50,      B50      },
        { 75,      B75      },
        { 110,     B110     },
        { 134,     B134     },
        { 150,     B150     },
        { 200,     B200     },
        { 300,     B300     },
        { 600,     B600     },
        { 1200,    B1200    },
        { 1800,    B1800    },
        { 2400,    B2400    },
        { 4800,    B4800    },
        { 9600,    B9600    },
        { 19200,   B19200   },
        { 38400,   B38400   },
        { 57600,   B57600   },
        { 115200,  B115200  },
        { 230400,  B230400  },
        { 460800,  B460800  },
        { 500000,  B500000  },
        { 576000,  B576000  },
        { 921600,  B921600  },
        { 1000000, B1000000 },
        { 1152000, B1152000 },
        { 1500000, B1500000 },
        { 2000000, B2000000 },
        { 2500000, B2500000 },
        { 3000000, B3000000 },
        { 3500000, B3500000 },
        { 4000000, B4000000 }
    };

    const std::map<uint8_t, int> DATA_BITS = {
        { 5, CS5 },
        { 6, CS6 },
        { 7, CS7 },
        { 8, CS8 }
    };

    const std::map<uint8_t, int> STOP_BITS = {
        { 1, 0 },
        { 2, CSTOPB }
    };

    const std::map<ParityType, int> PARITY = {
        { PARITY_TYPE_NONE, 0               },
        { PARITY_TYPE_ODD,  PARENB | PARODD },
        { PARITY_TYPE_EVEN, PARENB }
    };
#endif

    Port::Port(Port::OSHandle port) {
        // Save the handle
        this->port = port;

#ifdef _WIN32
        // TODO
#else
        // Get the termios attributes
        int err = tcgetattr(port, &attr);
        if (err) { throw std::runtime_error("Failed to get termios attributes"); }

        // Disable canonical mode to allow reading partial lines
        attr.c_lflag &= ~ICANON;
#endif
    }

    void Port::close() {
#ifdef _WIN32
        // TODO
#else
        // Close the port
        ::close(port);
#endif
    }

    bool Port::isOpen() {
        return port;
    }

    void Port::setBaudrate(uint32_t baudrate) {
#ifdef _WIN32
        // TODO
#else
        // Find the baudrate
        auto it = BAUDRATES.find(baudrate);
        if (it == BAUDRATES.end()) { throw std::runtime_error("Unsupported baudrate"); }

        // Set it in the attributes
        cfsetispeed(&attr, it->second);
        cfsetospeed(&attr, it->second);

        // Apply the attributes
        if (tcsetattr(port, TCSANOW, &attr)) { throw std::runtime_error("Failed to set the baudrate"); }
#endif
    }

    void Port::setBits(uint8_t bits) {
#ifdef _WIN32
        // TODO
#else

#endif
    }

    void Port::setParity(ParityType parity) {

    }

    void Port::setStopBits(uint8_t stopBits) {

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

    Port open(const std::string& name, uint32_t baudrate, uint8_t bits, ParityType parity, uint8_t stopBits) {
#ifdef _WIN32
        // TODO
        return Port(0);
#else
        // Open the serial port
        int fd = ::open(("/dev/" + name).c_str(), O_RDWR);
        if (fd <= 0) { throw std::runtime_error("Failed to open the serial port"); }

        // Create the port object
        Port port(fd);

        // Configure the port
        port.setBaudrate(baudrate);

        // Return the port
        return port;
#endif
    }
}