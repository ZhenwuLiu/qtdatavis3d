/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Data Visualization module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef DATA_H
#define DATA_H

#include "axesinputhandler.h"

#include <QtDataVisualization/q3dscatter.h>
#include <QtGui/QVector3D>

using namespace QtDataVisualization;

class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(Q3DScatter *scatter);
    ~Data();

    void toggleRanges();

private:
    void addData();
    QVector3D randVector();

private:
    Q3DScatter *m_graph;
    AxesInputHandler *m_inputHandler;
    bool m_autoAdjust;
};

#endif
