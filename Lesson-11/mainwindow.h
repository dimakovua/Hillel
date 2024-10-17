#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QImage>
#include <QThread>
#include <QComboBox>

#include "imageprocessor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void loadImage();
    void applyFilter();
    void onProcessingDone(const QImage& processedImage);

private:
    QLabel *imageLabel; // to display image
    QPushButton *loadButton;
    QPushButton *filterButton;
    QComboBox *filterComboBox;

    QImage currentImage;
    QThread workerThread;

    ImageProcessor processor;
};
