#include "debugdialog.h"
#include "ui_debugdialog.h"

DebugDialog::DebugDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DebugDialog)
{
    ui->setupUi(this);
    timer=new QTimer();
    connect(timer,&QTimer::timeout,this,&DebugDialog::on_RefreshBtn_clicked);
}

DebugDialog::~DebugDialog()
{
    delete ui;
}

void DebugDialog::on_pushButton_clicked()
{
    QString str="",msg="";
    for(auto item:Globals::getInstance()->GetVarList())
    {
        sReadVarPar var;
        var.addr=item.idaddr;
        var.length=item.length;
        var.num=1;
        var.type=item.type;
        sReadVarRet ret = Globals::getInstance()->ReadVar(var);
        switch (ret.type) {
        case 'I':
        case 'O':
            if(item.idaddr<800)
                continue;
            str=QString::number(ret.value[0]);
            break;

        case 'i':
        case 'o':
            if(item.idaddr<50)
                continue;
            str=QString::number((ret.value[0]<<8)+ret.value[1]);
            break;

        case 'N':
            if(item.idaddr<25)
                continue;
            str=QString::number((ret.value[0]<<24)
                                  +(ret.value[1]<<16)
                                  +(ret.value[2]<<8)
                                  +(ret.value[3]));
            break;

        case 'F':
        {
            if(item.idaddr<25)
                continue;
            uint8_t ch[4];
            ch[0]=ret.value[0];
            ch[1]=ret.value[1];
            ch[2]=ret.value[2];
            ch[3]=ret.value[3];
            str=QString::number(*((float*)ch));
        }
        break;

        case 'M':
        {
            if(item.idaddr<100)
                continue;
            char *lstr=new char[ret.value.size()];
            for(int i=0;i<ret.value.size();i++)
            {
                lstr[i]=ret.value[i];
            }
            str=QString(lstr);
            delete lstr;
        }
        break;

        default:
            break;
        }
        msg+=(item.idname+":"+str+"\r");
    }
    ui->textEdit->setText(msg);
    if(timer->isActive())
        timer->stop();
    else
        timer->start(1000);
}

void DebugDialog::on_RefreshBtn_clicked()
{
    int x=370,y=10,w=100,h=25,dw=10,dh=5;
    for(auto item:m_btn_list)
        delete item;
    m_btn_list.clear();
    for(auto item:m_line_list)
        delete item;
    m_line_list.clear();
    for(auto var_unit:Globals::getInstance()->GetVarList())
    {
        //按键布局
        QPushButton *pushbtn=new QPushButton(this);
        pushbtn->setGeometry(x,y+h+dh,w,h);
        //编辑属性
        pushbtn->setObjectName(var_unit.idname);
        pushbtn->setText(var_unit.idname);
        connect(pushbtn,&QPushButton::clicked,[=](){
            QList<QLineEdit*>object_list=this->findChildren<QLineEdit*>();
            for(auto line_edit_unit:object_list)
            {
                if(line_edit_unit->objectName()==pushbtn->objectName())
                {
                    QLineEdit *lineedit=line_edit_unit;
                    sWriteVarPar par;
                    par.addr=var_unit.idaddr;
                    par.length=var_unit.length;
                    par.type=var_unit.type;
                    switch (par.type) {
                    case 'I':
                    case 'O':
                        par.value.push_back(lineedit->text().toUInt()&0x01);
                        break;

                    case 'i':
                    case 'o':
                        par.value.push_back((lineedit->text().toUInt()>>8)&0xff);
                        par.value.push_back(lineedit->text().toUInt()&0xff);
                        break;

                    case 'N':
                        par.value.push_back((lineedit->text().toUInt()>>24)&0xff);
                        par.value.push_back((lineedit->text().toUInt()>>16)&0xff);
                        par.value.push_back((lineedit->text().toUInt()>>8)&0xff);
                        par.value.push_back(lineedit->text().toUInt()&0xff);
                        break;

                    case 'F':
                    {
                        uint8_t ch[4];
                        float f=lineedit->text().toFloat();
                        memcpy(ch,&f,sizeof(f));
                        par.value.push_back(ch[0]);
                        par.value.push_back(ch[1]);
                        par.value.push_back(ch[2]);
                        par.value.push_back(ch[3]);
                    }
                        break;

                    case 'M':
                        for(auto item:lineedit->text().toLatin1())
                            par.value.push_back(item);
                    break;

                    default:
                        break;
                    }
                    Globals::getInstance()->WriteVar(par);
                }
            }
        });
        m_btn_list.push_back(pushbtn);
        pushbtn->show();
        //编辑栏布局
        QLineEdit *lineedit=new QLineEdit(this);
        lineedit->setGeometry(x,y,w,h);
        //编辑属性
        lineedit->setObjectName(var_unit.idname);
        switch (var_unit.type) {
        case 'I':
        case 'O':
            lineedit->setText(QString::number(Globals::getInstance()->GetValueToD(var_unit)));
            break;

        case 'i':
        case 'o':
            lineedit->setText(QString::number(Globals::getInstance()->GetValueToA(var_unit)));
            break;

        case 'F':
            lineedit->setText(QString::number(Globals::getInstance()->GetValueToF(var_unit)));
            break;

        case 'N':
            lineedit->setText(QString::number(Globals::getInstance()->GetValueToN(var_unit)));
            break;

        case 'M':
            lineedit->setText(Globals::getInstance()->GetValueToM(var_unit));
            break;

        default:
            break;
        }
        m_line_list.push_back(lineedit);
        lineedit->show();
        //位移
        if(m_btn_list.size()%5==0)
        {
            y+=2*(h+dh);
            x=370;
        }
        else
        {
            x+=(w+dw);
        }
    }
}

