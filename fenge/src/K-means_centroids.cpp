#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    
        // 读取图像
    Mat img = imread("../../tuxiang/image/Stained_area.png");
        // 检查图像是否正确加载
    if (img.empty()) {
        cout << "Could not read the image" << endl;
        return 1;
    }
    
    // 打开包含坐标点的文件
    std::ifstream infile("../../zhongxindian/centroids.txt");
    std::string line;
    std::vector<cv::Point2f> points;

    // 读取文件中的每一行
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        float x, y;
        char comma;
        ss >> x >> comma >> y; // 读取x值，跳过逗号，然后读取y值
        points.push_back(cv::Point2f(x, y));
        //   if (ss && comma == ',') { // 确保读取成功并且逗号存在
        //     points.push_back(cv::Point2f(x, y));
        // } else {
        //     // 处理错误：如果这里有错误，你可能想要添加一些错误处理的代码
        // }
    }
    infile.close();

    // 将点转换为适合k-means的格式
    cv::Mat data(points.size(), 2, CV_32F);
    for (int i = 0; i < data.rows; ++i) {
        data.at<float>(i, 0) = points[i].x;
        data.at<float>(i, 1) = points[i].y;
    }

    // 应用k-means算法
    int K = 2; // 假设我们有2个类别
    cv::Mat labels;
    cv::Mat centers;
    cv::kmeans(data, K, labels, cv::TermCriteria(TermCriteria::MAX_ITER | TermCriteria::EPS, 10000, 0.0001), 3, cv::KMEANS_PP_CENTERS, centers);

    // 打开新文件用于写入
    std::ofstream outfile("../classified_points.txt");

    // 写入每个点的坐标和类别
    for (int i = 0; i < data.rows; ++i) {
        outfile << points[i].x << "," << points[i].y << "," << labels.at<int>(i, 0) << std::endl;
    }
    outfile.close();
// 将分类好的中心点可视化
        // 定义褐色与灰色
        Vec3b blue(255, 0, 0); // BGR格式，3b表示3个无符号字符元素
        Vec3b orange(0, 165, 255); // BGR格式

        // 创建一个新的图像，用于可视化聚类结果
        Mat clusteredImg = img.clone();

        // 根据聚类结果填充颜色
        for (size_t i = 0; i < points.size(); i++) {
            int clusterIdx = labels.at<int>(i);
            Point2i pos = points[i]; //这行代码声明了一个 Point2i 类型的变量 pos
            //clusteredImg.at<Vec3b>(pos) = (clusterIdx == 0) ? brown : gray;

        // 根据类别选择颜色，并在质点位置画圆
        Scalar color = (clusterIdx == 0) ? blue : orange;
        // 如果有更多类别，可以使用switch语句或者if-else链来选择颜色

        // 在clusteredImg上画圆
        circle(clusteredImg, pos, 10, color, -1); // 半径为10，填充圆

        }


    imshow("Center_clustered_area", clusteredImg);
    waitKey(0);
    // 储存图片
    cv::imwrite("../image/Center_clustered_area.png", clusteredImg);


    std::cout << "Classification complete and saved to 'classified_points.txt'." << std::endl;

    return 0;
}