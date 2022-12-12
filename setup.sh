#!/bin/sh -e
# 2022 Bimalka Piyaruwan Thalagala

################################################################################
#	A simple script,                                                           #
#       to install/build the dependencies                                      #
################################################################################

# label to inform the user that the dependencies are being installed
label_dependencies () {

    echo
    echo "==========================================================="
    echo "|                 Installing dependencies                 |"
    echo "==========================================================="
    echo

}

# Updating the systme to the latest version and installing the dependencies
install_dependencies () {

    echo "[INFO] installing build dependencies...\n"

    # sudo apt-get update #removed  due to an issue with a package
    # sudo apt-get upgrade -y
    sudo apt-get install -y \
        build-essential \
        cmake \
        gfortran \
        cron \
        libjpeg-dev \
        libpng-dev \
        libtiff-dev \
        libgtk-3-dev \
        libavcodec-extra \
        libavformat-dev \
        libswscale-dev \
        libv4l-dev \
        libxvidcore-dev \
        libx264-dev \
        libjasper1 \
        libjasper-dev \
        libatlas-base-dev \
        libeigen3-dev \
        libtbb-dev
    
    echo "Done!"
}

# Installing Optimized OpenCV for RPi
install_opencv () {

    echo "[INFO] installing OpenCV...\n"

    # change to the opencv directory
    cd OpenCV

    # install opencv debian package
    sudo dpkg -i OpenCV*.deb
    sudo ldconfig

    # change back to the main directory
    cd ..    

    echo "Done!"
    echo

}

# test if opencv is installed by running a test script
test_opencv () {
    
    echo "[INFO] testing OpenCV installation...\n"
    cd Tests/opencv/

    # remove build directory if it exists
    rm -rf build

    # create build directory: for new build
    mkdir build && cd build
    cmake ..
    make 
    ./cpp_opencv_test

    # remove the build directory
    cd ..
    rm -rf build # -r for recursive removal ( typically used with directories) - -f to force the action
    
    # change back to the main directory
    cd ../..

    echo "Done!"
    echo
}

## label to inform the user that the application is being built
label_build () {

    echo
    echo "==========================================================="
    echo "|                  Building face Detector                 |"
    echo "==========================================================="
    echo

}

# compiling the application
build_application () {

    echo "[INFO] building the face detction application...\n"

    # building the face detection framework
    cd Application/

    # remove build and bin directories if they exist
    rm -rf build
    rm -rf bin

    # create build directory: for new build
    mkdir build && cd build
    cmake ..
    make

    # remove the build directory
    cd ..
    rm -rf build # -r for recursive removal ( typically used with directories) - -f to force the action

    # change back to the main directory
    cd ..

    echo "Done!"
    echo
}

# fucntion to set up the cron job
setup_cron() {
    
    echo "[INFO] setting up cron job...\n"

    # remove existing cron jobs: this does not work. program terminates if uncommented
    # crontab -r
    
    # enable cron services: https://phoenixnap.com/kb/crontab-reboot
    sudo systemctl enable cron.service

    # create a cron job in one line: https://stackoverflow.com/a/9625233/15939357
    # no crontab is created at first try but at the second attemp. this is not desirable: https://stackoverflow.com/a/51497394/15939357
    (crontab -l 2>/dev/null || true; echo "@reboot cd ~/Desktop/Computer-Vision-with-Raspberry-Pi/Application/bin/ && ./detect_faces >> log.txt") | crontab -


    # display the set up cron job for the pi user.
    crontab -l
    
}

# main function 
main () {
    
    ## label to inform the user that the dependencies are being installed
    label_dependencies

    ## installing dependencies
    install_dependencies

    ## installing and testing opencv
    install_opencv
    test_opencv

    ## label to inform the user that the application is being built
    label_build
    
    ## build the framework
    build_application

    ## set up the cron job
    # setup_cron
}

main "$@"
