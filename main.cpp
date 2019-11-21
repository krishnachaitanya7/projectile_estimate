#include <iostream>
#include <cam.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Found a better Alternative to track ball
// https://www.pyimagesearch.com/2015/09/14/ball-tracking-with-opencv/
// Maybe I could try this

int main() {
    RealSenseCam my_cam;
    Mat src_gray;
    rs2::colorizer colorizer;
    rs2::spatial_filter spat;

    // Enable hole-filling
    // Hole filling is an agressive heuristic and it gets the depth wrong many times
    // However, this demo is not built to handle holes
    // (the shortest-path will always prefer to "cut" through the holes since they have zero 3D distance)
    spat.set_option(RS2_OPTION_HOLES_FILL, 2); // 5 = fill all the zero pixels
    // ToDo: Implement Hole Filling preprocessing algorithm from Realsense
    // To improve Hough Transform
    while (true){
        std::pair<rs2::depth_frame, rs2::frame> incoming_frames = my_cam.get_frames();
        rs2::frame color_frame = incoming_frames.second;
        rs2::depth_frame depth = incoming_frames.first;
        depth = depth.apply_filter(spat);
        Mat img(Size(640, 480), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);
//        cvtColor(img, img, COLOR_BGR2RGB);
        cvtColor( img, src_gray, COLOR_BGR2GRAY );
        vector<Vec3f> circles;
        if(!img.empty()) {
            HoughCircles(src_gray, circles, HOUGH_GRADIENT,
                         3,   // accumulator resolution (size of the image / 2)
                         1000,  // minimum distance between two circles
                         200, // Canny high threshold
                         110, // minimum number of votes
                         10, 10000); // min and max radius
            for (size_t i = 0; i < circles.size(); i++) {
                Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                int radius = cvRound(circles[i][2]);
                circle(img, center, 3, Scalar(0, 255, 0), -1, 8, 0);// circle center
                circle(img, center, radius, Scalar(0, 0, 255), 3, 8, 0);// circle outline
                cout << "center : " << center << "\nradius : " << radius << endl;
            }
            namedWindow("Hough Circle Transform Demo", WINDOW_AUTOSIZE);
            imshow("Hough Circle Transform Demo", img);
            auto colorized_depth = colorizer.colorize(depth);
            Mat colordepth(Size(640, 480), CV_8UC3, (void*)colorized_depth.get_data(), Mat::AUTO_STEP);
            namedWindow("Colorized Depth", WINDOW_AUTOSIZE);
            imshow("Colorized Depth", colordepth);

            waitKey(1);
        }


    }
    return 0;
}