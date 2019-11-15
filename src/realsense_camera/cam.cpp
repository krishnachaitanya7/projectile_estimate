#include <cam.h>
#include <constants.h>
#include <librealsense2/rs.hpp>
#include <unordered_map>


RealSenseCam::RealSenseCam() {
    rs2::config config;
    config.enable_stream(RS2_STREAM_DEPTH);
    config.enable_stream(RS2_STREAM_COLOR);
    this->pipe.start(config);
    for(int i = 0; i < 30; i++){
        // Wait for all configured streams to produce a frame

        this->pipe.wait_for_frames();
    }

}

std::pair<rs2::depth_frame, rs2::frame> RealSenseCam::get_frames() {
    rs2::frameset frames = this->pipe.wait_for_frames();
    //ToDo: Ask Caleb for a better way to do this
    rs2::align align_to_depth(RS2_STREAM_DEPTH);
    frames = align_to_depth.process(frames);
    return std::make_pair(frames.get_depth_frame(), frames.get_color_frame());
}


