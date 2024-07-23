#ifndef CAMERA_H
#define CAMERA_H


#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <chrono>


namespace fs = std::__fs::filesystem;


class Camera {
    private:
        // For communicating over Wi-Fi
        std::string phone_ip_port;

        // File paths
        std::string computer_folder;
        std::string computer_folder_motion;
        std::string phone_folder;

        // For motion detection
        cv::Mat frame;
        double last_mean = 0;
        double motion_threshold = 3.0;
        std::chrono::time_point<std::chrono::steady_clock> last_time = std::chrono::steady_clock::now();

    public:
        /**
         * @brief Start ADB server and connect to Android phone wirelessly over Wi-Fi
         * and clear the Android phone's saved images.
         * 
         * @param _phone_ip_port
         *  The IP address and port number for debugging over Wi-Fi on Android phone (in developer options)
         * @param _computer_folder
         *  The folder on computer containing temporary images for video
         * @param _computer_folder_motion
         *  The folder on computer containing saved images from motion detection
         * @param _phone_folder
         *  The folder on Android phone containing all saved photos
         */
        Camera(std::string _phone_ip_port, std::string _computer_folder, std::string , std::string _phone_folder);

        /**
         * @brief Open camera app.
         */
        void open_camera_app();

        /**
         * @brief Take picture in camera app and process into saved photos.
         */
        void take_picture();

        /**
         * @brief Remove all JPGs from a folder on computer.
         */
        void clear_computer_folder();
        
        /**
         * @brief Return the output of a shell command.
         * 
         * @param cmd
         *  The key to insert into the list
         * @return
         *  The most recent photo in computer folder containing temporary images for video
         */
        std::string system_output(const char* cmd);
        
        /**
         * @brief Transfer an image from Android phone to computer.
         */
        void transfer_image(bool motion);

        /**
         * @brief Display an image to computer screen.
         */
        void display_image();

        /**
         * @brief Store image when motion is detected.
         */
        void detect_motion();

        /**
         * @brief Start streaming video to computer.
         */
        void stream();

        /**
         * @brief Kill ADB server. 
         */
        ~Camera();
};

#endif