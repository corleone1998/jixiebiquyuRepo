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

// 分类绘制蚁群路线图像
Mat lujinghuoqu(const std::pair<std::vector<Point>, std::vector<Point>>& class_Points, const std::vector<int>& BestTour_forall_1, const std::vector<int>& BestTour_forall_2, Mat img)
{

    // 输出最佳路径

    // 第一条路径
    std::cout << "Best tour_1: ";
    for (int idx : BestTour_forall_1) 
    {
        std::cout << idx << "==>";
        //绘制路径
        cv::line(img, class_Points.first[BestTour_forall_1[idx]], class_Points.first[BestTour_forall_1[idx + 1]], cv::Scalar(0, 0, 255), 2); //2是指像素宽度
    }
        // 绘制路径的最后一条边
        cv::line(img, class_Points.first[BestTour_forall_1.back()], class_Points.first[BestTour_forall_1[0]], cv::Scalar(0, 0, 255), 2);
    
    std::cout << std::endl; // 换行

    // 第二条路径
    std::cout << "Best tour_2: ";
    for (int idx : BestTour_forall_2) 
    {
        std::cout << idx << "==>";
        //绘制路径
        cv::line(img, class_Points.second[BestTour_forall_2[idx]], class_Points.second[BestTour_forall_2[idx + 1]], cv::Scalar(255, 0, 0), 2); //2是指像素宽度
    }
        // 绘制路径的最后一条边
        cv::line(img, class_Points.second[BestTour_forall_2.back()], class_Points.second[BestTour_forall_2[0]], cv::Scalar(255, 0, 0), 2);
    
    // 可以依次执行更多条路径的路线绘制........

    double Tourlength_1 = tourLength(class_Points.first, BestTour_forall_1);
    double Tourlength_2 = tourLength(class_Points.second, BestTour_forall_2);

    std::cout << std::endl; // 换行

    // 输出第一条最佳路径长度
    std::cout << "Tour length_1: " << Tourlength_1 << std::endl;
    // 输出第二条最佳路径长度
    std::cout << "Tour length_2: " << Tourlength_2 << std::endl;

    // 返回画出路线的图
    return img;
}


int main() 
{
    // 读取图像
    Mat img = imread("../../fenge/image/Center_clustered_area30.png");
    // 检查图像是否正确加载
    if (img.empty()) 
     {
         cout << "Could not read the image" << endl;
         return 1;
     }

    // 从文本文件中分类读取坐标点
    //std::vector<Point> points = readPointsFromFile("../../fenge/classified_points.txt");
    // 从文本文件中分类读取坐标点,使用std::pair
    std::pair<std::vector<Point>, std::vector<Point>> classPoints = readClassPointsFromFile("../../fenge/classified_points30.txt");
    // 获取分类数组
    std::vector<Point> PointsClass1 = classPoints.first;
    std::vector<Point> PointsClass2 = classPoints.second;



        // 设置第一类初始参数
        int numAnts_1 = 50, maxIterations_1 = 1000; // 蚂蚁数量，最大迭代次数
        double alpha_1 = 1, beta_1 = 1, Q_1 = 10, evaporationRate_1 = 0.1; //信息素影响因子alpha，启发式影响因子beta，信息素挥发速率evaporationRate
        // 设置第二类初始参数
        int numAnts_2 = 50, maxIterations_2 = 1000; 
        double alpha_2 = 1, beta_2 = 1, Q_2 = 10, evaporationRate_2 = 0.1;

        // std::random_device rd;  // 获取一个随机设备用于种子
        // std::mt19937 generator(rd());  // 使用 Mersenne Twister 引擎和随机设备生成种子

        // 执行蚁群算法进行路径规划
        std::vector<int> BestTour_forall_1 = antColonyOptimization(PointsClass1, numAnts_1, maxIterations_1, alpha_1, beta_1, evaporationRate_1, Q_1);
        std::vector<int> BestTour_forall_2 = antColonyOptimization(PointsClass2, numAnts_2, maxIterations_2, alpha_2, beta_2, evaporationRate_2, Q_2);
        // // 输出最佳路径
        //  std::cout << "Best tour: ";
        //  for (int idx : BestTour_forall) 
        //  {
        //   std::cout << idx << " ";
        //  //绘制路径
        // cv::line(img, PointsClass1[BestTour_forall[idx]], PointsClass1[BestTour_forall[idx + 1]], cv::Scalar(0, 0, 255), 2); //2是指像素宽度
        // }
        //  // 绘制路径的最后一条边
        //  cv::line(img, PointsClass1[BestTour_forall.back()], PointsClass1[BestTour_forall[0]], cv::Scalar(0, 0, 255), 2);

        // double Tourlength = tourLength(PointsClass1, BestTour_forall);
        // std::cout << std::endl;
        // // 输出最佳路径长度
        // std::cout << "Tour length: " << Tourlength << std::endl;
        Mat img_lujinghuoqu = lujinghuoqu(classPoints, BestTour_forall_1, BestTour_forall_2, img);
    
    // 显示图像
    cv::imshow("Best Tour", img_lujinghuoqu);
    cv::waitKey(0);

    // 存储图像
    cv::imwrite("../image/Best_Tour30,1.png", img_lujinghuoqu);

    return 0;
}

