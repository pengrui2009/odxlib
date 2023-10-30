#ifndef ODXHANDLER_H
#define ODXHANDLER_H

#include <QString>
#include <memory>

#include "load_index.h"
#include "load_odx_v.h"
#include "load_odx_f.h"
#include "load_odx_d.h"

#include "QtGui/private/qzipreader_p.h"
#include "QtGui/private/qzipwriter_p.h"

class LoadPDX
{
public:
    LoadPDX();
    int load(const QString& filePath);

private:
    std::shared_ptr<LoadIndex> loadindex_ptr_{nullptr};
    std::shared_ptr<LoadODX_V> loadodx_v_ptr_{nullptr};
    std::shared_ptr<LoadODX_F> loadodx_f_ptr_{nullptr};
    std::shared_ptr<LoadODX_D> loadodx_d_ptr_{nullptr};
};

#endif // ODXHANDLER_H
