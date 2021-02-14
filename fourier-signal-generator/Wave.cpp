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

SquareWave::SquareWave(int n, int winW, int winH, float amplitude, float frequency) {
    float t = 0;
    float swc = (4 / PI) * amplitude;
    float freqCons = 2 * PI * frequency;
    this->addHarmonic(Harmonic(
        t, swc, freqCons, 0,
        cv::Point(winW / 4, winH / 2))
    );
    for (int i = 1; i < n; i++) {
        float N = 2 * i + 1;
        float a = swc / N;
        float f = N * freqCons;
        this->addHarmonic(Harmonic(
            t, a, f, 0,
            this->fourierSeries.back().value)
        );
    }
}

SawToothWave::SawToothWave(int n, int winW, int winH, float amplitude, float frequency) {
    float t = 0;
    float swc = (2 * amplitude) / PI;
    float freqCons = 2 * PI * frequency;
    this->addHarmonic(Harmonic(
        t, swc, freqCons, 0,
        cv::Point(winW / 4, winH / 2))
    );
    for (int i = 1; i < n; i++) {
        float N = i + 1;
        float a = (swc * pow(-1, N + 1)) / N;
        float f = N * freqCons;
        this->addHarmonic(Harmonic(
            t, a, f, 0,
            this->fourierSeries.back().value)
        );
    }
}

TriangleWave::TriangleWave(int n, int winW, int winH, float amplitude, float frequency) {
    float t = 0;
    float swc = (8 / (PI * PI)) * amplitude;
    float freqCons = 2 * PI * frequency;
    this->addHarmonic(Harmonic(
        t, swc, freqCons, PI / 2,
        cv::Point(winW / 4, winH / 2))
    );
    for (int i = 1; i < n; i++) {
        float N = 2 * i - 1;
        float a = swc / (N * N);
        float f = N * freqCons;
        this->addHarmonic(Harmonic(
            t, a, f, PI / 2,
            this->fourierSeries.back().value)
        );
    }
}
