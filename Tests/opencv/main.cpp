// a simple script to test the opencv library installation
// 2022 Bimalka Piyaruwan Thalagala

// importing the required libraries
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

int main(){

    // printing the installed version of opencv
    std::cout << "OpenCV version: " << cv::getVersionMajor() << "." << cv::getVersionMinor() << "." << cv::getVersionRevision() << std::endl;

    // checking the TBB support
    std::cout << "Available CPUs: " << cv::getNumberOfCPUs( ) << std::endl;
    std::cout << "Available threads: " << cv::getNumThreads( ) << std::endl;
    if ( cv::getNumThreads( ) < cv::getNumberOfCPUs( ) ) {
        std::cout << "ERROR: TBB is not enabled." << std::endl;        
    }else{
        std::cout << "SUCCESS: TBB is enabled." << std::endl;
    }

    // checking the NEON support
    std::cout << "Cpu NEON support: " << cv::checkHardwareSupport( CV_CPU_NEON ) << std::endl;
    if ( cv::checkHardwareSupport( CV_CPU_NEON ) == 0 ) {
        std::cout << "ERROR: NEON is not enabled." << std::endl;        
    }else{
        std::cout << "SUCCESS: NEON is enabled." << std::endl;
    }
}