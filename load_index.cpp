#include "load_index.h"
#include "odx_cmn.h"

#include <iostream>
#include <QDebug>

LoadIndex::LoadIndex()
{

}



int LoadIndex::load(const QByteArray &fileData)
{
    pugi::xml_parse_result result = doc.load_buffer(fileData.constData(), fileData.length());
    if (!result) {
        std::cout << "LoadIndex load content failed!" << std::endl;
        return -1;
    }

    // Access the root node: CATALOG
    pugi::xml_node root_catalog = doc.child("CATALOG");

    return read_catalog(root_catalog, catelog);
}

void LoadIndex::print()
{
    qDebug() << "CATALOG:"
             << " property:{ F-DTD-VERSION:" << catelog.attr_f_dtd_version
             << " xmlns:xsi:" << catelog.attr_xmlns_xsi
             << " xsi:noNamespaceSchemaLocation:" << catelog.attr_xsi_noNamespaceSchemaLocation
             << "}";
    qDebug() << "  SHORT-NAME:" << catelog.child_short_name;
    qDebug() << "  ABLOCKS SIZE:" << catelog.child_ablocks.ablock.size();
    for (auto iter : catelog.child_ablocks.ablock) {
        qDebug() << "   ABLOCK";
        qDebug() << "     SHORT-NAME:" << iter.child_short_name;
        qDebug() << "     ADMIN-DATA";
        qDebug() << "       DOC-REVISIONS SIZE:" << iter.child_admin_data.child_doc_revisions.child_doc_revision.size();
        for (auto iter1 : iter.child_admin_data.child_doc_revisions.child_doc_revision) {
            qDebug() << "         DOC-REVISION";
            qDebug() << "           REVISION-LABEL:" << iter1.child_revision_label;
            qDebug() << "           DATE:" << iter1.child_date;
        }
        qDebug() << "     CATEGORY:" << iter.child_category;
        qDebug() << "     FILES";
        for (auto iter1 : iter.child_files.child_file) {
            qDebug() << "       FILE:" << iter1.data_value;
        }
    }
}

int LoadIndex::read_catalog(pugi::xml_node node, CATELOG &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "F-DTD-VERSION") == 0) {
            data.attr_f_dtd_version = attr.value();
        } else if (strcmp(attr.name(), "xmlns:xsi") == 0) {
            data.attr_xmlns_xsi = attr.value();
        } else if (strcmp(attr.name(), "xsi:noNamespaceSchemaLocation") == 0) {
            data.attr_xsi_noNamespaceSchemaLocation = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            if (odxcmn::read_short_name(child, data.child_short_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "ABLOCKS") == 0) {
            if (read_ablocks(child, data.child_ablocks)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadIndex::read_ablock(pugi::xml_node node, ABLOCK &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            data.child_short_name = child.child_value();
        } else if (strcmp(child.name(), "ADMIN-DATA") == 0) {
            if (read_admindata(child, data.child_admin_data)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "FILES") == 0) {
            if (read_files(child, data.child_files)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "CATEGORY") == 0) {
            data.child_category = child.child_value();
        }

    }

    return result;
}

int LoadIndex::read_ablocks(pugi::xml_node node, ABLOCKS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {

        if (strcmp(child.name(), "ABLOCK") == 0) {
            ABLOCK ablock;
            if (read_ablock(child, ablock)) {
                result = -1;
                break;
            }
            data.ablock.push_back(ablock);
        }
    }

    result = 0;
    return result;
}


//int LoadIndex::read_category(pugi::xml_node node, QString &data)
//{
//    int result = 0;


//    return result;
//}

int LoadIndex::read_admindata(pugi::xml_node node, ADMIN_DATA &data)
{
    int result = 0;
    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DOC-REVISIONS") == 0) {
            if (read_docrevisions(child, data.child_doc_revisions)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadIndex::read_docrevisions(pugi::xml_node node, DOC_REVISIONS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DOC-REVISION") == 0) {
            DOC_REVISION doc_revision;
            if (read_docrevision(child, doc_revision)) {
                result = -1;
                break;
            }
            data.child_doc_revision.push_back(doc_revision);
        }
    }

    return result;
}



int LoadIndex::read_docrevision(pugi::xml_node node, DOC_REVISION &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "REVISION-LABEL") == 0) {
//            if (read_revision_label(child, data.revision_label))
//            {
//                result = -1;
//                break;
//            }
            data.child_revision_label = child.child_value();
        } else if (strcmp(child.name(), "DATE") == 0) {
//            if (read_date(child, data.date))
//            {
//                result = -1;
//                break;
//            }
            data.child_date = child.child_value();
        }
    }
    result = 0;

    return result;
}

int LoadIndex::read_file(pugi::xml_node node, FILE_ &file)
{
    int result = 0;

    if (strcmp(node.name(), "FILE") == 0) {
       file.data_value = node.child_value();
    }

    return result;
}


int LoadIndex::read_files(pugi::xml_node node, FILES &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        FILE_ file;
        if (strcmp(child.name(), "FILE") == 0) {
            if (read_file(child, file)) {
                result = -1;
                break;
            }
            data.child_file.push_back(file);
        }
    }
    result = 0;

    return result;
}
