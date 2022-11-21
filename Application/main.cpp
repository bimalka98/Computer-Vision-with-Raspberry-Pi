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

// include the standard C++ headers
#include <iostream> // for standard I/O
#include <fstream>  // for file I/O
#include <chrono>   // for high resolution timer
#include <thread>   // for sleep

// include the header files for OpenCV
#include <opencv2/highgui/highgui.hpp>  // for OpenCV window I/O
#include <opencv2/opencv.hpp>           // for OpenCV general functionality    

// include the user-defined header files
#include "src/facedetector.hpp"      // a library developed by the author for face detection fucntionalities


/*
*************************************************************************************
*              >>>          Start of Main Function           >>>                    *
*************************************************************************************
*/      

int main( int argc, char *argv[] )
{ 

    FaceDetector _facedetector; 

    // initializing the video capturing object
    _facedetector.InitializeVideoCapture();

    while(true){

        // get the frame from the camera
        _facedetector.CaptureFrame();

        // visualization of the frame
        _facedetector.VisualizeFrame();

        // wait for 'q' key to exit from the program
        if ( cv::waitKey( 1 ) == 'q' ) {
            break;
        } 
    }

    return 0;
}

/*
*************************************************************************************
*            <<<             End of Main Function               <<<                 *
*************************************************************************************
*/
