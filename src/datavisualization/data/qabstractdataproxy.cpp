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

#include "qabstractdataproxy.h"
#include "qabstractdataproxy_p.h"
#include "qabstract3dseries_p.h"

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

/*!
 * \class QAbstractDataProxy
 * \inmodule QtDataVisualization
 * \brief Base class for all QtDataVisualization data proxies.
 * \since Qt Data Visualization 1.0
 *
 * You use the visualization type specific inherited classes instead of the base class.
 * \sa QBarDataProxy, QScatterDataProxy, QSurfaceDataProxy, {Qt Data Visualization Data Handling}
 */

/*!
 * \qmltype AbstractDataProxy
 * \inqmlmodule QtDataVisualization
 * \since QtDataVisualization 1.0
 * \ingroup datavisualization_qml
 * \instantiates QAbstractDataProxy
 * \brief Base type for all QtDataVisualization data proxies.
 *
 * This type is uncreatable, but contains properties that are exposed via subtypes.
 * \sa BarDataProxy, ScatterDataProxy, SurfaceDataProxy, {Qt Data Visualization Data Handling}
 */

/*!
 * \qmlproperty AbstractDataProxy.DataType AbstractDataProxy::type
 * The type of the proxy.
 */

/*!
 * \enum QAbstractDataProxy::DataType
 *
 * Data type of the proxy.
 *
 * \value DataTypeNone
 *        No data type.
 * \value DataTypeBar
 *        Data type for Q3DBars.
 * \value DataTypeScatter
 *        Data type for Q3DScatter.
 * \value DataTypeSurface
 *        Data type for Q3DSurface.
 */

/*!
 * \internal
 */
QAbstractDataProxy::QAbstractDataProxy(QAbstractDataProxyPrivate *d, QObject *parent) :
    QObject(parent),
    d_ptr(d)
{
}

/*!
 * Destroys QAbstractDataProxy.
 */
QAbstractDataProxy::~QAbstractDataProxy()
{
}

/*!
 * \property QAbstractDataProxy::type
 *
 * The type of the proxy.
 */
QAbstractDataProxy::DataType QAbstractDataProxy::type() const
{
    return d_ptr->m_type;
}

// QAbstractDataProxyPrivate

QAbstractDataProxyPrivate::QAbstractDataProxyPrivate(QAbstractDataProxy *q, QAbstractDataProxy::DataType type)
    : QObject(0),
      q_ptr(q),
      m_type(type),
      m_series(0)
{
}

QAbstractDataProxyPrivate::~QAbstractDataProxyPrivate()
{
}

void QAbstractDataProxyPrivate::setSeries(QAbstract3DSeries *series)
{
    setParent(series);
    m_series = series;
}

QT_DATAVISUALIZATION_END_NAMESPACE
