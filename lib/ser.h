#pragma once
#include <string>
#include <vector>
#include <memory>
#ifdef _WIN32
#include <Windows.h>
#endif

namespace ser {
    enum ParityType {
        PARITY_TYPE_NONE,
        PARITY_TYPE_ODD,
        PARITY_TYPE_EVEN
    };

    enum {
        NO_TIMEOUT  = -1,
        NONBLOCKING = 0
    };

    /**
     * Object representing an open serial port.
     * This class is thread-safe.
    */
    class Port {
    private:
#ifdef _WIN32
        using OSHandle = HANDLE;
#else
        using OSHandle = int;
#endif
    public:
        Port(OSHandle port);

        /**
         * Close port. The port can no longer be used after this.
         */
        void close();

        /**
         * Check if the port is open.
         * @return True if open, false if closed.
         */
        bool isOpen();

        /**
         * Send data on port.
         * @param data Data to be sent.
         * @param len Number of bytes to be sent.
         * @return Number of bytes sent.
         */
        int send(const uint8_t* data, size_t len);

        /**
         * Send string on port. Terminating NULL byte is not sent, include one in the string if you need it.
         * @param str String to be sent.
         * @return Number of bytes sent.
         */
        int sendstr(const std::string& str);

        /**
         * Receive data from port.
         * @param data Buffer to read the data into.
         * @param maxLen Maximum number of bytes to read.
         * @param forceLen Read the maximum number of bytes even if it requires multiple receive operations.
         * @param timeout Timeout in milliseconds. Use NO_TIMEOUT or NONBLOCKING here if needed.
         * @return Number of bytes read. 0 means timed out or closed. -1 means would block or error.
         */
        int recv(uint8_t* data, size_t maxLen, bool forceLen = false, int timeout = NO_TIMEOUT);

        /**
         * Receive line from port.
         * @param str String to read the data into.
         * @param maxLen Maximum line length allowed, 0 for no limit.
         * @param timeout Timeout in milliseconds.  Use NO_TIMEOUT or NONBLOCKING here if needed.
         * @return Length of the returned string. 0 means timed out or closed. -1 means would block or error.
         */
        int recvline(std::string& str, int maxLen = 0, int timeout = NO_TIMEOUT);

    private:
        OSHandle port;
    };

    /**
     * List serial ports.
     * @return Names of the serial ports present on the system.
    */
    std::vector<std::string> list();

    /**
     * Open a serial port.
     * @param name Name of the serial port to open.
     * @param baudrate Baud rate in Hz.
     * @param bits Number of bits per character.
     * @param stopBits Number of stop bits.
     * @param parity Parity type.
    */
    Port open(const std::string& name, int baudrate = 9600, int bits = 8, int stopBits = 1, ParityType parity = PARITY_TYPE_NONE);
}