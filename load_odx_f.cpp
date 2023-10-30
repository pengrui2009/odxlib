#include "load_odx_f.h"

#include <iostream>
#include <QDebug>

LoadODX_F::LoadODX_F() :
    doc_ptr_{std::make_unique<pugi::xml_document>()}
{

}

int LoadODX_F::load(const QByteArray &fileData)
{
    pugi::xml_parse_result result = doc_ptr_->load_buffer(fileData.constData(), fileData.length());
    if (!result) {
        std::cout << "LoadIndex load content failed!" << std::endl;
        return -1;
    }

    // Access the root node: FLASH
    pugi::xml_node root = doc_ptr_->child("FLASH");

    return read_odx(root, odx_);

    return result;
}

void LoadODX_F::print()
{
    qDebug() << QString("odx-v property:{xmlns:xsi:%1 MODEL-VERSION:%2 xsi:noNamespaceSchemaLocation:%3}").
                arg(odx_.attr_xmlns_xsi, odx_.attr_model_version).arg(odx_.attr_xsi_noNamespaceSchemaLocation);
    qDebug() << QString("  FLASH property:{ID:%1 OID:%2}").arg(odx_.child_flash.attr_id, odx_.child_flash.attr_oid);
    qDebug() << QString("    SHORT-NAME:%1").arg(odx_.child_flash.child_short_name);
    qDebug() << QString("    LONG-NAME property:{%1} :%2").arg(odx_.child_flash.child_long_name.attr_ti).arg(odx_.child_flash.child_long_name.data_value);
    qDebug() << QString("    ECU-MEMS size:%1").arg(odx_.child_flash.child_ecu_mems.child_ecu_mem.size());
    for (auto iter : odx_.child_flash.child_ecu_mems.child_ecu_mem)
    {
    qDebug() << QString("      ECU-MEM property:{%1 %2}").arg(iter.attr_id).arg(iter.attr_oid);
    qDebug() << QString("        SHORT-NAME:%1").arg(iter.child_short_name);
    qDebug() << QString("        LONG-NAME property:{%1} %2").arg(iter.child_long_name.attr_ti).arg(iter.child_long_name.data_value);
    qDebug() << QString("        MEM");
    qDebug() << QString("          SESSIONS size:%1").arg(iter.child_mem.child_sessions.child_sessions.size());
        for (auto iter1 : iter.child_mem.child_sessions.child_sessions) {
    qDebug() << QString("            SESSION property:{%1 %2}").arg(iter1.attr_id).arg(iter1.attr_oid);
    qDebug() << QString("              SHORT-NAME: %1").arg(iter1.child_short_name);
    qDebug() << QString("              LONG-NAME: property:{%1} %2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("              DATABLOCK-REFS size: %1").arg(iter1.child_datablock_refs.child_datablock_ref.size());
            for (auto iter2 : iter1.child_datablock_refs.child_datablock_ref)
            {
    qDebug() << QString("                DATABLOCK-REF property:{%1}").arg(iter2.attr_id_ref);
            }
    qDebug() << QString("              EXPECTED-IDENTS size:%1").arg(iter1.child_expected_idents.child_expected_ident.size());
            for (auto iter2 : iter1.child_expected_idents.child_expected_ident)
            {
    qDebug() << QString("                EXPECTED-IDENT property:{%1}").arg(iter2.attr_id);
    qDebug() << QString("                  SHORT-NAME property:{%1}").arg(iter2.child_short_name);
    qDebug() << QString("                  LONG-NAME property:{%1} %2").arg(iter2.child_long_name.attr_ti).arg(iter2.child_long_name.data_value);
    qDebug() << QString("                  IDENT-VALUES size:%1").arg(iter2.child_ident_values.child_ident_value.size());
                for (auto iter3 : iter2.child_ident_values.child_ident_value)
                {
    qDebug() << QString("                    IDENT-VALUE property:{%1}").arg(iter3.attr_type);
    qDebug() << QString("                      IDENT-VALUE:%2").arg(iter3.data_value);
                }
            }
        }
    qDebug() << QString("          DATABLOCKS size:%1").arg(iter.child_mem.child_datablocks.child_datablocks.size());
        for (auto iter1 : iter.child_mem.child_datablocks.child_datablocks)
        {
    qDebug() << QString("            DATABLOCK property:{%1 %2 %3}").arg(iter1.attr_id).arg(iter1.attr_oid).arg(iter1.attr_type);
    qDebug() << QString("              SHORT-NAME property:%1").arg(iter1.child_short_name);
    qDebug() << QString("              LONG-NAME property:{%1} :%2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("              FLASHDATA-REF property:{%1}").arg(iter1.child_flashdata_ref.attr_id_ref);
    qDebug() << QString("              SEGMENTS size:%1").arg(iter1.child_segments.child_segments.size());
            for (auto iter2 : iter1.child_segments.child_segments)
            {
    qDebug() << QString("                SEGMENT property:{%1 %2}").arg(iter2.attr_id).arg(iter2.attr_oid);
    qDebug() << QString("                SHORT-NAME:%1").arg(iter2.child_short_name);
    qDebug() << QString("                LONG-NAME: property:{%1} %2").arg(iter2.child_long_name.attr_ti).arg(iter2.child_long_name.data_value);
    qDebug() << QString("                SOURCE-START-ADDRESS: %1").arg(iter2.child_source_start_address);
    qDebug() << QString("                SOURCE-END-ADDRESS: %1").arg(iter2.child_source_end_address);
    qDebug() << QString("                COMPRESSED-SIZE: %1").arg(iter2.child_compressed_size);
    qDebug() << QString("                UNCOMPRESSED-SIZE: %1").arg(iter2.child_uncompressed_size);
    qDebug() << QString("                ENCRYPT-COMPRESSED-METHOD: %1").arg(iter2.child_encrypt_compress_method.attr_type).arg(iter2.child_encrypt_compress_method.data_value);
            }
        }
    qDebug() << QString("                FLASHDATAS size: %1").arg(iter.child_mem.child_flashdatas.child_flashdata.size());
        for (auto iter1 : iter.child_mem.child_flashdatas.child_flashdata)
        {
    qDebug() << QString("                  FLASHDATA property:{%1 %2 %3}").arg(iter1.attr_xsi_type).arg(iter1.attr_id).arg(iter1.attr_oid);
    qDebug() << QString("                    SHORT-NAME: %1").arg(iter1.child_short_name);
    qDebug() << QString("                    LONG-NAME: property:{%1} %2").arg(iter1.child_long_name.attr_ti).arg(iter1.child_long_name.data_value);
    qDebug() << QString("                    DATAFORMAT: property:{%1}").arg(iter1.child_dataformat.attr_selection);
    qDebug() << QString("                    ADDRESS-LENGTH: %1").arg(iter1.child_address_length);
    qDebug() << QString("                    SIZE-LENGTH: %1").arg(iter1.child_size_length);
    qDebug() << QString("                    DATAFILE: property:{%1} %2").arg(iter1.child_datafile.attr_latebound_datafile).arg(iter1.child_datafile.data_value);
    qDebug() << QString("                    DATA: %1").arg(iter1.child_data);
    qDebug() << QString("                    ENCRYPT-COMPRESS-METHOD property:{%1} %2").arg(iter1.child_encrypt_compress_method.attr_type).arg(iter1.child_encrypt_compress_method.data_value);
        }
    qDebug() << QString("                PHYS-MEM");
    qDebug() << QString("                  SHORT-NAME: %1").arg(iter.child_phys_mem.child_short_name);
    qDebug() << QString("                  PHYS-SEGMENTS size: %1").arg(iter.child_phys_mem.child_phys_segments.phys_segments.size());
        for (auto iter1 : iter.child_phys_mem.child_phys_segments.phys_segments)
        {
    qDebug() << QString("                    PHYS-SEGMENT");
    qDebug() << QString("                     SHORT-NAME: %1").arg(iter1.child_short_name);
    qDebug() << QString("                     START-ADDRESS: %1").arg(iter1.child_start_address);
    qDebug() << QString("                     END-ADRESS: %1").arg(iter1.child_end_address);
    qDebug() << QString("                     FILLBYTE: %1").arg(iter1.child_fillbyte);
    qDebug() << QString("                     SIZE: %1").arg(iter1.child_size);
    qDebug() << QString("                     BLOCK-SIZE: %1").arg(iter1.child_block_size);
        }
    }
}

int LoadODX_F::read_odx(const pugi::xml_node &node, ODX_F &data)
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

int LoadODX_F::read_flash(const pugi::xml_node &node, FLASH &data)
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
        if (strcmp(child.name(), "ECU-MEMS") == 0) {
            if (read_ecu_mems(child, data.child_ecu_mems)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "SHORT-NAME") == 0) {
            data.child_short_name = child.child_value();
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name))
            {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "ECU-MEM-CONNECTORS") == 0) {
            if (read_ecu_mem_connectors(child, data.child_ecu_mem_connectors)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_F::read_ident_value(const pugi::xml_node &node, IDENT_VALUE &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "TYPE") == 0) {
            data.attr_type = attr.value();
        }
    }
    data.data_value = node.child_value();

    return result;
}

