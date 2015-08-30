/****************************************************************************
** Meta object code from reading C++ file 'fenetres_gestion_projets.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../fenetres_gestion_projets.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetres_gestion_projets.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GestionProj_t {
    QByteArrayData data[11];
    char stringdata[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GestionProj_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GestionProj_t qt_meta_stringdata_GestionProj = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GestionProj"
QT_MOC_LITERAL(1, 12, 7), // "majEdit"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 38, 4), // "item"
QT_MOC_LITERAL(5, 43, 11), // "ajoutprojet"
QT_MOC_LITERAL(6, 55, 5), // "suppr"
QT_MOC_LITERAL(7, 61, 7), // "exportp"
QT_MOC_LITERAL(8, 69, 7), // "importp"
QT_MOC_LITERAL(9, 77, 16), // "ajoutTacheRacine"
QT_MOC_LITERAL(10, 94, 10) // "ajoutTache"

    },
    "GestionProj\0majEdit\0\0QTreeWidgetItem*\0"
    "item\0ajoutprojet\0suppr\0exportp\0importp\0"
    "ajoutTacheRacine\0ajoutTache"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GestionProj[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,
       9,    0,   56,    2, 0x0a /* Public */,
      10,    0,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GestionProj::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GestionProj *_t = static_cast<GestionProj *>(_o);
        switch (_id) {
        case 0: _t->majEdit((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->ajoutprojet(); break;
        case 2: _t->suppr(); break;
        case 3: _t->exportp(); break;
        case 4: _t->importp(); break;
        case 5: _t->ajoutTacheRacine(); break;
        case 6: _t->ajoutTache(); break;
        default: ;
        }
    }
}

const QMetaObject GestionProj::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GestionProj.data,
      qt_meta_data_GestionProj,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GestionProj::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GestionProj::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GestionProj.stringdata))
        return static_cast<void*>(const_cast< GestionProj*>(this));
    return QWidget::qt_metacast(_clname);
}

int GestionProj::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
struct qt_meta_stringdata_suppressionProjet_t {
    QByteArrayData data[4];
    char stringdata[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_suppressionProjet_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_suppressionProjet_t qt_meta_stringdata_suppressionProjet = {
    {
QT_MOC_LITERAL(0, 0, 17), // "suppressionProjet"
QT_MOC_LITERAL(1, 18, 12), // "deleteprojet"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6) // "retour"

    },
    "suppressionProjet\0deleteprojet\0\0retour"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_suppressionProjet[] = {

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

void suppressionProjet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        suppressionProjet *_t = static_cast<suppressionProjet *>(_o);
        switch (_id) {
        case 0: _t->deleteprojet(); break;
        case 1: _t->retour(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject suppressionProjet::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_suppressionProjet.data,
      qt_meta_data_suppressionProjet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *suppressionProjet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *suppressionProjet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_suppressionProjet.stringdata))
        return static_cast<void*>(const_cast< suppressionProjet*>(this));
    return QWidget::qt_metacast(_clname);
}

int suppressionProjet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_exportProjet_t {
    QByteArrayData data[4];
    char stringdata[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_exportProjet_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_exportProjet_t qt_meta_stringdata_exportProjet = {
    {
QT_MOC_LITERAL(0, 0, 12), // "exportProjet"
QT_MOC_LITERAL(1, 13, 9), // "expprojet"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6) // "retour"

    },
    "exportProjet\0expprojet\0\0retour"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_exportProjet[] = {

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

void exportProjet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        exportProjet *_t = static_cast<exportProjet *>(_o);
        switch (_id) {
        case 0: _t->expprojet(); break;
        case 1: _t->retour(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject exportProjet::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_exportProjet.data,
      qt_meta_data_exportProjet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *exportProjet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *exportProjet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_exportProjet.stringdata))
        return static_cast<void*>(const_cast< exportProjet*>(this));
    return QWidget::qt_metacast(_clname);
}

int exportProjet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_importProjet_t {
    QByteArrayData data[4];
    char stringdata[26];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_importProjet_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_importProjet_t qt_meta_stringdata_importProjet = {
    {
QT_MOC_LITERAL(0, 0, 12), // "importProjet"
QT_MOC_LITERAL(1, 13, 4), // "load"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 6) // "retour"

    },
    "importProjet\0load\0\0retour"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_importProjet[] = {

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

void importProjet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        importProjet *_t = static_cast<importProjet *>(_o);
        switch (_id) {
        case 0: _t->load(); break;
        case 1: _t->retour(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject importProjet::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_importProjet.data,
      qt_meta_data_importProjet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *importProjet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *importProjet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_importProjet.stringdata))
        return static_cast<void*>(const_cast< importProjet*>(this));
    return QWidget::qt_metacast(_clname);
}

int importProjet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_ajouterProjet_t {
    QByteArrayData data[5];
    char stringdata[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ajouterProjet_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ajouterProjet_t qt_meta_stringdata_ajouterProjet = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ajouterProjet"
QT_MOC_LITERAL(1, 14, 11), // "ajoutProjet"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 6), // "retour"
QT_MOC_LITERAL(4, 34, 15) // "setmindateechee"

    },
    "ajouterProjet\0ajoutProjet\0\0retour\0"
    "setmindateechee"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ajouterProjet[] = {

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
       4,    1,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,    2,

       0        // eod
};

void ajouterProjet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ajouterProjet *_t = static_cast<ajouterProjet *>(_o);
        switch (_id) {
        case 0: _t->ajoutProjet(); break;
        case 1: _t->retour(); break;
        case 2: _t->setmindateechee((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ajouterProjet::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ajouterProjet.data,
      qt_meta_data_ajouterProjet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ajouterProjet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ajouterProjet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ajouterProjet.stringdata))
        return static_cast<void*>(const_cast< ajouterProjet*>(this));
    return QWidget::qt_metacast(_clname);
}

int ajouterProjet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
