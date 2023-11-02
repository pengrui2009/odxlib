#include "load_pdx.h"

#include <QDebug>
#include <iostream>

LoadPDX::LoadPDX() :
    loadindex_ptr_{std::make_shared<LoadIndex>()},
    loadodx_v_ptr_{std::make_shared<LoadODX_V>()},
    loadodx_f_ptr_{std::make_shared<LoadODX_F>()},
    loadodx_d_ptr_{std::make_shared<LoadODX_D>()},
    loadodx_e_ptr_{std::make_shared<LoadODX_E>()},
    loadodx_c_ptr_{std::make_shared<LoadODX_C>()},
    loadodx_cs_ptr_{std::make_shared<LoadODX_CS>()}
{

}

int LoadPDX::load(const QString &filePath)
{
    QString zipPath = "temp";

    QZipReader zipReader(filePath);
    if (!zipReader.exists()) {
        qWarning() << "ZIP 文件不存在";
        return -1;
    }

    // 获取 ZIP 文件中的文件列表
    QVector<QZipReader::FileInfo> fileList = zipReader.fileInfoList();
    qDebug() << "ZIP 文件中的文件列表:" << fileList.size();

    // 解压缩 ZIP 文件中的每个文件
    foreach (const QZipReader::FileInfo& fileinfo, fileList) {
        if (fileinfo.isFile) {
            if (fileinfo.filePath.endsWith("index.xml")) {
                loadindex_ptr_->load(zipReader.fileData(fileinfo.filePath));
//                loadindex_ptr_->print();
            } else if (fileinfo.filePath.endsWith(".odx-d")) {
                QString filename = fileinfo.filePath.left(fileinfo.filePath.length() - 6);
                std::shared_ptr<ODX_D> odx_ptr = std::make_shared<ODX_D>();
                loadodx_d_ptr_->load(zipReader.fileData(fileinfo.filePath), *odx_ptr);
                data_odx_d_map[filename] = odx_ptr;
//                loadodx_d_ptr_->print(*odx_ptr);
            } else if (fileinfo.filePath.endsWith(".odx-c")) {
                QString filename = fileinfo.filePath.left(fileinfo.filePath.length() - 6);
                std::shared_ptr<ODX_C> odx_ptr = std::make_shared<ODX_C>();
                loadodx_c_ptr_->load(zipReader.fileData(fileinfo.filePath), *odx_ptr);
                data_odx_c_map[filename] = odx_ptr;
//                loadodx_c_ptr_->print(*odx_ptr);
            } else if (fileinfo.filePath.endsWith(".odx-cs")) {
                QString filename = fileinfo.filePath.left(fileinfo.filePath.length() - 7);
                std::shared_ptr<ODX_CS> odx_ptr = std::make_shared<ODX_CS>();
                loadodx_cs_ptr_->load(zipReader.fileData(fileinfo.filePath), *odx_ptr);
                data_odx_cs_map[filename] = odx_ptr;
//                loadodx_cs_ptr_->print(*odx_ptr);
            } else if (fileinfo.filePath.endsWith(".odx-v")) {
                QString filename = fileinfo.filePath.left(fileinfo.filePath.length() - 6);
                std::shared_ptr<ODX_V> odx_ptr = std::make_shared<ODX_V>();
                loadodx_v_ptr_->load(zipReader.fileData(fileinfo.filePath), *odx_ptr);
                data_odx_v_map[filename] = odx_ptr;
//                loadodx_v_ptr_->print(*odx_ptr);
            } else if (fileinfo.filePath.endsWith(".odx-e")) {
                QString filename = fileinfo.filePath.left(fileinfo.filePath.length() - 6);
                std::shared_ptr<ODX_E> odx_ptr = std::make_shared<ODX_E>();
                loadodx_e_ptr_->load(zipReader.fileData(fileinfo.filePath), *odx_ptr);
                data_odx_e_map[filename] = odx_ptr;
//                loadodx_e_ptr_->print(*odx_ptr);
            } else if (fileinfo.filePath.endsWith(".odx-f")) {
                QString filename = fileinfo.filePath.left(fileinfo.filePath.length() - 6);
                std::shared_ptr<ODX_F> odx_ptr = std::make_shared<ODX_F>();
                loadodx_f_ptr_->load(zipReader.fileData(fileinfo.filePath), *odx_ptr);
                data_odx_f_map[filename] = odx_ptr;
//                loadodx_f_ptr_->print(*odx_ptr);
            }
            // 读取文件内容
            // QByteArray fileData = zipReader.fileData(fileinfo.filePath);

            // 处理文件数据...
            // qDebug() << "解压缩文件:" << fileinfo.filePath << "大小:" << fileData.size();
            // ...
        }
    }

    zipReader.close();

    return 0;
}

