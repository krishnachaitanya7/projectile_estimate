#include <iostream>
#include <cam.h>
#include <opencv2/opencv.hpp>



int main() {
    RealSenseCam my_cam;
    while (true){
        rs2::depth_frame dpt_frame = my_cam.get_frames().first;
        float width = dpt_frame.get_width();
        float height = dpt_frame.get_height();

        float dist_to_center = dpt_frame.get_distance(width / 2, height / 2);

        // Print the distance
        std::cout << "The camera is facing an object " << dist_to_center << " meters away" << std::endl;

    }
    return 0;
}