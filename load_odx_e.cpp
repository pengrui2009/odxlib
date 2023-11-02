#include "load_odx_e.h"

#include <iostream>
#include <QDebug>

LoadODX_E::LoadODX_E() :
    doc_ptr_{std::make_unique<pugi::xml_document>()}
{

}

int LoadODX_E::load(const QByteArray &fileData, ODX_E &odx)
{
    pugi::xml_parse_result result = doc_ptr_->load_buffer(fileData.constData(), fileData.length());
    if (!result) {
        std::cout << "LoadIndex load content failed!" << std::endl;
        return -1;
    }

    // Access the root node: ODX
    pugi::xml_node root = doc_ptr_->child("ODX");

    return read_odx(root, odx);
}

void LoadODX_E::print(const ODX_E &odx)
{
    qDebug() << QString("ODX property:{%1 %2 %3}").arg(odx.attr_model_version).arg(odx.attr_xmlns_xsi).arg(odx.attr_xsi_nonamespaceschemaLocation);
    qDebug() << QString("  ECU-CONFIG property:{%1 %2}").arg(odx.child_ecu_config.attr_id).arg(odx.child_ecu_config.attr_oid);
    qDebug() << QString("    SHORT-NAME:%1").arg(odx.child_ecu_config.child_short_name);
    qDebug() << QString("    LONG-NAME: property:{%1} %2").arg(odx.child_ecu_config.child_long_name.attr_ti).arg(odx.child_ecu_config.child_long_name.data_value);
    qDebug() << QString("    CONFIG-DATAS size:%1").arg(odx.child_ecu_config.child_config_datas.child_config_data.size());
    for (auto iter : odx.child_ecu_config.child_config_datas.child_config_data)
    {
    qDebug() << QString("      CONFIG-DATA");
    qDebug() << QString("        SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("        LONG-NAME: property:{%1} %2").arg(iter.child_long_name.data_value);
    qDebug() << QString("        VALID-BASE-VARIANTS size:%1").arg(iter.child_valid_base_variants.child_valid_base_variant.size());
    for (auto iter1 : iter.child_valid_base_variants.child_valid_base_variant)
    {
    qDebug() << QString("          VALID-BASE-VARIANT");
    qDebug() << QString("            ECU-VARIANT-SNREFS size:%1").arg(iter1.child_ecu_variant_snrefs.child_ecu_variant_snref.size());
    for (auto iter2 : iter1.child_ecu_variant_snrefs.child_ecu_variant_snref)
    {
    qDebug() << QString("              ECU-VARIANT-SNREF property:{%1}").arg(iter2.attr_short_name);
    }
    qDebug() << QString("            BASE-VARIANT-SNREF property:{%1}").arg(iter1.child_base_variant_snref.attr_short_name);
    qDebug() << QString("          VALID-BASE-VARIANT");
    }
    qDebug() << QString("        CONFIG-RECORDS size:%1").arg(iter.child_config_records.child_config_record.size());
    for (auto iter1 : iter.child_config_records.child_config_record)
    {
    qDebug() << QString("          CONFIG-RECORD");
    qDebug() << QString("            SHORT-NAME:%1").arg(iter1.child_short_name);
    qDebug() << QString("            LONG-NAME: property:{%1} %2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("            DIAG-COMM-DATA-CONNECTORS size:%1").arg(iter1.child_diag_comm_data_connectors.child_diag_comm_data_connector.size());
    for (auto iter2 : iter1.child_diag_comm_data_connectors.child_diag_comm_data_connector)
    {
    qDebug() << QString("              DIAG-COMM-DATA-CONNECTOR");
    qDebug() << QString("                UNCOMPRESSED-SIZE:%1").arg(iter2.child_uncompressed_size);
    qDebug() << QString("                SOURCE-START-ADDRESS:%1").arg(iter2.child_source_start_address);
    qDebug() << QString("                READ-DIAG-COMM-CONNECTOR");
    qDebug() << QString("                  READ-DIAG-COMM-SNREF property:{%1}").arg(iter2.child_read_diag_comm_connector.child_read_diag_comm_snref.attr_short_name);
    qDebug() << QString("                  READ-DATA-SNREF property:{%1}").arg(iter2.child_read_diag_comm_connector.child_read_data_snref.attr_short_name);
    qDebug() << QString("                WRITE-DIAG-COMM-CONNECTOR");
    qDebug() << QString("                  WRITE-DIAG-COMM-SNREF property:{%1}").arg(iter2.child_write_diag_comm_connector.child_write_diag_comm_snref.attr_short_name);
    qDebug() << QString("                  WRITE-DATA-SNREF property:{%1}").arg(iter2.child_write_diag_comm_connector.child_write_data_snref.attr_short_name);
    }
    qDebug() << QString("            DATA-RECORDS size:%1").arg(iter1.child_data_records.child_data_record.size());
    for (auto iter2 : iter1.child_data_records.child_data_record)
    {
    qDebug() << QString("              DATA-RECORD property:{%1}").arg(iter2.attr_dataformat);
    qDebug() << QString("                SHORT-NAME:%1").arg(iter2.child_short_name);
    qDebug() << QString("                LONG-NAME: property:{%1} %2").arg(iter2.child_long_name.attr_ti).arg(iter2.child_long_name.data_value);
    qDebug() << QString("                DATA:%1").arg(iter2.child_data);
    }
    qDebug() << QString("            OPTION-ITEMS size:%1").arg(iter1.child_option_items.child_option_item.size());
    for (auto iter2 : iter1.child_option_items.child_option_item)
    {
    qDebug() << QString("              OPTION-ITEM");
    qDebug() << QString("                SHORT-NAME:%1").arg(iter2.child_short_name);
    qDebug() << QString("                LONG-NAME property:{%1} %2").arg(iter2.child_long_name.attr_ti).arg(iter2.child_long_name.data_value);
    qDebug() << QString("                BYTE-POSITION:%1").arg(iter2.child_byte_position.data_value);
    qDebug() << QString("                BIT-POSITION:%1").arg(iter2.child_bit_position.data_value);
    qDebug() << QString("                DATA-OBJECT-PROP-REF property:{%1}").arg(iter2.child_data_object_prop_ref.attr_id_ref);
    qDebug() << QString("                PHYSICAL-DEFAULT-VALUE:%1").arg(iter2.child_physical_default_value.data_value);
    }
    }
    }
    qDebug() << QString("    CONFIG-DATA-DICTIONARY-SPEC");
    qDebug() << QString("      DATA-OBJECT-PROPS size:%1").arg(odx.child_ecu_config.child_config_data_dictionary_spec.child_data_object_props.child_data_object_prop.size());
    for (auto iter : odx.child_ecu_config.child_config_data_dictionary_spec.child_data_object_props.child_data_object_prop)
    {
    qDebug() << QString("        DATA-OBJECT-PROP property:{%1 %2}").arg(iter.attr_id).arg(iter.attr_oid);
    qDebug() << QString("          SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("          LONG-NAME property:{%1} %2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);
    qDebug() << QString("          COMPU-METHOD");
    qDebug() << QString("            CATEGORY:%1").arg(iter.child_compu_method.child_category.data_value);
    qDebug() << QString("          DIAG-CODED-TYPE property:{%1 %2 %3}").arg(iter.child_diag_coded_type.attr_xsi_type).arg(iter.child_diag_coded_type.attr_base_type_encoding).arg(iter.child_diag_coded_type.attr_base_data_type);
    qDebug() << QString("            BIT-LENGTH:%1").arg(iter.child_diag_coded_type.child_bit_length.data_value);
    qDebug() << QString("          PHYSICAL-TYPE property:{%1 %2}").arg(iter.child_physical_type.attr_base_data_type).arg(iter.child_physical_type.attr_display_radix);
    }
    qDebug() << QString("      UNIT-SPEC");
    qDebug() << QString("        UNITS size:%1").arg(odx.child_ecu_config.child_config_data_dictionary_spec.child_unit_spec.child_units.child_unit.size());
    for (auto iter : odx.child_ecu_config.child_config_data_dictionary_spec.child_unit_spec.child_units.child_unit)
    {
    qDebug() << QString("          UNIT property:{%1 %2}").arg(iter.attr_id).arg(iter.attr_oid);
    qDebug() << QString("            SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("            LONG-NAME property:{%1} %2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);
    qDebug() << QString("            DISPLAY-NAME:{%1}").arg(iter.child_display_name);
//    qDebug() << QString("            FACTOR-SI-TO-UNIT property:{%1 %2}").arg(iter.attr_id).arg(iter.attr_oid);
//    qDebug() << QString("            OFFSET-SI-TO-UNIT:{%1 %2}").arg(iter.attr_id).arg(iter.attr_oid);
//    qDebug() << QString("            PHYSICAL-DIMENSION-REF property:{%1}").arg(iter.);
    }
    qDebug() << QString("        PHYSICAL-DIMENSIONS size:%1").arg(odx.child_ecu_config.child_config_data_dictionary_spec.child_data_object_props.child_data_object_prop.size());
    for (auto iter : odx.child_ecu_config.child_config_data_dictionary_spec.child_unit_spec.child_physical_dimensions.child_physical_dimension)
    {
    qDebug() << QString("          PHYSICAL-DIMENSION property:{%1 %2}").arg(iter.attr_id).arg(iter.attr_oid);
    qDebug() << QString("            SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("            LONG-NAME property:{%1} %2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);
    qDebug() << QString("            TIME-EXP:%1").arg(iter.child_time_exp);
    }
}

int LoadODX_E::read_odx(const pugi::xml_node &node, ODX_E &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "xmlns:xsi") == 0) {
            data.attr_xmlns_xsi = attr.value();
        } else if (strcmp(attr.name(), "MODEL-VERSION") == 0) {
            data.attr_model_version = attr.value();
        } else if (strcmp(attr.name(), "xsi:noNamespaceSchemaLocation") == 0) {
            data.attr_xsi_nonamespaceschemaLocation = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "ECU-CONFIG") == 0) {
            if (read_ecu_config(child, data.child_ecu_config)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_E::read_ecu_variant_snref(const pugi::xml_node &node, ECU_VARIANT_SNREF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_E::read_ecu_variant_snrefs(const pugi::xml_node &node, ECU_VARIANT_SNREFS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "ECU-VARIANT-SNREF") == 0) {
            ECU_VARIANT_SNREF elem;
            if (read_ecu_variant_snref(child, elem)) {
                result = -1;
                break;
            }
            data.child_ecu_variant_snref.push_back(elem);
        }
    }

    return result;
}

