#include "load_odx_d.h"

#include <iostream>
#include <QDebug>

LoadODX_D::LoadODX_D() :
    doc_ptr_{std::make_unique<pugi::xml_document>()}
{

}

int LoadODX_D::load(const QByteArray &fileData)
{
    pugi::xml_parse_result result = doc_ptr_->load_buffer(fileData.constData(), fileData.length());
    if (!result) {
        std::cout << "LoadIndex load content failed!" << std::endl;
        return -1;
    }

    // Access the root node: ODX
    pugi::xml_node root = doc_ptr_->child("ODX");

    return read_odx(root, odx_);
}

void LoadODX_D::print()
{
    qDebug() << QString("odx-v property:{xmlns:xsi:%1 MODEL-VERSION:%2 xsi:noNamespaceSchemaLocation:%3}").
                arg(odx_.attr_xmlns_xsi, odx_.attr_model_version).arg(odx_.attr_xsi_noNamespaceSchemaLocation);
    qDebug() << QString("  DIAG-LAYER-CONTAINER property:{%1 :%2}").arg(odx_.child_diag_layer_container.attr_id).arg(odx_.child_diag_layer_container.attr_oid);
    qDebug() << QString("    SHORT-NAME:%1").arg(odx_.child_diag_layer_container.child_short_name);
    qDebug() << QString("    LONG-NAME: property{%1} :%2").arg(odx_.child_diag_layer_container.child_long_name.attr_ti).arg(odx_.child_diag_layer_container.child_long_name.data_value);
    if ("BASE-VARIANTS" == odx_.child_diag_layer_container.variants_type) {
    qDebug() << QString("    BASE-VARIANTS size:%1").arg(odx_.child_diag_layer_container.child_base_variants.child_base_variant.size());
    for (auto iter : odx_.child_diag_layer_container.child_base_variants.child_base_variant)
    {
    qDebug() << QString("      BASE-VARIANT property:{%1 :%2}").arg(iter.attr_id).arg(iter.attr_oid);
    qDebug() << QString("        SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("        LONG-NAME: property:{%1} :%2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);
    qDebug() << QString("        COMPARAM_REFS size:%1").arg(iter.child_comparam_refs.child_comparam_ref.size());
    for (auto iter1 : iter.child_comparam_refs.child_comparam_ref)
    {
    qDebug() << QString("          COMPARAM_REF property:{%1 %2 %3} ").arg(iter1.attr_id_ref).arg(iter1.attr_docref).arg(iter1.attr_doctype);
    if (iter1.value_type.contains("COMPLEX-VALUE")) {
    qDebug() << QString("            COMPLEX-VALUE size:%1").arg(iter1.child_complex_value.child_simple_value.size());
    for (auto iter2 : iter1.child_complex_value.child_simple_value)
    {
    qDebug() << QString("              SIMPLE-VALUE :%1").arg(iter2.data_value);
    }
    } else if (iter1.value_type.contains("SIMPLE-VALUE")) {
    qDebug() << QString("            SIMPLE-VALUE:%1").arg(iter1.child_simple_value.data_value);
    }
    qDebug() << QString("            PROTOCOL-SNREF property:{%1} ").arg(iter1.child_protocol_snref.attr_short_name);
    qDebug() << QString("            PROT-STACK-SNREF property:{%1} ").arg(iter1.child_prot_stack_snref.attr_short_name);
    }
    qDebug() << QString("        PARENT_REFS size:%1").arg(iter.child_parent_refs.child_parent_ref.size());
    for (auto iter1 : iter.child_parent_refs.child_parent_ref)
    {
    qDebug() << QString("          PARENT_REF property:{%1 %2 %3 %4}").arg(iter1.attr_xsi_type).arg(iter1.attr_id_ref).arg(iter1.attr_docref).arg(iter1.attr_doctype);
    }
    }
    } else if ("ECU-VARIANTS" == odx_.child_diag_layer_container.variants_type){
    qDebug() << QString("    ECU-VARIANTS size:%1").arg(odx_.child_diag_layer_container.child_ecu_variants.child_ecu_variant.size());
    for (auto iter : odx_.child_diag_layer_container.child_ecu_variants.child_ecu_variant)
    {
    qDebug() << QString("      ECU-VARIANT property:{%1 %2}").arg(iter.attr_id).arg(iter.attr_oid);
    qDebug() << QString("        SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("        LONG-NAME property:{%1} :%2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);
    qDebug() << QString("        DIAG-DATA-DICTIONARY-SPEC");
    qDebug() << QString("          DTC-DOPS size:%1").arg(iter.child_diag_data_dictionary_spec.child_dtc_dops.child_dtc_drop.size());
    for (auto iter1 : iter.child_diag_data_dictionary_spec.child_dtc_dops.child_dtc_drop)
    {
    qDebug() << QString("            DTC-DOP property:{%1 %2}").arg(iter1.attr_id).arg(iter.attr_oid);
    qDebug() << QString("              SHORT-NAME:%1").arg(iter1.child_short_name);
    qDebug() << QString("              LONG-NAME property:{%1} :%2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("              DIAG-CODED-TYPE property:{%1 %2 %3}").arg(iter1.child_diag_coded_type.attr_xsi_type).arg(iter1.child_diag_coded_type.attr_base_data_type).arg(iter1.child_diag_coded_type.attr_base_type_encoding);
    qDebug() << QString("                BIT-LENGTH:%1").arg(iter1.child_diag_coded_type.child_bit_length.data_value);
    qDebug() << QString("              PHYSICAL-TYPE property:{%1 %2}").arg(iter1.child_physical_type.attr_base_data_type).arg(iter1.child_physical_type.attr_display_radix);
    qDebug() << QString("              COMPU-METHOD");
    qDebug() << QString("                CATEGORY:%1").arg(iter1.child_compu_method.child_category.data_value);
    qDebug() << QString("             DTCS size:%1").arg(iter1.child_dtcs.child_dtc.size());
    for(auto iter2 : iter1.child_dtcs.child_dtc)
    {
    qDebug() << QString("               DTC property:{%1 %2}").arg(iter2.attr_id).arg(iter2.attr_oid);
    qDebug() << QString("                 SHORT-NAME:%1").arg(iter2.child_short_name);
    qDebug() << QString("                 TROUBLE-CODE:%1").arg(iter2.child_trouble_code.data_value);
    qDebug() << QString("                 DISPLAY-TROUBLE-CODE:%1").arg(iter2.child_display_trouble_code.data_value);
    qDebug() << QString("                 TEXT property:{%1} %2").arg(iter2.child_text.attr_ti).arg(iter2.child_text.data_value);
    qDebug() << QString("                 LEVEL:%1").arg(iter2.child_level.data_value);
    qDebug() << QString("                 SDGS size:%1").arg(iter2.child_sdgs.child_sdgs.size());
    for(auto iter3 : iter2.child_sdgs.child_sdgs)
    {
    qDebug() << QString("                   SDG");
    qDebug() << QString("                     SDG-CAPTION property:{%1}").arg(iter3.child_sdg_caption.attr_id);
    qDebug() << QString("                       SHORT-NAME:%1").arg(iter3.child_sdg_caption.child_short_name.data_value);
    qDebug() << QString("                       LONG-NAME: property:{%1} %2").arg(iter3.child_sdg_caption.child_long_name.attr_ti).arg(iter3.child_sdg_caption.child_long_name.data_value);
    for (auto iter4 : iter3.child_sd)
    {
    qDebug() << QString("                       SD property:{%1 %2}").arg(iter4.attr_si).arg(iter4.attr_ti);
    }
    }
    }
    qDebug() << QString("            DTC-DOP");
    qDebug() << QString("          DTC-DOPS");
    }

    qDebug() << QString("          DATA-OBJECT-PROPS size:%1").arg(iter.child_diag_data_dictionary_spec.child_data_object_props.child_data_object_prop.size());
    for (auto iter1 : iter.child_diag_data_dictionary_spec.child_data_object_props.child_data_object_prop)
    {
    qDebug() << QString("            DATA-OBJECT-PROP property:{%1 %2}").arg(iter1.attr_id).arg(iter1.attr_oid);
    qDebug() << QString("              SHORT-NAME:%1").arg(iter1.child_short_name);
    qDebug() << QString("              LONG-NAME property:{%1} :%2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("              COMPU-METHOD");
    qDebug() << QString("                CATEGORY:%1").arg(iter1.child_compu_method.child_category.data_value);
    qDebug() << QString("              DIAG-CODED-TYPE property:{%1 %2 %3}").arg(iter1.child_diag_coded_type.attr_xsi_type).arg(iter1.child_diag_coded_type.attr_base_data_type).arg(iter1.child_diag_coded_type.attr_base_type_encoding);
    qDebug() << QString("                BIT-LENGTH:%1").arg(iter1.child_diag_coded_type.child_bit_length.data_value);
    qDebug() << QString("              PHYSICAL-TYPE:{%1 %2}").arg(iter1.child_physical_type.attr_base_data_type).arg(iter1.child_physical_type.attr_display_radix);
    }
    qDebug() << QString("          STRUCTURES size:%1").arg(iter.child_diag_data_dictionary_spec.child_structures.child_structure.size());
    for (auto iter1 : iter.child_diag_data_dictionary_spec.child_structures.child_structure)
    {
    qDebug() << QString("            STRUCTURE property:{%1 %2}").arg(iter1.attr_id).arg(iter1.attr_oid);
    qDebug() << QString("              SHORT-NAME:%1").arg(iter1.child_short_name);
    qDebug() << QString("              LONG-NAME property:{%1} :%2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("              PARAMS size:%1").arg(iter1.child_params.child_param.size());
    for (auto iter2 : iter1.child_params.child_param)
    {
    qDebug() << QString("                PARAM property:{%1 %2 %3}").arg(iter2.attr_xsi_type).arg(iter2.attr_oid).arg(iter2.attr_semantic);
    qDebug() << QString("                  SHORT-NAME:%1").arg(iter2.child_short_name);
    qDebug() << QString("                  LONG-NAME property:{%1} :%2").arg(iter2.child_long_name.attr_ti).arg(iter2.child_long_name.data_value);
    qDebug() << QString("                  BYTE-POSITION property:{%1}").arg(iter2.child_byte_position.data_value);
    qDebug() << QString("                  BIT-POSITION property:{%1}").arg(iter2.child_bit_position.data_value);
    qDebug() << QString("                  DOP-REF property:{%1}").arg(iter2.child_dop_ref.attr_id_ref);
    qDebug() << QString("                  PHYSICAL-DEFAULT-VALUE:%1").arg(iter2.child_physical_default_value.data_value);
    }
    }
    qDebug() << QString("          TABLES size:%1").arg(iter.child_diag_data_dictionary_spec.child_tables.child_table.size());
    for (auto iter1 : iter.child_diag_data_dictionary_spec.child_tables.child_table)
    {
    qDebug() << QString("            TABLE property:{%1 %2}").arg(iter1.attr_id).arg(iter1.attr_oid);
    qDebug() << QString("              SHORT-NAME:%1").arg(iter1.child_short_name);
    qDebug() << QString("              LONG-NAME property:{%1} :%2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("              KEY-DOP-REF property:{%1}").arg(iter1.child_key_drop_ref.attr_id_ref);
    for (auto iter2 : iter1.child_table_row)
    {
    qDebug() << QString("              TABLE-ROW property:{%1 %2 %3 %4 %5}").arg(iter2.attr_id).arg(iter2.attr_oid).arg(iter2.attr_is_executable).arg(iter2.attr_is_mandatory).arg(iter2.attr_is_final);
    qDebug() << QString("                SHORT-NAME:%1").arg(iter2.child_short_name.data_value);
    qDebug() << QString("                LONG-NAME property:{%1} :%2").arg(iter2.child_long_name.attr_ti).arg(iter2.child_long_name.data_value);
    qDebug() << QString("                KEY:%1").arg(iter2.child_key.data_value);
    qDebug() << QString("                STRUCTURE-REF property:{%1}").arg(iter2.child_structure_ref.attr_id_ref);
    }
    }
    qDebug() << QString("        DIAG-COMMS");
    for (auto iter1 : iter.child_diag_comms.child_diag_service)
    {
    qDebug() << QString("          DIAG-SERVICE property:{%1 %2 %3 %4}").arg(iter1.attr_id).arg(iter1.attr_oid).arg(iter1.attr_addressing).arg(iter1.attr_transmission_mode);
    qDebug() << QString("            SHORT-NAME:%1").arg(iter1.child_short_name);
    qDebug() << QString("            LONG-NAME property:{%1} :%2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("            FUNCT-CLASS-REFS size:%1").arg(iter1.child_funct_class_refs.child_funct_class_ref.size());
    for (auto iter2 : iter1.child_funct_class_refs.child_funct_class_ref)
    {
    qDebug() << QString("              FUNCT-CLASS-REF property:{%1 %2 %3}").arg(iter2.attr_id_ref).arg(iter2.attr_docref).arg(iter2.attr_doctype);
    }
    qDebug() << QString("            PRE-CONDITION-STATE-REFS size:%1").arg(iter1.child_pre_condition_state_refs.child_pre_condition_state_ref.size());
    for (auto iter2 : iter1.child_pre_condition_state_refs.child_pre_condition_state_ref)
    {
    qDebug() << QString("              PRE-CONDITION-STATE-REF property:{%1 %2 %3}").arg(iter2.attr_id_ref).arg(iter2.attr_docref).arg(iter2.attr_doctype);
    }
    qDebug() << QString("            REQUEST-REF property:{%1 %2 %3}").arg(iter1.child_request_ref.attr_id_ref).arg(iter1.child_request_ref.attr_docref).arg(iter1.child_request_ref.attr_doctype);
    qDebug() << QString("            POS-RESPONSE-REFS size:%1").arg(iter1.child_pos_response_refs.child_pos_response_ref.size());
    for (auto iter2 : iter1.child_pos_response_refs.child_pos_response_ref)
    {
    qDebug() << QString("              POS-RESPONSE-REF property:{%1 %2 %3}").arg(iter2.attr_id_ref).arg(iter2.attr_docref).arg(iter2.attr_doctype);
    }
    qDebug() << QString("            NEG-RESPONSE-REFS size:%1").arg(iter1.child_neg_response_refs.child_neg_response_ref.size());
    for (auto iter2 : iter1.child_neg_response_refs.child_neg_response_ref)
    {
    qDebug() << QString("              NEG-RESPONSE-REF property:{%1}").arg(iter2.attr_id_ref);
    }
    qDebug() << QString("            POS-RESPONSE-SUPPRESSABLE");
    qDebug() << QString("              BIT-MASK:%1").arg(iter1.child_pos_response_suppressable.child_bit_mask.data_value);
    qDebug() << QString("              CODED-CONST-SNREF property:{%1}").arg(iter1.child_pos_response_suppressable.child_coded_const_snref.attr_short_name);
    }
    qDebug() << QString("        NEG-RESPONSES size:%1").arg(iter.child_neg_responses.child_neg_response.size());
    for (auto iter1 : iter.child_neg_responses.child_neg_response)
    {
    qDebug() << QString("          NEG-RESPONSE property:{%1 %2}").arg(iter1.attr_id).arg(iter1.attr_oid);
    qDebug() << QString("            SHORT-NAME:%1").arg(iter1.child_short_name);
    qDebug() << QString("            LONG-NAME property:{%1} :%2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("            PARAMS size:%1").arg(iter1.child_params.child_param.size());
    for (auto iter2 : iter1.child_params.child_param)
    {
    qDebug() << QString("              PARAM property:{%1 %2 %3}").arg(iter2.attr_xsi_type).arg(iter2.attr_oid).arg(iter2.attr_semantic);
    qDebug() << QString("                SHORT-NAME:%1").arg(iter2.child_short_name);
    qDebug() << QString("                LONG-NAME property:{%1} %2").arg(iter2.child_long_name.attr_ti).arg(iter2.child_long_name.data_value);
    qDebug() << QString("                BYTE-POSITION:%1").arg(iter2.child_byte_position.data_value);
    qDebug() << QString("                BIT-POSITION:%1").arg(iter2.child_bit_position.data_value);
    qDebug() << QString("                CODED-VALUE:%1").arg(iter2.child_coded_value.data_value);
    qDebug() << QString("                DIAG-CODED-TYPE property:{%1 %2 %3}").arg(iter2.child_diag_coded_type.attr_xsi_type).arg(iter2.child_diag_coded_type.attr_base_type_encoding).arg(iter2.child_diag_coded_type.attr_base_data_type);
    qDebug() << QString("                  BIT-LENGTH:%1").arg(iter2.child_diag_coded_type.child_bit_length.data_value);
    }
    }
    qDebug() << QString("        COMPARAM-REFS size:%1").arg(iter.child_comparam_refs.child_comparam_ref.size());
    for (auto iter1 : iter.child_comparam_refs.child_comparam_ref)
    {
    qDebug() << QString("          COMPARAM-REF property:{%1 %2 %3}").arg(iter1.attr_id_ref).arg(iter1.attr_docref).arg(iter1.attr_doctype);
    qDebug() << QString("            SIMPLE-VALUE size:%1").arg(iter1.child_simple_value.data_value);
    qDebug() << QString("            PROTOCOL-SNREF property:{%1}").arg(iter1.child_protocol_snref.attr_short_name);
    qDebug() << QString("            PROT-STACK-SNREF property:{%1}").arg(iter1.child_prot_stack_snref.attr_short_name);
    }
    qDebug() << QString("        ECU-VARIANT-PATTERNS size:%1").arg(iter.child_ecu_variant_patterns.child_ecu_variant_pattern.size());
    for (auto iter1 : iter.child_ecu_variant_patterns.child_ecu_variant_pattern)
    {
    qDebug() << QString("          ECU-VARIANT-PATTERN");
    qDebug() << QString("            MATCHING-PARAMETERS size:%1").arg(iter1.child_matching_parameters.child_matching_parameter.size());
    for (auto iter2 : iter1.child_matching_parameters.child_matching_parameter)
    {
    qDebug() << QString("              MATCHING-PARAMETER");
    qDebug() << QString("                EXPECTED-VALUE:%1").arg(iter2.child_expected_value.data_value);
    qDebug() << QString("                DIAG-COMM-SNREF property:{%1}").arg(iter2.child_diag_comm_snref.attr_short_name);
    qDebug() << QString("                OUT-PARAM-IF-SNREF property:{%1}").arg(iter2.child_out_param_if_snref.attr_short_name);
    }
    }
    qDebug() << QString("        PARENT-REFS size:%1").arg(iter.child_parent_refs.child_parent_ref.size());
    for (auto iter1: iter.child_parent_refs.child_parent_ref)
    {
    qDebug() << QString("          PARENT-REF property:{%1 %2 %3 %4}").arg(iter1.attr_xsi_type).arg(iter1.attr_id_ref).arg(iter1.attr_docref).arg(iter1.attr_doctype);
    }
    }
    } else {

    }
    qDebug() << QString("    FUNCTIONAL-GROUPS size:%1").arg(odx_.child_diag_layer_container.child_functional_groups.child_functional_group.size());
    for (auto iter : odx_.child_diag_layer_container.child_functional_groups.child_functional_group)
    {
    qDebug() << QString("      FUNCTIONAL-GROUP property:{%1 %2}").arg(iter.attr_id).arg(iter.attr_oid);
    qDebug() << QString("        SHORT-NAME:%1").arg(iter.child_short_name.data_value);
    qDebug() << QString("        COMPARAM-REFS size:%1").arg(iter.child_comparam_refs.child_comparam_ref.size());
    for (auto iter1 : iter.child_comparam_refs.child_comparam_ref)
    {
    qDebug() << QString("          COMPARAM-REF property:{%1 %2 %3}").arg(iter1.attr_id_ref).arg(iter1.attr_docref).arg(iter1.attr_doctype);
    if ("SIMPLE-VALUE" == iter1.value_type)
    {
    qDebug() << QString("            SIMPLE-VALUE:%1").arg(iter1.child_simple_value.data_value);
    } else {
    qDebug() << QString("            COMPLEX-VALUE");
    for (auto iter2 : iter1.child_complex_value.child_simple_value)
    {
    qDebug() << QString("              SIMPLE-VALUE:%1").arg(iter1.child_simple_value.data_value);
    }
    }
    }
    qDebug() << QString("        PARENT-REFS size:%1").arg(iter.child_parent_refs.child_parent_ref.size());
    for (auto iter1 : iter.child_parent_refs.child_parent_ref)
    {
    qDebug() << QString("          PARENT-REF property:{%1 %2 %3 %4}").arg(iter1.attr_docref).arg(iter1.attr_doctype).arg(iter1.attr_id_ref).arg(iter1.attr_xsi_type);
    }
    }
}

int LoadODX_D::read_odx(const pugi::xml_node &node, ODX_D &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "xmlns:xsi") == 0) {
            data.attr_xmlns_xsi = attr.value();
        } else if (strcmp(attr.name(), "MODEL-VERSION") == 0) {
            data.attr_model_version = attr.value();
        } else if (strcmp(attr.name(), "xsi:noNamespaceSchemaLocation") == 0) {
            data.attr_xsi_noNamespaceSchemaLocation = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DIAG-LAYER-CONTAINER") == 0) {
            if (read_diag_layer_container(child, data.child_diag_layer_container)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_functional_group(const pugi::xml_node &node, FUNCTIONAL_GROUP &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name.data_value)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "COMPARAM-REFS") == 0) {
            if (read_comparam_refs(child, data.child_comparam_refs)) {
                result = -1;
                break;
            }

        } else if (strcmp(child.name(), "PARENT-REFS") == 0) {
            if (read_parent_refs(child, data.child_parent_refs)) {
                result = -1;
                break;
            }

        }
    }

    return result;
}

int LoadODX_D::read_functional_groups(const pugi::xml_node &node, FUNCTIONAL_GROUPS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "FUNCTIONAL-GROUP ") == 0) {
            FUNCTIONAL_GROUP elem;
            if (read_functional_group(child, elem)) {
                result = -1;
                break;
            }
            data.child_functional_group.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_comparam_spec_ref(const pugi::xml_node &node, COMPARAM_SPEC_REF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "DOCREF") == 0) {
            data.attr_docref = attr.value();
        } else if (strcmp(attr.name(), "DOCTYPE") == 0) {
            data.attr_doctype = attr.value();
        }  else if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_protocol(const pugi::xml_node &node, PROTOCOL &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name.data_value)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "COMPARAM-SPEC-REF") == 0) {
            if (read_comparam_spec_ref(child, data.child_comparam_spec_ref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PROT-STACK-SNREF") == 0) {
            if (read_prot_stack_snref(child, data.child_prot_stack_snref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PARENT-REFS") == 0) {
            if (read_parent_refs(child, data.child_parent_refs)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_protocols(const pugi::xml_node &node, PROTOCOLS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "PROTOCOL") == 0) {
            PROTOCOL elem;
            if (read_protocol(child, elem)) {
                result = -1;
                break;
            }
            data.child_protocol.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_import_ref(const pugi::xml_node &node, IMPORT_REF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "DOCREF") == 0) {
            data.attr_docref = attr.value();
        } else if (strcmp(attr.name(), "DOCTYPE") == 0) {
            data.attr_doctype = attr.value();
        } else if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_import_refs(const pugi::xml_node &node, IMPORT_REFS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "IMPORT-REF") == 0) {
            IMPORT_REF elem;
            if (read_import_ref(child, elem)) {
                result = -1;
                break;
            }
            data.child_improt_ref.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_ecu_shared_data(const pugi::xml_node &node, ECU_SHARED_DATA &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name.data_value)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DIAG-DATA-DICTIONARY-SPEC") == 0) {
            if (read_diag_data_dictionary_spec(child, data.child_diag_data_dictionary_spec)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "IMPORT-REFS") == 0) {
            if (read_import_refs(child, data.child_import_refs)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_ecu_shared_datas(const pugi::xml_node &node, ECU_SHARED_DATAS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "ECU-SHARED-DATA") == 0) {
            ECU_SHARED_DATA elem;
            if (read_ecu_shared_data(child, elem)) {
                result = -1;
                break;
            }
            data.child_ecu_shated_data.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_diag_layer_container(const pugi::xml_node &node, DIAG_LAYER_CONTAINER &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "BASE-VARIANTS") == 0) {
            data.variants_type = "BASE-VARIANTS";
            if (read_base_variants(child, data.child_base_variants)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "ECU-VARIANTS") == 0) {
            data.variants_type = "ECU-VARIANTS";
            if (read_ecu_variants(child, data.child_ecu_variants)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "FUNCTIONAL-GROUPS") == 0) {
            if (read_functional_groups(child, data.child_functional_groups)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PROTOCOLS") == 0) {
            if (read_protocols(child, data.child_protocols)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "ECU-SHARED-DATAS") == 0) {
            if (read_ecu_shared_datas(child, data.child_ecu_shared_datas)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_simple_value(const pugi::xml_node &node, SIMPLE_VALUE &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_protocol_snref(const pugi::xml_node &node, PROTOCOL_SNREF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_prot_stack_snref(const pugi::xml_node &node, PROT_STACK_SNREF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_complex_value(const pugi::xml_node &node, COMPLEX_VALUE &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SIMPLE-VALUE") == 0) {
            SIMPLE_VALUE elem;
            if (read_simple_value(child, elem)) {
                result = -1;
                break;
            }
            data.child_simple_value.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_comparam_ref(const pugi::xml_node &node, COMPARAM_REF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        } else if (strcmp(attr.name(), "DOCREF") == 0) {
            data.attr_docref = attr.value();
        } else if (strcmp(attr.name(), "DOCTYPE") == 0) {
            data.attr_doctype = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SIMPLE-VALUE") == 0) {
            data.value_type = "SIMPLE-VALUE";
            if (read_simple_value(child, data.child_simple_value)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PROTOCOL-SNREF") == 0) {
            if (read_protocol_snref(child, data.child_protocol_snref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PROT-STACK-SNREF") == 0) {
            if (read_prot_stack_snref(child, data.child_prot_stack_snref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "COMPLEX-VALUE") == 0) {
            data.value_type = "COMPLEX-VALUE";
            if (read_complex_value(child, data.child_complex_value)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_comparam_refs(const pugi::xml_node &node, COMPARAM_REFS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "COMPARAM-REF") == 0) {
            COMPARAM_REF elem;
            if (read_comparam_ref(child, elem)) {
                result = -1;
                break;
            }
            data.child_comparam_ref.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_parent_ref(const pugi::xml_node &node, PARENT_REF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "xsi:type") == 0) {
            data.attr_xsi_type = attr.value();
        } else if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        } else if (strcmp(attr.name(), "DOCREF") == 0) {
            data.attr_docref = attr.value();
        } else if (strcmp(attr.name(), "DOCTYPE") == 0) {
            data.attr_doctype = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_parent_refs(const pugi::xml_node &node, PARENT_REFS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "PARENT-REF") == 0) {
            PARENT_REF elem;
            if (read_parent_ref(child, elem)) {
                result = -1;
                break;
            }
            data.child_parent_ref.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_base_variant(const pugi::xml_node &node, BASE_VARIANT &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "COMPARAM-REFS") == 0) {
            if (read_comparam_refs(child, data.child_comparam_refs)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PARENT-REFS") == 0) {
            if (read_parent_refs(child, data.child_parent_refs)) {
                result = -1;
                break;
            }

        }
    }

    return result;
}

int LoadODX_D::read_base_variants(const pugi::xml_node &node, BASE_VARIANTS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "BASE-VARIANT") == 0) {
            BASE_VARIANT elem;
            if (read_base_variant(child, elem)) {
                result = -1;
                break;
            }
            data.child_base_variant.push_back(elem);
        }
    }

    return result;
}




int LoadODX_D::read_trouble_code(const pugi::xml_node &node, TROUBLE_CODE &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_display_trouble_code(const pugi::xml_node &node, DISPLAY_TROUBLE_CODE &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_text(const pugi::xml_node &node, TEXT &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "TI") == 0) {
            data.attr_ti = attr.value();
        }
    }

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_level(const pugi::xml_node &node, LEVEL &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_sdg_caption(const pugi::xml_node &node, SDG_CAPTION &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name.data_value)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_sd(const pugi::xml_node &node, SD &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SI") == 0) {
            data.attr_si = attr.value();
        } else if (strcmp(attr.name(), "TI") == 0) {
            data.attr_ti = attr.value();
        }
    }

    data.data_value = node.child_value();

    return result;
}
int LoadODX_D::read_sdg(const pugi::xml_node &node, SDG &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SDG-CAPTION") == 0) {
            if (read_sdg_caption(child, data.child_sdg_caption)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "SD") == 0) {
            SD elem;
            if (read_sd(child, elem)) {
                result = -1;
                break;
            }
            data.child_sd.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_sdgs(const pugi::xml_node &node, SDGS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SDG") == 0) {
            SDG elem;
            if (read_sdg(child, elem)) {
                result = -1;
                break;
            }
            data.child_sdgs.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_dtc(const pugi::xml_node &node, DTC &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "TROUBLE-CODE") == 0) {
            if (read_trouble_code(child, data.child_trouble_code)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DISPLAY-TROUBLE-CODE") == 0) {
            if (read_display_trouble_code(child, data.child_display_trouble_code)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "TEXT") == 0) {
            if (read_text(child, data.child_text)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LEVEL") == 0) {
            if (read_level(child, data.child_level)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "SDGS") == 0) {
            if (read_sdgs(child, data.child_sdgs)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_dtcs(const pugi::xml_node &node, DTCS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        DTC elem;
        if (strcmp(child.name(), "DTC") == 0) {
            DTC elem;
            if (read_dtc(child, elem)) {
                result = -1;
                break;
            }
            data.child_dtc.push_back(elem);
        }
    }

    return result;
}


int LoadODX_D::read_dtc_dop(const pugi::xml_node &node, DTC_DOP &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DIAG-CODED-TYPE") == 0) {
            if (odxcmn::read_diag_coded_type(child, data.child_diag_coded_type)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PHYSICAL-TYPE") == 0) {
            if (odxcmn::read_physical_type(child, data.child_physical_type)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "COMPU-METHOD") == 0) {
            if (odxcmn::read_compu_method(child, data.child_compu_method)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DTCS") == 0) {
            if (read_dtcs(child, data.child_dtcs)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_dtc_dops(const pugi::xml_node &node, DTC_DOPS &data) {
    int result = 0;



    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DTC-DOP") == 0) {
            DTC_DOP elem;
            if (read_dtc_dop(child, elem)) {
                result = -1;
                break;
            }
            data.child_dtc_drop.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_data_object_prop(const pugi::xml_node &node, DATA_OBJECT_PROP &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "COMPU-METHOD") == 0) {
            if (odxcmn::read_compu_method(child, data.child_compu_method)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DIAG-CODED-TYPE") == 0) {
            if (odxcmn::read_diag_coded_type(child, data.child_diag_coded_type)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PHYSICAL-TYPE") == 0) {
            if (odxcmn::read_physical_type(child, data.child_physical_type)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_data_object_props(const pugi::xml_node &node, DATA_OBJECT_PROPS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DATA-OBJECT-PROP") == 0) {
            DATA_OBJECT_PROP elem;
            if (read_data_object_prop(child, elem)) {
                result = -1;
                break;
            }
            data.child_data_object_prop.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_structure(const pugi::xml_node &node, STRUCTURE &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PARAMS") == 0) {
            if (read_params(child, data.child_params)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_structures(const pugi::xml_node &node, STRUCTURES &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "STRUCTURE") == 0) {
            STRUCTURE elem;
            if (read_structure(child, elem)) {
                result = -1;
                break;
            }
            data.child_structure.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_key_dop_ref(const pugi::xml_node &node, KEY_DOP_REF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_structure_ref(const pugi::xml_node &node, STRUCTURE_REF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_key(const pugi::xml_node &node, KEY &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_table_row(const pugi::xml_node &node, TABLE_ROW &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        } else if (strcmp(attr.name(), "IS-EXECUTABLE") == 0) {
            data.attr_is_executable = attr.value();
        } else if (strcmp(attr.name(), "IS-MANDATORY") == 0) {
            data.attr_is_mandatory = attr.value();
        } else if (strcmp(attr.name(), "IS-FINAL") == 0) {
            data.attr_is_final = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name.data_value)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "STRUCTURE-REF") == 0) {
            if (read_structure_ref(child, data.child_structure_ref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "KEY") == 0) {
            if (read_key(child, data.child_key)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_table(const pugi::xml_node &node, TABLE &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "KEY-DOP-REF") == 0) {
            if (read_key_dop_ref(child, data.child_key_drop_ref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "TABLE-ROW") == 0) {
            TABLE_ROW elem;
            if (read_table_row(child, elem)) {
                result = -1;
                break;
            }
            data.child_table_row.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_tables(const pugi::xml_node &node, TABLES &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "TABLE") == 0) {
            TABLE elem;
            if (read_table(child, elem)) {
                result = -1;
                break;
            }
            data.child_table.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_diag_data_dictionary_spec(const pugi::xml_node &node, DIAG_DATA_DICTIONARY_SPEC &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DTC-DOPS") == 0) {
            if (read_dtc_dops(child, data.child_dtc_dops)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DATA-OBJECT-PROPS") == 0) {
            if (read_data_object_props(child, data.child_data_object_props)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "STRUCTURES") == 0) {
            if (read_structures(child, data.child_structures)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "TABLES") == 0) {
            if (read_tables(child, data.child_tables)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_funct_class_ref(const pugi::xml_node &node, FUNCT_CLASS_REF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        } else if (strcmp(attr.name(), "DOCREF") == 0) {
            data.attr_docref = attr.value();
        } else if (strcmp(attr.name(), "DOCTYPE") == 0) {
            data.attr_doctype = attr.value();
        }
    }

    return  result;
}


int LoadODX_D::read_funct_class_refs(const pugi::xml_node &node, FUNCT_CLASS_REFS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "FUNCT-CLASS-REF") == 0) {
            FUNCT_CLASS_REF elem;
            if (read_funct_class_ref(child, elem)) {
                result = -1;
                break;
            }
            data.child_funct_class_ref.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_pre_condition_state_ref(const pugi::xml_node &node, PRE_CONDITION_STATE_REF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        } else if (strcmp(attr.name(), "DOCREF") == 0) {
            data.attr_docref = attr.value();
        } else if (strcmp(attr.name(), "DOCTYPE") == 0) {
            data.attr_doctype = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_pre_condition_state_refs(const pugi::xml_node &node, PRE_CONDITION_STATE_REFS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "PRE-CONDITION-STATE-REF") == 0) {
            PRE_CONDITION_STATE_REF elem;
            if (read_pre_condition_state_ref(child, elem)) {
                result = -1;
                break;
            }
            data.child_pre_condition_state_ref.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_request_ref(const pugi::xml_node &node, REQUEST_REF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        } else if (strcmp(attr.name(), "DOCREF") == 0) {
            data.attr_docref = attr.value();
        } else if (strcmp(attr.name(), "DOCTYPE") == 0) {
            data.attr_doctype = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_pos_response_ref(const pugi::xml_node &node, POS_RESPONSE_REF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        } else if (strcmp(attr.name(), "DOCREF") == 0) {
            data.attr_docref = attr.value();
        } else if (strcmp(attr.name(), "DOCTYPE") == 0) {
            data.attr_doctype = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_pos_response_refs(const pugi::xml_node &node, POS_RESPONSE_REFS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "POS-RESPONSE-REF") == 0) {
            POS_RESPONSE_REF elem;
            if (read_pos_response_ref(child, elem)) {
                result = -1;
                break;
            }
            data.child_pos_response_ref.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_neg_response_ref(const pugi::xml_node &node, NEG_RESPONSE_REF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_neg_response_refs(const pugi::xml_node &node, NEG_RESPONSE_REFS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "NEG-RESPONSE-REF") == 0) {
            NEG_RESPONSE_REF elem;
            if (read_neg_response_ref(child, elem)) {
                result = -1;
                break;
            }
            data.child_neg_response_ref.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_bit_mask(const pugi::xml_node &node, BIT_MASK &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_coded_const_snref(const pugi::xml_node &node, CODED_CONST_SNREF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_pos_response_supperssable(const pugi::xml_node &node, POS_RESPONSE_SUPPRESSABLE &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "BIT-MASK") == 0) {
            if (read_bit_mask(child, data.child_bit_mask)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "CODED-CONST-SNREF") == 0) {
            if (read_coded_const_snref(child, data.child_coded_const_snref)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}


int LoadODX_D::read_diag_service(const pugi::xml_node &node, DIAG_SERVICE &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        } else if (strcmp(attr.name(), "ADDRESSING") == 0) {
            data.attr_addressing = attr.value();
        } else if (strcmp(attr.name(), "TRANSMISSION-MODE") == 0) {
            data.attr_transmission_mode = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "FUNCT-CLASS-REFS") == 0) {
            if (read_funct_class_refs(child, data.child_funct_class_refs)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PRE-CONDITION-STATE-REFS") == 0) {
            if (read_pre_condition_state_refs(child, data.child_pre_condition_state_refs)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "REQUEST-REF") == 0) {
            if (read_request_ref(child, data.child_request_ref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "POS-RESPONSE-REFS") == 0) {
            if (read_pos_response_refs(child, data.child_pos_response_refs)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "NEG-RESPONSE-REFS") == 0) {
            if (read_neg_response_refs(child, data.child_neg_response_refs)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "POS-RESPONSE-SUPPRESSABLE") == 0) {
            if (read_pos_response_supperssable(child, data.child_pos_response_suppressable)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_diag_comms(const pugi::xml_node &node, DIAG_COMMS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DIAG-SERVICE") == 0) {
            DIAG_SERVICE elem;
            if (read_diag_service(child, elem)) {
                result = -1;
                break;
            }
            data.child_diag_service.push_back(elem);
        }
    }
    return result;
}

int LoadODX_D::read_byte_position(const pugi::xml_node &node, BYTE_POSITION &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_bit_position(const pugi::xml_node &node, BIT_POSITION &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_coded_value(const pugi::xml_node &node, CODED_VALUE &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_dop_ref(const pugi::xml_node &node, DOP_REF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_physical_default_value(const pugi::xml_node &node, PHYSICAL_DEFAULT_VALUE &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_param(const pugi::xml_node &node, PARAM &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "xsi:type") == 0) {
            data.attr_xsi_type = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        } else if (strcmp(attr.name(), "SEMANTIC") == 0) {
            data.attr_semantic = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "BYTE-POSITION") == 0) {
            if (read_byte_position(child, data.child_byte_position)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "BIT-POSITION") == 0) {
            if (read_bit_position(child, data.child_bit_position)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DOP-REF") == 0) {
            if (read_dop_ref(child, data.child_dop_ref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "CODED-VALUE") == 0) {
            if (read_coded_value(child, data.child_coded_value)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DIAG-CODED-TYPE") == 0) {
            if (odxcmn::read_diag_coded_type(child, data.child_diag_coded_type)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "SDGS ") == 0) {
            if (read_sdgs(child, data.child_sdgs)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PHYSICAL-DEFAULT-VALUE")) {
            if (read_physical_default_value(child, data.child_physical_default_value)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_params(const pugi::xml_node &node, PARAMS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "PARAM") == 0) {
            PARAM elem;
            if (read_param(child, elem)) {
                result = -1;
                break;
            }
            data.child_param.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_neg_response(const pugi::xml_node &node, NEG_RESPONSE &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PARAMS") == 0) {
            if (read_params(child, data.child_params)) {
                result = -1;
                break;
            }
        }
    }
    return result;
}

int LoadODX_D::read_neg_responses(const pugi::xml_node &node, NEG_RESPONSES &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "NEG-RESPONSE") == 0) {
            NEG_RESPONSE elem;
            if (read_neg_response(child, elem)) {
                result = -1;
                break;
            }
            data.child_neg_response.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_expected_value(const pugi::xml_node &node, EXPECTED_VALUE &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_diag_comm_snref(const pugi::xml_node &node, DIAG_COMM_SNREF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_out_param_if_snref(const pugi::xml_node &node, OUT_PARAM_IF_SNREF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_matching_parameter(const pugi::xml_node &node, MATCHING_PARAMETER &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "EXPECTED-VALUE") == 0) {
            if (read_expected_value(child, data.child_expected_value)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DIAG-COMM-SNREF") == 0) {
            if (read_diag_comm_snref(child, data.child_diag_comm_snref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "OUT-PARAM-IF-SNREF") == 0) {
            if (read_out_param_if_snref(child, data.child_out_param_if_snref)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_matching_parameters(const pugi::xml_node &node, MATCHING_PARAMETERS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "MATCHING-PARAMETER") == 0) {
            MATCHING_PARAMETER elem;
            if (read_matching_parameter(child, elem)) {
                result = -1;
                break;
            }
            data.child_matching_parameter.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_ecu_variant_pattern(const pugi::xml_node &node, ECU_VARIANT_PATTERN &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "MATCHING-PARAMETERS") == 0) {
            if (read_matching_parameters(child, data.child_matching_parameters)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_ecu_variant_patterns(const pugi::xml_node &node, ECU_VARIANT_PATTERNS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "ECU-VARIANT-PATTERN") == 0) {
            ECU_VARIANT_PATTERN elem;
            if (read_ecu_variant_pattern(child, elem)) {
                result = -1;
                break;
            }
            data.child_ecu_variant_pattern.push_back(elem);
        }
    }

    return result;
}

int LoadODX_D::read_ecu_variant(const pugi::xml_node &node, ECU_VARIANT &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DIAG-DATA-DICTIONARY-SPEC") == 0) {
            if (read_diag_data_dictionary_spec(child, data.child_diag_data_dictionary_spec)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DIAG-COMMS") == 0) {
            if (read_diag_comms(child, data.child_diag_comms)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "NEG-RESPONSES") == 0) {
            if (read_neg_responses(child, data.child_neg_responses)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "COMPARAM-REFS") == 0) {
            if (read_comparam_refs(child, data.child_comparam_refs)) {
                result = -1;
                break;
            }
        }  else if (strcmp(child.name(), "ECU-VARIANT-PATTERNS") == 0) {
            if (read_ecu_variant_patterns(child, data.child_ecu_variant_patterns)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PARENT-REFS") == 0) {
            if (read_parent_refs(child, data.child_parent_refs)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_ecu_variants(const pugi::xml_node &node, ECU_VARIANTS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "ECU-VARIANT") == 0) {
            ECU_VARIANT elem;
            if (read_ecu_variant(child, elem)) {
                result = -1;
                break;
            }
            data.child_ecu_variant.push_back(elem);
        }
    }

    return result;
}

