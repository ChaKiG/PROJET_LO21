/****************************************************************************
** Meta object code from reading C++ file 'gestiontache.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gestiontache.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gestiontache.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GestionTache_t {
    QByteArrayData data[5];
    char stringdata[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GestionTache_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GestionTache_t qt_meta_stringdata_GestionTache = {
    {
QT_MOC_LITERAL(0, 0, 12), // "GestionTache"
QT_MOC_LITERAL(1, 13, 10), // "creertache"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 18), // "afficherpreemptive"
QT_MOC_LITERAL(4, 44, 17) // "affichercomposite"

    },
    "GestionTache\0creertache\0\0afficherpreemptive\0"
    "affichercomposite"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GestionTache[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GestionTache::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GestionTache *_t = static_cast<GestionTache *>(_o);
        switch (_id) {
        case 0: _t->creertache(); break;
        case 1: _t->afficherpreemptive(); break;
        case 2: _t->affichercomposite(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject GestionTache::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GestionTache.data,
      qt_meta_data_GestionTache,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GestionTache::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GestionTache::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GestionTache.stringdata))
        return static_cast<void*>(const_cast< GestionTache*>(this));
    return QWidget::qt_metacast(_clname);
}

int GestionTache::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_GestionSousTache_t {
    QByteArrayData data[5];
    char stringdata[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GestionSousTache_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GestionSousTache_t qt_meta_stringdata_GestionSousTache = {
    {
QT_MOC_LITERAL(0, 0, 16), // "GestionSousTache"
QT_MOC_LITERAL(1, 17, 10), // "creertache"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 18), // "afficherpreemptive"
QT_MOC_LITERAL(4, 48, 17) // "affichercomposite"

    },
    "GestionSousTache\0creertache\0\0"
    "afficherpreemptive\0affichercomposite"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GestionSousTache[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GestionSousTache::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GestionSousTache *_t = static_cast<GestionSousTache *>(_o);
        switch (_id) {
        case 0: _t->creertache(); break;
        case 1: _t->afficherpreemptive(); break;
        case 2: _t->affichercomposite(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject GestionSousTache::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GestionSousTache.data,
      qt_meta_data_GestionSousTache,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GestionSousTache::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GestionSousTache::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GestionSousTache.stringdata))
        return static_cast<void*>(const_cast< GestionSousTache*>(this));
    return QWidget::qt_metacast(_clname);
}

int GestionSousTache::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
