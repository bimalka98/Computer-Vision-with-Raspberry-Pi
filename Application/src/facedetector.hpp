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

#ifndef FACEDETECTOR_HPP
#define FACEDETECTOR_HPP

#include <iostream>                     // for standard I/O

#include <opencv2/highgui/highgui.hpp>  // for OpenCV window I/O
#include <opencv2/opencv.hpp>           // for OpenCV general functionality

#include <thread>   // for sleep_for and sleep_until
#include <chrono>   // for high resolution timer

class FaceDetector
{

    private:

        // parameters realated to the usb camera
        cv::VideoCapture usbCamera;
        int deviceID = 0;       // 0 for default camera input
        int FPS = 10;           // frames per second
        int framePosition = 1;  // 0-based index of the frame to be decoded/captured next.
        int bufferSize = 1;     // internal buffer will now store only 1 frames

        // varaible to store the captured frame and the preprocessed frame
        cv::Mat capturedFrame;       
    
        // parameters related to face detection                
        cv::dnn::Net network;               // Face detection network                
        const int inputImageWidth = 300;    // Input image width                
        const int inputImageHeight = 300;   // Input image height                
        const double scaleFactor = 1.0;     // Scale factor when creating image blob                
        const cv::Scalar meanValues = {104., 177.0, 123.0};       // Mean normalization values network was trained with                
        const float confidenceThreshold = 0.5;   // Face detection confidence threshold
        
        // vector to hold detected faces
        std::vector<cv::Rect> detectedFaces;
    
    public:
        
        // default constructor
        FaceDetector(){
            std::cout << "[INFO] face detection framework initialized" << std::endl;
        }

        // destructor
        ~FaceDetector(){
            std::cout << "[INFO] face detection framework terminated" << std::endl;
        }
        

        /*         Public Member Fucntions declarations      
        *******************************************************/
        
        // member function to initialize the video capturing object
        void InitializeVideoCapture();

        // member function to initialize the face detector
        void InitializeDNN();

        // member function to grab frame from the camera video stream
        void CaptureFrame();

        // public member function to detect faces
        void DetectFaces();
        
        // member function to visualize the detected faces (fully processed frame)
        void VisualizeFrame();

};

#endif
