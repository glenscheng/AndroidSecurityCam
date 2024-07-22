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


namespace fs = std::__fs::filesystem;


class Camera {
    private:
        std::string phone_ip_port;

    public:
        /**
         * @brief Start ADB server and connect to Android phone wirelessly over Wi-Fi.
         */
        Camera(std::string ip);

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
         * 
         * @param folder
         *  The folder to clear JPGs from
         */
        void clear_computer_folder(const std::string& folder);
        
        /**
         * @brief Return the output of a shell command.
         * 
         * @param cmd
         *  The key to insert into the list
         * @return
         *  The most recent photo in computer folder
         */
        std::string system_output(const char* cmd);
        
        /**
         * @brief Transfer an image from Android phone to computer.
         * 
         * @param from_path
         *  The path to image's source folder on the Android phone
         * @param to_path
         *  The path to image's destination folder on computer
         */
        void transfer_image(const std::string& from_path, const std::string& to_path);

        /**
         * @brief Display an image to computer screen.
         * 
         * @param folder
         *  The folder where the image is stored
         */
        void display_image(const std::string& folder);

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