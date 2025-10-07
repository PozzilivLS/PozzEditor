#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab.h"

class Lab : public QMainWindow
{
    Q_OBJECT

public:
    Lab(QWidget *parent = nullptr);
    ~Lab();

private:
    Ui::LabClass ui;
};

