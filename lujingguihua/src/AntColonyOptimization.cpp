#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <limits>
#include <fstream>
#include <opencv2/opencv.hpp>

#include "AntColonyOptimization.h"

using namespace std;
using namespace cv;

struct Ant 
{
    std::vector<int> tour; // 访问的城市
    std::vector<bool> visited; // 经过与否
    double passLength; // 蚂蚁走过的路径长度
};

// 初始化蚂蚁
void initializeAnts(std::vector<Ant>& ants, int numAnts, int numCities) 
{
    ants.resize(numAnts); //赋值蚂蚁的数量
    for (int i = 0; i < numAnts; ++i) {
        ants[i].tour.resize(numCities + 1); //将蚂蚁i赋值需要访问的城市数量+1（考虑到回到0的情况）
        ants[i].visited.assign(numCities, false); //将一个名为"ants"的数组中的每个元素的visited属性都设置为false。
        // 在这里可以根据需要进行蚂蚁的初始化
    }
}

// 执行蚁群算法
std::vector<int> antColonyOptimization(const std::vector<Point>& points, int numAnts, int maxIterations, double alpha, double beta, double evaporationRate, double Q) 
{
    int numCities = points.size();

    // 初始化信息素浓度
    std::vector<std::vector<double>> pheromones(numCities, std::vector<double>(numCities, 0.1));

    std::vector<Ant> ants;
    initializeAnts(ants, numAnts, numCities);
    std::vector<int> BestTour; // 定义最佳路径
    double bestTourlenth = 0;
    double BestTourlenth = std::numeric_limits<double>::max();//设置为其最大的能表示的值

    // 迭代执行蚁群算法
    for (int iteration = 0; iteration < maxIterations; ++iteration) 
    {
        // 迭代计算
        for (int k = 0; k < numAnts; ++k) 
        {
            ants[k].visited[0] = true; // 出发城市初始化为“已访问”
            ants[k].tour[0] = 0; //从“0”城市出发
            for (int i = 0; i < numCities ; ++i) 
            {
                // 选择下一个城市
                int nextCity = selectNextCity(points, ants[k], pheromones, ants[k].tour[i], alpha, beta, numCities);
                ants[k].tour[i + 1] = nextCity;
                ants[k].visited[nextCity] = true;
                ants[k].passLength +=  calculateDistance(points[ants[k].tour[i]], points[ants[k].tour[i+1]]);// 计算k蚂蚁当前城市与下一个城市之间的距离，记入它的总路程里面
            }
            // 返回起始城市
            ants[k].tour[numCities] = ants[k].tour[0];
            ants[k].passLength +=  calculateDistance(points[ants[k].tour[numCities-1]], points[ants[k].tour[numCities]]);

        // 更新信息素浓度
        updatePheromones(pheromones, ants, evaporationRate, Q); // 调用信息素更新函数
        // 在这里根据蚁群的路径更新信息素浓度，具体实现取决于蚁群算法的策略
        }
        // 找到最佳路径的蚂蚁代号
        int bestTourIndex = findBestTour(ants, points);
        bestTourlenth = ants[bestTourIndex].passLength;
        //比较每次迭代时的最短路径，找到全部迭代中最短的那条路径
        if(bestTourlenth<BestTourlenth)
        {BestTour = ants[bestTourIndex].tour;}
        // 最后清除蚂蚁的访问记录与路径长度
        for (int k = 0; k < numAnts; ++k) 
        {
            ants[k].visited.assign(numCities, false);
            //ants[k].tour.clear();  // 清空 ants.tour
            ants[k].passLength = 0;// 将 ants.length 设为 0
        }
    }
    return BestTour;
}


