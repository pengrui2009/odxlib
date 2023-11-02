#include "load_odx_cs.h"

#include <iostream>
#include <QDebug>

LoadODX_CS::LoadODX_CS() :
    doc_ptr_{std::make_unique<pugi::xml_document>()}
{

}

int LoadODX_CS::load(const QByteArray &fileData, ODX_CS &odx)
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

void LoadODX_CS::print(const ODX_CS &odx)
{
    qDebug() << QString("ODX property:{%1 %2 %3}").arg(odx.attr_model_version).arg(odx.attr_xmlns_xsi).arg(odx.attr_xsi_noNamespaceSchemaLocation);
    qDebug() << QString("  COMPARAM-SUBSET property:{%1 %2}").arg(odx.child_comparam_subset.attr_id).arg(odx.child_comparam_subset.attr_category);
    qDebug() << QString("    SHORT-NAME:%1").arg(odx.child_comparam_subset.child_short_name);
    qDebug() << QString("    LONG-NAME: property:{%1} %2").arg(odx.child_comparam_subset.child_long_name.attr_ti).arg(odx.child_comparam_subset.child_long_name.data_value);
    qDebug() << QString("    COMPANY-DATAS size:%1").arg(odx.child_comparam_subset.child_company_datas.child_company_data.size());
    for (auto iter : odx.child_comparam_subset.child_company_datas.child_company_data)
    {
    qDebug() << QString("      COMPANY-DATA property:{%1 %2}").arg(iter.attr_id).arg(iter.attr_oid);
    qDebug() << QString("        SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("        LONG-NAME property:{%1} :%2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);
    qDebug() << QString("        TEAM-MEMBERS size:%1").arg(iter.child_team_members.child_team_member.size());
    for (auto iter1 : iter.child_team_members.child_team_member)
    {
    qDebug() << QString("          TEAM-MEMBER property:{%1 %2}").arg(iter1.attr_id).arg(iter1.attr_oid);
    qDebug() << QString("            SHORT-NAME:%1").arg(iter1.child_short_name);
    qDebug() << QString("            LONG-NAME property:{%1} :%2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("            ADDRESS:%1").arg(iter1.child_address);
    qDebug() << QString("            ZIP:%1").arg(iter1.child_zip);
    qDebug() << QString("            CITY:%1").arg(iter1.child_city);
    qDebug() << QString("            PHONE:%1").arg(iter1.child_phone);
    qDebug() << QString("            FAX:%1").arg(iter1.child_fax);
    qDebug() << QString("            EMAIL:%1").arg(iter1.child_email);
    }
    qDebug() << QString("        COMPANY-SPECIFIC-INFO property:{%1} :%2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);
    qDebug() << QString("          RELATED-DOCS size:%1").arg(iter.child_company_specific_info.child_related_docs.child_related_doc.size());
    for (auto iter1 : iter.child_company_specific_info.child_related_docs.child_related_doc)
    {
    qDebug() << QString("            RELATED-DOC");
    qDebug() << QString("              XDOC");
    qDebug() << QString("                SHORT-NAME:%1").arg(iter1.child_xdoc.child_short_name);
    qDebug() << QString("                LONG-NAME:%1").arg(iter1.child_xdoc.child_long_name.data_value);
    qDebug() << QString("                NUMBER:%1").arg(iter1.child_xdoc.child_number);
    qDebug() << QString("                STATE:%1").arg(iter1.child_xdoc.child_state);
    qDebug() << QString("                DATE:%1").arg(iter1.child_xdoc.child_date);
    qDebug() << QString("                PUBLISHER:%1").arg(iter1.child_xdoc.child_publisher);
    }
    }
    qDebug() << QString("    COMPARAMS size:%1").arg(odx.child_comparam_subset.child_comparams.child_comparam.size());
    for (auto iter : odx.child_comparam_subset.child_comparams.child_comparam)
    {
    qDebug() << QString("      COMPARAM property:{%1 %2 %3 %4}").arg(iter.attr_cptype).arg(iter.attr_cpusage).arg(iter.attr_id).arg(iter.attr_param_class);
    qDebug() << QString("        SHORT-NAME size:%1").arg(iter.child_short_name);
    qDebug() << QString("        LONG-NAME: property:{%1} %2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);
    qDebug() << QString("        DESC:%1").arg(iter.child_desc.data_value);
    qDebug() << QString("        PHYSICAL-DEFAULT-VALUE:%1").arg(iter.child_physical_default_value);
    qDebug() << QString("        DATA-OBJECT-PROP-REF: property:{%1}").arg(iter.child_data_object_prop_ref.attr_id_ref);
    }
    qDebug() << QString("    COMPLEX-COMPARAMS size:%1").arg(odx.child_comparam_subset.child_complex_comparams.child_comparam.size());
    for (auto iter : odx.child_comparam_subset.child_complex_comparams.child_comparam)
    {
    qDebug() << QString("      COMPLEX-COMPARAM: property:{%1 %2 %3 %4 %5 %6}").arg(iter.attr_allow_multiple_values).arg(iter.attr_cptype).arg(iter.attr_cpusage).arg(iter.attr_display_level).arg(iter.attr_id).arg(iter.attr_param_class);
    qDebug() << QString("        SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("        LONG-NAME:property:{%1} %2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);
    qDebug() << QString("        DESC:%1").arg(iter.child_desc.data_value);
    for (auto iter1 : iter.child_comparam)
    {
    qDebug() << QString("        COMPARAM: property:{%1 %2 %3 %4 %5}").arg(iter1.attr_cptype).arg(iter1.attr_cpusage).arg(iter1.attr_display_level).arg(iter1.attr_id).arg(iter1.attr_param_class);
    qDebug() << QString("          SHORT-NAME: %1").arg(iter1.attr_cptype).arg(iter1.child_short_name);
    qDebug() << QString("          LONG-NAME: property:{%1} %2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("          DESC: %1").arg(iter1.child_desc.data_value);
    qDebug() << QString("          PHYSICAL-DEFAULT-VALUE: %1").arg(iter1.child_physical_default_value);
    qDebug() << QString("          DATA-OBJECT-PROP-REF: property:{%1}").arg(iter1.child_data_object_prop_ref.attr_id_ref);
    }
    qDebug() << QString("        COMPLEX-PHYSICAL-DEFAULT-VALUE");
    qDebug() << QString("          COMPLEX-VALUES size:%1").arg(iter.child_complex_physical_default_value.child_complex_values.child_complex_value.size());
    for (auto iter1 : iter.child_complex_physical_default_value.child_complex_values.child_complex_value)
    {
    qDebug() << QString("            COMPLEX-VALUE");
    for (auto iter2 : iter1.child_simple_value)
    {
    qDebug() << QString("              SIMPLE-VALUE:%1").arg(iter2.data_value);
    }

    }
    }
    qDebug() << QString("    DATA-OBJECT-PROPS size:%1").arg(odx.child_comparam_subset.child_data_obejct_props.child_data_object_prop.size());
    for (auto iter : odx.child_comparam_subset.child_data_obejct_props.child_data_object_prop)
    {
    qDebug() << QString("      DATA-OBJECT-PROP property:{%1 %2}").arg(iter.attr_id).arg(iter.attr_oid);
    qDebug() << QString("        SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("        LONG-NAME: property:{%1} %2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);
    qDebug() << QString("        COMPU-METHOD: property:{%1} %2").arg(iter.child_compu_method.child_category.data_value).arg(iter.child_long_name.data_value);
    qDebug() << QString("          CATEGORY: %1").arg(iter.child_compu_method.child_category.data_value);
    qDebug() << QString("        DIAG-CODED-TYPE: property:{%1 %2 %3}").arg(iter.child_diag_coded_type.attr_base_data_type).arg(iter.child_diag_coded_type.attr_termination).arg(iter.child_diag_coded_type.attr_xsi_type);
    qDebug() << QString("          MAX-LENGTH:%1").arg(iter.child_diag_coded_type.child_max_length.child_data_value);
    qDebug() << QString("          MIN-LENGTH:%2").arg(iter.child_diag_coded_type.child_min_length.child_data_value);
    qDebug() << QString("        PHYSICAL-TYPE: property:{%1} %2").arg(iter.child_physical_type.attr_base_data_type).arg(iter.child_physical_type.attr_display_radix);
    qDebug() << QString("        INTERNAL-CONSTR");
    qDebug() << QString("          LOWER-LIMIT property:{%1} %2").arg(iter.child_internal_constr.child_lower_limit.attr_interval_type).arg(iter.child_internal_constr.child_lower_limit.child_data_value);
    qDebug() << QString("          UPPER-LIMIT property:{%1} %2").arg(iter.child_internal_constr.child_upper_limie.attr_interval_type).arg(iter.child_internal_constr.child_upper_limie.child_data_value);
    }
    qDebug() << QString("    UNIT-SPEC");
    qDebug() << QString("      UNITS size:%1").arg(odx.child_comparam_subset.child_unit_spec.child_units.child_unit.size());
    for (auto iter : odx.child_comparam_subset.child_unit_spec.child_units.child_unit)
    {
    qDebug() << QString("        UNIT property:{%1}").arg(iter.attr_id);
    qDebug() << QString("          SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("          LONG-NAME:%1").arg(iter.child_long_name.data_value);
    qDebug() << QString("          DISPLAY-NAME:%1").arg(iter.child_display_name);
    }
    qDebug() << QString("      PHYSICAL-DIMENSIONS size:%1").arg(odx.child_comparam_subset.child_unit_spec.child_physical_dimensions.child_physical_dimension.size());
    for (auto iter : odx.child_comparam_subset.child_unit_spec.child_physical_dimensions.child_physical_dimension)
    {
    qDebug() << QString("        PHYSICAL-DIMENSION property:{%1 %2").arg(iter.attr_id).arg(iter.attr_oid);
    qDebug() << QString("          SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("          LONG-NAME:%1").arg(iter.child_long_name.data_value);
    qDebug() << QString("          TIME-EXP:%1").arg(iter.child_time_exp);
    }
}

int LoadODX_CS::read_data_object_prop_ref(const pugi::xml_node &node, DATA_OBJECT_PROP_REF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_CS::read_comparam(const pugi::xml_node &node, COMPARAM &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "CPTYPE") == 0) {
            data.attr_cptype = attr.value();
        } else if (strcmp(attr.name(), "CPUSAGE") == 0) {
            data.attr_cpusage = attr.value();
        } else if (strcmp(attr.name(), "DISPLAY-LEVEL") == 0) {
            data.attr_display_level = attr.value();
        } else if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "PARAM-CLASS") == 0) {
            data.attr_param_class = attr.value();
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
        } else if (strcmp(child.name(), "DESC") == 0) {
            if (odxcmn::read_desc(child, data.child_desc)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PHYSICAL-DEFAULT-VALUE") == 0) {
            data.child_physical_default_value = child.child_value();
        }  else if (strcmp(child.name(), "DATA-OBJECT-PROP-REF") == 0) {
            if (read_data_object_prop_ref(child, data.child_data_object_prop_ref)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_CS::read_comparams(const pugi::xml_node &node, COMPARAMS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            COMPARAM elem;
            if (read_comparam(child, elem)) {
                result = -1;
                break;
            }
            data.child_comparam.push_back(elem);
        }
    }

    return result;
}

int LoadODX_CS::read_complex_physical_default_value(const pugi::xml_node &node, COMPLEX_PHYSICAL_DEFAULT_VALUE &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "COMPLEX-VALUES") == 0) {
            if (odxcmn::read_complex_values(child, data.child_complex_values)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_CS::read_complex_comparam(const pugi::xml_node &node, COMPLEX_COMPARAM &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ALLOW-MULTIPLE-VALUES") == 0) {
            data.attr_allow_multiple_values = attr.value();
        } else if (strcmp(attr.name(), "CPTYPE") == 0) {
            data.attr_cptype = attr.value();
        } else if (strcmp(attr.name(), "CPUSAGE") == 0) {
            data.attr_cpusage = attr.value();
        } else if (strcmp(attr.name(), "DISPLAY-LEVEL") == 0) {
            data.attr_display_level = attr.value();
        } else if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "PARAM-CLASS") == 0) {
            data.attr_param_class = attr.value();
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
        } else if (strcmp(child.name(), "DESC") == 0) {
            if (odxcmn::read_desc(child, data.child_desc)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "COMPARAM") == 0) {
            COMPARAM elem;
            if (read_comparam(child, elem)) {
                result = -1;
                break;
            }
            data.child_comparam.push_back(elem);
        } else if (strcmp(child.name(), "COMPLEX-PHYSICAL-DEFAULT-VALUE") == 0) {
            if (read_complex_physical_default_value(child, data.child_complex_physical_default_value)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_CS::read_complex_comparams(const pugi::xml_node &node, COMPLEX_COMPARAMS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "COMPLEX-COMPARAM") == 0) {
            COMPLEX_COMPARAM elem;
            if (read_complex_comparam(child, elem)) {
                result = -1;
                break;
            }
            data.child_comparam.push_back(elem);
        }
    }

    return result;
}

int LoadODX_CS::read_data_object_prop(const pugi::xml_node &node, DATA_OBJECT_PROP &data) {
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
        }  else if (strcmp(child.name(), "PHYSICAL-TYPE") == 0) {
            if (odxcmn::read_physical_type(child, data.child_physical_type)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "INTERNAL-CONSTR")) {
            if (odxcmn::read_internal_constr(child, data.child_internal_constr)) {
                result = -1;
                break;
            }
        }
    }

    return  result;
}

int LoadODX_CS::read_data_object_props(const pugi::xml_node &node, DATA_OBJECT_PROPS &data) {
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

    return  result;
}

int LoadODX_CS::read_unit(const pugi::xml_node &node, UNIT &data) {
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
        } else if (strcmp(child.name(), "DISPLAY-NAME") == 0) {
            data.child_display_name = child.child_value();
        }
    }

    return result;
}

