// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#ifndef WNLMPRISMETADATAMAP_H
#define WNLMPRISMETADATAMAP_H

#include <QDBusArgument>
#include <QMap>
#include <QMetaType>
#include <QString>
#include <QDBusVariant>

class WNLMPRISMetadataMap : public QMap<QString, QDBusVariant>
{
public:
    WNLMPRISMetadataMap();
};

Q_DECLARE_METATYPE(WNLMPRISMetadataMap)

#endif // WNLMPRISMETADATAMAP_H
