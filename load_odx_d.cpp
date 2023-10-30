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

    // Access the root node: FLASH
    pugi::xml_node root = doc_ptr_->child("FLASH");

    return read_odx(root, odx_);
}

void LoadODX_D::print()
{
    qDebug() << QString("odx-v property:{xmlns:xsi:%1 MODEL-VERSION:%2 xsi:noNamespaceSchemaLocation:%3}").
                arg(odx_.attr_xmlns_xsi, odx_.attr_model_version).arg(odx_.attr_xsi_noNamespaceSchemaLocation);

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
        if (strcmp(child.name(), "FLASH") == 0) {
            if (read_flash(child, data.child_flash)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}
