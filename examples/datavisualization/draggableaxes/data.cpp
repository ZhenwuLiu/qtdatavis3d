/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtDataVisualization module.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#include "data.h"

#include <QtDataVisualization/QScatterDataProxy>
#include <QtDataVisualization/Q3DScene>
#include <QtDataVisualization/Q3DCamera>
#include <QtDataVisualization/QScatter3DSeries>
#include <QtDataVisualization/Q3DTheme>

using namespace QtDataVisualization;

const int itemCount = 500;

Data::Data(Q3DScatter *scatter)
    : m_graph(scatter),
      //! [1]
      m_inputHandler(new AxesInputHandler(scatter)),
      //! [1]
      m_autoAdjust(false)
{
    m_graph->activeTheme()->setType(Q3DTheme::ThemeEbony);
    m_graph->activeTheme()->setLabelBorderEnabled(true);
    m_graph->activeTheme()->setLabelBackgroundColor(QColor(QRgb(0x151550)));
    m_graph->activeTheme()->setLabelTextColor(Qt::lightGray);
    m_graph->activeTheme()->setFont(QFont("Arial Black", 30));
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityMedium);
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetIsometricRight);

    m_graph->axisX()->setRange(-20.0f, 20.0f);
    m_graph->axisY()->setRange(-10.0f, 10.0f);
    m_graph->axisZ()->setRange(-20.0f, 20.0f);

    //! [0]
    // Give ownership of the handler to the graph and make it the active handler
    m_graph->setActiveInputHandler(m_inputHandler);
    //! [0]

    //! [2]
    // Give our axes to the input handler
    m_inputHandler->setAxes(m_graph->axisX(), m_graph->axisZ(), m_graph->axisY());
    //! [2]

    addData();
}

Data::~Data()
{
    delete m_graph;
}

void Data::toggleRanges()
{
    if (!m_autoAdjust) {
        m_graph->axisX()->setAutoAdjustRange(true);
        m_graph->axisZ()->setAutoAdjustRange(true);
        m_graph->axisY()->setAutoAdjustRange(true);
        m_inputHandler->setDragSpeedModifier(1.5f);
        m_autoAdjust = true;
    } else {
        m_graph->axisX()->setRange(-20.0f, 20.0f);
        m_graph->axisY()->setRange(-10.0f, 10.0f);
        m_graph->axisZ()->setRange(-20.0f, 20.0f);
        m_inputHandler->setDragSpeedModifier(15.0f);
        m_autoAdjust = false;
    }
}

void Data::addData()
{
    QScatter3DSeries *series = new QScatter3DSeries;
    series->setMesh(QAbstract3DSeries::MeshCube);
    series->setMeshSmooth(true);
    m_graph->addSeries(series);

    QScatter3DSeries *series2 = new QScatter3DSeries;
    series2->setMesh(QAbstract3DSeries::MeshMinimal);
    series2->setMeshSmooth(true);
    m_graph->addSeries(series2);

    QScatter3DSeries *series3 = new QScatter3DSeries;
    series3->setMesh(QAbstract3DSeries::MeshSphere);
    series3->setMeshSmooth(true);
    m_graph->addSeries(series3);

    QScatter3DSeries *series4 = new QScatter3DSeries;
    series4->setMesh(QAbstract3DSeries::MeshBevelCube);
    series4->setMeshSmooth(true);
    m_graph->addSeries(series4);

    QScatter3DSeries *series5 = new QScatter3DSeries;
    series5->setMesh(QAbstract3DSeries::MeshSphere);
    m_graph->addSeries(series5);

    QScatterDataArray *dataArray = new QScatterDataArray;
    dataArray->resize(itemCount);
    QScatterDataItem *ptrToDataArray = &dataArray->first();
    for (int i = 0; i < itemCount; i++) {
        ptrToDataArray->setPosition(randVector());
        ptrToDataArray++;
    }
    QScatterDataArray *dataArray2 = new QScatterDataArray;
    dataArray2->resize(itemCount);
    ptrToDataArray = &dataArray2->first();
    for (int i = 0; i < itemCount; i++) {
        ptrToDataArray->setPosition(randVector());
        ptrToDataArray++;
    }
    QScatterDataArray *dataArray3 = new QScatterDataArray;
    dataArray3->resize(itemCount);
    ptrToDataArray = &dataArray3->first();
    for (int i = 0; i < itemCount; i++) {
        ptrToDataArray->setPosition(randVector());
        ptrToDataArray++;
    }
    QScatterDataArray *dataArray4 = new QScatterDataArray;
    dataArray4->resize(itemCount);
    ptrToDataArray = &dataArray4->first();
    for (int i = 0; i < itemCount; i++) {
        ptrToDataArray->setPosition(randVector());
        ptrToDataArray++;
    }
    QScatterDataArray *dataArray5 = new QScatterDataArray;
    dataArray5->resize(itemCount);
    ptrToDataArray = &dataArray5->first();
    for (int i = 0; i < itemCount; i++) {
        ptrToDataArray->setPosition(randVector());
        ptrToDataArray++;
    }

    m_graph->seriesList().at(0)->dataProxy()->resetArray(dataArray);
    m_graph->seriesList().at(1)->dataProxy()->resetArray(dataArray2);
    m_graph->seriesList().at(2)->dataProxy()->resetArray(dataArray3);
    m_graph->seriesList().at(3)->dataProxy()->resetArray(dataArray4);
    m_graph->seriesList().at(4)->dataProxy()->resetArray(dataArray5);
}

QVector3D Data::randVector()
{
    return QVector3D(
                (float)(rand() % 100) / 2.0f - (float)(rand() % 100) / 2.0f,
                (float)(rand() % 100) / 2.0f - (float)(rand() % 100) / 2.0f,
                (float)(rand() % 100) / 2.0f - (float)(rand() % 100) / 2.0f);
}
