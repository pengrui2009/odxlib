#ifndef LOADODX_F_H
#define LOADODX_F_H

#include "pugixml.hpp"
#include "odx_cmn.h"

#include <memory>
#include <QVector>
#include <QByteArray>

struct IDENT_VALUE {
    QString attr_type;
    QString data_value;
};

struct IDENT_VALUES {
    QVector <IDENT_VALUE> child_ident_value;
};

struct EXPECTED_IDENT {
    QString attr_id;
    QString child_short_name;
    LONG_NAME child_long_name;
    IDENT_VALUES child_ident_values;
};

struct EXPECTED_IDENTS {
    QVector<EXPECTED_IDENT> child_expected_ident;
};

struct DATABLOCK_REF {
    QString attr_id_ref;
};

struct DATABLOCK_REFS {
    QVector<DATABLOCK_REF> child_datablock_ref;
};

struct SDG {
    QString attr_si;
};

struct SDGS {
    QVector<SDG> child_sdg;
};

struct SESSION {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    EXPECTED_IDENTS child_expected_idents;
    DATABLOCK_REFS child_datablock_refs;
    SDGS child_sdgs;
};

struct SESSIONS {
    QVector<SESSION> child_sessions;
};

struct ENCRYPT_COMPRESS_METHOD {
    QString attr_type;
    QString data_value;
};

struct SEGMENT {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    QString child_source_start_address;
    QString child_source_end_address;
    QString child_compressed_size;
    QString child_uncompressed_size;
    ENCRYPT_COMPRESS_METHOD child_encrypt_compress_method;
};

struct SEGMENTS {
    QVector<SEGMENT> child_segments;
};

struct SECURITY {
    QString child_security_method;
    QString child_fw_signature;
};

struct SECURITYS {
    QVector<SECURITY> child_security;
};

struct OWN_IDENT {
    QString attr_id;
    QString child_short_name;
    QString child_long_name;
    IDENT_VALUE child_ident_value;
};

struct OWN_IDENTS {
    QVector<OWN_IDENT> child_own_ident;
};

struct FLASHDATA_REF {
    QString attr_id_ref;
};



struct DATABLOCK {
    QString attr_id;
    QString attr_oid;
    QString attr_type;
    QString child_short_name;
    LONG_NAME child_long_name;
    QString child_logical_block_index;
    FLASHDATA_REF child_flashdata_ref;
    SEGMENTS child_segments;
    OWN_IDENTS child_own_idents;
    SECURITYS child_securitys;
    QString child_audience;
};

struct DATABLOCKS {
    QVector<DATABLOCK> child_datablocks;
};

struct DATAFORMAT {
    QString attr_selection;
};

struct DATAFILE {
    QString attr_latebound_datafile;
    QString data_value;
};

struct FLASHDATA {
    QString attr_id;
    QString attr_oid;
    QString attr_xsi_type;
    QString child_short_name;
    LONG_NAME child_long_name;
    QString child_size_length;
    QString child_address_length;
    DATAFORMAT child_dataformat;
    QString child_data;
    ENCRYPT_COMPRESS_METHOD child_encrypt_compress_method;
    DATAFILE child_datafile;
};

struct FLASHDATAS {
    QVector<FLASHDATA> child_flashdata;
};

struct MEM {
    SESSIONS child_sessions;
    DATABLOCKS child_datablocks;
    FLASHDATAS child_flashdatas;
};

struct PHYS_SEGMENT {
    QString child_short_name;
    QString child_fillbyte;
    QString child_start_address;
    QString child_end_address;
    QString child_block_size;
    QString child_size;
};

struct PHYS_SEGMENTS {
    QVector<PHYS_SEGMENT> phys_segments;
};

struct PHYS_MEM {
    QString child_short_name;
    PHYS_SEGMENTS child_phys_segments;
};

struct ECU_MEM {
    QString attr_id;
    QString attr_oid;

    QString child_short_name;
    LONG_NAME child_long_name;
    MEM child_mem;
    PHYS_MEM child_phys_mem;
};

struct ECU_MEMS {
    QVector<ECU_MEM> child_ecu_mem;
};



struct SESSION_SNREF {
    QString attr_short_name;
};

struct DIAG_COMM_SNREF {
    QString attr_short_name;
};

struct SESSION_DESC {
    QString attr_oid;
    QString attr_direction;
    QString child_short_name;
    LONG_NAME child_long_name;
    QString child_partnumber;
    QString child_priority;
    SESSION_SNREF child_session_snref;
    DIAG_COMM_SNREF child_diag_comm_snref;
    QString child_audience;
};

struct SESSION_DESCS {
    QVector<SESSION_DESC> child_session_descs;
};


struct ECU_MEM_REF {
    QString attr_id_ref;
};

struct LAYER_REF {
    QString attr_id_ref;
    QString attr_docref;
    QString attr_doctype;
};

struct LAYER_REFS {
    QVector<LAYER_REF> child_layer_ref;
};

struct ECU_MEM_CONNECTOR {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    SESSION_DESCS child_session_descs;
    ECU_MEM_REF child_ecu_mem_ref;
    LAYER_REFS child_layer_refs;
};

