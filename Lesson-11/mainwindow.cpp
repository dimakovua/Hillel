#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    // Create interface
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setText("Load image pls");

    loadButton = new QPushButton("Load image", this);
    filterButton = new QPushButton("Apply filter", this);
    filterButton->setEnabled(false);

    filterComboBox = new QComboBox(this);
    filterComboBox->addItem("Сепія");
    filterComboBox->addItem("ЧБ");
    filterComboBox->addItem("Інвертування");
    filterComboBox->addItem("Розмиття");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    layout->addWidget(loadButton);
    layout->addWidget(filterComboBox);
    layout->addWidget(filterButton);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    //Connecting buttons
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadImage);
    connect(filterButton, &QPushButton::clicked, this, &MainWindow::applyFilter);

    processor.moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, &processor, &QObject::deleteLater);
    connect(this, &MainWindow::destroyed, &workerThread, &QThread::quit);
    connect(&processor, &ImageProcessor::processingDone, this, &MainWindow::onProcessingDone);

    workerThread.start();
}

MainWindow::~MainWindow()
{
    workerThread.quit();
    workerThread.wait();
}

void MainWindow::loadImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose image", "", "Images (*.png *.jpg *.bmp)");
    if(!fileName.isEmpty())
    {
        currentImage.load(fileName);
        imageLabel->setPixmap(QPixmap::fromImage(currentImage).scaled(imageLabel->size(), Qt::KeepAspectRatio));
        filterButton->setEnabled(true);
    }
}

void MainWindow::applyFilter()
{
    filterButton->setEnabled(false);
    filterComboBox->currentIndex();

    processor.setFilterType(ImageProcessor::FilterType(filterComboBox->currentIndex()));

    processor.setImage(currentImage);
    QMetaObject::invokeMethod(&processor, "processImage", Qt::QueuedConnection);
}

void MainWindow::onProcessingDone(const QImage& processedImage)
{
    currentImage = processedImage;
    imageLabel->setPixmap(QPixmap::fromImage(currentImage).scaled(imageLabel->size(), Qt::KeepAspectRatio));
    filterButton->setEnabled(true);
}