int LoadODX_F::read_ident_values(const pugi::xml_node &node, IDENT_VALUES &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "IDENT-VALUE") == 0) {
            IDENT_VALUE elem;
            if (read_ident_value(child, elem)) {
                result = -1;
                break;
            }
            data.child_ident_value.push_back(elem);
        }
    }
    return result;
}

int LoadODX_F::read_expected_ident(const pugi::xml_node &node, EXPECTED_IDENT &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            data.child_short_name = child.child_value();
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "IDENT-VALUES") == 0) {
            if (read_ident_values(child, data.child_ident_values)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_F::read_expected_idents(const pugi::xml_node &node, EXPECTED_IDENTS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "EXPECTED-IDENT") == 0) {
            EXPECTED_IDENT elem;
            if (read_expected_ident(child, elem)) {
                result = -1;
                break;
            }
            data.child_expected_ident.push_back(elem);
        }
    }

    return result;
}

int LoadODX_F::read_datablock_ref(const pugi::xml_node &node, DATABLOCK_REF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_F::read_datablock_refs(const pugi::xml_node &node, DATABLOCK_REFS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "DATABLOCK-REF") == 0) {
            DATABLOCK_REF elem;
            if (read_datablock_ref(child, elem)) {
                result = -1;
                break;
            }
            data.child_datablock_ref.push_back(elem);
        }
    }

    return result;
}

