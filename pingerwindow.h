#ifndef PINGERWINDOW_H
#define PINGERWINDOW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class PingerWindow;
}

class PingerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PingerWindow(QWidget *parent = 0);
    QProcess ping;
    ~PingerWindow();

private:
    Ui::PingerWindow *ui;

public slots:
    void readyRead();
    void changeHost();
    void stop();
    void enaStop();
    void disaStop(int code);
};

#endif // PINGERWINDOW_H
