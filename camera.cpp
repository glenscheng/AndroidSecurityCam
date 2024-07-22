#include "camera.h"


// Establish connection between computer and Android phone
Camera::Camera(std::string ip) {
    phone_ip_port = ip;

    if (system("adb start-server") != 0) {
        std::cout << "Error starting server" << std::endl;
        exit(1);
    }
    if (system("adb devices") != 0) {
        std::cout << "Error displaying devices connected through ADB" << std::endl;
        exit(1);
    }
    if (system(("adb connect " + phone_ip_port).c_str()) != 0) {
        std::cout << "Error connecting to phone over Wi-Fi" << std::endl;
        exit(1);
    }
    // delete old photos to open up memory space
    sleep(1);
}

void Camera::open_camera_app() {
    if (system(("adb -s " + phone_ip_port + " shell am start -a android.media.action.IMAGE_CAPTURE").c_str()) != 0) {
        std::cout << "Error opening camera app" << std::endl;
        exit(1);
    }
    sleep(5);
}

void Camera::take_picture() {
    if (system(("adb -s " + phone_ip_port + " shell input keyevent CAMERA").c_str()) != 0) {
        std::cout << "Error taking picture" << std::endl;
        exit(1);
    }
    usleep(300); // give time for Android to process image taken
}

void Camera::clear_computer_folder(const std::string& folder) {
    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.path().extension() == ".jpg") {
            fs::remove(entry.path());
            break;
        }
    }
}

std::string Camera::system_output(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
        exit(1);
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void Camera::transfer_image(const std::string& from_path, const std::string& to_path) {
    std::string most_recent = system_output(("adb -s " + phone_ip_port + " shell ls -t " + from_path + " | head -n 1").c_str());
    most_recent.erase(std::remove(most_recent.begin(), most_recent.end(), '\n'), most_recent.end());
    if (system(("adb -s " + phone_ip_port + " pull /sdcard/DCIM/Camera/" + most_recent + " " + to_path).c_str()) != 0) {
        std::cout << "Error transferring image from Android phone to computer" << std::endl;
        exit(1);
    }
}

void Camera::display_image(const std::string& folder) {
    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.path().extension() == ".jpg") {
            cv::Mat img = cv::imread(entry.path().string());
            frame = img;
            if (img.empty()) {
                std::cout << "Error displaying image on computer" << std::endl;
                return;
            }
            cv::imshow("Security Camera Feed", img);
            cv::waitKey(1);
            break;
        }
    }
}

void Camera::detect_motion(const std::string& from_path, const std::string& to_path) {
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY); // Convert to grayscale
    double curr_mean = cv::mean(gray)[0]; // Calculate mean of image
    double mean_diff = std::abs(curr_mean - last_mean); // Compare means

    std::chrono::time_point<std::chrono::steady_clock> curr_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = curr_time - last_time;
    if (elapsed_seconds.count() > 60) { // Only save image every minute
        if (mean_diff > motion_threshold) {
            last_time = std::chrono::steady_clock::now();
            transfer_image(from_path, to_path);
        }
    }

    last_mean = curr_mean;
}

void Camera::stream() {
    open_camera_app();
    while (true) {
        take_picture();
        clear_computer_folder("Images/");
        transfer_image("/sdcard/DCIM/Camera/", "Images/");
        display_image("Images/");
        detect_motion("/sdcard/DCIM/Camera/", "Images/Motion/");
        if (cv::waitKey(1) == 'q') {
            cv::destroyAllWindows();
            break;
        }
    }
}

// Kill the adb server
Camera::~Camera() {
    if (system("adb kill-server") != 0) {
        std::cout << "Error killing server" << std::endl;
        exit(1);
    }
}