int LoadODX_F::read_sdg(const pugi::xml_node &node, SDG &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SI") == 0) {
            data.attr_si = attr.value();
        }
    }

    return result;
}

int LoadODX_F::read_sdgs(const pugi::xml_node &node, SDGS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SDG") == 0) {
            SDG elem;
            if (read_sdg(child, elem)) {
                result = -1;
                break;
            }
            data.child_sdg.push_back(elem);
        }
    }

    return result;
}

int LoadODX_F::read_session(const pugi::xml_node &node, SESSION &data)
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
            data.child_short_name = child.child_value();
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "EXPECTED-IDENTS") == 0) {
            if (read_expected_idents(child, data.child_expected_idents)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DATABLOCK-REFS") == 0) {
            if (read_datablock_refs(child, data.child_datablock_refs)) {
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

int LoadODX_F::read_sessions(const pugi::xml_node &node, SESSIONS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SESSION") == 0) {
            SESSION elem;
            if (read_session(child, elem)) {
                result = -1;
                break;
            }
            data.child_sessions.push_back(elem);
        }
    }

    return result;
}

int LoadODX_F::read_encrypt_compress_method(const pugi::xml_node &node, ENCRYPT_COMPRESS_METHOD &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "TYPE") == 0) {
            data.attr_type = attr.value();
        }
    }
    data.data_value = node.child_value();

    return result;
}

