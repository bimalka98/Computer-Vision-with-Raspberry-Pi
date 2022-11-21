/*
*************************************************************************************
*                                Author Details                                     *
* Author: Bimalka Piyaruwan Thalagala                                               *                                            *
* Email: bimalkapiyaruwan1998322@gmail.com                                          *
*===================================================================================*

*                                Description                                        *
>>> OpenCV Version: 
------------------------------------------------------------------------------------
OpenCV 4.4.0 for Raspberry Pi optimized for deep learning / computer vision 
applications (NEON, VFPV3, TBB turned on)

>>> Refered Webpages/OpenCV Documentation:
------------------------------------------------------------------------------------
Links are commented near the code for convenience.

*************************************************************************************
*/

// standard and external libraries
#include <iostream> // for standard I/O
#include <fstream>  // for file I/O

#include <opencv2/highgui/highgui.hpp>  // for OpenCV window I/O
#include <opencv2/opencv.hpp>           // for OpenCV general functionality

#include <thread>   // for sleep_for and sleep_until
#include <chrono>   // for high resolution timer


// user defined libraries
#include "facedetector.hpp" // a library developed by the author for face detection fucntinalities





/*
**************************************************************************
*                       Private Member Functions                         *
**************************************************************************
*/


/*
**************************************************************************
*                       Public Member Functions                          *
**************************************************************************
*/

// public member function to initialize the video capturing object
void FaceDetector::InitializeVideoCapture(){
    
    // number of attempts to open the video input device
    int _attempts = 0;

    // open the video input device
    while(!this->usbCamera.isOpened()){
        
        // open the camera identified by deviceID
        this->usbCamera.open(this->deviceID);

        // if the attempt is unsuccessful, wait for 1 second and try again
        if(!this->usbCamera.isOpened()){
            std::cout << "Unable to open the camera. Attempt " << _attempts << "." << std::endl;
            std::cout << "Waiting for 100 millisecond..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            _attempts++;
        }

        // if the attempt is unsuccessful after 10 attempts, exit the program
        if(_attempts == 10){
            std::cout << "Unable to open the camera after 10 attempts. Exiting..." << std::endl;
            exit(1);
        }
    }
    
    
    // set the camera properties
    // identified values through trial and error to get near real time performance
    this->usbCamera.set(cv::CAP_PROP_FPS, this->FPS);
    this->usbCamera.set(cv::CAP_PROP_POS_FRAMES, this->framePosition);
    this->usbCamera.set(cv::CAP_PROP_BUFFERSIZE, this->bufferSize);

    std::cout << "[INFO] usb camera initialized" << std::endl;
}

// public member function to grab frame from the camera video stream
void FaceDetector::CaptureFrame(){


    // remove the previous frame if it exists
    if(this->capturedFrame.data){
        this->capturedFrame.release();
    }

    // read the frame from the usb camera
    bool _success = this->usbCamera.read(this->capturedFrame);
    
    // check if the frame is captured
    if ( !_success ) {
        std::cout << "[ERROR] Could not read a frame" << std::endl;
        exit(EXIT_FAILURE);
    }    
        
}

// public member function to detect faces
void FaceDetector::DetectFaces(){

}

// public member function to visualize the detected objects (fully processed frame)
void FaceDetector::VisualizeFrame(){
    
    // create a window to display the frame
    cv::namedWindow( "Face Detection", cv::WINDOW_AUTOSIZE );

    // display the frame
    cv::imshow( "Face Detection", this->capturedFrame );

}


