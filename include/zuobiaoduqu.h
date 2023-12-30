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