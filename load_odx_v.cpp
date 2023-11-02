#include "load_odx_v.h"
#include "fmt/format.h"
#include <iostream>
#include <QDebug>

LoadODX_V::LoadODX_V() :
    doc_ptr_{std::make_unique<pugi::xml_document>()}
{

}

int LoadODX_V::load(const QByteArray &fileData, ODX_V &odx)
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

void LoadODX_V::print(const ODX_V &odx)
{
    qDebug() << QString("odx-v property:{xmlns:xsi:%1 MODEL-VERSION:%2 xsi:noNamespaceSchemaLocation:%3}").
                arg(odx.attr_xmlns_xsi, odx.attr_model_version).arg(odx.attr_xsi_noNamespaceSchemaLocation);
    qDebug() << QString("  VEHICLE-INFO-SPEC property:{ID:%1 OID:%2}").arg(odx.child_vehicle_info_spec.attr_id, odx.child_vehicle_info_spec.attr_oid);
    qDebug() << QString("      SHORT-NAME:%1").arg(odx.child_vehicle_info_spec.child_short_name);
    qDebug() << QString("      LONG-NAME: property:{%1} %2").arg(odx.child_vehicle_info_spec.child_long_name.attr_ti).arg(odx.child_vehicle_info_spec.child_long_name.data_value);
    qDebug() << QString("      INFO-COMPONENTS size:%1").arg(odx.child_vehicle_info_spec.child_info_components.child_info_component.size());
    for (auto iter : odx.child_vehicle_info_spec.child_info_components.child_info_component) {
    qDebug() << QString("        INFO-COMPONENT property:{%1 %2 %3}").arg(iter.attr_id).arg(iter.attr_oid).arg(iter.attr_xsi_type);
    qDebug() << QString("          SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("          LONG-NAME property:{%1} %2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);

    qDebug() << QString("      VEHICLE-INFORMATIONS size:%1").arg(odx.child_vehicle_info_spec.child_vehicle_informations.child_vehicle_information.size());
        for (auto iter : odx.child_vehicle_info_spec.child_vehicle_informations.child_vehicle_information) {
    qDebug() << QString("        VEHICLE-INFORMATION property:{%1}").arg(iter.attr_oid);
    qDebug() << QString("          SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("          LONG-NAME property:{%1} :%2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);
    qDebug() << QString("          INFO-COMPONENT-REFS size:%1").arg(iter.child_info_component_refs.child_info_component_ref.size());
            for (auto iter1 : iter.child_info_component_refs.child_info_component_ref) {
    qDebug() << QString("            INFO-COMPONENT-REF property{%1}").arg(iter1.attr_id_ref);
            }
    qDebug() << QString("          VEHICLE-CONNECTORS size:%1").arg(iter.child_vehicle_connectors.child_vehicle_connector.size());
            for (auto iter1 : iter.child_vehicle_connectors.child_vehicle_connector) {
    qDebug() << QString("            VEHICLE-CONNECTOR property:{%1}").arg(iter1.attr_oid);
    qDebug() << QString("              SHORT-NAME:%1").arg(iter1.child_short_name);
    qDebug() << QString("              LONG-NAME: property:{%1} %2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("              VEHICLE-CONNECTOR-PINS size:%1").arg(iter1.child_vehicle_connector_pins.vehicle_connector_pin.size());
                for (auto iter2 : iter1.child_vehicle_connector_pins.vehicle_connector_pin) {
    qDebug() << QString("                VEHICLE-CONNECTOR-PIN property:{%1 %2 %3}").arg(iter2.attr_id).arg(iter2.attr_oid).arg(iter2.attr_type);
    qDebug() << QString("                  SHORT-NAME:%1").arg(iter2.child_short_name);
    qDebug() << QString("                  LONG-NAME:property:{%1} :%2").arg(iter2.child_long_name.attr_ti).arg(iter2.child_long_name.data_value);
    qDebug() << QString("                  PIN-NUMBER: %1").arg(iter2.child_pin_number);
                }
            }
    qDebug() << QString("          LOGICAL-LINKS size:%1").arg(iter.child_logical_links.child_logical_link.size());
            for (auto iter1 : iter.child_logical_links.child_logical_link) {
    qDebug() << QString("            LOGICAL-LINK property{%1 %2 %3}").arg(iter1.attr_id).arg(iter1.attr_oid).arg(iter1.attr_xsi_type);
    qDebug() << QString("              SHORT-NAME: %1").arg(iter1.child_short_name);
    qDebug() << QString("              LONG-NAME:property:{%1} %2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("              PHYSICAL-VEHICLE-LINK-REF: property:{%1}").arg(iter1.child_physical_vehicle_link_ref.attr_id_ref);
    qDebug() << QString("              PROTOCOL-REF:property:{%1 %2 %3}").arg(iter1.child_protocol_ref.attr_docref).arg(iter1.child_protocol_ref.attr_doctype).arg(iter1.child_protocol_ref.attr_id_ref);
    qDebug() << QString("              BASE-VARIANT-REF:property:{%1}").arg(iter1.child_base_variant_ref.attr_id_ref);
    qDebug() << QString("              PROT-STACK-SNREF:property:{%1}").arg(iter1.child_prot_stack_snref.attr_short_name);
    qDebug() << QString("              FUNCTIONAL-GROUP-REF property:{%1 %2 %3}").arg(iter1.child_functional_group_ref.attr_id_ref).arg(iter1.child_functional_group_ref.attr_docref).arg(iter1.child_functional_group_ref.attr_doctype);
            }
    qDebug() << QString("          PHYSICAL-VEHICLE-LINKS size:%1").arg(iter.child_physical_vehicle_links.child_physical_vehicle_link.size());
            for (auto iter1 : iter.child_physical_vehicle_links.child_physical_vehicle_link) {
    qDebug() << QString("            PHYSICAL-VEHICLE-LINK property:{%1 %2 %3}").arg(iter1.attr_id).arg(iter1.attr_oid).arg(iter1.attr_type);
    qDebug() << QString("              SHORT-NAME:%1").arg(iter1.child_short_name);
    qDebug() << QString("              LONG-NAME: property:{%1} %2}").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("              VEHICLE-CONNECTOR-PIN-REFS size:%1").arg(iter1.child_vehicle_connector_pin_refs.child_vehicle_connector_pin_ref.size());
                for (auto iter2 : iter1.child_vehicle_connector_pin_refs.child_vehicle_connector_pin_ref)
                {
    qDebug() << QString("                VEHICLE-CONNECTOR-PIN-REF property:{%1}").arg(iter2.attr_id_ref);
                }
            }
        }
    }
}

int LoadODX_V::read_odx(const pugi::xml_node &node, ODX_V &data)
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
        if (strcmp(child.name(), "VEHICLE-INFO-SPEC") == 0) {
            if (read_vehicle_info_spec(child, data.child_vehicle_info_spec)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_V::read_vehicle_info_spec(const pugi::xml_node &node, VEHICLE_INFO_SPEC &data)
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
        } else if (strcmp(child.name(), "INFO-COMPONENTS") == 0) {
            if (read_info_components(child, data.child_info_components)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "VEHICLE-INFORMATIONS") == 0) {
            if (read_vehicle_informations(child, data.child_vehicle_informations)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_V::read_info_component(const pugi::xml_node &node, INFO_COMPONENT &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "xsi:type") == 0) {
            data.attr_xsi_type = attr.value();
        } else if (strcmp(attr.name(), "ID") == 0) {
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
        }
    }

    return result;
}

int LoadODX_V::read_info_components(const pugi::xml_node &node, INFO_COMPONENTS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "INFO-COMPONENT") == 0) {
            INFO_COMPONENT elem;
            if (read_info_component(child, elem)) {
                result = -1;
                break;
            }
            data.child_info_component.push_back(elem);
        }
    }

    return result;
}

