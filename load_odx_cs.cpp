#include "load_odx_cs.h"

#include <iostream>
#include <QDebug>

LoadODX_CS::LoadODX_CS()
{

}

int LoadODX_CS::load(const QByteArray &fileData)
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

void LoadODX_CS::print()
{

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
            if (odxcmn::read_short_name(child, data.child_short_name)) {
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
