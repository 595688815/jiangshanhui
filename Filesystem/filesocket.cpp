#include "filesocket.h"

FileSocket::FileSocket(QObject *parent)
    : QTcpSocket{parent}
{
    qDebug()<<"filesocket created";
    connect(this,SIGNAL(acceptError),this,SLOT(displayError));
    //connect(this,SIGNAL(readyRead()),this,SLOT(onReceiveProgress()));
    connect(this,SIGNAL(readyRead()),this,SLOT(onReceiveJsonFile()));
    // connect(this, SIGNAL(bytesWritten(qint64)),this, SLOT(onUpdateSendProgress(qint64)));  //may be too late to call this while in loop

    m_timer = new QTimer(this);  //add this to set timer to child of this object,it allows us do not need to sdelete timer
    m_timer->setInterval(72000000); // 30分钟 = 1800000毫秒
    connect(m_timer, &QTimer::timeout, this, &FileSocket::onTimeout);
    connect(this, &QTcpSocket::readyRead, this, &FileSocket::resetTimeout);
    m_timer->start();


    m_fileNameSize = 0;
    m_totalBytes = 0;
    m_bytesReceived = 0;
    m_bytesWritten = 0;
    m_bytesTobeWrite = 0;

    //系统最大为64K，但可以自行修改系统设置
    m_payLoadSize = 64 * 1024;
    m_cmd = 0;
}

FileSocket::~FileSocket()
{
    if (m_timer) {
        m_timer->deleteLater();
    }


    qDebug()<<"FileSocket deconstructed";
}


void FileSocket::resetTimeout() {
    m_timer->start(); // 重置定时器
}

void FileSocket::onTimeout() {
    emit timeout(); // 发射超时信号
}

void FileSocket::onUpdateSendProgress(qint64 numBytes)
{
    //发送文件内容
    m_bytesWritten += numBytes;
    int temp;
    if(m_bytesTobeWrite > 0)
    {
        //100<200?100:200
        // m_outBlock = m_localFile->read(qMin(m_bytesTobeWrite,m_payLoadSize));
        m_outBlock = m_localFile->read(m_bytesTobeWrite);

        temp = this->write((m_outBlock));
        qDebug()<<"temp"<<temp;
        m_bytesTobeWrite -= temp;
        m_outBlock.resize(0);
    }
    else
    {
        if(m_localFile){
            m_localFile->close();
            delete m_localFile;
            m_localFile = nullptr;
        }
    }
    //更新回传进度条
    m_bytesWritten += temp;
    if(m_bytesWritten == m_totalBytes)
    {
        qDebug()<<"execuate clear";
        m_totalBytes = 0;
        m_bytesWritten = 0;
        m_bytesTobeWrite = 0;
        m_cmd = 0;
        m_outBlock.resize(0);
        if(m_localFile){
            m_localFile->close();
            delete m_localFile;
            m_localFile = nullptr;
        }
        // qDebug()<<"test";
    }
}

void FileSocket::onReceiveJsonFile()
{
    QFile file("config.json");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(readAll());
    file.close();
    Globals::getInstance()->Logging("Json File Recv");
}

