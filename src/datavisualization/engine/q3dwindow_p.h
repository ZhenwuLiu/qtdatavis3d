/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QtDataVisualization API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Q3DWINDOW_P_H
#define Q3DWINDOW_P_H

#include "datavisualizationglobal_p.h"

#include <QObject>

class QOpenGLContext;
class QOpenGLPaintDevice;

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

class Q3DWindow;
class Abstract3DController;

class Q3DWindowPrivate : public QObject
{
    Q_OBJECT
public:
    Q3DWindowPrivate(Q3DWindow *q);
    ~Q3DWindowPrivate();

    void render();

    void setVisualController(Abstract3DController *controller);
    void handleDevicePixelRatioChange();

public slots:
    void renderLater();
    void renderNow();

public:
    Q3DWindow *q_ptr;

    bool m_updatePending;
    QOpenGLContext *m_context;
    Abstract3DController *m_visualController;
    float m_devicePixelRatio;
};

QT_DATAVISUALIZATION_END_NAMESPACE

#endif
