#ifndef ODXCMN_H
#define ODXCMN_H

#include "pugixml.hpp"
#include <QString>
#include <QVector>

struct LONG_NAME {
    QString attr_ti{""};
    QString data_value{""};
};

struct PROT_STACK_SNREF {
    QString attr_short_name{""};
};

struct DIAG_COMM_SNREF {
    QString attr_short_name;
};

struct DESC {
    QString data_value;
};

struct TEAM_MEMBER_REF {
    QString attr_id_ref;
};

struct MODIFICATION {
    QString child_change;
    QString child_reason;
};

struct MODIFICATIONS {
    QVector<MODIFICATION> child_modification;
};

struct DOC_REVISION {
    TEAM_MEMBER_REF child_team_member_ref;
    QString child_revision_label;
    QString child_state;
    QString child_date;
    QString child_tool;
    MODIFICATIONS child_modifications;
};

struct DOC_REVISIONS {
    QVector<DOC_REVISION> child_doc_revision;
};

struct ADMIN_DATA {
    QString child_language;
    DOC_REVISIONS child_doc_revisions;
};

struct TEAM_MEMBER {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    QString child_department;
    QString child_address;
    QString child_zip;
    QString child_city;
    QString child_phone;
    QString child_fax;
    QString child_email;
};

struct TEAM_MEMBERS {
    QVector<TEAM_MEMBER> child_team_member;
};

struct XDOC {
    QString child_short_name;
    LONG_NAME child_long_name;
    QString child_number;
    QString child_state;
    QString child_date;
    QString child_publisher;
};

struct RELATED_DOC {
    XDOC child_xdoc;
};

struct RELATED_DOCS {
    QVector<RELATED_DOC> child_related_doc;
};

struct COMPANY_SPECIFIC_INFO {
    RELATED_DOCS child_related_docs;
};

struct COMPANY_DATA {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    TEAM_MEMBERS child_team_members;
    COMPANY_SPECIFIC_INFO child_company_specific_info;
};

struct COMPANY_DATAS {
    QVector<COMPANY_DATA> child_company_data;
};

struct CATEGORY {
    QString data_value;
};



struct BIT_LENGTH {
    QString data_value;
};

struct MAX_LENGTH {
    QString child_data_value;
};

struct MIN_LENGTH {
    QString child_data_value;
};

struct DIAG_CODED_TYPE {
    QString attr_xsi_type;
    QString attr_base_type_encoding;
    QString attr_termination;
    QString attr_base_data_type;
    BIT_LENGTH child_bit_length;
    MAX_LENGTH child_max_length;
    MIN_LENGTH child_min_length;
};

struct PHYSICAL_TYPE {
    QString attr_base_data_type;
    QString attr_display_radix;
};

struct COMPU_METHOD {
    CATEGORY child_category;
};

struct LOWER_LIMIT {
    QString attr_interval_type;
    QString child_data_value;
};

struct UPPER_LIMIT {
    QString attr_interval_type;
    QString child_data_value;
};

struct INTERNAL_CONSTR {
    LOWER_LIMIT child_lower_limit;
    UPPER_LIMIT child_upper_limie;
};

struct DATA_OBJECT_PROP {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    COMPU_METHOD child_compu_method;
    DIAG_CODED_TYPE child_diag_coded_type;
    PHYSICAL_TYPE child_physical_type;
    INTERNAL_CONSTR child_internal_constr;
};

struct DATA_OBJECT_PROPS {
    QVector<DATA_OBJECT_PROP> child_data_object_prop;
};

struct SIMPLE_VALUE {
    QString data_value;
};


struct COMPLEX_VALUE {
    QVector<SIMPLE_VALUE> child_simple_value;
};

struct COMPLEX_VALUES {
    QVector<COMPLEX_VALUE> child_complex_value;
};

struct BYTE_POSITION {
    QString data_value;
};

struct BIT_POSITION {
    QString data_value;
};

struct DATA_OBJECT_PROP_REF {
    QString attr_id_ref;
};

struct PHYSICAL_DEFAULT_VALUE {
    QString data_value;
};

struct COMPLEX_PHYSICAL_DEFAULT_VALUE {
    COMPLEX_VALUES child_complex_values;
};

struct PHYSICAL_DIMENSION {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    QString child_time_exp;
};

struct PHYSICAL_DIMENSION_REF {
    QString attr_id_ref;
};

