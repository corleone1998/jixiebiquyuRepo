#include <opencv2/opencv.hpp>
#include <random>


// #include <mutex>


int main() {
    // 图像的宽度和高度
    const int width = 1920;
    const int height = 1080;

    // 创建一个灰色背景的图像
    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);
    image.setTo(cv::Scalar(245, 245, 245));

    // 设置方块个数
    int area_number = 20;
       // 每个方块的尺寸
    int block_size = 50;

    // 循环产生每个随机方块
for (size_t i = 0; i < area_number; i++)
{
    
    // 创建随机种子及随机序列
    std::random_device rd;
    std::mt19937 mt(rd());

    // 确保随机位置对齐到1920*1080像素的网格上
    std::uniform_int_distribution<int> dist_x(0, width-1); // 0到1919
    std::uniform_int_distribution<int> dist_y(0, height-1); // 0到1079

    // 生成一个随机位置
    int x_start = dist_x(mt);
    int y_start = dist_y(mt) ;

    // 确保绿色区域不小于50x50
    cv::Rect greenRect(x_start, y_start, 50, 50);

    // 在图像中绘制绿色区域
    cv::rectangle(image, greenRect, cv::Scalar(0, 255, 0), cv::FILLED);
}

    // 显示图像
    cv::imshow("Image with Random Stained Area", image);
    cv::waitKey(0);

    // 保存清洗区域“Stained_area”图像
    cv::imwrite("../image/Stained_area20.png", image);

    return 0;
}
