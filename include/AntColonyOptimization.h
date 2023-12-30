#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <limits>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct Ant ;

// 初始化蚂蚁
void initializeAnts(std::vector<Ant>& ants, int numAnts, int numCities) ;

// 蚁群算法
std::vector<int> antColonyOptimization(const std::vector<Point>& points, int numAnts, int maxIterations, double alpha, double beta, double evaporationRate, double Q,std::mt19937 generator) ;

// 选择下一个城市
int selectNextCity(const std::vector<Point>& points, const Ant& ant, const std::vector<std::vector<double>>& pheromones, int currentCity, double alpha, double beta, int numCities,std::mt19937 generator) ;

// 更新信息素浓度
void updatePheromones(std::vector<std::vector<double>>& pheromones, const std::vector<Ant>& ants, double evaporationRate, double Q) ;

// 计算路径长度
double tourLength(const std::vector<Point>& points, const std::vector<int>& tour) ;

// 计算两点之间的距离
double calculateDistance(const Point& p1, const Point& p2) ;

// 找到最佳路径
std::vector<int> findBestTour(const std::vector<Ant>& ants, const std::vector<Point>& points) ;




