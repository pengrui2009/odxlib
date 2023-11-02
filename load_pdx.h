#ifndef ODXHANDLER_H
#define ODXHANDLER_H

#include <QMap>
#include <QString>
#include <memory>

#include "load_index.h"
#include "load_odx_v.h"
#include "load_odx_f.h"
#include "load_odx_d.h"
#include "load_odx_e.h"
#include "load_odx_c.h"
#include "load_odx_cs.h"

#include "QtGui/private/qzipreader_p.h"
#include "QtGui/private/qzipwriter_p.h"

//class EcuFlashInfo {
//public:
//    QString ecu_name;
//    QString proto;
//    SESSIONS sessions;
//};
class EcuFlashData {
public:
    QString name;
    QString filename;
    QString fileformat;
};

class DoCANParam {
public:
    uint32_t docan_physical_request_id;
    uint32_t docan_physical_response_id;
    uint32_t docan_functional_request_id;
    uint32_t docan_can_baudrate;
    uint32_t docan_canfd_baudrate;
};

class DoIPParam {
public:
    uint32_t doip_logical_tester_address;
    uint32_t doip_logical_gateway_address;
    uint32_t doip_logical_functional_address;
};

enum UDSType {
    kUdsTypeUdsOnCAN = 1,
    kUdsTypeUdsOnIP = 2,
};

class ComParam {
public:
    int physical_address;
    int function_address;
    int response_address;
};

class EcuFLashParam {
public:
    UDSType uds_type;
    DoCANParam docan_param;
    DoIPParam doip_param;
    ComParam com_param;
};

class EcuFlashInfo {
public:
    QString name;
    EcuFLashParam param;
    QVector<EcuFlashData> data;
};

class EcuFlashInfos {
public:
    QString name;
    QVector<EcuFlashInfo> info;
};

class LoadPDX
{
public:
    LoadPDX();
    int load(const QString& filePath);
    int resolve();
    void print(const EcuFlashInfos& data);

    EcuFlashInfos GetEcuFlashInfo() const
    {
        return ecu_flash_info;
    }
protected:
    int resolve(std::shared_ptr<ODX_V> &odx_ptr);
    int resolve(std::shared_ptr<ODX_D> &odx_ptr);
    int resolve(std::shared_ptr<ODX_F> &odx_ptr);
private:
    EcuFlashInfos ecu_flash_info;

    QMap<QString, std::shared_ptr<ODX_V>> data_odx_v_map;
    QMap<QString, std::shared_ptr<ODX_D>> data_odx_d_map;
    QMap<QString, std::shared_ptr<ODX_C>> data_odx_c_map;
    QMap<QString, std::shared_ptr<ODX_CS>> data_odx_cs_map;
    QMap<QString, std::shared_ptr<ODX_E>> data_odx_e_map;
    QMap<QString, std::shared_ptr<ODX_F>> data_odx_f_map;


    QMap<QString, std::shared_ptr<Flash>> flash_map;
    QMap<QString, std::shared_ptr<BaseVariant>> base_variant_map;

    std::shared_ptr<LoadIndex> loadindex_ptr_{nullptr};
    std::shared_ptr<LoadODX_V> loadodx_v_ptr_{nullptr};
    std::shared_ptr<LoadODX_F> loadodx_f_ptr_{nullptr};
    std::shared_ptr<LoadODX_D> loadodx_d_ptr_{nullptr};
    std::shared_ptr<LoadODX_E> loadodx_e_ptr_{nullptr};
    std::shared_ptr<LoadODX_C> loadodx_c_ptr_{nullptr};
    std::shared_ptr<LoadODX_CS> loadodx_cs_ptr_{nullptr};


};

#endif // ODXHANDLER_H
