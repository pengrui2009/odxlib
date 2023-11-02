#include "load_odx_c.h"

#include <iostream>
#include <QDebug>

LoadODX_C::LoadODX_C() :
    doc_ptr_{std::make_unique<pugi::xml_document>()}
{

}

int LoadODX_C::load(const QByteArray &fileData, ODX_C &odx)
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

void LoadODX_C::print(const ODX_C &odx)
{
    qDebug() << QString("ODX property:{%1 %2 %3}").arg(odx.attr_model_version).arg(odx.attr_xmlns_xsi).arg(odx.attr_xsi_noNamespaceSchemaLocation);
    qDebug() << QString("  COMPARAM-SPEC property:{%1}").arg(odx.child_comparam_spec.attr_id);
    qDebug() << QString("    SHORT-NAME:%1").arg(odx.child_comparam_spec.child_short_name);
    qDebug() << QString("    LONG-NAME property:{%1} :%2").arg(odx.child_comparam_spec.child_long_name.attr_ti).arg(odx.child_comparam_spec.child_long_name.data_value);
    qDebug() << QString("    DESC:%1").arg(odx.child_comparam_spec.child_desc.data_value);
    qDebug() << QString("    ADMIN-DATA");
    qDebug() << QString("      LANGUAGE:%1").arg(odx.child_comparam_spec.child_admin_data.child_language);
    qDebug() << QString("      DOC-REVISIONS size:%1").arg(odx.child_comparam_spec.child_admin_data.child_doc_revisions.child_doc_revision.size());
    for (auto iter : odx.child_comparam_spec.child_admin_data.child_doc_revisions.child_doc_revision)
    {
    qDebug() << QString("        DOC-REVISION");
    qDebug() << QString("          TEAM-MEMBER-REF property:{%1}").arg(iter.child_team_member_ref.attr_id_ref);
    qDebug() << QString("          REVISION-LABEL:%1").arg(iter.child_revision_label);
    qDebug() << QString("          STATE:%1").arg(iter.child_state);
    qDebug() << QString("          DATE:%1").arg(iter.child_date);
    qDebug() << QString("          MODIFICATIONS size:%1").arg(iter.child_modifications.child_modification.size());
    for (auto iter1 : iter.child_modifications.child_modification)
    {
    qDebug() << QString("            MODIFICATION");
    qDebug() << QString("              CHANGE:%1").arg(iter1.child_change);
    qDebug() << QString("              REASON:%1").arg(iter1.child_reason);
    }
    }
    qDebug() << QString("    COMPANY-DATAS size:%1").arg(odx.child_comparam_spec.child_company_datas.child_company_data.size());
    for (auto iter : odx.child_comparam_spec.child_company_datas.child_company_data)
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
    qDebug() << QString("    PROT-STACKS size:%1").arg(odx.child_comparam_spec.child_proto_stacks.child_prot_stack.size());
    for (auto iter : odx.child_comparam_spec.child_proto_stacks.child_prot_stack)
    {
    qDebug() << QString("      PROT-STACK property:{%1}").arg(iter.attr_id);
    qDebug() << QString("        SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("        LONG-NAME:%1").arg(iter.child_long_name.data_value);
    qDebug() << QString("        DESC:%1").arg(iter.child_desc.data_value);
    qDebug() << QString("        PDU-PROTOCOL-TYPE:%1").arg(iter.child_pdu_protocol_type);
    qDebug() << QString("        PHYSICAL-LINK-TYPE:%1").arg(iter.child_physical_link_type);
    qDebug() << QString("        COMPARAM-SUBSET-REFS size:%1").arg(iter.child_comparam_subset_refs.child_comparam_subset_ref.size());
    for (auto iter1 : iter.child_comparam_subset_refs.child_comparam_subset_ref)
    {
    qDebug() << QString("          COMPARAM-SUBSET-REF property:{%1 %2 %3}").arg(iter1.attr_docref).arg(iter1.attr_doctype).arg(iter1.attr_id_ref);
    }
    }
}

int LoadODX_C::read_odx(const pugi::xml_node &node, ODX_C &data)
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
        if (strcmp(child.name(), "COMPARAM-SPEC") == 0) {
            if (read_comparam_spec(child, data.child_comparam_spec)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_C::read_comparam_subset_ref(const pugi::xml_node &node, COMPARAM_SUBSET_REF &data) {
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


int LoadODX_C::read_comparam_subset_refs(const pugi::xml_node &node, COMPARAM_SUBSET_REFS &data) {
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "COMPARAM-SUBSET-REF") == 0) {
            COMPARAM_SUBSET_REF elem;
            if (read_comparam_subset_ref(child, elem)) {
                result = -1;
                break;
            }
            data.child_comparam_subset_ref.push_back(elem);
        }
    }

    return result;
}

int LoadODX_C::read_prot_stack(const pugi::xml_node &node, PROT_STACK &data) {
    int result;

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
        } else if (strcmp(child.name(), "DESC") == 0) {
            if (odxcmn::read_desc(child, data.child_desc)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PDU-PROTOCOL-TYPE") == 0) {
            data.child_pdu_protocol_type = child.child_value();
        } else if (strcmp(child.name(), "PHYSICAL-LINK-TYPE") == 0) {
            data.child_physical_link_type = child.child_value();
        } else if (strcmp(child.name(), "COMPARAM-SUBSET-REFS") == 0) {
            if (read_comparam_subset_refs(child, data.child_comparam_subset_refs)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}


int LoadODX_C::read_prot_stacks(const pugi::xml_node &node, PROT_STACKS &data) {
    int result;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "PROT-STACK") == 0) {
            PROT_STACK elem;
            if (read_prot_stack(child, elem)) {
                result = -1;
                break;
            }
            data.child_prot_stack.push_back(elem);
        }
    }

    return result;
}

int LoadODX_C::read_comparam_spec(const pugi::xml_node &node, COMPARAM_SPEC &data)
{
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
        } else if (strcmp(child.name(), "DESC") == 0) {
            if (odxcmn::read_desc(child, data.child_desc)) {
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
        } else if (strcmp(child.name(), "PROT-STACKS") == 0) {
            if (read_prot_stacks(child, data.child_proto_stacks)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}
