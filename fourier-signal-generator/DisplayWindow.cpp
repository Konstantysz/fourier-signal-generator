#include "DisplayWindow.h"

void Wave::addHarmonic(Harmonic h) {
    fourierSeries.push_back(h);
}

void Wave::calcYPos() {
    if (fourierSeries.size() > 0) {
        y.push_back(fourierSeries.back().value.y);
    }
}

SquareWave::SquareWave(int n, cv::Mat frame) {
    float t = 0;
    this->addHarmonic(Harmonic(
        t, 100, 1, 0,
        cv::Point(frame.cols / 4, frame.rows / 2))
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

void DisplayWindow::drawAxis(cv::Mat& frame) {
    cv::Scalar axisColor(127, 127, 127);
    cv::Point start(frame.cols / 2, frame.rows / 2);
    cv::Point end(frame.cols / 2 + frame.rows / 2, frame.rows / 2);
    cv::line(frame, start, end, axisColor);
    int len = end.x - start.x;
    for (int i = 0; i < len; i++) {
        if (i % 10 == 0) {
            cv::Point upper(start.x + i, start.y + 5);
            cv::Point lower(start.x + i, start.y - 5);
            cv::line(frame, upper, lower, axisColor);
        }
    }
}


void DisplayWindow::draw(cv::Mat& frame) {

    //SquareWave wave(10, this->time, frame);
    wave.addHarmonic(Harmonic(
        this->time, 100, 1, 0,
        cv::Point(frame.cols / 4, frame.rows / 2))
    );
    for (int i = 1; i < 15; i++) {
        float f = 2 * i + 1;
        float a = (1 / f) * 100;
        wave.addHarmonic(Harmonic(
            this->time, a, f, 0,
            wave.fourierSeries.back().value)
        );
    }

    wave.calcYPos();

    for (auto h : wave.fourierSeries) {
        cv::circle(frame, h.center, h.amplitude, this->color);
        cv::line(frame, h.center, h.value, this->color);
    }

    int xWaveTranslation = frame.cols / 2;
    if (wave.y.size() > 1) {
        for (int i = 0; i < wave.y.size() - 1; i++) {
            cv::line(frame, cv::Point(i + xWaveTranslation, wave.y[i]), cv::Point(i + 1 + xWaveTranslation, wave.y[i + 1]), this->color);
        }
    }
    drawAxis(frame);

    if (wave.y.size() > frame.rows / 2)
        wave.y.erase(wave.y.begin());

    this->time += 0.05;
    wave.fourierSeries.clear();
}

void DisplayWindow::drawAnimation() {

    for (;;) {
        cv::Mat frame = cv::Mat::zeros(cv::Size(this->width, this->height), CV_8UC3);

        draw(frame);

        cv::imshow("Frame", frame);

        char c = (char)cv::waitKey(25);
        if (c == 27) break;
    }
    cv::destroyAllWindows();

    return;
}