#include "camera.h"


int main(int argc, char **argv) {
    if (argc != 5) {
        std::cout << "Incorrect arguments. Do: ./camera <phone_ip_address>:<phone_port> <path to computer folder for temp images> <path to computer folder for motion images> <path to phone saved images folder>" << std::endl;
        return 1;
    }

    // Parse arguments
    std::string phone_ip_port = argv[1];
    std::string computer_folder = argv[2];
    std::string computer_folder_motion = argv[3];
    std::string phone_folder = argv[4];

    Camera android(phone_ip_port, computer_folder, computer_folder_motion, phone_folder);
    android.stream();
    return 0;
}