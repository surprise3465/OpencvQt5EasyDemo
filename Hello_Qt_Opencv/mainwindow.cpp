#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLibrary>
#include <QPluginLoader>
#define FILTERS_SUBFOLDER "/filter_plugins/"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();

    turkishTranslator = new QTranslator(this);
    turkishTranslator->load(":/translations/translation_tr.qm");

    germanTranslator = new QTranslator(this);
    germanTranslator->load(":/translations/translation_de.qm");
    getPluginsList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputPushButton_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Input Image"), QDir::currentPath(), tr("Images") + " (*.jpg *.png *.bmp)");
    if(QFile::exists(fileName))
    {
        ui->inputLineEdit->setText(fileName);
    }
}

void MainWindow::on_outputPushButton_pressed()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Select Output Image"), QDir::currentPath(), "*.jpg;;*.png;;*.bmp");
    if(!fileName.isEmpty())
    {
        ui->outputLineEdit->setText(fileName);
        using namespace cv;

        Mat inpImg, outImg;
        inpImg = imread(ui->inputLineEdit->text().toStdString());
        QPluginLoader qPluginloader(qApp->applicationDirPath() + FILTERS_SUBFOLDER + ui->filtersList->currentItem()->text());
        CvPluginInterface* plugin = dynamic_cast<CvPluginInterface*>(qPluginloader.instance());

        using namespace cv;
        plugin->processImage(inpImg,outImg);

        imwrite(fileName.toStdString(), outImg);
        if(ui->displayImageCheckBox->isChecked())
            imshow(tr("Output Image").toStdString(), outImg);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::warning(this, tr("Exit"), tr("Are you sure you want to close this program?"), QMessageBox::Yes, QMessageBox::No);
    if(result == QMessageBox::Yes)
    {
        saveSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::loadSettings()
{
    QSettings settings("Packt", "Hello_OpenCV_Qt", this);
    ui->inputLineEdit->setText(settings.value("inputLineEdit", "").toString());
    ui->outputLineEdit->setText(settings.value("outputLineEdit", "").toString());

    ui->displayImageCheckBox->setChecked(settings.value("displayImageCheckBox", false).toBool());
}

void MainWindow::saveSettings()
{
    QSettings settings("Packt", "Hello_OpenCV_Qt", this);
    settings.setValue("inputLineEdit", ui->inputLineEdit->text());
    settings.setValue("outputLineEdit", ui->outputLineEdit->text());
    settings.setValue("displayImageCheckBox", ui->displayImageCheckBox->isChecked());
}

void MainWindow::getPluginsList()
{
    QDir filtersDir(qApp->applicationDirPath() + FILTERS_SUBFOLDER);
    QFileInfoList filters = filtersDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    foreach(QFileInfo filter, filters)
    {
        if(QLibrary::isLibrary(filter.absoluteFilePath()))
        {
            QPluginLoader pluginLoader(filter.absoluteFilePath(), this);
            if(dynamic_cast<CvPluginInterface*>(pluginLoader.instance()))
            {
                ui->filtersList->addItem(filter.fileName());
                pluginLoader.unload(); // we can unload for now
            }
            else
            {
                QMessageBox::warning(this, tr("Warning"),
                                     QString(tr("Make sure %1 is a correct plugin for this application<br>"
                                                "and it's not in use by some other application!")).arg(filter.fileName()));
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Warning"),
                                 QString(tr("Make sure only plugins exist in plugins folder.<br>"
                                            "%1 is not a plugin.")).arg(filter.fileName()));
        }
    }

    if(ui->filtersList->count() <= 0)
    {
        QMessageBox::critical(this, tr("No Plugins"), tr("This application cannot work without plugins!"
                                                         "<br>Make sure that filter_plugins folder exists "
                                                         "in the same folder as the application<br>and that "
                                                         "there are some filter plugins inside it"));
        this->setEnabled(false);
    }
};

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
    else
    {
        QMainWindow::changeEvent(event);
    }
}

void MainWindow::on_actionTurkish_triggered()
{
    qApp->installTranslator(turkishTranslator);
}

void MainWindow::on_actionGerman_triggered()
{
    qApp->installTranslator(germanTranslator);
}

void MainWindow::on_actionEnglish_triggered()
{
    qApp->removeTranslator(turkishTranslator);
    qApp->removeTranslator(germanTranslator);
}
