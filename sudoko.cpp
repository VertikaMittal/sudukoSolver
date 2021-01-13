#include "opencv2/opencv.hpp"

int main()
{
    cv::Mat src = cv::imread("im.png", CV_LOAD_IMAGE_UNCHANGED);
    double angle = -45;

    cv::Point2f center((src.cols-1)/2.0, (src.rows-1)/2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
    
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
    
    rot.at<double>(0,2) += bbox.width/2.0 - src.cols/2.0;
    rot.at<double>(1,2) += bbox.height/2.0 - src.rows/2.0;

    cv::Mat dst;
    cv::warpAffine(src, dst, rot, bbox.size());
    cv::imwrite("rotated_im.png", dst);

    return 0;
}