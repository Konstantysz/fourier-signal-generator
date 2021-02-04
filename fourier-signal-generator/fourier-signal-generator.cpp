#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "DisplayWindow.h"

int main()
{
    DisplayWindow Window(800, 600);

    Window.drawAnimation();

    return 0;
}