struct ECU_MEM_CONNECTORS {
    QVector<ECU_MEM_CONNECTOR> child_ecu_mem_connector;
};

struct FLASH {
    QString attr_id;
    QString attr_oid;

    ECU_MEMS child_ecu_mems;
    QString child_short_name;
    LONG_NAME child_long_name;
    ECU_MEM_CONNECTORS child_ecu_mem_connectors;
};

struct ODX_F {
    QString attr_xmlns_xsi{""};
    QString attr_model_version{""};
    QString attr_xsi_noNamespaceSchemaLocation{""};
    FLASH child_flash;
};

class LoadODX_F
{
public:
    LoadODX_F();
    int load(const QByteArray &fileData);
    void print();

private:
    std::unique_ptr<pugi::xml_document> doc_ptr_;
    ODX_F odx_;

    int read_odx(const pugi::xml_node &node, ODX_F &data);

    int read_flash(const pugi::xml_node &node, FLASH &data);
    int read_ident_value(const pugi::xml_node &node, IDENT_VALUE &data);
    int read_ident_values(const pugi::xml_node &node, IDENT_VALUES &data);
    int read_expected_ident(const pugi::xml_node &node, EXPECTED_IDENT &data);
    int read_expected_idents(const pugi::xml_node &node, EXPECTED_IDENTS &data);
    int read_datablock_ref(const pugi::xml_node &node, DATABLOCK_REF &data);
    int read_datablock_refs(const pugi::xml_node &node, DATABLOCK_REFS &data);
    int read_sdg(const pugi::xml_node &node, SDG &data);
    int read_sdgs(const pugi::xml_node &node, SDGS &data);
    int read_session(const pugi::xml_node &node, SESSION &data);
    int read_sessions(const pugi::xml_node &node, SESSIONS &data);

    int read_datablock(const pugi::xml_node &node, DATABLOCK &data);
    int read_datablocks(const pugi::xml_node &node, DATABLOCKS &data);

    int read_encrypt_compress_method(const pugi::xml_node &node, ENCRYPT_COMPRESS_METHOD &data);
    int read_segment(const pugi::xml_node &node, SEGMENT &data);
    int read_segments(const pugi::xml_node &node, SEGMENTS &data);
    int read_own_ident(const pugi::xml_node &node, OWN_IDENT &data);
    int read_own_idents(const pugi::xml_node &node, OWN_IDENTS &data);
    int read_flashdata_ref(const pugi::xml_node &node, FLASHDATA_REF &data);
    int read_security(const pugi::xml_node &node, SECURITY &data);
    int read_securitys(const pugi::xml_node &node, SECURITYS &data);
    int read_dataformat(const pugi::xml_node &node, DATAFORMAT &data);
    int read_datafile(const pugi::xml_node &node, DATAFILE &data);
    int read_flashdata(const pugi::xml_node &node, FLASHDATA &data);
    int read_flashdatas(const pugi::xml_node &node, FLASHDATAS &data);

    int read_mem(const pugi::xml_node &node, MEM &data);

    int read_phys_segment(const pugi::xml_node &node, PHYS_SEGMENT &data);
    int read_phys_segments(const pugi::xml_node &node, PHYS_SEGMENTS &data);
    int read_phys_mem(const pugi::xml_node &node, PHYS_MEM &data);

    int read_ecu_mem(const pugi::xml_node &node, ECU_MEM &data);
    int read_ecu_mems(const pugi::xml_node &node, ECU_MEMS &data) ;

    int read_long_name(const pugi::xml_node &node, LONG_NAME &data);
    int read_session_snref(const pugi::xml_node &node, SESSION_SNREF &data);
    int read_diag_comm_snref(const pugi::xml_node &node, DIAG_COMM_SNREF &data);
    int read_session_desc(const pugi::xml_node &node, SESSION_DESC &data);
    int read_session_descs(const pugi::xml_node &node, SESSION_DESCS &data);

    int read_ecu_mem_ref(const pugi::xml_node &node, ECU_MEM_REF &data);

    int read_layer_ref(const pugi::xml_node &node, LAYER_REF &data);
    int read_layer_refs(const pugi::xml_node &node, LAYER_REFS &data);
    int read_ecu_mem_connector(const pugi::xml_node &node, ECU_MEM_CONNECTOR &data);
    int read_ecu_mem_connectors(const pugi::xml_node &node, ECU_MEM_CONNECTORS &data);


//    int read_ablocks(pugi::xml_node node, QVector<ABLOCK> &data);
//    int read_ablock(pugi::xml_node node, ABLOCK &data);
//    int read_admindata(pugi::xml_node node, ADMIN_DATA &data);
//    int read_docrevisions(pugi::xml_node node, QVector<DOC_REVISION> &data);
////    int read_revision_label(pugi::xml_node node, QString &data);
////    int read_date(pugi::xml_node node, QString &data);
//    int read_docrevision(pugi::xml_node node, DOC_REVISION &data);
//    int read_files(pugi::xml_node node, QVector<XMLFILE> &files);
//    int read_file(pugi::xml_node node, XMLFILE &file);

    int read_category(pugi::xml_node node, QString &);
};

#endif // LOADODX_F_H
