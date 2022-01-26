#ifndef WEBCLIENT_H
#define WEBCLIENT_H

#include "ui_webclient.h"
#include <QAbstractSocket>
#include <QTcpSocket>

class Webclient : public QWidget, private Ui::Webclient
{
    Q_OBJECT

public:
    explicit Webclient(QWidget *parent = nullptr);
private slots:
    void on_los_clicked();



private:

    void connected();
    void read();

private:
    QTcpSocket* m_socket;
    QString m_ip;

    unsigned char m_port = 80;
};

#endif // WEBCLIENT_H