// 选择下一个城市
int selectNextCity(const std::vector<Point>& points, const Ant& ant, const std::vector<std::vector<double>>& pheromones, int currentCity, double alpha, double beta, int numCities) 
{
    // 在这里实现蚂蚁选择下一个城市的逻辑，可以使用信息素浓度和启发式因子等进行选择
    //int numCities = points.size();
    std::vector<double> probabilities(numCities, 0.0); //可能性（选择下一个城市时，有多少城市没有被访问就有多少路径，最多有numCities-1个（从城市0出发时））
    double total = 0.0;
    double P = 0;

    for (int i = 0; i < numCities; ++i) 
    {
        if (!ant.visited[i]) 
        {   // 仅计算没有访问过的城市，以城市为对象计算
            double pheromone = std::pow(pheromones[currentCity][i], alpha); // 信息素计算
            double distance = calculateDistance(points[currentCity], points[i]);
            double heuristic = pow(1.0 / distance, beta);  // 简单起见，这里使用了距离的倒数作为启发式信息
            double prob = pheromone * heuristic;
            probabilities[i] = prob; // 访问每个未访问过的城市的可能性大小
            total += prob; // 下一个访问的城市的可能性的总和
            P++;//对没有访问的城市进行记数
        }
    }

    // 根据概率选择下一个城市
    std::random_device rd;  // 获取随机设备的种子
    std::mt19937 generator(rd());  // 使用随机设备生成种子
    std::uniform_real_distribution<double> distribution(0.0, 1.0); //定义一个随机数分布对象
    double rand = (1 + distribution(generator))/ P  ;// 将随机数映射到(1 + distribution(generator))/ P的位置，增加随机性
    double p_t = 0.0;
    for (int i = 0; i < numCities; ++i) 
    {
        p_t = probabilities[i]/total;//0~1
        if (!ant.visited[i]) 
        { //是以蚂蚁为对象
            if (p_t  >= rand) 
            {return i;}
        }
    }

    // 如果出现问题，随机选择一个未访问的城市
        // for (int i = 0; i < numCities; ++i) 
        // {
        //     if (!ant.visited[i]) 
        //     {return i;}
        // }

        // 使用std::max_element找到最大元素的迭代器
        auto maxElement = std::max_element(probabilities.begin(), probabilities.end());
        // 检查最大元素是否存在，并输出
        if (maxElement != probabilities.end()) 
        {
            int maxIndex = std::distance(probabilities.begin(), maxElement); // 获取最大元素的索引
            //if (!ant.visited[maxIndex]) 
            return maxIndex;
        }

    return currentCity;  // 所有都访问过了就回到0城市
    //return -1; //不用返回错误，用执行不到这一步
}

// 更新信息素浓度
void updatePheromones(std::vector<std::vector<double>>& pheromones, const std::vector<Ant>& ants, double evaporationRate, double Q) 
{
    // 信息素挥发
    for (size_t i = 0; i < pheromones.size(); ++i) {
        for (size_t j = 0; j < pheromones[i].size(); ++j) {
            pheromones[i][j] = pheromones[i][j]*(1.0 - evaporationRate); // 信息素挥发
        }
    }

    // 信息素增加
    for (const auto& ant : ants) {
        //ant.passLength = 
        double antPheromoneAmount = Q / ant.passLength; // 根据蚂蚁走过的路径长度计算蚂蚁留下的信息素量
        for (size_t i = 0; i < ant.tour.size() - 1; ++i) {
            int cityA = ant.tour[i];
            int cityB = ant.tour[i + 1];
            pheromones[cityA][cityB] += antPheromoneAmount; // 根据路径长度更新信息素浓度
            //pheromones[cityB][cityA] += antPheromoneAmount; // 由于是无向图，需要更新两个方向上的信息素浓度（这里反向没走过，感觉不用加信息素？）
        }
    }
}

// 计算路径长度
double tourLength(const std::vector<Point>& points, const std::vector<int>& tour) 
{
    double length = 0.0;
    for (size_t i = 0; i < tour.size() -1 ; ++i) //tour本身有回到原点的情况，tour.size()比城市数大1
    {
        length += calculateDistance(points[tour[i]], points[tour[i + 1]]); //tour本身没有回到原点的情况使用
    }
    //    length += calculateDistance(points[tour.back()], points[tour[0]]);
    return length;
}

// 计算两点之间的距离
double calculateDistance(const Point& p1, const Point& p2) 
{
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

// 找到单次迭代中的最佳路径
int findBestTour(const std::vector<Ant>& ants, const std::vector<Point>& points) 
{
    double bestLength = std::numeric_limits<double>::max(); //bestLength 的值将会被设置为 1.79769e+308，这是 double 类型能够表示的最大值。
    // std::vector<int> bestTour;

    // for (const auto& ant : ants) 
    // {
    //     if (ant.passLength < bestLength) 
    //     {
    //         bestLength = ant.passLength;
    //         bestTour = ant.tour;
    //     }
    // }

    // return bestTour;
int bestIndex = -1;  // 初始化为一个无效的索引值

for (int i = 0; i < ants.size(); ++i) 
{
    const auto& ant = ants[i];
    if (ant.passLength < bestLength) 
    {
        bestLength = ant.passLength;
        bestIndex = i;  // 记录满足条件的 ant 的索引值
    }
}

return bestIndex;
}