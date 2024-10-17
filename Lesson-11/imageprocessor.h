#pragma once

#include <QObject>
#include <QImage>

class ImageProcessor : public QObject
{
    Q_OBJECT

public:
    enum FilterType { Sepia, Grayscale, Invert, Blur };
    explicit ImageProcessor(QObject *parent = nullptr);
    void setImage(const QImage& image);

    QImage applyFilter(); // main logic

    void setFilterType(FilterType type);

signals:
    void processingDone(const QImage &processedImage);

public slots:
    void processImage();

private:

    QImage applySepiaFilter(const QImage& image);
    QImage applyGrayscaleFilter(const QImage& image);
    QImage applyInvertFilter(const QImage& image);
    QImage applyBlurFilter(const QImage& image);

    QImage m_image;
    FilterType filterType;
};