void FileSocket::onReceiveProgress()
{
    //1.传输大文件时，界面不会卡住
    /*qDebug()<<"receive";
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_6_6);

    //2.如果已接收到的数据小于等于24个字节，保存文件头结构
    if ((m_bytesReceived)<=static_cast<long long>(sizeof(qint64)*3))
    {
        if((this->bytesAvailable()>=static_cast<long long>(sizeof(qint64)*3))&&(m_fileNameSize==0))
        {
            //(1)接收数据总大小和文件名大小和命令
            QByteArray ar1,ar2,ar3;
            in>>m_totalBytes>>m_fileNameSize>>m_cmd;
            in>>ar1>>ar2>>ar3;
            qDebug()<<m_totalBytes;
            qDebug()<<m_fileNameSize;
            qDebug()<<m_cmd;
            qDebug()<<ar1;
            qDebug()<<ar2;
            qDebug()<<ar3;
            m_bytesReceived +=sizeof(qint64)*3;
        }
        if((this->bytesAvailable()>=m_fileNameSize)&&(m_fileNameSize!=0))
        {
            //(2)接收文件名
            in>>m_fileName>>controllername;
            qDebug()<<"controllername"<<controllername;
            m_bytesReceived+=m_fileNameSize;
            m_bytesReceived+=controllername.size();

            //(3)解析命令：收到消息不处理，收到客户端上传命令建立文件
            if(m_cmd == UPLOAD_FILE)
            {
                //创建同名文件
                QString filePath = QCoreApplication::applicationDirPath();
                QDir dir(filePath);
                filePath = dir.absolutePath() +QString("/%1").arg(controllername) + QString("/%1").arg(m_fileName);
                qDebug()<<filePath;

                m_localFile = new QFile(filePath);
                qDebug()<<"m_fileName"<<m_fileName;
                qDebug()<<"filePath"<<filePath;
                qDebug()<<"m_localFile"<<m_localFile;
                if (!m_localFile->open(QFile::WriteOnly)){
                    qDebug() << "FileServer::onReceiveProgress: open file error!";
                    return;
                }
            }
        }
        else
        {
            return;
        }
        qDebug()<<"接收头部数据："<<"总大小"<<m_totalBytes<<"头部大小"<<m_bytesReceived<<"命令"<<m_cmd-3840
                 <<"文件名"<<m_fileName;
    }
    qDebug()<<"m_bytesReceived"<<m_bytesReceived;
    // 如果接收的数据小于总数据，那么写入文件
    if(m_bytesReceived<m_totalBytes) {
        m_bytesReceived+=this->bytesAvailable();
        qDebug()<<"byteavailbale"<<this->bytesAvailable();
        m_inBlock = this->readAll();
        qDebug()<<"m_inBlock.size"<<m_inBlock.size();
        m_localFile->write(m_inBlock);
        m_inBlock.resize(0);
    }

    // 接收数据完成时,字段初始化，防止数据污染
    if (m_bytesReceived == m_totalBytes)
    {
        qDebug()<<"接收文件内容："<<"总大小"<<m_totalBytes<<"已接收"<<m_bytesReceived<<"文件名"<<m_fileName;
        if(m_cmd == UPLOAD_FILE)
        {
            m_localFile->close();
            delete m_localFile;
            m_localFile = nullptr;
            clearVar();
        }

        if(m_cmd == DOWNLOAD_CONFIG){
            qDebug()<<"DOWNLOAD_CONFIG";
            clearVar();
            sendconfigFile();
        }
        if(m_cmd == DOWNLOAD_FILE)
        {
            clearVar();
            sendFile();
        }
    }*/
}

void FileSocket::getRemoteFileList()
{
    QString fileList = QCoreApplication::applicationDirPath() + "/../../tcpFileServerFile/FILELIST.TXT";
    QDir dir(fileList);
    fileList = dir.absolutePath();
    QFile f(fileList);
    QTextStream out(&f);
    if(!f.open(QFile::WriteOnly|QFile::Text))
    {
        qDebug()<<"write FILELIST.TXT error!";
        return;
    }

    QString remotePath = QCoreApplication::applicationDirPath() + "/../../tcpFileServerFile/RemoteFile";
    QDir d(remotePath);
    remotePath = d.absolutePath();
    QDir r(remotePath);
    QStringList str;
    str << "*";
    QFileInfoList files = r.entryInfoList((QStringList)"*",
                                          QDir::Files|QDir::Dirs,QDir::DirsFirst);
    for(int i=0;i<files.count();i++)
    {
        QFileInfo tmpFileInfo = files.at(i);
        QString fileName = tmpFileInfo.fileName();
        //过滤"."和".."
        if(fileName=="."||fileName=="..")
            continue;
        if(tmpFileInfo.isFile())
            //写入TXT中
            out << fileName ;
        else
            continue;
    }
    f.close();
}

void FileSocket::clearVar()
{
    m_fileNameSize = 0;
    m_totalBytes = 0;
    m_bytesReceived = 0;
    m_bytesWritten = 0;
    m_bytesTobeWrite = 0;
    m_inBlock.resize(0);
    m_outBlock.resize(0);
}

QString FileSocket::clearFilePath(QString filePath)
{
    QString fileName = filePath.right(filePath.size() - filePath.lastIndexOf('/')-1);
    return fileName;
}

void FileSocket::displayError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "FileServer::displayError " << socketError;
    this->close();
}

