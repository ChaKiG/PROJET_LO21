/****************************************************************************
** Meta object code from reading C++ file 'tache_editeur.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tache_editeur.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tache_editeur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TacheEditeur_t {
    QByteArrayData data[8];
    char stringdata[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TacheEditeur_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TacheEditeur_t qt_meta_stringdata_TacheEditeur = {
    {
QT_MOC_LITERAL(0, 0, 12), // "TacheEditeur"
QT_MOC_LITERAL(1, 13, 6), // "addPre"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 6), // "majPre"
QT_MOC_LITERAL(4, 28, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(5, 45, 4), // "item"
QT_MOC_LITERAL(6, 50, 6), // "delPre"
QT_MOC_LITERAL(7, 57, 4) // "save"

    },
    "TacheEditeur\0addPre\0\0majPre\0"
    "QListWidgetItem*\0item\0delPre\0save"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TacheEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    1,   35,    2, 0x0a /* Public */,
       6,    0,   38,    2, 0x0a /* Public */,
       7,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TacheEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TacheEditeur *_t = static_cast<TacheEditeur *>(_o);
        switch (_id) {
        case 0: _t->addPre(); break;
        case 1: _t->majPre((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->delPre(); break;
        case 3: _t->save(); break;
        default: ;
        }
    }
}

const QMetaObject TacheEditeur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TacheEditeur.data,
      qt_meta_data_TacheEditeur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TacheEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TacheEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TacheEditeur.stringdata))
        return static_cast<void*>(const_cast< TacheEditeur*>(this));
    return QWidget::qt_metacast(_clname);
}

int TacheEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_AjoutPre_t {
    QByteArrayData data[5];
    char stringdata[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AjoutPre_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AjoutPre_t qt_meta_stringdata_AjoutPre = {
    {
QT_MOC_LITERAL(0, 0, 8), // "AjoutPre"
QT_MOC_LITERAL(1, 9, 9), // "valuesent"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(4, 37, 5) // "choix"

    },
    "AjoutPre\0valuesent\0\0QListWidgetItem*\0"
    "choix"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AjoutPre[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void AjoutPre::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AjoutPre *_t = static_cast<AjoutPre *>(_o);
        switch (_id) {
        case 0: _t->valuesent((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->choix(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AjoutPre::*_t)(QListWidgetItem * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AjoutPre::valuesent)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject AjoutPre::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AjoutPre.data,
      qt_meta_data_AjoutPre,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AjoutPre::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AjoutPre::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AjoutPre.stringdata))
        return static_cast<void*>(const_cast< AjoutPre*>(this));
    return QWidget::qt_metacast(_clname);
}

int AjoutPre::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void AjoutPre::valuesent(QListWidgetItem * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