int LoadODX_F::read_segment(const pugi::xml_node &node, SEGMENT &data)
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
            data.child_short_name = child.child_value();
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name))
            {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "SOURCE-START-ADDRESS") == 0) {
            data.child_source_start_address = child.child_value();
        } else if (strcmp(child.name(), "SOURCE-END-ADDRESS") == 0) {
            data.child_source_end_address = child.child_value();
        } else if (strcmp(child.name(), "COMPRESSED-SIZE") == 0) {
            data.child_compressed_size = child.child_value();
        } else if (strcmp(child.name(), "UNCOMPRESSED-SIZE") == 0) {
            data.child_uncompressed_size = child.child_value();
        } else if (strcmp(child.name(), "ENCRYPT-COMPRESS-METHOD") == 0) {
            if (read_encrypt_compress_method(child, data.child_encrypt_compress_method)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_F::read_segments(const pugi::xml_node &node, SEGMENTS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SEGMENT") == 0) {
            SEGMENT elem;
            if (read_segment(child, elem)) {
                result = -1;
                break;
            }
            data.child_segments.push_back(elem);
        }
    }

    return result;
}

int LoadODX_F::read_own_ident(const pugi::xml_node &node, OWN_IDENT &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            data.child_short_name = child.child_value();
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            data.child_long_name = child.child_value();
        } else if (strcmp(child.name(), "IDENT-VALUE") == 0) {
            if (read_ident_value(child, data.child_ident_value)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_F::read_own_idents(const pugi::xml_node &node, OWN_IDENTS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SEGMENT") == 0) {
            OWN_IDENT elem;
            if (read_own_ident(child, elem)) {
                result = -1;
                break;
            }
            data.child_own_ident.push_back(elem);
        }
    }

    return result;
}

int LoadODX_F::read_flashdata_ref(const pugi::xml_node &node, FLASHDATA_REF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_F::read_security(const pugi::xml_node &node, SECURITY &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SECURITY-METOHD") == 0) {
            data.child_security_method = child.child_value();
        } else if (strcmp(child.name(), "FW-SIGNATURE") == 0) {
            data.child_fw_signature = child.child_value();
        }
    }

    return result;
}

int LoadODX_F::read_securitys(const pugi::xml_node &node, SECURITYS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SECURITY") == 0) {
            SECURITY elem;
            if (read_security(child, elem)) {
                result = -1;
                break;
            }
            data.child_security.push_back(elem);
        }
    }

    return result;
}

int LoadODX_F::read_datablock(const pugi::xml_node &node, DATABLOCK &data)
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
            data.child_short_name = child.child_value();
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LOGICAL-BLOCK-INDEX") == 0) {
            data.child_logical_block_index = child.child_value();
        } else if (strcmp(child.name(), "FLASHDATA-REF") == 0) {
            if (read_flashdata_ref(child, data.child_flashdata_ref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "SEGMENTS") == 0) {
            if (read_segments(child, data.child_segments)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "OWN-IDENTS") == 0) {
            if (read_own_idents(child, data.child_own_idents)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "SECURITYS") == 0) {
            if (read_securitys(child, data.child_securitys)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "AUDIENCE") == 0) {
            data.child_audience = child.value();
        }

    }

    return result;
}

int LoadODX_F::read_datablocks(const pugi::xml_node &node, DATABLOCKS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SESSIONS") == 0) {
            DATABLOCK elem;
            if (read_datablock(child, elem)) {
                result = -1;
                break;
            }
            data.child_datablocks.push_back(elem);
        }
    }

    return result;
}

