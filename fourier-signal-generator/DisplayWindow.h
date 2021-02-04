#pragma once
#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

struct Harmonic {
    Harmonic(int a, float f, float phi) : amplitude(a), frequency(f), phase(phi) {}
    int amplitude;
    float frequency;
    float phase;
};

class Wave {
public:
    std::vector<int> y;
    std::vector<Harmonic> fourierSeries;

public:
    void addHarmonic();
};

class DisplayWindow
{
private:
	int width, height;
    float time;
    std::vector<int> wave;
    cv::Scalar color;

public:
    DisplayWindow(int w, int h) : width(w), height(h), time(0.f), color(cv::Scalar(255, 255, 255)) {}
    void draw(cv::Mat&);
    void drawAnimation();
};

