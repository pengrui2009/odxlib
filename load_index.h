#ifndef LOADINDEX_H
#define LOADINDEX_H

#include "pugixml.hpp"
#include "odx_cmn.h"

#include <QString>
#include <QVector>
#include <QByteArray>


class FILE_ {
public:
    QString data_value;
};

class FILES {
public:
    QVector<FILE_> child_file;
};

class ABLOCK {
public:
    // ablock property
    QString attr_upd{""};

    QString child_short_name{""};
    ADMIN_DATA child_admin_data;
    QString child_category{""};
    FILES child_files;
};

class ABLOCKS {
public:
    QVector<ABLOCK> ablock;
};

class CATELOG {
public:
    QString attr_f_dtd_version{""};
    QString attr_xmlns_xsi{""};
    QString attr_xsi_noNamespaceSchemaLocation{""};

    QString child_short_name{""};
    ABLOCKS child_ablocks;
};

class LoadIndex
{
public:
    LoadIndex();

    int load(const QByteArray &fileData);
    void print();

    CATELOG catelog;
private:
    pugi::xml_document doc;

    int read_catalog(pugi::xml_node node, CATELOG &data);
    int read_ablocks(pugi::xml_node node, ABLOCKS &data);
    int read_ablock(pugi::xml_node node, ABLOCK &data);
    int read_admindata(pugi::xml_node node, ADMIN_DATA &data);
    int read_docrevisions(pugi::xml_node node, DOC_REVISIONS &data);
//    int read_revision_label(pugi::xml_node node, QString &data);
//    int read_date(pugi::xml_node node, QString &data);
    int read_docrevision(pugi::xml_node node, DOC_REVISION &data);
    int read_files(pugi::xml_node node, FILES &files);
    int read_file(pugi::xml_node node, FILE_ &file);

//    int read_category(pugi::xml_node node, QString &);
};

#endif // LOADINDEX_H
