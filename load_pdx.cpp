#include "load_pdx.h"

#include <QDebug>

LoadPDX::LoadPDX() :
    loadindex_ptr_{std::make_shared<LoadIndex>()},
    loadodx_v_ptr_{std::make_shared<LoadODX_V>()},
    loadodx_f_ptr_{std::make_shared<LoadODX_F>()},
    loadodx_d_ptr_{std::make_shared<LoadODX_D>()},
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
                loadodx_d_ptr_->load(zipReader.fileData(fileinfo.filePath));
//                loadodx_d_ptr_->print();
            } else if (fileinfo.filePath.endsWith(".odx-c")) {
                loadodx_c_ptr_->load(zipReader.fileData(fileinfo.filePath));
//                loadodx_c_ptr_->print();
            } else if (fileinfo.filePath.endsWith(".odx-cs")) {
                loadodx_cs_ptr_->load(zipReader.fileData(fileinfo.filePath));
                loadodx_cs_ptr_->print();
            } else if (fileinfo.filePath.endsWith(".odx-v")) {
                loadodx_v_ptr_->load(zipReader.fileData(fileinfo.filePath));
//                loadodx_v_ptr_->print();
            } else if (fileinfo.filePath.endsWith(".odx-f")) {
                loadodx_f_ptr_->load(zipReader.fileData(fileinfo.filePath));
//                loadodx_f_ptr_->print();
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
