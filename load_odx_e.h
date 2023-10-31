#ifndef LOADODX_E_H
#define LOADODX_E_H

#include "pugixml.hpp"
#include "odx_cmn.h"

#include <memory>
#include <QVector>
#include <QByteArray>

struct ODX_E {

};

class LoadODX_E
{
public:
    LoadODX_E();
    int load(const QByteArray &fileData);
    void print();

private:
    std::unique_ptr<pugi::xml_document> doc_ptr_;
    ODX_E odx_;

    int read_odx(const pugi::xml_node &node, ODX_E &data);
};

#endif // LOADODX_E_H
