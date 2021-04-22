// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#include "wnlmprismetadatamap.h"

WNLMPRISMetadataMap::WNLMPRISMetadataMap()
    : QMap<QString, QDBusVariant>()
{

}

// As of Qt 5.7 all custom Qt D-Bus types must have custom << and >> operators defined, so that's what I'm doing here
// These are mostly copied from the examples on Qt's website, as I really don't need anything special for these, they're basically just a QMap
QDBusArgument &operator<<(QDBusArgument &argument, const WNLMPRISMetadataMap &map)
{
    // Append a map that associates strings to variants
    argument.beginMap(QMetaType::QString, qMetaTypeId<QDBusVariant>());

    for (QString key : map.keys())
    {
        argument.beginMapEntry();
        argument << key << map.value(key);
        argument.endMapEntry();
    }
    argument.endMap();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, WNLMPRISMetadataMap &map)
{
    // Extract a map that associates strings to variants
    argument.beginMap();
    map.clear();

    while (!argument.atEnd())
    {
        QString key;
        QDBusVariant value;

        argument.beginMapEntry();
        argument >> key >> value;
        argument.endMapEntry();

        map.insert(key, value);
    }

    argument.endMap();

    return argument;
}
