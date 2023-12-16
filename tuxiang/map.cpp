#include <opencv2/opencv.hpp>
#include <opencv2/world.hpp>
#include <random>


// #include <mutex>


int main() {
    // 图像的宽度和高度
    const int width = 1920;
    const int height = 1080;

    // 创建一个白色背景的图像
    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);
    image.setTo(cv::Scalar(255, 255, 255));

    // 随机数生成器，用于确定绿色区域的位置和大小
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist_width(0, width - 500);
    std::uniform_int_distribution<int> dist_height(0, height - 500);

    // 确定绿色区域的随机起点
    int x_start = dist_width(mt);
    int y_start = dist_height(mt);

    // 确保绿色区域不小于500x500
    cv::Rect greenRect(x_start, y_start, 500, 500);

    // 在图像中绘制绿色区域
    cv::rectangle(image, greenRect, cv::Scalar(0, 255, 0), cv::FILLED);

    // 用红色线将图像分为左右两个相等的部分
    cv::line(image, cv::Point(width / 2, 0), cv::Point(width / 2, height), cv::Scalar(0, 0, 255), 3);

    // 显示图像
    cv::imshow("Image with Random Green Area", image);
    cv::waitKey(0);

    // 保存图像
    cv::imwrite("output_image.png", image);

    return 0;
}
