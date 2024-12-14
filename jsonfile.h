#ifndef JSONFILE_H
#define JSONFILE_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <iostream>
#include <QList>
#include "globals.h"

struct Prop
{
    QString x;
    QString y;
    QString w;
    QString h;
    QString text;
    QString size;
    QString var;
    QString txtcolor;
    QString imgcolor;
};

struct Components
{
    QString guid;
    QString name;
    int type;
    Prop prop;
};

struct Setting
{
    int resolutionw;
    int resolutionh;
    QString bgurl;
};

class Layout
{
public:
    QString guid;
    QString name;
    int type;
    Setting setting;
    QList<Components> components;
};

class JsonFile
{
public:
    JsonFile();
    bool ReadJsonFile(const QString &filePath);
private:
    QJsonObject m_jsonobject;
    QList<Layout> m_layout_list;
};
#endif // JSONFILE_H
