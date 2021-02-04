#include "DisplayWindow.h"

void DisplayWindow::draw(cv::Mat& frame) {
    int r1 = 100;
    int r2 = 25;
    int r3 = 10;
    int r4 = 5;

    float f1 = 0.5;
    float f2 = 5;
    float f3 = 10;
    float f4 = 25;

    cv::Point p0(frame.cols / 4, frame.rows / 2);
    cv::Point p1(p0.x + r1 * cos(f1 * this->time), p0.y + r1 * sin(f1 * this->time));
    cv::Point p2(p1.x + r2 * cos(f2 * this->time), p1.y + r2 * sin(f2 * this->time));
    cv::Point p3(p2.x + r3 * cos(f3 * this->time), p2.y + r3 * sin(f3 * this->time));
    cv::Point p4(p3.x + r4 * cos(f4 * this->time), p3.y + r4 * sin(f4 * this->time));

    this->wave.push_back(p4.y);

    cv::circle(frame, p0, r1, this->color);
    cv::line(frame, p0, p1, this->color);
    cv::circle(frame, p1, r2, this->color);
    cv::line(frame, p1, p2, this->color);
    cv::circle(frame, p2, r3, this->color);
    cv::line(frame, p2, p3, this->color);
    cv::circle(frame, p3, r4, this->color);
    cv::line(frame, p3, p4, this->color);


    int xWaveTranslation = frame.cols / 2;
    if (wave.size() > 1) {
        for (int i = 0; i < wave.size() - 1; i++) {
            cv::line(frame, cv::Point(i + xWaveTranslation, wave[i]), cv::Point(i + 1 + xWaveTranslation, wave[i + 1]), this->color);
        }
    }

    if (this->wave.size() > frame.rows / 2)
        this->wave.erase(wave.begin());

    this->time += 0.05;
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