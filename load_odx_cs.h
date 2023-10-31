#ifndef LOADODX_CS_H
#define LOADODX_CS_H

#include "pugixml.hpp"
#include "odx_cmn.h"

#include <memory>
#include <QVector>
#include <QByteArray>

struct DATA_OBJECT_PROP_REF {
    QString attr_id_ref;
};

struct COMPARAM {
    QString attr_cptype;
    QString attr_cpusage;
    QString attr_display_level;
    QString attr_id;
    QString attr_param_class;
    QString child_short_name;
    LONG_NAME child_long_name;
    DESC child_desc;
    QString child_physical_default_value;
    DATA_OBJECT_PROP_REF child_data_object_prop_ref;
};

struct COMPARAMS {
    QVector<COMPARAM> child_comparam;
};

//struct COMPLEX_VALUES {
//    QVector<COMPLEX_VALUE> child_complex_values;
//};

struct COMPLEX_PHYSICAL_DEFAULT_VALUE {
    COMPLEX_VALUES child_complex_values;

};

struct COMPLEX_COMPARAM {
    QString attr_allow_multiple_values;
    QString attr_cptype;
    QString attr_cpusage;
    QString attr_display_level;
    QString attr_id;
    QString attr_param_class;

    QString child_short_name;
    LONG_NAME child_long_name;
    DESC child_desc;
    QVector<COMPARAM> child_comparam;
    COMPLEX_PHYSICAL_DEFAULT_VALUE child_complex_physical_default_value;
};

struct COMPLEX_COMPARAMS {
    QVector<COMPLEX_COMPARAM> child_comparam;
};

struct UNIT {
    QString attr_id;
    QString child_short_name;
    LONG_NAME child_long_name;
    QString child_display_name;
};

struct UNITS {
    QVector<UNIT> child_unit;
};

struct PHYSICAL_DIMENSION {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    QString child_long_name;
    QString child_time_exp;
};

struct PHYSICAL_DIMENSIONS {
    QVector<PHYSICAL_DIMENSION> child_physical_dimension;
};

struct UNIT_SPEC {
    UNITS child_units;
    PHYSICAL_DIMENSIONS child_physical_dimensions;
};

struct COMPARAM_SUBSET {
    QString attr_category;
    QString attr_id;
    QString child_short_name;
    LONG_NAME child_long_name;
    ADMIN_DATA child_admin_data;
    COMPANY_DATAS child_company_datas;
    COMPARAMS child_comparams;
    COMPLEX_COMPARAMS child_complex_comparams;
    DATA_OBJECT_PROPS child_data_obejct_props;
    UNIT_SPEC child_unit_spec;
};

struct ODX_CS {
    QString attr_xmlns_xsi{""};
    QString attr_model_version{""};
    QString attr_xsi_noNamespaceSchemaLocation{""};

    COMPARAM_SUBSET child_comparam_subset;
};

class LoadODX_CS
{
public:
    LoadODX_CS();
    int load(const QByteArray &fileData);
    void print();

private:
    std::unique_ptr<pugi::xml_document> doc_ptr_;
    ODX_CS odx_;

    int read_odx(const pugi::xml_node &node, ODX_CS &data);
    int read_comparam_subset(const pugi::xml_node &node, COMPARAM_SUBSET &data);
    int read_comparam(const pugi::xml_node &node, COMPARAM &data);
    int read_comparams(const pugi::xml_node &node, COMPARAMS &data);
    int read_data_object_prop_ref(const pugi::xml_node &node, DATA_OBJECT_PROP_REF &data);
    int read_complex_comparam(const pugi::xml_node &node, COMPLEX_COMPARAM &data);
    int read_complex_comparams(const pugi::xml_node &node, COMPLEX_COMPARAMS &data);
    int read_complex_physical_default_value(const pugi::xml_node &node, COMPLEX_PHYSICAL_DEFAULT_VALUE &data);
    int read_data_object_prop(const pugi::xml_node &node, DATA_OBJECT_PROP &data);
    int read_data_object_props(const pugi::xml_node &node, DATA_OBJECT_PROPS &data);
    int read_unit_spec(const pugi::xml_node &node, UNIT_SPEC &data);
    int read_unit(const pugi::xml_node &node, UNIT &data);
    int read_units(const pugi::xml_node &node, UNITS &data);
    int read_physical_dimension(const pugi::xml_node &node, PHYSICAL_DIMENSION &data);
    int read_physical_dimensions(const pugi::xml_node &node, PHYSICAL_DIMENSIONS &data);

};

#endif // LOADODX_CS_H
