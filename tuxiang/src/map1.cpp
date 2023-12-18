#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
    // 创建一个空白的黑色图像

    cout << "Loading" << endl;

    cv::Mat blank_image = cv::Mat::zeros(480, 640, CV_8UC3);

    cout << "1" << endl;

    // 创建一个窗口
    cv::namedWindow("Blank Window", cv::WINDOW_AUTOSIZE);
    cout << "2" << endl;

    // 在窗口中显示图像
    cv::imshow("Blank Window", blank_image);
    cout << "3" << endl;

    // 等待用户按键
    cv::waitKey(0);
    cout << "4" << endl;

    return 0;
}
