#ifndef PROJECTILE_ESTIMATE_CONSTANTS_H
#define PROJECTILE_ESTIMATE_CONSTANTS_H
class RealsenseCamConstants{
public:
    int intrinsic_params = 0;
};

class HoughCirclesParams{
public:
    int accumulator_resolution = 2;
    int minimum_distance_between_circles = 10;
    int canny_high_threshold = 100;
    int minimum_number_of_votes = 100;
    int min_radius = 185;
    int max_radius = 10000;
};
#endif //PROJECTILE_ESTIMATE_CONSTANTS_H
