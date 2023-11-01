#ifndef LOADODX_E_H
#define LOADODX_E_H

#include "pugixml.hpp"
#include "odx_cmn.h"

#include <memory>
#include <QVector>
#include <QByteArray>

struct ECU_VARIANT_SNREF {
    QString attr_short_name;
};

struct ECU_VARIANT_SNREFS {
    QVector<ECU_VARIANT_SNREF> child_ecu_variant_snref;
};

struct BASE_VARIANT_SNREF {
    QString attr_short_name;
};

struct VALID_BASE_VARIANT {
    ECU_VARIANT_SNREFS child_ecu_variant_snrefs;
    BASE_VARIANT_SNREF child_base_variant_snref;
};

struct VALID_BASE_VARIANTS {
    QVector<VALID_BASE_VARIANT> child_valid_base_variant;
};

struct READ_DIAG_COMM_SNREF {
    QString attr_short_name;
};

struct READ_DATA_SNREF {
    QString attr_short_name;
};

struct READ_DIAG_COMM_CONNECTOR {
    READ_DIAG_COMM_SNREF child_read_diag_comm_snref;
    READ_DATA_SNREF child_read_data_snref;
};

struct WRITE_DIAG_COMM_SNREF {
    QString attr_short_name;
};

struct WRITE_DATA_SNREF {
    QString attr_short_name;
};

struct WRIT_DIAG_COMM_CONNECTOR {
    WRITE_DIAG_COMM_SNREF child_write_diag_comm_snref;
    WRITE_DATA_SNREF child_write_data_snref;
};

struct DIAG_COMM_DATA_CONNECTOR {
    QString child_uncompressed_size;
    QString child_source_start_address;
    READ_DIAG_COMM_CONNECTOR child_read_diag_comm_connector;
    WRIT_DIAG_COMM_CONNECTOR child_write_diag_comm_connector;

};

struct DIAG_COMM_DATA_CONNECTORS {
    QVector<DIAG_COMM_DATA_CONNECTOR> child_diag_comm_data_connector;
};

struct DATA_RECORD {
    QString attr_dataformat;
    QString child_short_name;
    LONG_NAME child_long_name;
    QString child_data;
};

struct DATA_RECORDS {
    QVector<DATA_RECORD> child_data_record;
};

struct OPTION_ITEM {
    QString child_short_name;
    LONG_NAME child_long_name;
    BYTE_POSITION child_byte_position;
    BIT_POSITION child_bit_position;
    DATA_OBJECT_PROP_REF child_data_object_prop_ref;
    PHYSICAL_DEFAULT_VALUE child_physical_default_value;
};

struct OPTION_ITEMS {
    QVector<OPTION_ITEM> child_option_item;
};

struct CONFIG_RECORD {
    QString child_short_name;
    LONG_NAME child_long_name;
    DIAG_COMM_DATA_CONNECTORS child_diag_comm_data_connectors;
    DATA_RECORDS child_data_records;
    OPTION_ITEMS child_option_items;
};

struct CONFIG_RECORDS {
    QVector<CONFIG_RECORD> child_config_record;
};

struct CONFIG_DATA {
    QString child_short_name;
    LONG_NAME child_long_name;
    VALID_BASE_VARIANTS child_valid_base_variants;
    CONFIG_RECORDS child_config_records;
};

struct CONFIG_DATAS {
    QVector<CONFIG_DATA> child_config_data;
};

struct CONFIG_DATA_DICTIONARY_SPEC {
    DATA_OBJECT_PROPS child_data_object_props;
    UNIT_SPEC child_unit_spec;
};

struct ECU_CONFIG {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    CONFIG_DATAS child_config_datas;
    CONFIG_DATA_DICTIONARY_SPEC child_config_data_dictionary_spec;

};

struct ODX_E {
    QString attr_xmlns_xsi;
    QString attr_model_version;
    QString attr_xsi_nonamespaceschemaLocation;
    ECU_CONFIG child_ecu_config;

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
    int read_ecu_config(const pugi::xml_node &node, ECU_CONFIG &data);
    int read_ecu_variant_snref(const pugi::xml_node &node, ECU_VARIANT_SNREF &data);
    int read_ecu_variant_snrefs(const pugi::xml_node &node, ECU_VARIANT_SNREFS &data);
    int read_base_variant_snref(const pugi::xml_node &node, BASE_VARIANT_SNREF &data);
    int read_valid_base_variant(const pugi::xml_node &node, VALID_BASE_VARIANT &data);
    int read_valid_base_variants(const pugi::xml_node &node, VALID_BASE_VARIANTS &data);
    int read_read_diag_comm_snref(const pugi::xml_node &node, READ_DIAG_COMM_SNREF &data);
    int read_read_data_snref(const pugi::xml_node &node, READ_DATA_SNREF &data);
    int read_read_diag_comm_connector(const pugi::xml_node &node, READ_DIAG_COMM_CONNECTOR &data);
    int read_write_diag_comm_snref(const pugi::xml_node &node, WRITE_DIAG_COMM_SNREF &data);
    int read_write_data_snref(const pugi::xml_node &node, WRITE_DATA_SNREF &data);
    int read_write_diag_comm_connector(const pugi::xml_node &node, WRIT_DIAG_COMM_CONNECTOR &data);
    int read_diag_comm_data_connector(const pugi::xml_node &node, DIAG_COMM_DATA_CONNECTOR &data);
    int read_diag_comm_data_connectors(const pugi::xml_node &node, DIAG_COMM_DATA_CONNECTORS &data);
    int read_config_record(const pugi::xml_node &node, CONFIG_RECORD &data);
    int read_data_record(const pugi::xml_node &node, DATA_RECORD &data);
    int read_data_records(const pugi::xml_node &node, DATA_RECORDS &data);
    int read_option_item(const pugi::xml_node &node, OPTION_ITEM &data);
    int read_option_items(const pugi::xml_node &node, OPTION_ITEMS &data);
    int read_config_records(const pugi::xml_node &node, CONFIG_RECORDS &data);
    int read_config_data(const pugi::xml_node &node, CONFIG_DATA &data);
    int read_config_datas(const pugi::xml_node &node, CONFIG_DATAS &data);
    int read_config_data_dictionary_spec(const pugi::xml_node &node, CONFIG_DATA_DICTIONARY_SPEC &data);
};

#endif // LOADODX_E_H