struct UNIT {
    QString attr_id;
    QString attr_oid;
    QString child_short_name;
    LONG_NAME child_long_name;
    QString child_display_name;
    QString child_factor_si_to_unit;
    QString child_offset_si_to_unit;
    PHYSICAL_DIMENSION_REF child_physical_dimension_ref;
};

struct UNITS {
    QVector<UNIT> child_unit;
};

struct PHYSICAL_DIMENSIONS {
    QVector<PHYSICAL_DIMENSION> child_physical_dimension;
};

struct UNIT_SPEC {
    UNITS child_units;
    PHYSICAL_DIMENSIONS child_physical_dimensions;
};

class odxcmn
{
public:
    odxcmn();
    static int read_short_name(const pugi::xml_node &node, QString &data);
    static int read_long_name(const pugi::xml_node &node, LONG_NAME &data);
    static int read_desc(const pugi::xml_node &node, DESC &data);
    static int read_admin_data(const pugi::xml_node &node, ADMIN_DATA &data);
    static int read_modification(const pugi::xml_node &node, MODIFICATION &data);
    static int read_modifications(const pugi::xml_node &node, MODIFICATIONS &data);
    static int read_xdoc(const pugi::xml_node &node, XDOC &data);
    static int read_related_doc(const pugi::xml_node &node, RELATED_DOC &data);
    static int read_related_docs(const pugi::xml_node &node, RELATED_DOCS &data);
    static int read_company_specific_info(const pugi::xml_node &node, COMPANY_SPECIFIC_INFO &data);
    static int read_company_data(const pugi::xml_node &node, COMPANY_DATA &data);
    static int read_company_datas(const pugi::xml_node &node, COMPANY_DATAS &data);
    static int read_doc_revision(const pugi::xml_node &node, DOC_REVISION &data);
    static int read_doc_revisions(const pugi::xml_node &node, DOC_REVISIONS &data);
    static int read_team_member_ref(const pugi::xml_node &node, TEAM_MEMBER_REF &data);
    static int read_team_member(const pugi::xml_node &node, TEAM_MEMBER &data);
    static int read_team_members(const pugi::xml_node &node, TEAM_MEMBERS &data);
    static int read_simple_value(const pugi::xml_node &node, SIMPLE_VALUE &data);
    static int read_complex_value(const pugi::xml_node &node, COMPLEX_VALUE &data);
    static int read_complex_values(const pugi::xml_node &node, COMPLEX_VALUES &data);
    static int read_category(const pugi::xml_node &node, CATEGORY &data);
    static int read_compu_method(const pugi::xml_node &node, COMPU_METHOD &data);
    static int read_bit_length(const pugi::xml_node &node, BIT_LENGTH &data);
    static int read_max_length(const pugi::xml_node &node, MAX_LENGTH &data);
    static int read_min_length(const pugi::xml_node &node, MIN_LENGTH &data);
    static int read_diag_coded_type(const pugi::xml_node &node, DIAG_CODED_TYPE &data);
    static int read_physical_type(const pugi::xml_node &node, PHYSICAL_TYPE &data);
    static int read_lower_limit(const pugi::xml_node &node, LOWER_LIMIT &data);
    static int read_upper_limit(const pugi::xml_node &node, UPPER_LIMIT &data);
    static int read_internal_constr(const pugi::xml_node &node, INTERNAL_CONSTR &data);
    static int read_byte_position(const pugi::xml_node &node, BYTE_POSITION &data);
    static int read_bit_position(const pugi::xml_node &node, BIT_POSITION &data);
    static int read_data_object_prop_ref(const pugi::xml_node &node, DATA_OBJECT_PROP_REF &data);
    static int read_physical_default_value(const pugi::xml_node &node, PHYSICAL_DEFAULT_VALUE &data);
    static int read_unit_spec(const pugi::xml_node &node, UNIT_SPEC &data);
    static int read_unit(const pugi::xml_node &node, UNIT &data);
    static int read_units(const pugi::xml_node &node, UNITS &data);
    static int read_physical_dimension(const pugi::xml_node &node, PHYSICAL_DIMENSION &data);
    static int read_physical_dimensions(const pugi::xml_node &node, PHYSICAL_DIMENSIONS &data);
    static int read_data_object_prop(const pugi::xml_node &node, DATA_OBJECT_PROP &data);
    static int read_data_object_props(const pugi::xml_node &node, DATA_OBJECT_PROPS &data);
    static int read_physical_dimension_ref(const pugi::xml_node &node, PHYSICAL_DIMENSION_REF &data);
};

#endif // ODXCMN_H
