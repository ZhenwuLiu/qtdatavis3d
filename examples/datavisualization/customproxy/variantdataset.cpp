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

#include "variantdataset.h"

VariantDataSet::VariantDataSet()
    : QObject(0)
{
}

VariantDataSet::~VariantDataSet()
{
    clear();
}

void VariantDataSet::clear()
{
    foreach (VariantDataItem *item, m_variantData) {
        item->clear();
        delete item;
    }
    m_variantData.clear();
    emit dataCleared();
}

int VariantDataSet::addItem(VariantDataItem *item)
{
    m_variantData.append(item);
    int addIndex =  m_variantData.size();

    emit itemsAdded(addIndex, 1);
    return addIndex;
}

int VariantDataSet::addItems(VariantDataItemList *itemList)
{
    int newCount = itemList->size();
    int addIndex = m_variantData.size();
    m_variantData.append(*itemList);
    delete itemList;
    emit itemsAdded(addIndex, newCount);
    return addIndex;
}

const VariantDataItemList &VariantDataSet::itemList() const
{
    return m_variantData;
}
