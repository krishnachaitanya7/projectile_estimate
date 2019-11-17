#ifndef PROJECTILE_ESTIMATE_CAM_H
#define PROJECTILE_ESTIMATE_CAM_H

#include <librealsense2/rs.hpp>

class RealSenseCam{
public:
    RealSenseCam();
    std::pair<rs2::depth_frame, rs2::frame> get_frames();
private:
    void initialise_camera();
    rs2::pipeline pipe;

};

#endif //PROJECTILE_ESTIMATE_CAM_H
