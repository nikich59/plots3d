/****************************************************************************
** Meta object code from reading C++ file 'settingswidgetcommon.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/settingswidgetcommon.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingswidgetcommon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SettingsWidgetCommon_t {
    QByteArrayData data[11];
    char stringdata0[304];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingsWidgetCommon_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingsWidgetCommon_t qt_meta_stringdata_SettingsWidgetCommon = {
    {
QT_MOC_LITERAL(0, 0, 20), // "SettingsWidgetCommon"
QT_MOC_LITERAL(1, 21, 28), // "on_pushButton_colorX_clicked"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 32), // "on_pushButton_configFile_clicked"
QT_MOC_LITERAL(4, 84, 33), // "on_pushButton_isonetColor_cli..."
QT_MOC_LITERAL(5, 118, 33), // "on_checkBox_isonetEnabled_cli..."
QT_MOC_LITERAL(6, 152, 31), // "on_checkBox_timeEnabled_clicked"
QT_MOC_LITERAL(7, 184, 28), // "on_pushButton_colorY_clicked"
QT_MOC_LITERAL(8, 213, 28), // "on_pushButton_colorZ_clicked"
QT_MOC_LITERAL(9, 242, 30), // "on_pushButton_netColor_clicked"
QT_MOC_LITERAL(10, 273, 30) // "on_checkBox_netEnabled_clicked"

    },
    "SettingsWidgetCommon\0on_pushButton_colorX_clicked\0"
    "\0on_pushButton_configFile_clicked\0"
    "on_pushButton_isonetColor_clicked\0"
    "on_checkBox_isonetEnabled_clicked\0"
    "on_checkBox_timeEnabled_clicked\0"
    "on_pushButton_colorY_clicked\0"
    "on_pushButton_colorZ_clicked\0"
    "on_pushButton_netColor_clicked\0"
    "on_checkBox_netEnabled_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingsWidgetCommon[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SettingsWidgetCommon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SettingsWidgetCommon *_t = static_cast<SettingsWidgetCommon *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_colorX_clicked(); break;
        case 1: _t->on_pushButton_configFile_clicked(); break;
        case 2: _t->on_pushButton_isonetColor_clicked(); break;
        case 3: _t->on_checkBox_isonetEnabled_clicked(); break;
        case 4: _t->on_checkBox_timeEnabled_clicked(); break;
        case 5: _t->on_pushButton_colorY_clicked(); break;
        case 6: _t->on_pushButton_colorZ_clicked(); break;
        case 7: _t->on_pushButton_netColor_clicked(); break;
        case 8: _t->on_checkBox_netEnabled_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SettingsWidgetCommon::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SettingsWidgetCommon.data,
      qt_meta_data_SettingsWidgetCommon,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SettingsWidgetCommon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsWidgetCommon::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsWidgetCommon.stringdata0))
        return static_cast<void*>(const_cast< SettingsWidgetCommon*>(this));
    return QWidget::qt_metacast(_clname);
}

int SettingsWidgetCommon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
