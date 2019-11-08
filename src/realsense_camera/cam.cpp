#include <cam.h>
#include <constants.h>
#include <librealsense2/rs.hpp>
#include <thread>


void RealSenseCam::initialise_camera(){
    rs2::pipeline pipe;
    pipe.start();
    rs2::frameset frames = pipe.wait_for_frames();
    while(true){
        this->depth_frame = frames.get_depth_frame();
        this->color_frame = frames.get_color_frame();
    }
}

RealSenseCam::RealSenseCam() {
    std::thread realsense_thread(&RealSenseCam::initialise_camera, this);
    realsense_thread.detach();
}

