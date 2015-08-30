/****************************************************************************
** Meta object code from reading C++ file 'fenetres_gestion_programmations.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../fenetres_gestion_programmations.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetres_gestion_programmations.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CreationProgrammation_t {
    QByteArrayData data[4];
    char stringdata[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreationProgrammation_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreationProgrammation_t qt_meta_stringdata_CreationProgrammation = {
    {
QT_MOC_LITERAL(0, 0, 21), // "CreationProgrammation"
QT_MOC_LITERAL(1, 22, 9), // "creerProg"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 9) // "creerActi"

    },
    "CreationProgrammation\0creerProg\0\0"
    "creerActi"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreationProgrammation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CreationProgrammation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreationProgrammation *_t = static_cast<CreationProgrammation *>(_o);
        switch (_id) {
        case 0: _t->creerProg(); break;
        case 1: _t->creerActi(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CreationProgrammation::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CreationProgrammation.data,
      qt_meta_data_CreationProgrammation,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CreationProgrammation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreationProgrammation::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CreationProgrammation.stringdata))
        return static_cast<void*>(const_cast< CreationProgrammation*>(this));
    return QWidget::qt_metacast(_clname);
}

int CreationProgrammation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_CreationActivite_t {
    QByteArrayData data[4];
    char stringdata[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreationActivite_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreationActivite_t qt_meta_stringdata_CreationActivite = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CreationActivite"
QT_MOC_LITERAL(1, 17, 4), // "save"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 6) // "change"

    },
    "CreationActivite\0save\0\0change"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreationActivite[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    1,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void CreationActivite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreationActivite *_t = static_cast<CreationActivite *>(_o);
        switch (_id) {
        case 0: _t->save(); break;
        case 1: _t->change((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CreationActivite::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CreationActivite.data,
      qt_meta_data_CreationActivite,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CreationActivite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreationActivite::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CreationActivite.stringdata))
        return static_cast<void*>(const_cast< CreationActivite*>(this));
    return QWidget::qt_metacast(_clname);
}

int CreationActivite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_ProgrammationEditeur_t {
    QByteArrayData data[4];
    char stringdata[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProgrammationEditeur_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProgrammationEditeur_t qt_meta_stringdata_ProgrammationEditeur = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ProgrammationEditeur"
QT_MOC_LITERAL(1, 21, 4), // "save"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7) // "delprog"

    },
    "ProgrammationEditeur\0save\0\0delprog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProgrammationEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ProgrammationEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProgrammationEditeur *_t = static_cast<ProgrammationEditeur *>(_o);
        switch (_id) {
        case 0: _t->save(); break;
        case 1: _t->delprog(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ProgrammationEditeur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ProgrammationEditeur.data,
      qt_meta_data_ProgrammationEditeur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ProgrammationEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProgrammationEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ProgrammationEditeur.stringdata))
        return static_cast<void*>(const_cast< ProgrammationEditeur*>(this));
    return QWidget::qt_metacast(_clname);
}

int ProgrammationEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
