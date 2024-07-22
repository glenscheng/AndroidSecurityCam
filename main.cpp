#include "camera.h"


int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Incorrect arguments. Do: ./camera <phone_ip_address>:<phone_port> (for wireless connection)" << std::endl;
        return 1;
    }

    std::string phone_ip = argv[1];
    Camera android(phone_ip);
    android.stream();
    return 0;
}