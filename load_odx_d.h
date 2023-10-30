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

struct COMPLEX_VALUE {
    QVector<SIMPLE_VALUE> child_simple_value;
};

//struct VALUES {
//    VALUES() : child_simple_value() {}
//    ~VALUES() {}
//    union {
//        SIMPLE_VALUE child_simple_value;
//        COMPLEX_VALUE child_complex_value;
//    } ;

//};

struct COMPARAM_REF {
    QString attr_id_ref;
    QString attr_docref;
    QString attr_doctype;
    QString value_type;
    SIMPLE_VALUE child_simple_value;
    COMPLEX_VALUE child_complex_value;

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
    LONG_NAME child_long_name;
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

struct FUNCT_CLASS_REF {
    QString attr_id_ref;
    QString attr_docref;
    QString attr_doctype;
};

struct FUNCT_CLASS_REFS {
    QVector<FUNCT_CLASS_REF> child_funct_class_ref;
};

struct PRE_CONDITION_STATE_REF {
    QString attr_id_ref;
    QString attr_docref;
    QString attr_doctype;
};

struct PRE_CONDITION_STATE_REFS {
    QVector<PRE_CONDITION_STATE_REF> child_pre_condition_state_ref;
};

struct REQUEST_REF {
    QString attr_id_ref;
    QString attr_docref;
    QString attr_doctype;
};

struct POS_RESPONSE_REF {
    QString attr_id_ref;
    QString attr_docref;
    QString attr_doctype;
};

struct POS_RESPONSE_REFS {
    QVector<POS_RESPONSE_REF> child_pos_response_ref;
};

struct NEG_RESPONSE_REF {
    QString attr_id_ref;
};

struct NEG_RESPONSE_REFS {
    QVector<NEG_RESPONSE_REF> child_neg_response_ref;
};

struct BIT_MASK {
    QString data_value;
};

struct CODED_CONST_SNREF {
    QString attr_short_name;
};

struct POS_RESPONSE_SUPPRESSABLE {
    BIT_MASK child_bit_mask;
    CODED_CONST_SNREF child_coded_const_snref;
};

struct DIAG_SERVICE {
    QString attr_id;
    QString attr_oid;
    QString attr_addressing;
    QString attr_transmission_mode;
    QString child_short_name;
    LONG_NAME child_long_name;
    FUNCT_CLASS_REFS child_funct_class_refs;
    PRE_CONDITION_STATE_REFS child_pre_condition_state_refs;
    REQUEST_REF child_request_ref;
    POS_RESPONSE_REFS child_pos_response_refs;
    NEG_RESPONSE_REFS child_neg_response_refs;
    POS_RESPONSE_SUPPRESSABLE child_pos_response_suppressable;
};

struct DIAG_COMMS {
    QVector<DIAG_SERVICE> child_diag_service;
};

struct NEG_RESPONSES {
    QVector<NEG_RESPONSE> child_neg_response;
};

struct EXPECTED_VALUE {
    QString data_value;
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
    LONG_NAME child_long_name;
    DIAG_DATA_DICTIONARY_SPEC child_diag_data_dictionary_spec;
    DIAG_COMMS child_diag_comms;
    NEG_RESPONSES child_neg_responses;
    COMPARAM_REFS child_comparam_refs;
    ECU_VARIANT_PATTERNS child_ecu_variant_patterns;
    PARENT_REFS child_parent_refs;
};

struct ECU_VARIANTS {
    QVector<ECU_VARIANT> child_ecu_variant;
};

struct VARIANTS {
    VARIANTS() : child_base_variants(){}
    ~VARIANTS(){}
    union {
        BASE_VARIANTS child_base_variants;
        ECU_VARIANTS child_ecu_variants;
    } ;
};

struct DIAG_LAYER_CONTAINER {
    QString attr_id;
    QString attr_oid;

    QString child_short_name;
    LONG_NAME child_long_name;

    QString variants_type;
    VARIANTS variants_data;

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
    // BASE VARIANT
    int read_odx(const pugi::xml_node &node, ODX_D &data);
    int read_diag_layer_container(const pugi::xml_node &node, DIAG_LAYER_CONTAINER &data);
    int read_simple_value(const pugi::xml_node &node, SIMPLE_VALUE &data);
    int read_protocol_snref(const pugi::xml_node &node, PROTOCOL_SNREF &data);
    int read_prot_stack_snref(const pugi::xml_node &node, PROT_STACK_SNREF &data);
    int read_complex_value(const pugi::xml_node &node, COMPLEX_VALUE &data);
    int read_comparam_ref(const pugi::xml_node &node, COMPARAM_REF &data);
    int read_comparam_refs(const pugi::xml_node &node, COMPARAM_REFS &data);
    int read_parent_ref(const pugi::xml_node &node, PARENT_REF &data);
    int read_parent_refs(const pugi::xml_node &node, PARENT_REFS &data);
    int read_base_variant(const pugi::xml_node &node, BASE_VARIANT &data);
    int read_base_variants(const pugi::xml_node &node, BASE_VARIANTS &data);
    // ECU VARIANT
    int read_bit_length(const pugi::xml_node &node, BIT_LENGTH &data);
    int read_diag_coded_type(const pugi::xml_node &node, DIAG_CODED_TYPE &data);
    int read_physical_type(const pugi::xml_node &node, PHYSICAL_TYPE &data);
    int read_category(const pugi::xml_node &node, CATEGORY &data);
    int read_compu_method(const pugi::xml_node &node, COMPU_METHOD &data);

