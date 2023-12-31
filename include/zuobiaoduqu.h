#pragma once
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
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

// 定义读取分类点的点结构体
struct ClassifiedPoints 
{
    int x; 
    int y;
    int category;
};
// 从文本文件中分类读取坐标点，使用std::pair
std::pair<std::vector<Point>, std::vector<Point>> readClassPointsFromFile(const std::string& filename) 
{
    std::ifstream file(filename);
    std::vector<Point> pointsCategory1;
    std::vector<Point> pointsCategory2;
    // ... 可能还有更多的分类数组

    if (file.is_open()) 
    {
        std::string line;
        while (std::getline(file, line)) 
        {
            std::istringstream iss(line);
            int x, y, category;
            char comma;
            if (iss >> x >> comma >> y >> comma >> category) 
            {
                ClassifiedPoints newPoint = {x, y, category};
                if (category == 0) 
                {
                    pointsCategory1.push_back({newPoint.x, newPoint.y});
                } 
                else if (category == 1) 
                {
                    pointsCategory2.push_back({newPoint.x, newPoint.y});
                }
                // ... 可能还有更多的分类判断和数组操作
            }
        }
        file.close();
    } 
    else 
    {
        std::cerr << "Unable to open file" << std::endl;
    }

   // 使用 std::make_pair 返回两个分类的数组
    return std::make_pair(pointsCategory1, pointsCategory2);
}