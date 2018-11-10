#ifndef CPUWORKER_H
#define CPUWORKER_H

#include <QObject>
#include <QBitArray>
#include <QByteArray>
#include <QElapsedTimer>
#include <QMutex>
#include <QMutexLocker>
#include <QCoreApplication>
#include <QEventLoop>
#include <QDebug>

#define RAM_SIZE 4096
#define START_ADDR 0x200
#define DISPLAY_X 64
#define DISPLAY_Y 32


class CPUWorker : public QObject
{
    Q_OBJECT

public:
    explicit CPUWorker(QObject *parent = nullptr);


signals:
    void ReadyToWork(bool flag);
    void finished();
    void updateScreen(QBitArray screen);
    void updateScreenTxt(QString text);


public slots:
    void setRom(QByteArray data);
    void start();
    void stop();
    void debugSetRom();
    void testSlot();

private:
    void doEmulationLoop();
    void closeRom();

    QMutex* m_mutex;

    bool m_stopped;
    QBitArray m_screen;
    QByteArray m_memory;
    unsigned short PC;   // mem offset counter
    unsigned short regI; // address register I
    unsigned short delay_timer;               //  delay timer;
    unsigned short  sound_timer; //  sound timer;
    int opcode_count;
};

#endif // CPUWORKER_H
