#pragma once
#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

struct Harmonic {
    Harmonic(float t, float a, float f, float phi, cv::Point c) : t(t), amplitude(a), frequency(f), phase(phi), center(c),
        value(cv::Point(center.x + amplitude * cos(frequency * t + phase), center.y + amplitude * sin(frequency * t + phase))) {}
    float t;
    float amplitude;
    float frequency;
    float phase;
    cv::Point center;
    cv::Point value;
};

class Wave {
public:
    std::vector<int> y;
    std::vector<Harmonic> fourierSeries;

public:
    void addHarmonic(Harmonic);
    void calcYPos();
    void updateHarmonics(float);
};

class SquareWave : public Wave {
    SquareWave(int, cv::Mat);
};

class DisplayWindow
{
private:
	int width, height;
    float time;
    //SquareWave wave;
    Wave wave;
    cv::Scalar color;

public:
    DisplayWindow(int w, int h) : width(w), height(h), time(0.f), color(cv::Scalar(255, 255, 255))/*, wave(10, frame)*/{}
    void drawAxis(cv::Mat&);
    void draw(cv::Mat&);
    void drawAnimation();
};

