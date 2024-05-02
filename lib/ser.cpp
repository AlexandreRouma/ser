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
    std::vector<std::string> list() {
        std::vector<std::string> ports;

#ifdef _WIN32
        // Get the list of com ports
        HDEVINFO info = SetupDiGetClassDevsA(&GUID_CLASS_COMPORT, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
        if (info == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("Could not list serial ports");
        }

        // Iterate through devices
        int count = 0;
        for (int i = 0;; i++) {
            // Get the interface data
            SP_DEVICE_INTERFACE_DATA data = {};
            data.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
            if (!SetupDiEnumDeviceInterfaces(info, NULL, &GUID_CLASS_COMPORT, i, &data)) { break; }

            printf("Found\n");

            // Get the required size
            DWORD requiredSize;
            SetupDiGetDeviceInterfaceDetailA(info, &data, NULL, NULL, &requiredSize, NULL);

            // Get the device path
            int dataLen = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A) + requiredSize;
            PSP_DEVICE_INTERFACE_DETAIL_DATA_A detailedData = (PSP_DEVICE_INTERFACE_DETAIL_DATA_A)malloc(dataLen);
            memset(detailedData, 0, dataLen);
            detailedData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A);
            if (!SetupDiGetDeviceInterfaceDetailA(info, &data, detailedData, dataLen, NULL, NULL)) {
                printf("Last error: %d\n", GetLastError());
                continue;
            }
            std::string path(detailedData->DevicePath); // TF is this?

            // Add path to the list
            ports.push_back(std::string(detailedData->DevicePath)); // why isn't it used here?

            // Free the detailed data
            free(detailedData);
        }

        // Free the device list
        SetupDiDestroyDeviceInfoList(info);
#else
        // List all terminal devices
        auto sysTTY = std::filesystem::path("/sys/class/tty");
        auto ttys = std::filesystem::directory_iterator(sysTTY);
        for (const auto& tty : ttys) {
            // Skip if not a directory
            if (!tty.is_directory()) { continue; }

            // Skip if not linked with a device
            if (!std::filesystem::exists(sysTTY / tty / "device")) { continue; }

            // Save to list
            ports.push_back(tty.path().filename());
        }
#endif

        return ports;
    }
}