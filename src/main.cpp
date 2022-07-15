#include "initialize.h"
#include "image_loader.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    std::string pathSeq(argv[1]);

    std::string file_path = pathSeq + "/mav0/cam0/data";
    std::string imu_time_path = argv[2];
    
    std::vector<double> vTimeStamps;

    auto loader = alike::ImageLoader(file_path);

    alike::load_imu_timestamps(imu_time_path, vTimeStamps);
    if (vTimeStamps.size()>0)
        std::cout << "LOADED!" << "\n";
    // ===============> main loop
    cv::Mat image;
    bool no_display = false;
    int cnt = 0;
    while (loader.read_next(image))
    {
        std::cout << vTimeStamps[cnt] << "\n";
        if (!no_display)
        {
            cv::imshow("tracking image", image);
            auto c = cv::waitKey(1);
            if (c=='q') break;
        }
        cnt++;
    }

    return 0;
}