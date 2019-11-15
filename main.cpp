#include <iostream>
#include <cam.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    RealSenseCam my_cam;
    Mat src_gray;
    while (true){
        rs2::frame color_frame = my_cam.get_frames().second;

        Mat img(Size(640, 480), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);
        cvtColor( img, src_gray, COLOR_BGR2GRAY );
        vector<Vec3f> circles;
        if(!img.empty()) {


            HoughCircles(src_gray, circles, HOUGH_GRADIENT,
                         6,   // accumulator resolution (size of the image / 2)
                         1000,  // minimum distance between two circles
                         300, // Canny high threshold
                         100, // minimum number of votes
                         10, 100); // min and max radius
            for (size_t i = 0; i < circles.size(); i++) {
                Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                int radius = cvRound(circles[i][2]);
                circle(img, center, 3, Scalar(0, 255, 0), -1, 8, 0);// circle center
                circle(img, center, radius, Scalar(0, 0, 255), 3, 8, 0);// circle outline
                cout << "center : " << center << "\nradius : " << radius << endl;
            }
            namedWindow("Hough Circle Transform Demo", WINDOW_AUTOSIZE);
            imshow("Hough Circle Transform Demo", img);

            waitKey(1);
        }


    }
    return 0;
}