int LoadODX_F::read_dataformat(const pugi::xml_node &node, DATAFORMAT &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SELECTION") == 0) {
            data.attr_selection = attr.value();
        }
    }

    return result;
}

int LoadODX_F::read_datafile(const pugi::xml_node &node, DATAFILE &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "LATEBOUND-DATAFILE") == 0) {
            data.attr_latebound_datafile = attr.value();
        }
    }
    data.data_value = node.child_value();

    return result;
}

int LoadODX_F::read_flashdata(const pugi::xml_node &node, FLASHDATA &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID") == 0) {
            data.attr_id = attr.value();
        } else if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        } else if (strcmp(attr.name(), "xsi:type") == 0) {
            data.attr_xsi_type = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            data.child_short_name = child.child_value();
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (odxcmn::read_long_name(child, data.child_long_name))
            {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "SIZE-LENGTH") == 0) {
            data.child_size_length = child.child_value();
        } else if (strcmp(child.name(), "ADDRESS-LENGTH") == 0) {
            data.child_address_length = child.child_value();
        } else if (strcmp(child.name(), "DATAFORMAT") == 0) {
            if (read_dataformat(child, data.child_dataformat)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "ENCRYPT-COMPRESS-METHOD") == 0) {
            if (read_encrypt_compress_method(child, data.child_encrypt_compress_method)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DATAFILE") == 0) {
            if (read_datafile(child, data.child_datafile)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DATA") == 0) {
            data.child_data = child.child_value();
        }
    }

    return result;
}

int LoadODX_F::read_flashdatas(const pugi::xml_node &node, FLASHDATAS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "FLASHDATA") == 0) {
            FLASHDATA elem;
            if (read_flashdata(child, elem)) {
                result = -1;
                break;
            }
            data.child_flashdata.push_back(elem);
        }
    }

    return result;
}

int LoadODX_F::read_mem(const pugi::xml_node &node, MEM &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SESSIONS") == 0) {
            if (read_sessions(child, data.child_sessions)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DATABLOCKS") == 0) {
            if (read_datablocks(child, data.child_datablocks)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "FLASHDATAS") == 0) {
            if (read_flashdatas(child, data.child_flashdatas)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_F::read_phys_segment(const pugi::xml_node &node, PHYS_SEGMENT &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            data.child_short_name = child.child_value();
        } else if (strcmp(child.name(), "FILLBYTE") == 0) {
            data.child_fillbyte = child.child_value();
        } else if (strcmp(child.name(), "START-ADDRESS") == 0) {
            data.child_start_address = child.child_value();
        } else if (strcmp(child.name(), "END-ADDRESS") == 0) {
            data.child_end_address = child.child_value();
        } else if (strcmp(child.name(), "BLOCK-SIZE") == 0) {
            data.child_block_size = child.child_value();
        } else if (strcmp(child.name(), "SIZE") == 0) {
            data.child_size = child.child_value();
        }
    }

    return result;
}

int LoadODX_F::read_phys_segments(const pugi::xml_node &node, PHYS_SEGMENTS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "PHYS-SEGMENT") == 0) {
            PHYS_SEGMENT elem;
            if (read_phys_segment(child, elem)) {
                result = -1;
                break;
            }
            data.phys_segments.push_back(elem);
        }
    }

    return result;
}

