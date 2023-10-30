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
