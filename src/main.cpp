#include <stdio.h>
#include "ser.h"

int main() {
    try {
        // List available ports
        std::vector<std::string> ports = ser::list();
        if (ports.empty()) {
            printf("No ports found.\n");
            return 0;
        }
        else {
            printf("Ports Found:\n");
            for (const auto& p : ports) {
                printf(" - %s\n", p.c_str());
            }
        }

        // // Exit if no ports are available
        // if (ports.empty()) { return -1; }

        // // Open the first one
        // std::shared_ptr<ser::Port> com = ser::open(ports[0], 115200);

        // // Send a message
        // com->sendstr("Hello World!");

        // // Close the port
        // com->close();
        return 0;
    }
    catch (const std::exception& e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return -1;
    }
}