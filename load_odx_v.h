#ifndef LOADODX_V_H
#define LOADODX_V_H

#include "odx_cmn.h"
#include "pugixml.hpp"

#include <memory>
#include <QVector>
#include <QByteArray>

struct INFO_COMPONENT {
    QString attr_xsi_type{""};
    QString attr_id{""};
    QString attr_oid{""};
    QString child_short_name{""};
    LONG_NAME child_long_name{""};
};

struct INFO_COMPONENTS {
    QVector<INFO_COMPONENT> child_info_component;
};

struct INFO_COMPONENT_REF {
    QString attr_id_ref{""};
};

struct INFO_COMPONENT_REFS {
    QVector<INFO_COMPONENT_REF> child_info_component_ref;
};

struct VEHICLE_CONNECTOR_PIN {
    QString attr_id{""};
    QString attr_oid{""};
    QString attr_type{""};
    QString child_short_name{""};
    LONG_NAME child_long_name;
    QString child_pin_number{""};
};

struct VEHICLE_CONNECTOR_PINS {
    QVector<VEHICLE_CONNECTOR_PIN> vehicle_connector_pin;
};

struct VEHICLE_CONNECTOR {
    QString attr_oid{""};
    QString child_short_name{""};
    LONG_NAME child_long_name;
    VEHICLE_CONNECTOR_PINS child_vehicle_connector_pins;
};

struct VEHICLE_CONNECTORS {
    QVector<VEHICLE_CONNECTOR> child_vehicle_connector;
};

struct PHYSICAL_VEHICLE_LINK_REF {
    QString attr_id_ref{""};
};

struct PROTOCOL_REF {
    QString attr_id_ref{""};
    QString attr_docref{""};
    QString attr_doctype{""};
};

struct FUNCTIONAL_GROUP_REF {
    QString attr_id_ref{""};
    QString attr_docref{""};
    QString attr_doctype{""};
};

struct BASE_VARIANT_REF {
    QString attr_id_ref{""};
};



struct LOGICAL_LINK {
    QString attr_xsi_type{""};
    QString attr_id{""};
    QString attr_oid{""};
    QString child_short_name{""};
    LONG_NAME child_long_name;
    PHYSICAL_VEHICLE_LINK_REF child_physical_vehicle_link_ref;
    PROTOCOL_REF child_protocol_ref;
    BASE_VARIANT_REF child_base_variant_ref;
    PROT_STACK_SNREF child_prot_stack_snref;
    FUNCTIONAL_GROUP_REF child_functional_group_ref;
};

struct LOGICAL_LINKS {
    QVector<LOGICAL_LINK> child_logical_link;
};

struct VEHICLE_CONNECTOR_PIN_REF {
    QString attr_id_ref{""};
};

struct VEHICLE_CONNECTOR_PIN_REFS {
    QVector<VEHICLE_CONNECTOR_PIN_REF> child_vehicle_connector_pin_ref;
};

struct PHYSICAL_VEHICLE_LINK {
    QString attr_id{""};
    QString attr_oid{""};
    QString attr_type{""};
    QString child_short_name{""};
    LONG_NAME child_long_name;
    VEHICLE_CONNECTOR_PIN_REFS child_vehicle_connector_pin_refs;
};

struct PHYSICAL_VEHICLE_LINKS {
    QVector<PHYSICAL_VEHICLE_LINK> child_physical_vehicle_link;
};

struct VEHICLE_INFORMATION {
    QString attr_oid{""};
    QString child_short_name{""};
    LONG_NAME child_long_name;
    INFO_COMPONENT_REFS child_info_component_refs;
    VEHICLE_CONNECTORS child_vehicle_connectors;
    LOGICAL_LINKS child_logical_links;
    PHYSICAL_VEHICLE_LINKS child_physical_vehicle_links;
};

struct VEHICLE_INFORMATIONS {
    QVector<VEHICLE_INFORMATION> child_vehicle_information;
};

struct VEHICLE_INFO_SPEC {
    QString attr_id{""};
    QString attr_oid{""};
    QString child_short_name{""};
    LONG_NAME child_long_name;
    INFO_COMPONENTS child_info_components;
    VEHICLE_INFORMATIONS child_vehicle_informations;
};

struct ODX_V {
    QString attr_xmlns_xsi{""};
    QString attr_model_version{""};
    QString attr_xsi_noNamespaceSchemaLocation{""};
    VEHICLE_INFO_SPEC child_vehicle_info_spec;
};

class LoadODX_V
{
public:
    LoadODX_V();
    int load(const QByteArray &fileData);
    void print();

private:
    ODX_V odx_;
    std::unique_ptr<pugi::xml_document> doc_ptr_{nullptr};

    int read_odx(const pugi::xml_node &node, ODX_V &data);

    int read_info_component(const pugi::xml_node &node, INFO_COMPONENT &data);
    int read_info_components(const pugi::xml_node &node, INFO_COMPONENTS &data);

    int read_info_component_ref(const pugi::xml_node &node, INFO_COMPONENT_REF &data);
    int read_info_component_refs(const pugi::xml_node &node, INFO_COMPONENT_REFS &data);

    int read_pin_number(const pugi::xml_node &node, QString &data);
    int read_vehicle_connector_pin(const pugi::xml_node &node, VEHICLE_CONNECTOR_PIN &data);
    int read_vehicle_connector_pins(const pugi::xml_node &node, VEHICLE_CONNECTOR_PINS &data);
    int read_vehicle_connector(const pugi::xml_node &node, VEHICLE_CONNECTOR &data);
    int read_vehicle_connectors(const pugi::xml_node &node, VEHICLE_CONNECTORS &data);

    int read_physical_vehicle_link_ref(const pugi::xml_node &node, PHYSICAL_VEHICLE_LINK_REF &data);
    int read_protocol_ref(const pugi::xml_node &node, PROTOCOL_REF &data);

    int read_base_variant_ref(const pugi::xml_node &node, BASE_VARIANT_REF &data);
    int read_prot_stack__snref(const pugi::xml_node &node, PROT_STACK_SNREF &data);
    int read_functional_group_ref(const pugi::xml_node &node, FUNCTIONAL_GROUP_REF &data);
    int read_logical_link(const pugi::xml_node &node, LOGICAL_LINK &data);
    int read_logical_links(const pugi::xml_node &node, LOGICAL_LINKS &data);
    int read_physical_vehicle_links(const pugi::xml_node &node, PHYSICAL_VEHICLE_LINKS &data);

    int read_vehicle_connector_pin_ref(const pugi::xml_node &node, VEHICLE_CONNECTOR_PIN_REF &data);
    int read_vehicle_connector_pin_refs(const pugi::xml_node &node, VEHICLE_CONNECTOR_PIN_REFS &data);
    int read_physical_vehicle_link(const pugi::xml_node &node, PHYSICAL_VEHICLE_LINK &data);
    int read_vehicle_information(const pugi::xml_node &node, VEHICLE_INFORMATION &data);
    int read_vehicle_informations(const pugi::xml_node &node, VEHICLE_INFORMATIONS &data);

    int read_vehicle_info_spec(const pugi::xml_node &node, VEHICLE_INFO_SPEC &data);
};

#endif // LOADODX_V_H
