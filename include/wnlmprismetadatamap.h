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
