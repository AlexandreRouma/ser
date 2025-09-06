#include <stdio.h>
#include "ser/ser.h"

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

        // Open the first one
        ser::Port com = ser::open("ttyACM0", 115200);//ser::open(ports[0], 115200);

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