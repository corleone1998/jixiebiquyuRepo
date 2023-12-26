#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>

using namespace cv;
using namespace std;

int main() {
    // 读取图像
    Mat img = imread("../../tuxiang/image/Stained_area.png");
        // 检查图像是否正确加载
    if (img.empty()) {
        cout << "Could not read the image" << endl;
        return 1;
    }

    // 读取中心点
        std::ifstream infile("../../zhongxindian/centroids.txt");
        std::string line;
        std::vector<cv::Point2i> centerPoints;
        
        // 读取文件中的每一行
        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string x, y;
            
            // 使用逗号作为分隔符
            std::getline(ss, x, ',');
            std::getline(ss, y);
            
            // 将字符串转换为整数
            int ix = std::stoi(x);
            int iy = std::stoi(y);
            
            // 创建Point2i对象并添加到向量中
            centerPoints.push_back(cv::Point2i(ix, iy));
        }
        
        // 关闭文件
        infile.close();

    // 创建一个向量来存储所有非白色像素点的坐标
    vector<Point2f> nonWhiteCoords;
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            Vec3b color = img.at<Vec3b>(y, x);
            // 检查像素是否不是白色
            if (color != Vec3b(255, 255, 255)) {
                // 将非白色像素的坐标添加到列表中
                nonWhiteCoords.push_back(Point2f(x, y));
            }
        }
    }

    // 将非白色像素点的坐标转换为Mat对象
    Mat samples(nonWhiteCoords.size(), 2, CV_32F); // 默认单通道
    for (size_t i = 0; i < nonWhiteCoords.size(); ++i) {
        samples.at<float>(i, 0) = nonWhiteCoords[i].x;
        samples.at<float>(i, 1) = nonWhiteCoords[i].y;
    }

    // 应用k-means聚类
    int clusterCount = 2; // 分成两类
    Mat labels;
    int attempts = 5;
    Mat centers;
    kmeans(samples, clusterCount, labels, TermCriteria(TermCriteria::MAX_ITER | TermCriteria::EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);

    // //根据聚类结果把中心点进行分类
    // for (size_t i = 0; i < nonWhiteCoords.size(); i++)
    // {
        
    //     Point2i pos = nonWhiteCoords[i];
    //     for (size_t c = 0; i < centerPoints.size(); i++)
    //     {
    //         if (centerPoints[i] == pos)

    //     }
        
    // }
    

    // 定义褐色与灰色
    Vec3b brown(19, 69, 139); // BGR格式，3b表示3个无符号字符元素
    Vec3b gray(128, 128, 128); // BGR格式

    // 创建一个新的图像，用于可视化聚类结果
    Mat clusteredImg = img.clone();

    // 根据聚类结果填充颜色
    for (size_t i = 0; i < nonWhiteCoords.size(); i++) {
        int clusterIdx = labels.at<int>(i);
        Point2i pos = nonWhiteCoords[i]; //这行代码声明了一个 Point2i 类型的变量 pos，
                                                            // 并将其初始化为 nonWhiteCoords 向量中索引为 i 的元素的值。Point2i 是 OpenCV 中的一个数据结构，
                                                            // 用于表示二维空间中的点，其中 2i 表示点的坐标是整数类型（通常是 int 类型）。
                                                            // 这里，nonWhiteCoords[i] 返回一个 Point2f 类型的对象，它被隐式转换为 Point2i 类型，
                                                            // 因为 Point2f 和 Point2i 之间的转换通常是自动的（浮点数坐标被转换为整数坐标）。
        clusteredImg.at<Vec3b>(pos) = (clusterIdx == 0) ? brown : gray;
    }

    // 显示图像
    imshow("Original Image", img);
    imshow("Clustered Image", clusteredImg);
    waitKey(0);
    // 储存图片
     cv::imwrite("../image/Clustered_area.png", clusteredImg);

    return 0;
}