int LoadODX_E::read_base_variant_snref(const pugi::xml_node &node, BASE_VARIANT_SNREF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_E::read_valid_base_variant(const pugi::xml_node &node, VALID_BASE_VARIANT &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "ECU-VARIANT-SNREFS") == 0) {
            if (read_ecu_variant_snrefs(child, data.child_ecu_variant_snrefs)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "BASE-VARIANT-SNREF") == 0) {
            if (read_base_variant_snref(child, data.child_base_variant_snref)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_E::read_valid_base_variants(const pugi::xml_node &node, VALID_BASE_VARIANTS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "VALID-BASE-VARIANT") == 0) {
            VALID_BASE_VARIANT elem;
            if (read_valid_base_variant(child, elem)) {
                result = -1;
                break;
            }
            data.child_valid_base_variant.push_back(elem);
        }
    }

    return result;
}

int LoadODX_E::read_read_diag_comm_snref(const pugi::xml_node &node, READ_DIAG_COMM_SNREF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_E::read_read_data_snref(const pugi::xml_node &node, READ_DATA_SNREF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_E::read_read_diag_comm_connector(const pugi::xml_node &node, READ_DIAG_COMM_CONNECTOR &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "READ-DIAG-COMM-SNREF") == 0) {
            if (read_read_diag_comm_snref(child, data.child_read_diag_comm_snref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "READ-DATA-SNREF") == 0) {
            if (read_read_data_snref(child, data.child_read_data_snref)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_E::read_write_diag_comm_snref(const pugi::xml_node &node, WRITE_DIAG_COMM_SNREF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_E::read_write_data_snref(const pugi::xml_node &node, WRITE_DATA_SNREF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_E::read_write_diag_comm_connector(const pugi::xml_node &node, WRIT_DIAG_COMM_CONNECTOR &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "WRITE-DIAG-COMM-SNREF") == 0) {
            if (read_write_diag_comm_snref(child, data.child_write_diag_comm_snref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "WRITE-DATA-SNREF") == 0) {
            if (read_write_data_snref(child, data.child_write_data_snref)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_E::read_diag_comm_data_connector(const pugi::xml_node &node, DIAG_COMM_DATA_CONNECTOR &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "UNCOMPRESSED-SIZE") == 0) {
            data.child_uncompressed_size = child.child_value();
        } else if (strcmp(child.name(), "SOURCE-START-ADDRESS") == 0) {
            data.child_source_start_address = child.child_value();
        } else if (strcmp(child.name(), "READ-DIAG-COMM-CONNECTOR") == 0) {
            if (read_read_diag_comm_connector(child, data.child_read_diag_comm_connector)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "WRITE-DIAG-COMM-CONNECTOR") == 0) {
            if (read_write_diag_comm_connector(child, data.child_write_diag_comm_connector)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_E::read_diag_comm_data_connectors(const pugi::xml_node &node, DIAG_COMM_DATA_CONNECTORS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DIAG-COMM-DATA-CONNECTOR") == 0) {
            DIAG_COMM_DATA_CONNECTOR elem;
            if (read_diag_comm_data_connector(child, elem)) {
                result = -1;
                break;
            }
            data.child_diag_comm_data_connector.push_back(elem);
        }
    }

    return result;
}

int LoadODX_E::read_data_record(const pugi::xml_node &node, DATA_RECORD &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "DATAFORMAT") == 0) {
            data.attr_dataformat = attr.value();
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
        } else if (strcmp(child.name(), "DATA") == 0) {
            data.child_data = child.child_value();
        }
    }

    return result;
}

int LoadODX_E::read_data_records(const pugi::xml_node &node, DATA_RECORDS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DATA-RECORD") == 0) {
            DATA_RECORD elem;
            if (read_data_record(child, elem)) {
                result = -1;
                break;
            }
            data.child_data_record.push_back(elem);
        }
    }

    return result;
}

int LoadODX_E::read_option_item(const pugi::xml_node &node, OPTION_ITEM &data)
{
    int result = 0;

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
            data.child_byte_position.data_value = child.child_value();
        } else if (strcmp(child.name(), "BIT-POSITION") == 0) {
            data.child_bit_position.data_value = child.child_value();
        } else if (strcmp(child.name(), "DATA-OBJECT-PROP-REF") == 0) {
            if (odxcmn::read_data_object_prop_ref(child, data.child_data_object_prop_ref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PHYSICAL-DEFAULT-VALUE") == 0) {
            data.child_physical_default_value.data_value = child.child_value();
        }
    }

    return result;
}

int LoadODX_E::read_option_items(const pugi::xml_node &node, OPTION_ITEMS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "OPTION-ITEM") == 0) {
            OPTION_ITEM elem;
            if (read_option_item(child, elem)) {
                result = -1;
                break;
            }
            data.child_option_item.push_back(elem);
        }
    }

    return result;
}