int LoadODX_V::read_info_component_ref(const pugi::xml_node &node, INFO_COMPONENT_REF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_V::read_info_component_refs(const pugi::xml_node &node, INFO_COMPONENT_REFS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "INFO-COMPONENT-REF") == 0) {
            INFO_COMPONENT_REF elem;
            if (read_info_component_ref(child, elem)) {
                result = -1;
                break;
            }
            data.child_info_component_ref.push_back(elem);
        }
    }

    return result;
}

int LoadODX_V::read_pin_number(const pugi::xml_node &node, QString &data)
{
    int result = 0;

    data = node.child_value();

    return result;
}

int LoadODX_V::read_vehicle_connector_pin(const pugi::xml_node &node, VEHICLE_CONNECTOR_PIN &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        } else if (strcmp(attr.name(), "TYPE") == 0) {
            data.attr_type = attr.value();
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
        } else if (strcmp(child.name(), "PIN-NUMBER") == 0) {
            if (read_pin_number(child, data.child_pin_number)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_V::read_vehicle_connector_pins(const pugi::xml_node &node, VEHICLE_CONNECTOR_PINS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "VEHICLE-CONNECTOR-PIN") == 0) {
            VEHICLE_CONNECTOR_PIN elem;
            if (read_vehicle_connector_pin(child, elem)) {
                result = -1;
                break;
            }
            data.vehicle_connector_pin.push_back(elem);
        }
    }

    return result;
}

