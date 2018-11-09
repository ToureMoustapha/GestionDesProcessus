/****************************************************************************
** Meta object code from reading C++ file 'Chronogramme.h'
**
** Created: Sun 14. Feb 16:07:14 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GestionDesProcessus/Chronogramme.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Chronogramme.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Chronogramme[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      27,   13,   13,   13, 0x08,
      45,   13,   13,   13, 0x08,
      57,   13,   13,   13, 0x08,
      74,   13,   13,   13, 0x08,
      95,   13,   13,   13, 0x08,
     113,   13,   13,   13, 0x08,
     136,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Chronogramme[] = {
    "Chronogramme\0\0clicOkHaut()\0clicAnnulerHaut()\0"
    "clicOkBas()\0clicAnnulerBas()\0"
    "clicJoindreFichier()\0clicOkBasDroite()\0"
    "clicAnnulerBasDroite()\0"
    "clicAfficherMethodePlusOptimale()\0"
};

const QMetaObject Chronogramme::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Chronogramme,
      qt_meta_data_Chronogramme, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Chronogramme::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Chronogramme::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Chronogramme::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Chronogramme))
        return static_cast<void*>(const_cast< Chronogramme*>(this));
    return QDialog::qt_metacast(_clname);
}

int Chronogramme::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clicOkHaut(); break;
        case 1: clicAnnulerHaut(); break;
        case 2: clicOkBas(); break;
        case 3: clicAnnulerBas(); break;
        case 4: clicJoindreFichier(); break;
        case 5: clicOkBasDroite(); break;
        case 6: clicAnnulerBasDroite(); break;
        case 7: clicAfficherMethodePlusOptimale(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