int LoadPDX::resolve(std::shared_ptr<ODX_F> &odx_ptr)
{
    int result = 0;
    std::shared_ptr<Flash> flash_info_ptr = std::make_shared<Flash>();
    std::shared_ptr<ODX_F_Resolve> odx_resolve_ptr = std::make_shared<ODX_F_Resolve>(*odx_ptr);

    result = odx_resolve_ptr->resolve(*flash_info_ptr);
    if (result)
    {
        std::cout << "odx_f resolve failed!" << std::endl;
        return result;
    }

    flash_map[flash_info_ptr->short_name] = flash_info_ptr;

    return result;
}

int LoadPDX::resolve(std::shared_ptr<ODX_V> &odx_ptr)
{
    int result = 0;

    return result;
}

int LoadPDX::resolve(std::shared_ptr<ODX_D> &odx_ptr)
{
    int result = 0;

    std::shared_ptr<DiagLayerContianer> diaglayercontainer_ptr = std::make_shared<DiagLayerContianer>();
    std::shared_ptr<ODX_D_Resolve> odx_d_resolve_ptr = std::make_shared<ODX_D_Resolve>(*odx_ptr);

    result = odx_d_resolve_ptr->resolve(*diaglayercontainer_ptr);
    if (result)
    {
        std::cout << "odx_d resolve failed!" << std::endl;
        return result;
    }

    switch (diaglayercontainer_ptr->data_type)
    {
    case kOdxDataTypeBaseVariant:
        for (auto iter = diaglayercontainer_ptr->base_variants.begin(); iter != diaglayercontainer_ptr->base_variants.end(); iter++)
        {
            base_variant_map[iter->first] = std::make_shared<BaseVariant>(iter->second);
        }
        break;
    default:
        break;
    }

    return result;
}