int LoadODX_V::read_vehicle_connector(const pugi::xml_node &node, VEHICLE_CONNECTOR &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "OID") == 0) {
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
        } else if (strcmp(child.name(), "VEHICLE-CONNECTOR-PINS") == 0) {
            if (read_vehicle_connector_pins(child, data.child_vehicle_connector_pins)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_V::read_vehicle_connectors(const pugi::xml_node &node, VEHICLE_CONNECTORS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "VEHICLE-CONNECTOR") == 0) {
            VEHICLE_CONNECTOR elem;
            if (read_vehicle_connector(child, elem)) {
                result = -1;
                break;
            }
            data.child_vehicle_connector.push_back(elem);
        }
    }

    return result;
}

int LoadODX_V::read_physical_vehicle_link_ref(const pugi::xml_node &node, PHYSICAL_VEHICLE_LINK_REF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_V::read_protocol_ref(const pugi::xml_node &node, PROTOCOL_REF &data)
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

    return result;
}

int LoadODX_V::read_functional_group_ref(const pugi::xml_node &node, FUNCTIONAL_GROUP_REF &data)
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

    return result;
}

int LoadODX_V::read_base_variant_ref(const pugi::xml_node &node, BASE_VARIANT_REF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_V::read_prot_stack__snref(const pugi::xml_node &node, PROT_STACK_SNREF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_V::read_logical_link(const pugi::xml_node &node, LOGICAL_LINK &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "xsi:type") == 0) {
            data.attr_xsi_type = attr.value();
        } else if (strcmp(attr.name(), "ID") == 0) {
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
        } else if (strcmp(child.name(), "PHYSICAL-VEHICLE-LINK-REF") == 0) {
            if (read_physical_vehicle_link_ref(child, data.child_physical_vehicle_link_ref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PROTOCOL-REF") == 0) {
            if (read_protocol_ref(child, data.child_protocol_ref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "BASE-VARIANT-REF") == 0) {
            if (read_base_variant_ref(child, data.child_base_variant_ref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PROT-STACK-SNREF") == 0) {
            if (read_prot_stack__snref(child, data.child_prot_stack_snref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "FUNCTIONAL-GROUP-REF") == 0) {
            if (read_functional_group_ref(child, data.child_functional_group_ref)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_V::read_logical_links(const pugi::xml_node &node, LOGICAL_LINKS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "LOGICAL-LINK") == 0) {
            LOGICAL_LINK elem;
            if (read_logical_link(child, elem)) {
                result = -1;
                break;
            }
            data.child_logical_link.push_back(elem);
        }
    }

    return result;
}

int LoadODX_V::read_vehicle_connector_pin_ref(const pugi::xml_node &node, VEHICLE_CONNECTOR_PIN_REF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_V::read_vehicle_connector_pin_refs(const pugi::xml_node &node, VEHICLE_CONNECTOR_PIN_REFS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "VEHICLE-CONNECTOR-PIN-REF") == 0) {
            VEHICLE_CONNECTOR_PIN_REF elem;
            if (read_vehicle_connector_pin_ref(child, elem)) {
                result = -1;
                break;
            }
            data.child_vehicle_connector_pin_ref.push_back(elem);
        }
    }

    return result;
}

int LoadODX_V::read_physical_vehicle_link(const pugi::xml_node &node, PHYSICAL_VEHICLE_LINK &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        } else if (strcmp(attr.name(), "TYPE") == 0) {
            data.attr_type = attr.value();
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
        } else if (strcmp(child.name(), "VEHICLE-CONNECTOR-PIN-REFS") == 0) {
            if (read_vehicle_connector_pin_refs(child, data.child_vehicle_connector_pin_refs)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_V::read_physical_vehicle_links(const pugi::xml_node &node, PHYSICAL_VEHICLE_LINKS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "PHYSICAL-VEHICLE-LINK") == 0) {
            PHYSICAL_VEHICLE_LINK elem;
            if (read_physical_vehicle_link(child, elem)) {
                result = -1;
                break;
            }
            data.child_physical_vehicle_link.push_back(elem);
        }
    }

    return result;
}

int LoadODX_V::read_vehicle_information(const pugi::xml_node &node, VEHICLE_INFORMATION &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "OID") == 0) {
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
        } else if (strcmp(child.name(), "INFO-COMPONENT-REFS") == 0) {
            if (read_info_component_refs(child, data.child_info_component_refs)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "VEHICLE-CONNECTORS") == 0) {
            if (read_vehicle_connectors(child, data.child_vehicle_connectors)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LOGICAL-LINKS") == 0) {
            if (read_logical_links(child, data.child_logical_links)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name() , "PHYSICAL-VEHICLE-LINKS") == 0) {
            if (read_physical_vehicle_links(child, data.child_physical_vehicle_links)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_V::read_vehicle_informations(const pugi::xml_node &node, VEHICLE_INFORMATIONS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "VEHICLE-INFORMATION") == 0) {
            VEHICLE_INFORMATION elem;
            if (read_vehicle_information(child, elem)) {
                result = -1;
                break;
            }
            data.child_vehicle_information.push_back(elem);
        }
    }

    return result;
}