int LoadODX_F::read_phys_mem(const pugi::xml_node &node, PHYS_MEM &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            data.child_short_name = child.child_value();
        } else if (strcmp(child.name(), "PHYS-SEGMENTS") == 0) {
            if (read_phys_segments(child, data.child_phys_segments)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_F::read_ecu_mem(const pugi::xml_node &node, ECU_MEM &data)
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
            data.child_short_name = child.child_value();
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (read_long_name(child, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "MEM") == 0) {
            if (read_mem(child, data.child_mem)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PHYS-MEM") == 0) {
            if (read_phys_mem(child, data.child_phys_mem)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_F::read_ecu_mems(const pugi::xml_node &node, ECU_MEMS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "ECU-MEM") == 0) {
            ECU_MEM elem;
            if (read_ecu_mem(child, elem)) {
                result = -1;
                break;
            }
            data.child_ecu_mem.push_back(elem);
        }
    }

    return result;
}

int LoadODX_F::read_long_name(const pugi::xml_node &node, LONG_NAME &data)
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

int LoadODX_F::read_session_snref(const pugi::xml_node &node, SESSION_SNREF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_F::read_diag_comm_snref(const pugi::xml_node &node, DIAG_COMM_SNREF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "SHORT-NAME") == 0) {
            data.attr_short_name = attr.value();
        }
    }

    return result;
}

int LoadODX_F::read_session_desc(const pugi::xml_node &node, SESSION_DESC &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "OID") == 0) {
            data.attr_oid = attr.value();
        } else if (strcmp(attr.name(), "DIRECTION") == 0) {
            data.attr_direction = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SHORT-NAME") == 0) {
            data.child_short_name = child.child_value();
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (read_long_name(node, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "PARTNUMBER") == 0) {
            data.child_partnumber = child.child_value();
        } else if (strcmp(child.name(), "PRIORITY") == 0) {
            data.child_priority = child.child_value();
        } else if (strcmp(child.name(), "SESSION-SNREF") == 0) {
            if (read_session_snref(node, data.child_session_snref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "DIAG-COMM-SNREF") == 0) {
            if (read_diag_comm_snref(node, data.child_diag_comm_snref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "AUDIENCE") == 0) {
            data.child_audience = child.child_value();
        }
    }

    return result;
}

int LoadODX_F::read_session_descs(const pugi::xml_node &node, SESSION_DESCS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SESSION-DESC") == 0) {
            SESSION_DESC elem;
            if (read_session_desc(child, elem)) {
                result = -1;
                break;
            }
            data.child_session_descs.push_back(elem);
        }
    }

    return result;
}

int LoadODX_F::read_ecu_mem_ref(const pugi::xml_node &node, ECU_MEM_REF &data)
{
    int result = 0;

    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "ID-REF") == 0) {
            data.attr_id_ref = attr.value();
        }
    }

    return result;
}

int LoadODX_F::read_layer_ref(const pugi::xml_node &node, LAYER_REF &data)
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

int LoadODX_F::read_layer_refs(const pugi::xml_node &node, LAYER_REFS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "SESSION-DESC") == 0) {
            LAYER_REF elem;
            if (read_layer_ref(child, elem)) {
                result = -1;
                break;
            }
            data.child_layer_ref.push_back(elem);
        }
    }

    return result;
}

int LoadODX_F::read_ecu_mem_connector(const pugi::xml_node &node, ECU_MEM_CONNECTOR &data)
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
            data.child_short_name = child.child_value();
        } else if (strcmp(child.name(), "LONG-NAME") == 0) {
            if (read_long_name(node, data.child_long_name)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "SESSION-DESCS") == 0) {
            if (read_session_descs(child, data.child_session_descs)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "ECU-MEM-REF") == 0) {
            if (read_ecu_mem_ref(child, data.child_ecu_mem_ref)) {
                result = -1;
                break;
            }
        } else if (strcmp(child.name(), "LAYER-REFS") == 0) {
            if (read_layer_refs(child, data.child_layer_refs)) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

int LoadODX_F::read_ecu_mem_connectors(const pugi::xml_node &node, ECU_MEM_CONNECTORS &data)
{
    int result = 0;

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
        if (strcmp(child.name(), "ECU-MEM-CONNECTOR") == 0) {
            ECU_MEM_CONNECTOR elem;
            if (read_ecu_mem_connector(child, elem)) {
                result = -1;
                break;
            }
            data.child_ecu_mem_connector.push_back(elem);
        }
    }

    return result;
}
