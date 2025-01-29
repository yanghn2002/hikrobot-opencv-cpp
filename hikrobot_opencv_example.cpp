#include "hikrobot_opencv.hpp"
#include <iostream>


int main(void) {

    // get HikrobotMvContext instance
    hikcv::MvContext& context = hikcv::MvContext::instance();

    // enum Hikrobot Mv devices
    hikcv::MvContext::DeviceIndex devices = context.enumDevices();
    std::cout << "devices:" << std::endl;
    for(auto device: devices)
        std::cout << '\t' << device.first << ": " << device.second << std::endl;
    
    // open camera and start grabbing
    std::string input_serial_number;
    std::cout << "input camera serial number to open: " << std::flush;
    std::getline(std::cin, input_serial_number);
    hikcv::OpencvCamera camera = context.createCapture(input_serial_number);
    camera.start();

    // get OpenCV Mat and show
    while(true) {
        cv::Mat image = camera.ref_cv_mat();
        cv::imshow("image cv", image);
        cv::waitKey(1);
    }

    return 0;

}