/****************************************************************************
** Meta object code from reading C++ file 'HelloSignal.h'
**
** Created: Wed Aug 28 18:35:51 2013
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "HelloSignal.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HelloSignal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HelloSignal[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      20,   12,   12,   12, 0x0a,
      27,   12,   12,   12, 0x0a,
      49,   44,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_HelloSignal[] = {
    "HelloSignal\0\0Show()\0Hide()\0NewRootCommand()\0"
    "indx\0SetPrompt(int)\0"
};

const QMetaObject HelloSignal::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HelloSignal,
      qt_meta_data_HelloSignal, 0 }
};

const QMetaObject *HelloSignal::metaObject() const
{
    return &staticMetaObject;
}

void *HelloSignal::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HelloSignal))
        return static_cast<void*>(const_cast< HelloSignal*>(this));
    return QObject::qt_metacast(_clname);
}

int HelloSignal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Show(); break;
        case 1: Hide(); break;
        case 2: NewRootCommand(); break;
        case 3: SetPrompt((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
