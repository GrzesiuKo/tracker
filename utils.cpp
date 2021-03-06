#include <sstream>
#include <iostream>
#include <cmath>

#include "utils.hpp"
#include "templates.hpp"


namespace utils
{
    namespace sys
    {
        void make_tmp_dirs(std::string tmp_folder) 
        {
            std::stringstream ss;
            ss << "mkdir " << tmp_folder << "/img " << tmp_folder << "/csv";
            std::string mkdir_command = ss.str();
            std::cout << "Executing: " << mkdir_command << std::endl;
            system(mkdir_command.c_str());
        }

        void clear_tmp(std::string tmp_folder) 
        {
            std::stringstream ss;
            ss << "exec rm -r " << tmp_folder << "/*";
            std::string del_command = ss.str();
            std::cout << "Executing: " << del_command << std::endl;
            system(del_command.c_str());
        }

        void mv(std::string what, std::string where)
        {
            std::stringstream ss;
            ss << "mv " << what << " " << where;
            std::string mv_command = ss.str();
            std::cout << "Executing: " << mv_command << std::endl;
            system(mv_command.c_str());
        }

        void cp(std::string what, std::string where)
        {
            std::stringstream ss;
            ss << "cp " << what << " " << where;
            std::string cp_command = ss.str();
            std::cout << "Executing: " << cp_command << std::endl;
            system(cp_command.c_str());
        }
    }

    std::string get_frame_path(int frame, std::string tmp_folder)
    {
        std::stringstream ss;
        ss << tmp_folder << "/img/frame" << std::setw(5) << std::setfill('0') << std::to_string(frame) << ".jpeg";
        std::string path = ss.str();
        return path;
    }

    namespace printing
    {
        void print_usage_info()
        {
            const char* usage_info =
            "\n    -s, --segment_size   frames in a segment\n"
            "    -i, --in_video         input video path\n"
            "    -o, --out_video        output video path\n"
            "    -d, --detector         object detector (ssd or yolo or fchd)\n"
            "    -c, --detector_cfg     path to detector cfg\n"
            "    -f, --tmp_folder       path to folder where temporary files will be stored\n"
            "    -h, --help             show this help msg";
            std::cout << usage_info << std::endl;
        }

        void print_parameters(int segment_size, std::string in_video, std::string out_video, 
                            std::string detector, std::string detector_cfg, std::string tmp_folder)
        {
            printf("Segment size set to %d\n", segment_size);
            printf("Input video path set to %s\n", in_video.c_str());
            printf("Output video path set to %s\n", out_video.c_str());
            printf("Detector set to %s\n", detector.c_str());
            printf("Detector cfg path set to %s\n", detector_cfg.c_str());
            printf("Temporary files will be stored in %s\n", tmp_folder.c_str());
        }

        void print_exec_time(std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end)
        {
            std::cout << "Execution time = " << std::chrono::duration_cast<std::chrono::minutes>(end - begin).count() 
                    << "[min] (" << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()  
                    << "[s])" << std::endl;
        }

        void print_detect_time(std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end)
        {
            std::cout << "Detection took = " << std::chrono::duration_cast<std::chrono::minutes>(end - begin).count() 
                    << "[min] (" << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()  
                    << "[s])" << std::endl;
        }
        
        void print_track_time(std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end)
        {
            std::cout << "Tracking took = " << std::chrono::duration_cast<std::chrono::minutes>(end - begin).count() 
                      << "[min] (" << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()  
                      << "[s])" << std::endl;
        }
    }

    namespace regression
    {
        std::pair<double, double> get_linear_fit(vector<double> x, vector<double> y, int n)
        {
            double x_sum = 0, x2_sum = 0, y_sum = 0, xy_sum = 0;
            double a;
            double b;
            for (size_t i = 0; i < n; i++)
            {
                x_sum = x_sum + x[i];
                y_sum = y_sum + y[i];
                x2_sum = x2_sum + pow(x[i], 2);
                xy_sum = xy_sum + x[i] * y[i];
            }
            if ((n * x2_sum - x_sum * x_sum) == 0)
                x2_sum += 0.5;
            double div = (n * x2_sum - x_sum * x_sum);
            a = (n * xy_sum - x_sum * y_sum) / div;
            b = (x2_sum * y_sum - x_sum * xy_sum) / div;
            return std::make_pair(a, b);
        }

        double euclidean_dist(double x1, double y1, double x2, double y2)
        {
            double x = x1 - x2;
            double y = y1 - y2;
            double dist;
            dist = pow(x, 2) + pow(y, 2);
            dist = sqrt(dist);
            return dist;
        }
    }
}
