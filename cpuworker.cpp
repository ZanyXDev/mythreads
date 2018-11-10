#include "cpuworker.h"

CPUWorker::CPUWorker(QObject *parent) : QObject(parent)
{
    m_mutex = new QMutex();
    m_stopped = false;

    closeRom();
}

void CPUWorker::start()
{

    QElapsedTimer et;
    et.start();
    opcode_count = 0;

    m_stopped = false;

    while (true){
        QCoreApplication::processEvents( QEventLoop::AllEvents );
        opcode_count ++;
        // Execute  decode next OpCode

        //decrease timers every 1/60sec and redraw screen
        if (et.hasExpired(1000/60)) {
            et.restart();
            //emit updateScreen(m_screen);
            emit updateScreenTxt( QString("%1").arg(opcode_count));
            opcode_count = 0;
        }
        // check to see if we were stopped
        {
            QMutexLocker locker(m_mutex);
            if (m_stopped){
                closeRom();
                break;
            }
        }
        // locker goes out scope and releases the mutex

    }
}

void CPUWorker::stop()
{
    QMutexLocker locker(m_mutex);
    m_stopped = true;
}

void CPUWorker::setRom(QByteArray data)
{
    qDebug() << "load: " << data.size() << " bytes";
    if ( !data.isEmpty() &&
         ( data.size() <= RAM_SIZE - START_ADDR)  ) {
        m_memory.insert(START_ADDR,data);
        emit ReadyToWork(true);
    }
}


void CPUWorker::debugSetRom()
{
    emit ReadyToWork(true);
}

void CPUWorker::testSlot()
{
    qDebug() << "test slot cpuworker";
}

void CPUWorker::doEmulationLoop()
{

}

void CPUWorker::closeRom()
{
    PC = START_ADDR;
    regI = START_ADDR;
    m_screen = QBitArray(DISPLAY_X * DISPLAY_Y,false);  // clear screen map
    m_memory.fill(0x0,RAM_SIZE);   // clear 4k ram memory
    delay_timer = 0;               // clear delay timer;
    sound_timer = 0;               // clear sound timer;
    opcode_count = 0;

    emit ReadyToWork( false );
}
