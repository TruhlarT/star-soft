/****************************************************************************
** Meta object code from reading C++ file 'PixmapWidget.h'
**
** Created: Wed Aug 28 18:35:38 2013
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "PixmapWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PixmapWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PixmapWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      39,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   13,   13,   13, 0x0a,
      70,   13,   13,   13, 0x0a,
      87,   80,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PixmapWidget[] = {
    "PixmapWidget\0\0zoomFactorChanged(float)\0"
    "Zoommed()\0setZoomFactor(float)\0Magnify()\0"
    "pixmap\0ResetPixmap(QPixmap)\0"
};

const QMetaObject PixmapWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PixmapWidget,
      qt_meta_data_PixmapWidget, 0 }
};

const QMetaObject *PixmapWidget::metaObject() const
{
    return &staticMetaObject;
}

void *PixmapWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PixmapWidget))
        return static_cast<void*>(const_cast< PixmapWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int PixmapWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: zoomFactorChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: Zoommed(); break;
        case 2: setZoomFactor((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: Magnify(); break;
        case 4: ResetPixmap((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void PixmapWidget::zoomFactorChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PixmapWidget::Zoommed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
