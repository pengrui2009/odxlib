#include "load_odx_d.h"

#include <iostream>
#include <QDebug>

LoadODX_D::LoadODX_D()
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
    qDebug() << QString("  DIAG-LAYER-CONTAINER property:{%1 :2}").arg(odx_.child_diag_layer_container.attr_id).arg(odx_.child_diag_layer_container.attr_oid);
    qDebug() << QString("    SHORT-NAME:%1").arg(odx_.child_diag_layer_container.child_short_name);
    qDebug() << QString("    LONG-NAME: property{%1} :2").arg(odx_.child_diag_layer_container.child_long_name.attr_ti).arg(odx_.child_diag_layer_container.child_long_name.data_value);
    if ("BASE-VARIANTS" == odx_.child_diag_layer_container.variants_type) {
    qDebug() << QString("    BASE-VARIANTS size:%1").arg(odx_.child_diag_layer_container.variants_data.child_base_variants.child_base_variant.size());
    for (auto iter : odx_.child_diag_layer_container.variants_data.child_base_variants.child_base_variant)
    {
    qDebug() << QString("      BASE-VARIANT property:{%1 :2}").arg(iter.attr_id).arg(iter.attr_oid);
    qDebug() << QString("        SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("        LONG-NAME: property:{%1} :%2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);
    qDebug() << QString("        COMPARAM_REFS size:%1").arg(iter.child_comparam_refs.child_comparam_ref.size());
    for (auto iter1 : iter.child_comparam_refs.child_comparam_ref)
    {
    qDebug() << QString("          COMPARAM_REF property:{%1 %2 %3} ").arg(iter1.attr_id_ref).arg(iter1.attr_docref).arg(iter1.attr_doctype);
    if ("COMPLEX-VALUE" == iter1.value_type) {
    qDebug() << QString("            COMPLEX-VALUE size:%1").arg(iter1.child_complex_value.child_simple_value.size());
    for (auto iter2 : iter1.child_complex_value.child_simple_value)
    {
    qDebug() << QString("              SIMPLE-VALUE :%1").arg(iter2.data_value);
    }
    } else if ("COMPLEX-VALUE" == iter1.value_type) {
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

//    qDebug() << QString("  DIAG-LAYER-CONTAINER property:{%1 :2}");
    } else {

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
            if (read_base_variants(child, data.variants_data.child_base_variants)) {
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

int LoadODX_D::read_bit_length(const pugi::xml_node &node, BIT_LENGTH &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_diag_coded_type(const pugi::xml_node &node, DIAG_CODED_TYPE &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "xsi:type") == 0) {
            data.attr_xsi_type = attr.value();
        } else if (strcmp(attr.name(), "BASE-DATA-TYPE") == 0) {
            data.attr_base_data_type = attr.value();
        } else if (strcmp(attr.name(), "BASE-TYPE-ENCODING") == 0) {
            data.attr_base_type_encoding = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "BIT-LENGTH") == 0) {
            if (read_bit_length(child, data.child_bit_length)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_D::read_physical_type(const pugi::xml_node &node, PHYSICAL_TYPE &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "BASE-DATA-TYPE") == 0) {
            data.attr_base_data_type = attr.value();
        } else if (strcmp(attr.name(), "DISPLAY-RADIX") == 0) {
            data.attr_display_radix = attr.value();
        }
    }

    return result;
}

int LoadODX_D::read_category(const pugi::xml_node &node, CATEGORY &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int LoadODX_D::read_compu_method(const pugi::xml_node &node, COMPU_METHOD &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "CATEGORY") == 0) {
            if (read_category(child, data.child_category)) {
                result = -1;
                break;
            }
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
        }
    }

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
            if (read_diag_coded_type(child, data.child_diag_coded_type)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PHYSICAL-TYPE") == 0) {
            if (read_physical_type(child, data.child_physical_type)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "COMPU-METHOD") == 0) {
            if (read_compu_method(child, data.child_compu_method)) {
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

int LoadODX_D::read_diag_data_dictionary_spec(const pugi::xml_node &node, DIAG_DATA_DICTIONARY_SPEC &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DTC-DOPS") == 0) {
            if (read_dtc_dops(child, data.child_dtc_dops)) {
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
        if (strcmp(child.name(), "NEG-RESPONSE-REFS") == 0) {
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
        } else if (strcmp(child.name(), "CODED-VALUE") == 0) {
            if (read_coded_value(child, data.child_coded_value)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DIAG-CODED-TYPE ") == 0) {
            if (read_diag_coded_type(child, data.child_diag_coded_type)) {
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

