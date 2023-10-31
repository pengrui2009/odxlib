#include "odx_cmn.h"

odxcmn::odxcmn()
{

}

int odxcmn::read_short_name(const pugi::xml_node &node, QString &data)
{
    int result = 0;

    data = node.child_value();

    return result;
}

int odxcmn::read_long_name(const pugi::xml_node &node, LONG_NAME &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "TI") == 0) {
            data.attr_ti = attr.value();
        }
    }

    data.data_value = node.child_value();

    return result;
}

int odxcmn::read_desc(const pugi::xml_node &node, DESC &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "p") == 0) {
            data.data_value = child.child_value();
        }
    }


    return result;
}

int odxcmn::read_team_member_ref(const pugi::xml_node &node, TEAM_MEMBER_REF &data) {
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int odxcmn::read_doc_revision(const pugi::xml_node &node, DOC_REVISION &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "TEAM-MEMBER-REF") == 0) {
            if (read_team_member_ref(child, data.child_team_member_ref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "REVISION-LABEL") == 0) {
            data.child_revision_label = child.child_value();
        } else if (strcmp(child.name(), "STATE") == 0) {
            data.child_state = child.child_value();
        } else if (strcmp(child.name(), "DATE") == 0) {
            data.child_date = child.child_value();
        } else if (strcmp(child.name(), "TOOL") == 0) {
            data.child_tool = child.child_value();
        } else if (strcmp(child.name(), "MODIFICATIONS") == 0) {
            if (read_modifications(child, data.child_modifications)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int odxcmn::read_doc_revisions(const pugi::xml_node &node, DOC_REVISIONS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DOC-REVISION") == 0) {
            DOC_REVISION elem;
            if (read_doc_revision(child, elem)) {
                result = -1;
                break;
            }
            data.child_doc_revision.push_back(elem);
        }
    }

    return result;
}

int odxcmn::read_modification(const pugi::xml_node &node, MODIFICATION &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "CHANGE") == 0) {
             data.child_change = child.child_value();
        } else if (strcmp(child.name(), "REASON") == 0) {
             data.child_reason = child.child_value();
       }
    }

    return result;
}

int odxcmn::read_modifications(const pugi::xml_node &node, MODIFICATIONS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "MODIFICATION") == 0) {
             MODIFICATION elem;
             if (read_modification(child, elem)) {
                 result = -1;
                 break;
             }
             data.child_modification.push_back(elem);
        }
    }

    return result;
}

int odxcmn::read_admin_data(const pugi::xml_node &node, ADMIN_DATA &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DOC-REVISIONS") == 0) {
            if (read_doc_revisions(child, data.child_doc_revisions)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LANGUAGE") == 0) {
            data.child_language = child.child_value();
        }
    }

    return result;
}

int odxcmn::read_team_member(const pugi::xml_node &node, TEAM_MEMBER &data) {
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
            if (read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DEPARTMENT") == 0) {
            data.child_department = child.child_value();
        } else if (strcmp(child.name(), "ADDRESS") == 0) {
            data.child_address = child.child_value();
        } else if (strcmp(child.name(), "ZIP") == 0) {
            data.child_zip = child.child_value();
        } else if (strcmp(child.name(), "CITY") == 0) {
            data.child_city = child.child_value();
        } else if (strcmp(child.name(), "PHONE") == 0) {
            data.child_phone = child.child_value();
        } else if (strcmp(child.name(), "FAX") == 0) {
            data.child_fax = child.child_value();
        } else if (strcmp(child.name(), "EMAIL") == 0) {
            data.child_email = child.child_value();
        }
    }

    return result;
}

int odxcmn::read_team_members(const pugi::xml_node &node, TEAM_MEMBERS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "TEAM-MEMBER") == 0) {
            TEAM_MEMBER elem;
            if (read_team_member(child, elem)) {
                result = -1;
                break;
            }
            data.child_team_member.push_back(elem);
        }
    }

    return result;
}

