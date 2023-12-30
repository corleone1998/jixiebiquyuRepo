#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <limits>
#include <fstream>
#include <opencv2/opencv.hpp>

#include "AntColonyOptimization.h"
#include "zuobiaoduqu.h"

using namespace std;
using namespace cv;

int main() {

            // 读取图像
    Mat img = imread("../../tuxiang/image/Stained_area.png");
        // 检查图像是否正确加载
    if (img.empty()) 
    {
        cout << "Could not read the image" << endl;
        return 1;
    }

    // 从文本文件中读取坐标点
    std::vector<Point> points = readPointsFromFile("../../zhongxindian/centroids.txt");

    // 执行蚁群算法进行路径规划
    int numAnts = 10, maxIterations = 5; // 蚂蚁数量，最大迭代次数
    double alpha = 1, beta = 1, Q = 10, evaporationRate = 0.1; //信息素影响因子alpha，启发式影响因子beta，信息素挥发速率evaporationRate

    std::random_device rd;  // 获取一个随机设备用于种子
    std::mt19937 generator(rd());  // 使用 Mersenne Twister 引擎和随机设备生成种子

    std::vector<int> BestTour_forall = antColonyOptimization(points, numAnts, maxIterations, alpha, beta, evaporationRate, Q, generator);

    // 输出最佳路径
    std::cout << "Best tour: ";
    for (int idx : BestTour_forall) 
    {
        std::cout << idx << " ";
        //绘制路径
        cv::line(img, points[BestTour_forall[idx]], points[BestTour_forall[idx + 1]], cv::Scalar(0, 0, 255), 2); //2是指像素宽度
    }
        // 绘制路径的最后一条边
        cv::line(img, points[BestTour_forall.back()], points[BestTour_forall[0]], cv::Scalar(0, 0, 255), 2);

    double Tourlength = tourLength(points, BestTour_forall);
    std::cout << std::endl;
    // 输出最佳路径长度
    std::cout << "Tour length: " << Tourlength << std::endl;

    // 显示图像
    cv::imshow("Best Tour", img);
    cv::waitKey(0);

    // 存储图像
    cv::imwrite("../image/Best_Tour.png", img);

    return 0;
}

