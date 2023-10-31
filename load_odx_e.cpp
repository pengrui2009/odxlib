#include "load_odx_e.h"

#include <iostream>
#include <QDebug>

LoadODX_E::LoadODX_E() :
    doc_ptr_{std::make_unique<pugi::xml_document>()}
{

}

int LoadODX_E::load(const QByteArray &fileData)
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

void LoadODX_E::print()
{

}

int LoadODX_E::read_odx(const pugi::xml_node &node, ODX_E &data)
{
    int result = 0;

//    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
//        if (strcmp(attr.name(), "xmlns:xsi") == 0) {
//            data.attr_xmlns_xsi = attr.value();
//        } else if (strcmp(attr.name(), "MODEL-VERSION") == 0) {
//            data.attr_model_version = attr.value();
//        } else if (strcmp(attr.name(), "xsi:noNamespaceSchemaLocation") == 0) {
//            data.attr_xsi_noNamespaceSchemaLocation = attr.value();
//        }
//    }

//    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
//        if (strcmp(child.name(), "DIAG-LAYER-CONTAINER") == 0) {
//            if (read_diag_layer_container(child, data.child_diag_layer_container)) {
//                result = -1;
//                break;
//            }
//        }
//    }

    return result;
}