int LoadODX_E::read_config_record(const pugi::xml_node &node, CONFIG_RECORD &data)
{
    int result = 0;

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
        } else if (strcmp(child.name(), "DIAG-COMM-DATA-CONNECTORS") == 0) {
            if (read_diag_comm_data_connectors(child, data.child_diag_comm_data_connectors)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DATA-RECORDS") == 0) {
            if (read_data_records(child, data.child_data_records)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "OPTION-ITEMS") == 0) {
            if (read_option_items(child, data.child_option_items)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_E::read_config_records(const pugi::xml_node &node, CONFIG_RECORDS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "CONFIG-RECORD") == 0) {
            CONFIG_RECORD elem;
            if (read_config_record(child, elem)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}



int LoadODX_E::read_config_data(const pugi::xml_node &node, CONFIG_DATA &data)
{
    int result = 0;

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
        } else if (strcmp(child.name(), "VALID-BASE-VARIANTS") == 0) {
            if (read_valid_base_variants(child, data.child_valid_base_variants)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "CONFIG-RECORDS") == 0) {
            if (read_config_records(child, data.child_config_records)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_E::read_config_datas(const pugi::xml_node &node, CONFIG_DATAS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "CONFIG-DATA") == 0) {
            CONFIG_DATA elem;
            if (read_config_data(child, elem)) {
                result = -1;
                break;
            }
            data.child_config_data.push_back(elem);
        }
    }

    return result;
}

int LoadODX_E::read_config_data_dictionary_spec(const pugi::xml_node &node, CONFIG_DATA_DICTIONARY_SPEC &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DATA-OBJECT-PROPS") == 0) {
            if (odxcmn::read_data_object_props(child, data.child_data_object_props)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "UNIT-SPEC") == 0) {
            if (odxcmn::read_unit_spec(child, data.child_unit_spec)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_E::read_ecu_config(const pugi::xml_node &node, ECU_CONFIG &data)
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
        } else if (strcmp(child.name(), "CONFIG-DATAS") == 0) {
            if (read_config_datas(child, data.child_config_datas)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "CONFIG-DATA-DICTIONARY-SPEC") == 0) {
            if (read_config_data_dictionary_spec(child, data.child_config_data_dictionary_spec)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}