int LoadODX_CS::read_units(const pugi::xml_node &node, UNITS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "UNIT") == 0) {
            UNIT elem;
            if (read_unit(child, elem)) {
                result = -1;
                break;
            }
            data.child_unit.push_back(elem);
        }
    }

    return result;
}

int LoadODX_CS::read_physical_dimension(const pugi::xml_node &node, PHYSICAL_DIMENSION &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_id = attr.value();
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
        } else if (strcmp(child.name(), "TIME-EXP") == 0) {
            data.child_time_exp = child.child_value();
        }
    }

    return result;
}

int LoadODX_CS::read_physical_dimensions(const pugi::xml_node &node, PHYSICAL_DIMENSIONS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "PHYSICAL-DIMENSION") == 0) {
            PHYSICAL_DIMENSION elem;
            if (read_physical_dimension(child, elem)) {
                result = -1;
                break;
            }
            data.child_physical_dimension.push_back(elem);
        }
    }

    return result;
}

int LoadODX_CS::read_unit_spec(const pugi::xml_node &node, UNIT_SPEC &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "UNITS") == 0) {
            if (read_units(child, data.child_units)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PHYSICAL-DIMENSIONS") == 0) {
            if (read_physical_dimensions(child, data.child_physical_dimensions)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_CS::read_comparam_subset(const pugi::xml_node &node, COMPARAM_SUBSET &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "CATEGORY") == 0) {
            data.attr_category = attr.value();
        } else if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
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
        } else if (strcmp(child.name(), "ADMIN-DATA") == 0) {
            if (odxcmn::read_admin_data(child, data.child_admin_data)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "COMPANY-DATAS") == 0) {
            if (odxcmn::read_company_datas(child, data.child_company_datas)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "COMPARAMS") == 0) {
            if (read_comparams(child, data.child_comparams)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "COMPLEX-COMPARAMS") == 0) {
            if (read_complex_comparams(child, data.child_complex_comparams)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DATA-OBJECT-PROPS") == 0) {
            if (read_data_object_props(child, data.child_data_obejct_props)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "UNIT-SPEC") == 0) {
            if (read_unit_spec(child, data.child_unit_spec)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_CS::read_odx(const pugi::xml_node &node, ODX_CS &data)
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
        if (strcmp(child.name(), "COMPARAM-SUBSET") == 0) {
            if (read_comparam_subset(child, data.child_comparam_subset)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}
