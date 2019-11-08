#include <iostream>
#include <cam.h>


int main() {
    RealSenseCam my_cam;
    while (true) {
        rs2::depth_frame depth_frame = my_cam.depth_frame;
        rs2::frame color_frame = my_cam.color_frame;
    }
    return 0;
}