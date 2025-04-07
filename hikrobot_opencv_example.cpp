#include "hikrobot_opencv.hpp"
#include <iostream>


namespace hik = hikcv;


int main(void) {

    // get HikrobotMvContext instance
    hik::MvContext& context = hik::MvContext::instance();

    // enum Hikrobot Mv devices
    hik::MvContext::DeviceIndex devices = context.enumDevices();
    std::cout << "devices:" << std::endl;
    for(auto device: devices)
        std::cout << '\t' << device.first << ": " << device.second << std::endl;
    
    // open camera and start grabbing
    std::string input_serial_number;
    std::cout << "input camera serial number to open: " << std::flush;
    std::getline(std::cin, input_serial_number);
    hik::CvCapture camera = context.createCapture(input_serial_number);
    camera.start();

    // get OpenCV Mat and show
    while(true) {
        cv::Mat image = camera.ref_cv_mat();
        auto width = image.cols;
        auto height = image.rows;
        while(width >= 1000 || height >= 1000) {
            width /= 2;
            height /= 2;
        }
        cv::Mat image_show;
        cv::resize(image, image_show, cv::Size(width, height));
        cv::imshow("Hikrobot OpenCV Cpp example (ESC to exit)", image_show);
        if(27 == cv::waitKey(1)) break;
    }

    return 0;

}