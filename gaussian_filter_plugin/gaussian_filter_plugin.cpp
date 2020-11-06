#include "Gaussian_filter_plugin.h"


Gaussian_filter_plugin::Gaussian_filter_plugin()
{
}

Gaussian_filter_plugin::~Gaussian_filter_plugin()
{

}

QString Gaussian_filter_plugin::title()
{
    return "";
}

QString Gaussian_filter_plugin::version()
{
    return "";
}

QString Gaussian_filter_plugin::description()
{
    return "This plugin applies Gaussian blur filters to any image."
           " This plugin's goal is to make us more familiar with the"
           " concept of plugins in general.";
}


QString Gaussian_filter_plugin::help()
{
    return "";
}


void Gaussian_filter_plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    cv::GaussianBlur(inputImage, outputImage, cv::Size(5, 5), 1.25);
}