int LoadPDX::resolve()
{
    int result = 0;

    for (auto iter : data_odx_v_map)
    {

    }

    for (auto iter = data_odx_d_map.begin(); iter != data_odx_d_map.end(); iter++)
    {
        result = resolve(iter.value());
        if (result) {
            std::cout << "odx_d resolve "<< iter.key().toStdString() <<" failed!" << std::endl;
            return result;
        }
    }

    for (auto iter : data_odx_d_map)
    {

    }

    for (auto iter : data_odx_c_map)
    {

    }

    for (auto iter : data_odx_cs_map)
    {

    }

    for (auto iter : data_odx_e_map)
    {

    }

    for (auto iter = data_odx_f_map.begin(); iter != data_odx_f_map.end(); iter++)
    {
        result = resolve(iter.value());
        if (result) {
            std::cout << "odx_f resolve "<< iter.key().toStdString() <<" failed!" << std::endl;
            return result;
        }
    }


    // resolve link bettwen odx
    ecu_flash_info.name = "";
    for (auto iter = flash_map.begin(); iter != flash_map.end(); iter++)
    {
        std::shared_ptr<Flash> flash_ptr = iter.value();
        EcuFlashInfo info_elem;

        info_elem.name = flash_ptr->short_name;
//        qDebug() << "ecu flash sensor name:" << ecu_flash_info.name;
        for (auto iter1 : flash_ptr->ecu_mem_connectors)
        {

            for (auto iter2 : iter1.layer_refs)
            {
//                qDebug() << "base variant name:" << iter2;
                if (base_variant_map.count(iter2))
                {
//                    qDebug() << "base variant name:" << iter2 << " found!";
                    std::shared_ptr<BaseVariant> base_variant_ptr = base_variant_map[iter2];
                    for (auto iter3 : base_variant_ptr->comparam_refs)
                    {
                        if (iter3.second.child_protocol_snref.attr_short_name.contains("DoIP"))
                        {
                            info_elem.param.uds_type = kUdsTypeUdsOnIP;
                            if (iter3.second.attr_id_ref.contains("DoIPLogicalTesterAddress")) {
                                info_elem.param.doip_param.doip_logical_tester_address =
                                        iter3.second.child_simple_value.data_value.toUInt();
                            } else if (iter3.second.attr_id_ref.contains("DoIPLogicalGatewayAddresss")) {
                                info_elem.param.doip_param.doip_logical_gateway_address =
                                        iter3.second.child_simple_value.data_value.toUInt();
                            }  else if (iter3.second.attr_id_ref.contains("DoIPLogicalFunctionalAddress")) {
                                info_elem.param.doip_param.doip_logical_functional_address =
                                        iter3.second.child_simple_value.data_value.toUInt();
                            }
                        } else {
                            info_elem.param.uds_type = kUdsTypeUdsOnCAN;
                            if (iter3.second.attr_id_ref.contains("ISO_15765_2.CP_UniqueRespIdTable"))
                            {
                                if (iter3.second.child_complex_value.child_simple_value.size() >= 10)
                                {
                                    info_elem.param.docan_param.docan_physical_request_id = iter3.second.child_complex_value.child_simple_value[2].data_value.toUInt();
                                    info_elem.param.docan_param.docan_physical_response_id = iter3.second.child_complex_value.child_simple_value[5].data_value.toUInt();
                                }
                            } else if (iter3.second.attr_id_ref.contains("ISO_15765_2.CP_CanFuncReqId")) {
                                info_elem.param.docan_param.docan_functional_request_id = iter3.second.child_simple_value.data_value.toUInt();
                            } else if (iter3.second.attr_id_ref.contains("ISO_11898_2_DWCAN.CP_Baudrate")) {
                                info_elem.param.docan_param.docan_can_baudrate = iter3.second.child_simple_value.data_value.toUInt();
                            } else if (iter3.second.attr_id_ref.contains("ISO_11898_2_DWCAN.CP_CANFDBaudrate")) {
                                info_elem.param.docan_param.docan_canfd_baudrate = iter3.second.child_simple_value.data_value.toUInt();
                            }
                        }
//                        qDebug() << iter3.first << ":" << iter3.second.child_simple_value.data_value;
                    }
                }
            }
//            qDebug() << "iter1.sessiondescs size:" << iter1.sessiondescs.size();
            for (auto iter2 : iter1.sessiondescs)
            {
//                qDebug() << "iter1.sessiondescs size:" << iter2.session.data_blocks.size();
                for (auto iter3 : iter2.session.data_blocks)
                {
                    EcuFlashData elem;
                    elem.name = iter3.flash_data.short_name;
                    elem.fileformat = iter3.flash_data.data_format;
                    elem.filename = iter3.flash_data.data_file;
                    info_elem.data.push_back(elem);
                }
            }

        }
        ecu_flash_info.info.push_back(info_elem);

    }

    return result;
}

void LoadPDX::print(const EcuFlashInfos &data)
{
    qDebug() << "name:" << data.name;
    for (auto iter : data.info)
    {
        qDebug() << "ecu name:" << iter.name;
        qDebug() << "ecu param:";
        if (iter.param.uds_type == kUdsTypeUdsOnCAN)
        {
        qDebug() << "ecu param physical_request_id:" << iter.param.docan_param.docan_physical_request_id;
        qDebug() << "ecu param docan_physical_response_id:" << iter.param.docan_param.docan_physical_response_id;
        qDebug() << "ecu param functional_request_id:" << iter.param.docan_param.docan_functional_request_id;
        qDebug() << "ecu param can baudrate:" << iter.param.docan_param.docan_can_baudrate;
        qDebug() << "ecu param canfd baudrate:" << iter.param.docan_param.docan_canfd_baudrate;
        } else if (iter.param.uds_type == kUdsTypeUdsOnIP) {
        qDebug() << "ecu param logical_tester_address:" << iter.param.doip_param.doip_logical_tester_address;
        qDebug() << "ecu param logical_gateway_address:" << iter.param.doip_param.doip_logical_gateway_address;
        qDebug() << "ecu param logical_functional_address:" << iter.param.doip_param.doip_logical_functional_address;
        }
        qDebug() << "ecu data:";
        for (auto iter1 : iter.data)
        {
        qDebug() << "ecu data file name:" << iter1.name;
        qDebug() << "ecu data file foramt:" << iter1.fileformat;
        qDebug() << "ecu data file name:" << iter1.filename;
        }
    }

}
