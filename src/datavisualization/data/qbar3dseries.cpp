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

#include "qbar3dseries_p.h"
#include "bars3dcontroller_p.h"

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

/*!
 * \class QBar3DSeries
 * \inmodule QtDataVisualization
 * \brief Base series class for Q3DBars.
 * \since Qt Data Visualization 1.0
 *
 * QBar3DSeries manages the series specific visual elements, as well as series data
 * (via data proxy).
 *
 * If no data proxy is set explicitly for the series, QBar3DSeries creates a default
 * proxy. If any other proxy is set as active data proxy later, the default proxy and all data
 * added to it are destroyed.
 *
 * QBar3DSeries optionally keeps track of row and column labels, which Q3DCategoryAxis can utilize
 * to show axis labels. The row and column labels are stored in separate array from the data and
 * row manipulation methods provide an alternate versions that don't affect the row labels.
 * This enables the option of having row labels that relate to the position of the data in the
 * array rather than the data itself.
 *
 * QBar3DSeries supports the following format tags for QAbstract3DSeries::setItemLabelFormat():
 * \table
 *   \row
 *     \li @rowTitle      \li Title from row axis
 *   \row
 *     \li @colTitle      \li Title from column axis
 *   \row
 *     \li @valueTitle    \li Title from value axis
 *   \row
 *     \li @rowIdx        \li Visible row index
 *   \row
 *     \li @colIdx        \li Visible Column index
 *   \row
 *     \li @rowLabel      \li Label from row axis
 *   \row
 *     \li @colLabel      \li Label from column axis
 *   \row
 *     \li @valueLabel    \li Item value formatted using the same format the value axis attached to the graph uses,
 *                            see \l{Q3DValueAxis::setLabelFormat()} for more information.
 *   \row
 *     \li %<format spec> \li Item value in specified format.
 * \endtable
 *
 * For example:
 * \snippet doc_src_qtdatavisualization.cpp 1
 *
 * \sa {Qt Data Visualization Data Handling}
 */

/*!
 * \qmltype Bar3DSeries
 * \inqmlmodule QtDataVisualization
 * \since QtDataVisualization 1.0
 * \ingroup datavisualization_qml
 * \instantiates QBar3DSeries
 * \inherits Abstract3DSeries
 * \brief Base series type for Bars3D.
 *
 * This type  manages the series specific visual elements, as well as series data
 * (via data proxy).
 *
 * For more complete description, see QBar3DSeries.
 *
 * \sa {Qt Data Visualization Data Handling}
 */


/*!
 * Constructs QBar3DSeries with the given \a parent.
 */
QBar3DSeries::QBar3DSeries(QObject *parent) :
    QAbstract3DSeries(new QBar3DSeriesPrivate(this), parent)
{
    // Default proxy
    dptr()->setDataProxy(new QBarDataProxy);
}

QBar3DSeries::QBar3DSeries(QBarDataProxy *dataProxy, QObject *parent) :
    QAbstract3DSeries(new QBar3DSeriesPrivate(this), parent)
{
    dptr()->setDataProxy(dataProxy);
}

/*!
 * \internal
 */
QBar3DSeries::QBar3DSeries(QBar3DSeriesPrivate *d, QObject *parent) :
    QAbstract3DSeries(d, parent)
{
}

/*!
 * Destroys QBar3DSeries.
 */
QBar3DSeries::~QBar3DSeries()
{
}

/*!
 * \property QBar3DSeries::dataProxy
 *
 * This property holds the active data \a proxy. The series assumes ownership of any proxy set to
 * it and deletes any previously set proxy when a new one is added. The \a proxy cannot be null or
 * set to another series.
 */
void QBar3DSeries::setDataProxy(QBarDataProxy *proxy)
{
    d_ptr->setDataProxy(proxy);
}

QBarDataProxy *QBar3DSeries::dataProxy() const
{
    return static_cast<QBarDataProxy *>(d_ptr->dataProxy());
}

/*!
 * \internal
 */
QBar3DSeriesPrivate *QBar3DSeries::dptr()
{
    return static_cast<QBar3DSeriesPrivate *>(d_ptr.data());
}

/*!
 * \internal
 */
const QBar3DSeriesPrivate *QBar3DSeries::dptrc() const
{
    return static_cast<const QBar3DSeriesPrivate *>(d_ptr.data());
}

// QBar3DSeriesPrivate

QBar3DSeriesPrivate::QBar3DSeriesPrivate(QBar3DSeries *q)
    : QAbstract3DSeriesPrivate(q, QAbstract3DSeries::SeriesTypeBar)
{
    m_itemLabelFormat = QStringLiteral("@valueTitle: @valueLabel");
}

QBar3DSeriesPrivate::~QBar3DSeriesPrivate()
{
}

QBar3DSeries *QBar3DSeriesPrivate::qptr()
{
    return static_cast<QBar3DSeries *>(q_ptr);
}

void QBar3DSeriesPrivate::setDataProxy(QAbstractDataProxy *proxy)
{
    Q_ASSERT(proxy->type() == QAbstractDataProxy::DataTypeBar);

    QAbstract3DSeriesPrivate::setDataProxy(proxy);

    emit qptr()->dataProxyChanged(static_cast<QBarDataProxy *>(proxy));
}

void QBar3DSeriesPrivate::connectControllerAndProxy(Abstract3DController *newController)
{
    QBarDataProxy *barDataProxy = static_cast<QBarDataProxy *>(m_dataProxy);

    if (m_controller && barDataProxy) {
        //Disconnect old controller/old proxy
        QObject::disconnect(barDataProxy, 0, m_controller, 0);
        QObject::disconnect(q_ptr, 0, m_controller, 0);
    }

    if (newController && barDataProxy) {
        Bars3DController *controller = static_cast<Bars3DController *>(newController);

        QObject::connect(barDataProxy, &QBarDataProxy::arrayReset, controller,
                         &Bars3DController::handleArrayReset);
        QObject::connect(barDataProxy, &QBarDataProxy::rowsAdded, controller,
                         &Bars3DController::handleRowsAdded);
        QObject::connect(barDataProxy, &QBarDataProxy::rowsChanged, controller,
                         &Bars3DController::handleRowsChanged);
        QObject::connect(barDataProxy, &QBarDataProxy::rowsRemoved, controller,
                         &Bars3DController::handleRowsRemoved);
        QObject::connect(barDataProxy, &QBarDataProxy::rowsInserted, controller,
                         &Bars3DController::handleRowsInserted);
        QObject::connect(barDataProxy, &QBarDataProxy::itemChanged, controller,
                         &Bars3DController::handleItemChanged);
        QObject::connect(barDataProxy, &QBarDataProxy::rowLabelsChanged, controller,
                         &Bars3DController::handleDataRowLabelsChanged);
        QObject::connect(barDataProxy, &QBarDataProxy::columnLabelsChanged, controller,
                         &Bars3DController::handleDataColumnLabelsChanged);

        QObject::connect(q_ptr, &QAbstract3DSeries::visibilityChanged, controller,
                         &Abstract3DController::handleSeriesVisibilityChanged);

        // Always clear selection on proxy change
        // TODO: setSelectedBar(noSelectionPoint());

        newController->handleSeriesVisibilityChanged(m_visible);
    }
}

QT_DATAVISUALIZATION_END_NAMESPACE
