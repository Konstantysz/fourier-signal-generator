#pragma once
#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "Wave.h"

class DisplayWindow
{
private:
	int width, height;
    float time;
    Wave* wave;
    cv::Scalar color;

public:
    DisplayWindow(int w, int h) : width(w), height(h), time(0.f), color(cv::Scalar(255, 255, 255)) {
        //this->wave = new SawToothWave(10, w, h);
        //this->wave = new SquareWave(20, w, h);
        this->wave = new PulseWave(20, 0.9, w, h);
        //this->wave = new TriangleWave(50, w, h);
    }
    void drawAxis(cv::Mat&);
    void draw(cv::Mat&);
    void drawAnimation();
};

