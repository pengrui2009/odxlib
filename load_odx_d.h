#ifndef LOADODX_D_H
#define LOADODX_D_H

#include "pugixml.hpp"
#include "odx_cmn.h"

#include <memory>
#include <QVector>
#include <QByteArray>

struct SIMPLE_VALUE {
    QString data_value;
};

struct PROTOCOL_SNREF {
    QString attr_short_name;
};

struct PROT_STACK_SNREF {
    QString attr_short_name;
};

struct COMPARAM_REF {
    QString attr_id_ref;
    QString attr_docref;
    QString attr_doctype;

    SIMPLE_VALUE child_simple_value;
    PROTOCOL_SNREF child_protocol_snref;
    PROT_STACK_SNREF child_prot_stack_snref;
};

struct COMPARAM_REFS {
    QVector<COMPARAM_REF> child_comparam_ref;
};

struct PARENT_REF {
    QString attr_xsi_type;
    QString attr_id_ref;
    QString attr_docref;
    QString attr_doctype;
};

struct PARENT_REFS {
    QVector<PARENT_REF> child_parent_ref;
};

struct BASE_VARIANT {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    COMPARAM_REFS child_comparam_refs;
    PARENT_REFS child_parent_refs;
};

struct BASE_VARIANTS {
    QVector<BASE_VARIANT> child_base_variant;
};

struct BYTE_POSITION {
    QString data_value;
};

struct BIT_POSITION {
    QString data_value;
};

struct CODED_VALUE {
    QString data_value;
};

struct BIT_LENGTH {
    QString data_value;
};

struct DIAG_CODED_TYPE {
    QString attr_xsi_type;
    QString attr_base_type_encoding;
    QString attr_base_data_type;
    BIT_LENGTH child_bit_length;
};

struct PHYSICAL_TYPE {
    QString attr_base_data_type;
    QString attr_display_radix;
};

struct CATEGORY {
    QString data_value;
};

struct COMPU_METHOD {
    CATEGORY child_category;
};

struct TROUBLE_CODE {
    QString data_value;
};

struct DISPLAY_TROUBLE_CODE {
    QString data_value;
};

struct TEXT {
    QString attr_ti;
    QString data_value;
};

struct LEVEL {
    QString data_value;
};

struct SHORT_NAME {
    QString data_value;
};

struct SDG_CAPTION {
    QString attr_id;
    SHORT_NAME child_short_name;
    LONG_NAME child_long_name;
};

struct SD {
    QString attr_si;
};


struct PARAMS {
    QVector<PARAM> child_param;
};

struct NEG_RESPONSE {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    PARAMS child_params;
};

struct SDG {
    SDG_CAPTION child_sdg_caption;
    QVector<SD> child_sd;
};

struct SDGS {
    QVector<SDG> child_sdgs;
};


struct DTC {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    TROUBLE_CODE child_trouble_code;
    DISPLAY_TROUBLE_CODE child_display_trouble_code;
    TEXT child_text;
    LEVEL child_level;
    SDGS child_sdgs;
};

struct DTCS {
    QVector<DTC> child_dtc;
};

struct DTC_DOP {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    DIAG_CODED_TYPE child_diag_coded_type;
    PHYSICAL_TYPE child_physical_type;
    COMPU_METHOD child_compu_method;
    DTCS child_dtcs;
};

struct DTC_DOPS {
    QVector<DTC_DOP> child_dtc_drop;
};

struct DATA_OBJECT_PROP {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    COMPU_METHOD child_compu_method;
    DIAG_CODED_TYPE child_diag_coded_type;
    PHYSICAL_TYPE child_physical_type;
};

struct DATA_OBJECT_PROPS {
    QVector<DATA_OBJECT_PROP> child_data_object_prop;
};

struct STRUCTURE {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    PARAMS child_params;

};

struct STRUCTURES {
    QVector<STRUCTURE> child_structure;
};

struct KEY_DOP_REF {
    QString attr_id_ref;
};

struct TABLE_ROW {
    QString attr_id;
    QString attr_oid;
    QString attr_is_executable;
    QString attr_is_mandatory;
    QString attr_id_final;
};

struct TABLE {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    KEY_DOP_REF child_key_drop_ref;
    QVector<TABLE_ROW> child_table_row;
};

struct TABLES {
    QVector<TABLE> child_table;
};

struct DIAG_DATA_DICTIONARY_SPEC {
    DTC_DOPS child_dtc_dops;
    DATA_OBJECT_PROPS child_data_object_props;
    STRUCTURES child_structures;
    TABLES child_tables;
};

struct DIAG_COMMS {

};


struct PARAM {
    QString attr_xsi_type;
    QString attr_oid;
    QString attr_semantic;
    QString child_short_name;
    LONG_NAME child_long_name;
    BYTE_POSITION child_byte_position;
    BIT_POSITION child_bit_position;
    CODED_VALUE child_coded_value;
    DIAG_CODED_TYPE child_diag_coded_type;
};


struct NEG_RESPONSES {
    QVector<NEG_RESPONSE> child_neg_response;
};

struct EXPECTED_VALUE {
    QString data_value;
};

struct DIAG_COMM_SNREF {
    QString attr_short_name;
};

struct OUT_PARAM_IF_SNREF {
    QString attr_short_name;
};

struct MATCHING_PARAMETER {
    EXPECTED_VALUE child_expected_value;
    DIAG_COMM_SNREF child_diag_comm_snref;
    OUT_PARAM_IF_SNREF child_out_param_if_snref;
};

struct MATCHING_PARAMETERS {
    QVector<MATCHING_PARAMETER> child_matching_parameter;
};

struct ECU_VARIANT_PATTERN {
    MATCHING_PARAMETERS child_matching_parameters;
};

struct ECU_VARIANT_PATTERNS {
    QVector<ECU_VARIANT_PATTERN> child_ecu_variant_pattern;
};

struct ECU_VARIANT {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;

    DIAG_DATA_DICTIONARY_SPEC child_diag_data_dictionary_spec;
    DIAG_COMMS child_diag_comms;
    NEG_RESPONSES child_neg_responses;
    COMPARAM_REFS child_comparam_refs;
    ECU_VARIANT_PATTERNS child_ecu_variant_patterns
    PARENT_REFS child_parent_refs;
};

struct ECU_VARIANTS {
    QVector<ECU_VARIANT> child_ecu_variant;
};

struct DIAG_LAYER_CONTAINER {
    QString attr_id;
    QString attr_oid;

    QString child_short_name;
    LONG_NAME child_long_name;

    QString variants_type;
    union variants {
        BASE_VARIANTS child_base_variants;
        ECU_VARIANTS child_ecu_variants;
    };
};

struct ODX_D {
    QString attr_xmlns_xsi{""};
    QString attr_model_version{""};
    QString attr_xsi_noNamespaceSchemaLocation{""};

    DIAG_LAYER_CONTAINER child_diag_layer_container;
};

class LoadODX_D
{
public:
    LoadODX_D();
    int load(const QByteArray &fileData);
    void print();

private:
    std::unique_ptr<pugi::xml_document> doc_ptr_;
    ODX_D odx_;

    int read_odx(const pugi::xml_node &node, ODX_D &data);
};

#endif // LOADODX_D_H
