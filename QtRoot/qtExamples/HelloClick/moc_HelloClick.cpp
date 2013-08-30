/****************************************************************************
** Meta object code from reading C++ file 'HelloClick.h'
**
** Created: Wed Aug 28 18:35:35 2013
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "HelloClick.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HelloClick.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HelloClick[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      33,   19,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_HelloClick[] = {
    "HelloClick\0\0init()\0select,event,\0"
    "DynamicExec(TObject*,uint,TCanvas*)\0"
};

const QMetaObject HelloClick::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_HelloClick,
      qt_meta_data_HelloClick, 0 }
};

const QMetaObject *HelloClick::metaObject() const
{
    return &staticMetaObject;
}

void *HelloClick::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HelloClick))
        return static_cast<void*>(const_cast< HelloClick*>(this));
    return QFrame::qt_metacast(_clname);
}

int HelloClick::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: init(); break;
        case 1: DynamicExec((*reinterpret_cast< TObject*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< TCanvas*(*)>(_a[3]))); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
