#include "impls.h"
#include <opencv2/opencv.hpp>
#include <vector>

std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    // IMPLEMENT YOUR CODE HERE
    cv::Mat gray, thresh;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    // 将输入图像转换为灰度图
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    // 对灰度图进行二值化
    cv::threshold(gray, thresh, 100, 255, cv::THRESH_BINARY);

    // 使用 cv::findContours 函数找出所有的轮廓
    cv::findContours(thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    // 遍历轮廓，找到近似为矩形的轮廓
    for (size_t i = 0; i < contours.size(); i++) {
        // 计算轮廓的近似多边形
        std::vector<cv::Point> approx;
        cv::approxPolyDP(contours[i], approx, cv::arcLength(contours[i], true) * 0.02, true);

        // 检查轮廓是否为矩形（4个顶点）
        if (approx.size() == 4) {
            // 计算外接矩形
            cv::Rect boundingRect = cv::boundingRect(contours[i]);

            // 计算最小面积外接矩形
            cv::RotatedRect minAreaRect = cv::minAreaRect(contours[i]);

            // 通常，我们只关心第一个找到的矩形轮廓
            res = std::make_pair(boundingRect, minAreaRect);
            break;
        }
    }
    return res;
}