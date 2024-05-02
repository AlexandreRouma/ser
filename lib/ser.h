#pragma once
#include <string>
#include <vector>
#include <memory>

namespace ser {
    enum Parity {
        PARITY_NONE,
        PARITY_ODD,
        PARITY_EVEN
    };

    enum {
        NO_TIMEOUT  = -1,
        NONBLOCKING = 0
    };

    struct PortInfo {
        std::string name;
        std::string path;
    };

    // class Port {
    // public:
    //     /**
    //      * Close port. The port can no longer be used after this.
    //      */
    //     void close();

    //     /**
    //      * Check if the port is open.
    //      * @return True if open, false if closed.
    //      */
    //     bool isOpen();

    //     /**
    //      * Send data on port.
    //      * @param data Data to be sent.
    //      * @param len Number of bytes to be sent.
    //      * @return Number of bytes sent.
    //      */
    //     int send(const uint8_t* data, size_t len);

    //     /**
    //      * Send string on port. Terminating NULL byte is not sent, include one in the string if you need it.
    //      * @param str String to be sent.
    //      * @return Number of bytes sent.
    //      */
    //     int sendstr(const std::string& str);

    //     /**
    //      * Receive data from port.
    //      * @param data Buffer to read the data into.
    //      * @param maxLen Maximum number of bytes to read.
    //      * @param forceLen Read the maximum number of bytes even if it requires multiple receive operations.
    //      * @param timeout Timeout in milliseconds. Use NO_TIMEOUT or NONBLOCKING here if needed.
    //      * @return Number of bytes read. 0 means timed out or closed. -1 means would block or error.
    //      */
    //     int recv(uint8_t* data, size_t maxLen, bool forceLen = false, int timeout = NO_TIMEOUT);

    //     /**
    //      * Receive line from port.
    //      * @param str String to read the data into.
    //      * @param maxLen Maximum line length allowed, 0 for no limit.
    //      * @param timeout Timeout in milliseconds.  Use NO_TIMEOUT or NONBLOCKING here if needed.
    //      * @return Length of the returned string. 0 means timed out or closed. -1 means would block or error.
    //      */
    //     int recvline(std::string& str, int maxLen = 0, int timeout = NO_TIMEOUT);

    // private:

    // };

    std::vector<std::string> list();

    // std::shared_ptr<Port> open(const std::string& name, int baudrate, int bits = 8, int stopBits = 1, Parity parity = PARITY_NONE);
}