#include <iostream>
#include <cam.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>


using namespace cv;
using namespace std;
RNG rng(12345);

// Found a better Alternative to track ball
// https://www.pyimagesearch.com/2015/09/14/ball-tracking-with-opencv/
// Maybe I could try this

int main() {
    RealSenseCam my_cam;
    Mat src_gray;
    rs2::colorizer colorizer;
    rs2::spatial_filter spat;
    Mat img_blurred;
    Mat hsv_image;
    Mat frame_threshold;

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
        Mat img(Size(640, 480), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);
        GaussianBlur(img, img_blurred, Size(3, 3), 0);
        cvtColor(img_blurred, hsv_image, COLOR_BGR2HSV);
        inRange(hsv_image, Scalar(29, 86, 6), Scalar(64, 255, 255), frame_threshold);
        erode(frame_threshold, frame_threshold, Mat());
        dilate(frame_threshold, frame_threshold, Mat());
        std::vector<std::vector<cv::Point> > contours;
        cv::findContours( frame_threshold.clone(), contours, RETR_LIST, CHAIN_APPROX_NONE );
        if (!contours.empty()){
            vector<vector<Point> > contours_poly( contours.size() );
            vector<Rect> boundRect( contours.size() );
            vector<Point2f>centers( contours.size() );
            vector<float>radius( contours.size() );
            for( size_t i = 0; i < contours.size(); i++ )
            {

                        approxPolyDP( contours[i], contours_poly[i], 3, true );
                        boundRect[i] = boundingRect( contours_poly[i] );
                        minEnclosingCircle( contours_poly[i], centers[i], radius[i] );





            }

            Mat drawing = Mat::zeros( frame_threshold.size(), CV_8UC3 );
            for( size_t i = 0; i< contours_poly.size(); i++ )
            {
                Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
                if(radius[i] > 50.0){
                    circle( img, centers[i], (int)radius[i], color, 2 );
                }

            }
            imshow( "Contours", img );
            waitKey(1);
        }
    }
    return 0;
}