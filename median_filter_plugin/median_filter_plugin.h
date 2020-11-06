#ifndef MEDIAN_FILTER_PLUGIN_H
#define MEDIAN_FILTER_PLUGIN_H

#include "median_filter_plugin_global.h"

#include "cvplugininterface.h"

class MEDIAN_FILTER_PLUGINSHARED_EXPORT Median_filter_plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.amin.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Median_filter_plugin();
    ~Median_filter_plugin();
    QString title();
    QString version();
    QString description();
    QString help();
    void processImage(const cv::Mat &inputImage, cv::Mat &outputImage);
};

#endif // MEDIAN_FILTER_PLUGIN_H
