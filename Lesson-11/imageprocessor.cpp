#include "imageprocessor.h"

ImageProcessor::ImageProcessor(QObject *parent) : QObject(parent) {}

void ImageProcessor::setImage(const QImage& image)
{
    m_image = image;
}

void ImageProcessor::setFilterType(FilterType type)
{
    filterType = type;
}

QImage ImageProcessor::applyBlurFilter(const QImage& image)
{
    QImage result = image;

    for (int y = 1; y < result.height() - 1; ++y) {
        for (int x = 1; x < result.width() - 1; ++x) {
            QColor color1 = result.pixelColor(x - 1, y);
            QColor color2 = result.pixelColor(x + 1, y);
            QColor color3 = result.pixelColor(x, y - 1);
            QColor color4 = result.pixelColor(x, y + 1);
            QColor centerColor = result.pixelColor(x, y);

            int avgRed = (color1.red() + color2.red() + color3.red() + color4.red() + centerColor.red()) / 5;
            int avgGreen = (color1.green() + color2.green() + color3.green() + color4.green() + centerColor.green()) / 5;
            int avgBlue = (color1.blue() + color2.blue() + color3.blue() + color4.blue() + centerColor.blue()) / 5;

            result.setPixelColor(x, y, QColor(avgRed, avgGreen, avgBlue));
        }
    }
    return result;
}

QImage ImageProcessor::applyInvertFilter(const QImage &image) {
    QImage result = image;

    for (int y = 0; y < result.height(); ++y) {
        for (int x = 0; x < result.width(); ++x) {
            QColor color = result.pixelColor(x, y);

            color.setRed(255 - color.red());
            color.setGreen(255 - color.green());
            color.setBlue(255 - color.blue());

            result.setPixelColor(x, y, color);
        }
    }
    return result;
}

QImage ImageProcessor::applySepiaFilter(const QImage &image) {
    QImage result = image;

    for (int y = 0; y < result.height(); ++y) {
        for (int x = 0; x < result.width(); ++x) {
            QColor color = result.pixelColor(x, y);

            int tr = (color.red() * 0.393) + (color.green() * 0.769) + (color.blue() * 0.189);
            int tg = (color.red() * 0.349) + (color.green() * 0.686) + (color.blue() * 0.168);
            int tb = (color.red() * 0.272) + (color.green() * 0.534) + (color.blue() * 0.131);

            color.setRed(qBound(0, tr, 255));
            color.setGreen(qBound(0, tg, 255));
            color.setBlue(qBound(0, tb, 255));

            result.setPixelColor(x, y, color);
        }
    }
    return result;
}

QImage ImageProcessor::applyGrayscaleFilter(const QImage& image)
{
    QImage result = image;

    for(int y = 0; y < result.height(); ++y)
    {
        for(int x = 0; x < result.width(); ++x)
        {
            QColor color = result.pixelColor(x, y);

            int gray = qGray(color.red(), color.green(), color.blue());

            color.setRed(gray);
            color.setBlue(gray);
            color.setGreen(gray);

            result.setPixelColor(x, y, color);
        }
    }


    return result;
}

void ImageProcessor::processImage()
{
    QImage processedImage;

    switch(filterType)
    {
    case Sepia:
        processedImage = applySepiaFilter(m_image);
        break;
    case Grayscale:
        processedImage = applyGrayscaleFilter(m_image);
        break;
    case Blur:
        processedImage = applyBlurFilter(m_image);
        break;
    case Invert:
        processedImage = applyInvertFilter(m_image);
        break;
    }

    emit processingDone(processedImage);
}
