#pragma once
#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#define PI 3.14159265359

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
public:
    SquareWave(int, int, int, float = 100, float = 0.1);
};

class SawToothWave : public Wave {
public:
    SawToothWave(int, int, int, float = 100, float = 0.1);
};

class TriangleWave : public Wave {
public:
    TriangleWave(int, int, int, float = 100, float = 0.1);
};

class AbsSinWave : public Wave {
public:
    AbsSinWave(int, int, int, float = 100, float = 0.1);
};