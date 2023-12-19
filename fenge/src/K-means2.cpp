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
    Mat samples(nonWhiteCoords.size(), 2, CV_32F);
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

    // 定义褐色与灰色
    Vec3b brown(19, 69, 139); // BGR格式
    Vec3b gray(128, 128, 128); // BGR格式

    // 创建一个新的图像，用于可视化聚类结果
    Mat clusteredImg = img.clone();

    // 根据聚类结果填充颜色
    for (size_t i = 0; i < nonWhiteCoords.size(); i++) {
        int clusterIdx = labels.at<int>(i);
        Point2i pos = nonWhiteCoords[i];
        clusteredImg.at<Vec3b>(pos) = (clusterIdx == 0) ? brown : gray;
    }

    // 显示图像
    imshow("Original Image", img);
    imshow("Clustered Image", clusteredImg);
    waitKey(0);

    return 0;
}
