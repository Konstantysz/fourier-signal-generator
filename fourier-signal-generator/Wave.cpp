#include "Wave.h"

void Wave::addHarmonic(Harmonic h) {
    fourierSeries.push_back(h);
}

void Wave::calcYPos() {
    if (fourierSeries.size() > 0) {
        y.push_back(fourierSeries.back().value.y);
    }
}

void Wave::updateHarmonics(float t) {
    this->fourierSeries[0] = Harmonic(t, fourierSeries[0].amplitude, fourierSeries[0].frequency, fourierSeries[0].phase, fourierSeries[0].center);
    for (size_t i = 1; i < this->fourierSeries.size(); i++) {
        this->fourierSeries[i] = Harmonic(t, fourierSeries[i].amplitude, fourierSeries[i].frequency, fourierSeries[i].phase, fourierSeries[i - 1].value);
    }
}

SquareWave::SquareWave(int n, int winW, int winH) {
    float t = 0;
    this->addHarmonic(Harmonic(
        t, 100, 1, 0,
        cv::Point(winW / 4, winH / 2))
    );
    for (int i = 1; i < n; i++) {
        float f = 2 * i + 1;
        float a = (1 / f) * 100;
        this->addHarmonic(Harmonic(
            t, a, f, 0,
            this->fourierSeries.back().value)
        );
    }
}

SawToothWave::SawToothWave(int n, int winW, int winH) {
    float t = 0;
    this->addHarmonic(Harmonic(
        t, 100, 1, 0,
        cv::Point(winW / 4, winH / 2))
    );
    for (int i = 1; i < n; i++) {
        float f = i;
        float a = (pow(-1, i) * 100) / (PI * i);
        this->addHarmonic(Harmonic(
            t, a, f, 0,
            this->fourierSeries.back().value)
        );
    }
}

TriangleWave::TriangleWave(int n, int winW, int winH) {
    float t = 0;
    this->addHarmonic(Harmonic(
        t, 50, 1, 0,
        cv::Point(winW / 4, winH / 2))
    );
    for (int i = 1; i < n; i++) {
        float f = i;
        float a = (pow(-1, (i - 1) / 2) * 100) / (i * i);
        this->addHarmonic(Harmonic(
            t, a, f, 0,
            this->fourierSeries.back().value)
        );
    }
}

PulseWave::PulseWave(int n, float D, int winW, int winH) {
    float t = 0;
    this->addHarmonic(Harmonic(
        t, 50 * D, 1, 0,
        cv::Point(winW / 4, winH / 2))
    );
    for (int i = 1; i < n; i++) {
        float f = i;
        float a = sin(PI * i * D) * (2 / i);
        this->addHarmonic(Harmonic(
            t, a, f, 0,
            this->fourierSeries.back().value)
        );
    }
}