int odxcmn::read_xdoc(const pugi::xml_node &node, XDOC &data) {
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
        } else if (strcmp(child.name(), "NUMBER") == 0) {
            data.child_number = child.child_value();
        } else if (strcmp(child.name(), "STATE") == 0) {
            data.child_state = child.child_value();
        } else if (strcmp(child.name(), "DATE") == 0) {
            data.child_date = child.child_value();
        } else if (strcmp(child.name(), "PUBLISHER") == 0) {
            data.child_publisher = child.child_value();
        }
    }

    return  result;
}

int odxcmn::read_related_doc(const pugi::xml_node &node, RELATED_DOC &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "XDOC") == 0) {
            if (read_xdoc(child, data.child_xdoc)) {
                result = -1;
                break;
            }
        }
    }

    return  result;
}

int odxcmn::read_related_docs(const pugi::xml_node &node, RELATED_DOCS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "RELATED-DOC") == 0) {
            RELATED_DOC elem;
            if (read_related_doc(child, elem)) {
                result = -1;
                break;
            }
            data.child_related_doc.push_back(elem);
        }
    }

    return  result;
}

int odxcmn::read_company_specific_info(const pugi::xml_node &node, COMPANY_SPECIFIC_INFO &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "RELATED-DOCS") == 0) {
            if (read_related_docs(child, data.child_related_docs)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int odxcmn::read_company_data(const pugi::xml_node &node, COMPANY_DATA &data) {
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
            if (read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        }else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "TEAM-MEMBERS") == 0) {
            if (read_team_members(child, data.child_team_members)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "COMPANY-SPECIFIC-INFO") == 0) {
            if (read_company_specific_info(child, data.child_company_specific_info)) {
                result = -1;
                break;
            }
        }
    }


    return result;
}

int odxcmn::read_company_datas(const pugi::xml_node &node, COMPANY_DATAS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "COMPANY-DATA") == 0) {
            COMPANY_DATA elem;
            if (read_company_data(child, elem)) {
                result = -1;
                break;
            }
            data.child_company_data.push_back(elem);
        }
    }

    return result;
}

int odxcmn::read_simple_value(const pugi::xml_node &node, SIMPLE_VALUE &data)
{
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int odxcmn::read_complex_value(const pugi::xml_node &node, COMPLEX_VALUE &data)
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

int odxcmn::read_complex_values(const pugi::xml_node &node, COMPLEX_VALUES &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "COMPLEX-VALUES") == 0) {
            COMPLEX_VALUE elem;
            if (read_complex_value(child, elem)) {
                result = -1;
                break;
            }
            data.child_complex_value.push_back(elem);
        }
    }

    return result;
}

int odxcmn::read_category(const pugi::xml_node &node, CATEGORY &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int odxcmn::read_compu_method(const pugi::xml_node &node, COMPU_METHOD &data) {
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

int odxcmn::read_bit_length(const pugi::xml_node &node, BIT_LENGTH &data) {
    int result = 0;

    data.data_value = node.child_value();

    return result;
}

int odxcmn::read_diag_coded_type(const pugi::xml_node &node, DIAG_CODED_TYPE &data) {
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

int odxcmn::read_physical_type(const pugi::xml_node &node, PHYSICAL_TYPE &data) {
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

int odxcmn::read_lower_limit(const pugi::xml_node &node, LOWER_LIMIT &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "INTERVAL-TYPE") == 0) {
            data.attr_interval_type = attr.value();
        }
    }

    data.child_data_value = node.child_value();

    return result;
}

int odxcmn::read_upper_limit(const pugi::xml_node &node, UPPER_LIMIT &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "INTERVAL-TYPE") == 0) {
            data.attr_interval_type = attr.value();
        }
    }

    data.child_data_value = node.child_value();

    return result;
}

int odxcmn::read_internal_constr(const pugi::xml_node &node, INTERNAL_CONSTR &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "LOWER-LIMIT") == 0) {
            if (read_lower_limit(child, data.child_lower_limit)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "UPPER-LIMIT") == 0) {
            if (read_upper_limit(child, data.child_upper_limie)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}