    int read_trouble_code(const pugi::xml_node &node, TROUBLE_CODE &data);
    int read_display_trouble_code(const pugi::xml_node &node, DISPLAY_TROUBLE_CODE &data);
    int read_text(const pugi::xml_node &node, TEXT &data);
    int read_level(const pugi::xml_node &node, LEVEL &data);
    int read_sdg_caption(const pugi::xml_node &node, SDG_CAPTION &data);
    int read_sd(const pugi::xml_node &node, SD &data);
    int read_sdg(const pugi::xml_node &node, SDG &data);
    int read_sdgs(const pugi::xml_node &node, SDGS &data);


    int read_dtc(const pugi::xml_node &node, DTC &data);
    int read_dtcs(const pugi::xml_node &node, DTCS &data);

    int read_dtc_dop(const pugi::xml_node &node, DTC_DOP &data);
    int read_dtc_dops(const pugi::xml_node &node, DTC_DOPS &data);
    int read_diag_data_dictionary_spec(const pugi::xml_node &node, DIAG_DATA_DICTIONARY_SPEC &data);


    int read_funct_class_ref(const pugi::xml_node &node, FUNCT_CLASS_REF &data);
    int read_funct_class_refs(const pugi::xml_node &node, FUNCT_CLASS_REFS &data);
    int read_pre_condition_state_ref(const pugi::xml_node &node, PRE_CONDITION_STATE_REF &data);
    int read_pre_condition_state_refs(const pugi::xml_node &node, PRE_CONDITION_STATE_REFS &data);
    int read_request_ref(const pugi::xml_node &node, REQUEST_REF &data);
    int read_pos_response_ref(const pugi::xml_node &node, POS_RESPONSE_REF &data);
    int read_pos_response_refs(const pugi::xml_node &node, POS_RESPONSE_REFS &data);
    int read_neg_response_ref(const pugi::xml_node &node, NEG_RESPONSE_REF &data);
    int read_neg_response_refs(const pugi::xml_node &node, NEG_RESPONSE_REFS &data);
    int read_bit_mask(const pugi::xml_node &node, BIT_MASK &data);
    int read_coded_const_snref(const pugi::xml_node &node, CODED_CONST_SNREF &data);
    int read_pos_response_supperssable(const pugi::xml_node &node, POS_RESPONSE_SUPPRESSABLE &data);
    int read_diag_service(const pugi::xml_node &node, DIAG_SERVICE &data);
    int read_diag_comms(const pugi::xml_node &node, DIAG_COMMS &data);


    int read_byte_position(const pugi::xml_node &node, BYTE_POSITION &data);
    int read_bit_position(const pugi::xml_node &node, BIT_POSITION &data);
    int read_coded_value(const pugi::xml_node &node, CODED_VALUE &data);

    int read_param(const pugi::xml_node &node, PARAM &data);
    int read_params(const pugi::xml_node &node, PARAMS &data);

    int read_neg_response(const pugi::xml_node &node, NEG_RESPONSE &data);
    int read_neg_responses(const pugi::xml_node &node, NEG_RESPONSES &data);
    int read_expected_value(const pugi::xml_node &node, EXPECTED_VALUE &data);
    int read_diag_comm_snref(const pugi::xml_node &node, DIAG_COMM_SNREF &data);
    int read_out_param_if_snref(const pugi::xml_node &node, OUT_PARAM_IF_SNREF &data);

    int read_matching_parameter(const pugi::xml_node &node, MATCHING_PARAMETER &data);
    int read_matching_parameters(const pugi::xml_node &node, MATCHING_PARAMETERS &data);

    int read_ecu_variant_pattern(const pugi::xml_node &node, ECU_VARIANT_PATTERN &data);
    int read_ecu_variant_patterns(const pugi::xml_node &node, ECU_VARIANT_PATTERNS &data);
    int read_child_parent_refs(const pugi::xml_node &node, PARENT_REFS &data);
    int read_ecu_variant(const pugi::xml_node &node, ECU_VARIANT &data);
    int read_ecu_variants(const pugi::xml_node &node, ECU_VARIANTS &data);

};

#endif // LOADODX_D_H
