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
        this->wave = new SawToothWave(100, w, h, 100.f, 0.1f);
        //this->wave = new SquareWave(5, w, h, 100.f, 0.5f);
        //this->wave = new AbsSinWave(100, w, h, 100.f, 0.1f);
        //this->wave = new TriangleWave(10, w, h, 100.f, 0.05f);
    }
    void drawAxis(cv::Mat&);
    void draw(cv::Mat&);
    void drawAnimation();
};

