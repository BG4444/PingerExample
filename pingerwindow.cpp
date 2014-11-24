#include "pingerwindow.h"
#include "ui_pingerwindow.h"

PingerWindow::PingerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PingerWindow)
{
    ui->setupUi(this);
    //Запуск процесса в фоне
    ping.start("ping 127.0.0.1");
    //Привязываем сигналы от кнопок

    connect(ui->pingButton,SIGNAL(clicked()),this,SLOT(changeHost()));
    connect(ui->stopButton,SIGNAL(clicked()),this,SLOT(stop()));
    //Привязываем сигналы от процесса
    connect(&ping,SIGNAL(readyRead()),this,SLOT(readyRead()));   //процесс что-то написал в свой stdout
    connect(&ping,SIGNAL(started()),this,SLOT(enaStop()));       //процесс запустился
    connect(&ping,SIGNAL(finished(int)),this,SLOT(disaStop(int))); //процесс звершил работу

}

PingerWindow::~PingerWindow()
{
    stop();
    delete ui;
}

void PingerWindow::readyRead()
{
    //обработка сигнала о приходе новых данных - вывод их в окно
    ui->pingerOut->appendPlainText(ping.readAll().data());
}

void PingerWindow::changeHost()
{
    //обработка сигнала о необходимости сменить хост
    stop(); //стоп процесса
    ping.start(QString("ping \"%1\"").arg(ui->hostname->text())); //запуск нового процесса
}

void PingerWindow::stop()
{
    //остановка процесса
    if(ping.isOpen())         //если процесс открыт
    {
        ping.terminate();     //прекращаем его
        ping.waitForFinished();   //ждем прекращения
    }
}

void PingerWindow::enaStop()
{
    //делаем кнопку остановки доступной, если процесс запустился
    ui->stopButton->setEnabled(true);
}

void PingerWindow::disaStop(int code)
{
    //после остановки процесса, выводим код возврата в окно
    ui->pingerOut->appendHtml(QString("<i>Return code is %1</i>").arg(code));
    //делаем кнопку остановки недоступной
    ui->stopButton->setDisabled(true);
}
