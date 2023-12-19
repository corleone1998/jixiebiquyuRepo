#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 加载图像
    Mat img = imread("../../tuxiang/build/Stained_area.png");
    if (img.empty()) {
        cout << "Could not read the image" << endl;
        return 1;
    }

    // 将图像转换为二维样本数据
    Mat samples(img.rows * img.cols, 3, CV_32F);
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            for (int z = 0; z < 3; z++) {
                samples.at<float>(y + x * img.rows, z) = img.at<Vec3b>(y, x)[z];
            }
        }
    }

    // 应用k-means算法
    int clusterCount = 2;
    Mat labels;
    int attempts = 5;
    Mat centers;
    kmeans(samples, clusterCount, labels, TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0), attempts, KMEANS_PP_CENTERS, centers);

    // 用聚类中心的颜色替换图像中的每个像素
    Mat new_image(img.size(), img.type());
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            int cluster_idx = labels.at<int>(y + x * img.rows, 0);
            new_image.at<Vec3b>(y, x)[0] = centers.at<float>(cluster_idx, 0);
            new_image.at<Vec3b>(y, x)[1] = centers.at<float>(cluster_idx, 1);
            new_image.at<Vec3b>(y, x)[2] = centers.at<float>(cluster_idx, 2);
        }
    }

    // 显示原始图像和聚类后的图像
    imshow("original image", img);
    imshow("clustered image", new_image);
    //cv::imwrite("Clustered_area", new_image);
    waitKey(0);

    return 0;
}
