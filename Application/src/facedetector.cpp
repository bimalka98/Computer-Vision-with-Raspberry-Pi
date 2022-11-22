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

// member function to initialize the face detector
void FaceDetector::InitializeDNN(){

    // Note: The varibles MODEL_CONFIGURATION_FILE and MODEL_WEIGHTS_FILE are passed in via cmake
    this->network = cv::dnn::readNetFromCaffe(FACE_DETECTION_CONFIGURATION, FACE_DETECTION_WEIGHTS);

    // check if the model is properly loaded
    if ( this->network.empty() ) {
        std::cout << "[ERROR] Could not load the model" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "[INFO] loaded the model successfully" << std::endl;
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

    // clear the vector containing detected faces
    this->detectedFaces.clear();

    /* transforming the input image into a data blob. 
     The function cv::dnn::blobFromImage takes care of
     rescaling the image to the correct input size for the network. 
     It also subtracts the mean value in each color channel
     */
    this->inpuBlob = cv::dnn::blobFromImage(
        this->capturedFrame, 
        this->scaleFactor, 
        cv::Size(this->inputImageWidth, this->inputImageHeight),
        this->meanValues, false, false);
    
    // forward our data through the network
    this->network.setInput(this->inpuBlob, "data");    
    cv::Mat _detection = this->network.forward("detection_out");
    
    cv::Mat _detectionmatrix(_detection.size[2], _detection.size[3], CV_32F, _detection.ptr<float>());

    for (int i = 0; i < _detectionmatrix.rows; i++) {
        
        float _confidence = _detectionmatrix.at<float>(i, 2);

        // neglect faces with low confidence 
        if (_confidence < this->confidenceThreshold) {
            continue;
        }
        
        // left bottom coordinates
        int _xlb = static_cast<int>(_detectionmatrix.at<float>(i, 3) * this->capturedFrame.cols);
        int _ylb = static_cast<int>(_detectionmatrix.at<float>(i, 4) * this->capturedFrame.rows);

        // right top coordinates
        int _xrt = static_cast<int>(_detectionmatrix.at<float>(i, 5) * this->capturedFrame.cols);
        int _yrt = static_cast<int>(_detectionmatrix.at<float>(i, 6) * this->capturedFrame.rows);

        this->detectedFaces.emplace_back(_xlb, _ylb, (_xrt - _xlb), (_yrt - _ylb));
    }

}

// public member function to visualize the detected objects (fully processed frame)
void FaceDetector::VisualizeFrame(){
    
    
    cv::Scalar _color(0, 105, 205);

    for(const auto & rectangle : this->detectedFaces){
        cv::rectangle(this->capturedFrame, rectangle, _color, 4);
    }

    // create a window to display the frame
    cv::namedWindow( "Face Detection", cv::WINDOW_AUTOSIZE );

    // display the frame
    cv::imshow( "Face Detection", this->capturedFrame );

}


