#ifndef LOADODX_C_H
#define LOADODX_C_H

#include "pugixml.hpp"
#include "odx_cmn.h"

#include <memory>
#include <QVector>
#include <QByteArray>

struct COMPARAM_SUBSET_REF {
    QString attr_docref;
    QString attr_doctype;
    QString attr_id_ref;
};

struct COMPARAM_SUBSET_REFS {
    QVector<COMPARAM_SUBSET_REF> child_comparam_subset_ref;
};

struct PROT_STACK {
    QString attr_id;
    QString child_short_name;
    LONG_NAME child_long_name;
    DESC child_desc;
    QString child_pdu_protocol_type;
    QString child_physical_link_type;
    COMPARAM_SUBSET_REFS child_comparam_subset_refs;

};

struct PROT_STACKS {
    QVector<PROT_STACK> child_prot_stack;
};

struct COMPARAM_SPEC {
    QString attr_id;

    QString child_short_name;
    LONG_NAME child_long_name;
    DESC child_desc;
    ADMIN_DATA child_admin_data;
    COMPANY_DATAS child_company_datas;
    PROT_STACKS child_proto_stacks;
};

struct ODX_C {
    QString attr_xmlns_xsi{""};
    QString attr_model_version{""};
    QString attr_xsi_noNamespaceSchemaLocation{""};

    COMPARAM_SPEC child_comparam_spec;
};

class LoadODX_C
{
public:
    LoadODX_C();
    int load(const QByteArray &fileData);
    void print();

private:
    std::unique_ptr<pugi::xml_document> doc_ptr_;
    ODX_C odx_;

    int read_odx(const pugi::xml_node &node, ODX_C &data);
    int read_comparam_spec(const pugi::xml_node &node, COMPARAM_SPEC &data);
    int read_prot_stack(const pugi::xml_node &node, PROT_STACK &data);
    int read_prot_stacks(const pugi::xml_node &node, PROT_STACKS &data);
    int read_comparam_subset_ref(const pugi::xml_node &node, COMPARAM_SUBSET_REF &data);
    int read_comparam_subset_refs(const pugi::xml_node &node, COMPARAM_SUBSET_REFS &data);
};

#endif // LOADODX_C_H
