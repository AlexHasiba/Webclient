#include "webclient.h"
#include <thread>

Webclient::Webclient(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(hostname, &QLineEdit::returnPressed, this, &Webclient::on_los_clicked);

    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &Webclient::connected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Webclient::read);
}


void Webclient::on_los_clicked()
{
    if(!hostname->text().isEmpty())
    {
        m_ip = hostname->text();

        m_socket->connectToHost(m_ip, m_port);
        if(!m_socket->waitForConnected(5000))
        {
            screan->setText(m_ip + ":dauert zu lang!!!");
            m_socket->reset();
        }
    }
    else screan->setText("Eingabe is nicht da!!!");
}

void Webclient::connected()
{
    m_socket->write(QString("GET / HTTP/1.1\r\nHost:" + m_ip + "\r\n\r\n").toLocal8Bit());
}

void Webclient::read()
{

    screan->setText(m_socket->readAll());
    m_socket->disconnectFromHost();
}
