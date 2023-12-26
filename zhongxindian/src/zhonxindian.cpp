#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>

using namespace cv;
using namespace std;

int main() {
    Mat img = imread("../../tuxiang/image/Stained_area.png", IMREAD_GRAYSCALE);
    Mat img_yuantu= imread("../../tuxiang/image/Stained_area.png");

    // 定义一个点的向量来存储质心
std::vector<cv::Point> centroids;
    // 打开一个文件来写入质心坐标
std::ofstream outfile("../centroids.txt");

    // 检查图像是否正确加载
    if (img.empty()) {
        cout << "Could not read the image" << endl;
        return 1;
    }

    // 对图像进行边缘填充
    int border = 1; // 可以根据需要调整边缘的大小
    Mat padded_img;
    copyMakeBorder(img, padded_img, border, border, border, border, BORDER_CONSTANT, Scalar(255,255,255));

    // 边缘检测
    Mat edges;
    Canny(padded_img, edges, 100, 200);

    // 查找轮廓
    vector<vector<Point>> contours;
    findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 遍历所有轮廓
    for (size_t i = 0; i < contours.size(); i++) {
        // 计算轮廓的矩
        Moments m = moments(contours[i]);
        if (m.m00 != 0) { // 防止除以0
            // 计算质心
            int cx = int(m.m10 / m.m00);
            int cy = int(m.m01 / m.m00);

            // 考虑到边缘填充，调整质心坐标???
            cx -= border;
            cy -= border;

             // 将质心坐标写入文件
        outfile << cx << "," << cy << std::endl;

            // 在原图上绘制中心点
            circle(img_yuantu, Point(cx, cy), 5, Scalar(0, 0, 255), -1);
        }
    }

    // 关闭文件
    outfile.close();

    // 显示图像
    imshow("Centroids", img_yuantu);
    waitKey(0);

    imwrite("../image/zhongxindian.png", img_yuantu);

    return 0;
}
