#pragma once

#include <vector>
#include <iostream>

#include "tracker.hpp"
#include "location.hpp"
#include "node.hpp"
#include "utils.hpp"

#include <opencv2/opencv.hpp>

class Tracklet
{
public:
    vector<Node> detection_track;
    Location center;
    cv::Mat histogram;
    bool is_end_of_traj;

    Tracklet(const vector<Node> &path, int video_w, int video_h)
    {
        detection_track = path;
        set_middle_point();
        set_histogram();
        is_end_of_traj =  is_end_of_trajectory(video_w, video_h);
        print();
    }
    void print() const;
    
    static void print_tracklets(const vector2d<Tracklet> &tracklets);

private:
    void set_middle_point();
    void set_histogram();
    bool is_end_of_trajectory(int video_w, int video_h);
};