void FileSocket::sendconfigFile(){
    /*qDebug()<<"客户端请求下载远程config文件";
    QString sendFilelocation;
    QString fileList = QCoreApplication::applicationDirPath() + QString("/%1").arg(controllername);     //"/../../tcpFileServerFile/RemoteFile"
    qDebug()<<"fileList:"<<fileList;
    QDir dir(fileList);
    sendFilelocation= dir.absolutePath()+ QString("/%1").arg(m_fileName);
    m_localFile = new QFile(sendFilelocation);
    if(!m_localFile->open(QFile::ReadOnly))
    {
        qDebug()<<"文件打开错误";
    }
    m_totalBytes = m_localFile->size();
    qDebug()<<"m_localFile->size"<<m_localFile->size();
    QDataStream sendOut(&m_outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_7);

    sendOut<<qint64(0)<<qint64(0)<<qint64(0)<<clearFilePath(sendFilelocation);
    //计算文件总大小(总文件大小 = 文件大小 + 文件名大小 + sizeof(qint64)*3))
    m_totalBytes += m_outBlock.size();
    qDebug()<<"发送总文件大小："<<m_totalBytes;

    //将读写操作指向从头开始
    sendOut.device()->seek(0);
    //总长度和文件总长度和命令
    sendOut<<m_totalBytes<<qint64((m_outBlock.size()-sizeof(qint64)*3))<<qint64(UPLOAD_FILE);
    m_cmd = UPLOAD_FILE;

    //修改待发送字节数
    m_bytesTobeWrite = m_totalBytes - this->write(m_outBlock);
    qDebug()<<"m_outBlock.size()"<<m_outBlock.size();

    onUpdateSendProgress(m_outBlock.size());

    m_outBlock.resize(0);*/
}


void FileSocket::sendFile()
{
    /*QString directoryPath = QCoreApplication::applicationDirPath() + QString("/%1").arg(controllername);
    qDebug()<<directoryPath;
    QDir dir(directoryPath);

    // 检查目录是否存在
    if (!dir.exists()) {
        qDebug() << "Directory does not exist!";
        //can be added with error infomation
        return;
    }
    // 获取目录中的所有文件
    QStringList fileName2s = dir.entryList(QDir::Files);

    // 输出文件数量和文件名
    qDebug() << "Number of files:" << fileName2s.size();
    foreach (QString fileName2, fileName2s) {
        qDebug() << fileName2;
    }
    QString sendFilelocation;

    foreach (QString fileName2, fileName2s) {

        qDebug()<<"客户端请求下载远程文件";

        QString fileList = QCoreApplication::applicationDirPath() + QString("/%1").arg(controllername);     //"/../../tcpFileServerFile/RemoteFile"
        qDebug()<<"fileList:"<<fileList;
        QDir dir(fileList);
        sendFilelocation= dir.absolutePath()+ QString("/%1").arg(fileName2);
        // fileList = dir.absolutePath() + QString("/%1").arg(controllername) + QString("/%1").arg(fileName2);
        // m_fileName = fileList;

        qDebug()<<"sendFilelocation"<<sendFilelocation;
        qDebug()<<"发送文件名称："<<fileName2;
        m_localFile = new QFile(sendFilelocation);
        if(!m_localFile->open(QFile::ReadOnly))
        {
            qDebug()<<"文件打开错误";
        }
        m_totalBytes = m_localFile->size();
        qDebug()<<"m_localFile->size"<<m_localFile->size();
        QDataStream sendOut(&m_outBlock,QIODevice::WriteOnly);
        sendOut.setVersion(QDataStream::Qt_5_7);

        sendOut<<qint64(0)<<qint64(0)<<qint64(0)<<clearFilePath(sendFilelocation);
        //计算文件总大小(总文件大小 = 文件大小 + 文件名大小 + sizeof(qint64)*3))
        m_totalBytes += m_outBlock.size();
        qDebug()<<"发送总文件大小："<<m_totalBytes;

        //将读写操作指向从头开始
        sendOut.device()->seek(0);
        //总长度和文件总长度和命令
        sendOut<<m_totalBytes<<qint64((m_outBlock.size()-sizeof(qint64)*3))<<qint64(UPLOAD_FILE);
        m_cmd = UPLOAD_FILE;

        //修改待发送字节数
        m_bytesTobeWrite = m_totalBytes - this->write(m_outBlock);
        qDebug()<<"m_outBlock.size()"<<m_outBlock.size();

        onUpdateSendProgress(m_outBlock.size());

        m_outBlock.resize(0);
    }*/
}
