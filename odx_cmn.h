#ifndef ODXCMN_H
#define ODXCMN_H

#include "pugixml.hpp"
#include <QString>

struct LONG_NAME {
    QString attr_ti{""};
    QString data_value{""};
};


class odxcmn
{
public:
    odxcmn();
    static int read_short_name(const pugi::xml_node &node, QString &data);
    static int read_long_name(const pugi::xml_node &node, LONG_NAME &data);
};

#endif // ODXCMN_H
