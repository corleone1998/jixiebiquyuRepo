#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// 从文本文件中读取坐标点
std::vector<Point> readPointsFromFile(const std::string& filename) 
{
    std::vector<Point> points;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Point p;
            char comma;
            if (iss >> p.x >> comma >> p.y) {
                points.push_back(p);
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    return points;
}


// 计算两点之间的距离
double distance(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

// 计算路径长度
double tourLength(const std::vector<Point>& points, const std::vector<int>& tour) {
    double length = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        length += distance(points[tour[i]], points[tour[i + 1]]);
    }
    length += distance(points[tour.back()], points[tour[0]]);
    return length;
}

// 蚁群算法
std::vector<int> antColonyOptimization(const std::vector<Point>& points) {
    // 初始化参数和蚂蚁数量等

    std::vector<int> bestTour; // 存储最佳路径

    // 执行蚁群算法，更新bestTour

    return bestTour;
}

int main() {
    // 从文本文件中读取坐标点
    std::vector<Point> points = readPointsFromFile("../../zhongxindian/centroids.txt");

    // 执行蚁群算法进行路径规划
    std::vector<int> bestTour = antColonyOptimization(points);

    // 输出最佳路径
    std::cout << "Best tour: ";
    for (int idx : bestTour) {
        std::cout << idx << " ";
    }

    double Tourlength = tourLength(points, bestTour);

    std::cout << std::endl;

    // 输出最佳路径长度
    std::cout << "Tour length: " << Tourlength << std::endl;

    return 0;
}
