#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main() {
    // 读取图像
    Mat img = imread("../../tuxiang/build/Stained_area.png");

    // 检查图像是否正确加载
    if (img.empty()) {
        cout << "Could not read the image" << endl;
        return 1;
    }

    // 将图像转换为浮点型，因为k-means函数需要float类型的数据
    Mat imgFloat;
    img.convertTo(imgFloat, CV_32F);

    // 创建一个向量来存储所有非白色像素点
    vector<Vec3f> nonWhitePixels;
    vector<Point2i> nonWhitePositions; // 记录非白色像素的位置
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            Vec3b color = img.at<Vec3b>(y, x);
            // 检查像素是否不是白色
            if (color != Vec3b(255, 255, 255)) {
                // 将非白色像素添加到列表中
                nonWhitePixels.push_back(imgFloat.at<Vec3f>(y, x));
                nonWhitePositions.push_back(Point2i(x, y));
            }
        }
    }

    // 将非白色像素点的数据转换为Mat对象,这里需要将RGB值转换为坐标值！！！
    Mat samples(nonWhitePixels.size(), 3, CV_32F, nonWhitePixels.data());

    // 应用k-means聚类
    int clusterCount = 2; // 分成两类
    Mat labels;
    int attempts = 5;
    Mat centers;
    kmeans(samples, clusterCount, labels, TermCriteria(TermCriteria::MAX_ITER | TermCriteria::EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);

    // 定义褐色与灰色
    Vec3b brown(19, 69, 139); // BGR格式
    Vec3b gray(128, 128, 128); // BGR格式

    // 创建一个新的图像，用于可视化聚类结果
    Mat clusteredImg = Mat::zeros(img.size(), img.type());

    // 根据聚类结果填充颜色
    for (size_t i = 0; i < nonWhitePositions.size(); i++) {
        int clusterIdx = labels.at<int>(i);
        Point2i pos = nonWhitePositions[i];
        clusteredImg.at<Vec3b>(pos) = (clusterIdx == 0) ? brown : gray;
    }

    // 显示图像
    imshow("Original Image", img);
    imshow("Clustered Image", clusteredImg);
    waitKey(0);

    return 0;
}
