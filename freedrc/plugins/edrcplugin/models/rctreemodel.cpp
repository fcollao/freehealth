/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2012 by Eric MAEKER, MD (France) <eric.maeker@gmail.com>      *
 *  All rights reserved.                                                   *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program (COPYING.FREEMEDFORMS file).                   *
 *  If not, see <http://www.gnu.org/licenses/>.                            *
 ***************************************************************************/
/***************************************************************************
 *   Main developers: Eric MAEKER, <eric.maeker@gmail.com>                 *
 *   Contributors:                                                         *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 ***************************************************************************/
/*!
 * \class eDRC::RcTreeModel
 * \brief short description of class
 *
 * Long description of class
 * \sa eDRC::
 */

#include "rctreemodel.h"
#include <edrcplugin/edrccore.h>
#include <edrcplugin/database/edrcbase.h>

//#include <translationutils/constants.h>

#include <QDebug>

using namespace eDRC;
using namespace Internal;

static inline eDRC::EdrcCore &edrcCore() {return eDRC::EdrcCore::instance();}
static inline eDRC::Internal::DrcDatabase &edrcBase() {return eDRC::EdrcCore::instance().edrcBase();}

namespace eDRC {
namespace Internal {
class RcTreeModelPrivate
{
public:
    RcTreeModelPrivate(RcTreeModel *parent) :
        q(parent)
    {
    }
    
    ~RcTreeModelPrivate()
    {
    }

    void populateClasses()
    {
        // Get classes
        QHash<int, QString> classes = edrcBase().getRcClasses();
        QFont bold;
        bold.setBold(true);

        // Append classes
        QHashIterator<int, QString> i(classes);
        while (i.hasNext()) {
            i.next();
            QStandardItem *key = new QStandardItem(QString::number(i.key()));
            QStandardItem *value = new QStandardItem(i.value());
            value->setFont(bold);
            value->setToolTip(i.value());
            q->invisibleRootItem()->appendRow(QList<QStandardItem*>()
                                              << value
                                              << key);

            // Add RC children
            QHash<int, QString> rc = edrcBase().getRcForClasses(i.key());
            QHashIterator<int, QString> irc(rc);
            while (irc.hasNext()) {
                irc.next();
                QStandardItem *rckey = new QStandardItem(QString::number(irc.key()));
                QStandardItem *rcvalue = new QStandardItem(irc.value());
                rcvalue->setToolTip(irc.value());
                value->appendRow(QList<QStandardItem*>()
                                 << rcvalue
                                 << rckey);
                // May be we can add here the SeeAlso related RC
                QHash<int, QString> sa = edrcBase().getSeeAlsoRcForRc(irc.key());
                QHashIterator<int, QString> isa(sa);
                while (isa.hasNext()) {
                    isa.next();
                    QStandardItem *sakey = new QStandardItem(QString::number(isa.key()));
                    QStandardItem *savalue = new QStandardItem(QString("%1 : %2").arg("Voir aussi").arg(isa.value()));
                    savalue->setToolTip(isa.value());
                    rcvalue->appendRow(QList<QStandardItem*>()
                                     << savalue
                                     << sakey);
                }
                rcvalue->sortChildren(0, Qt::AscendingOrder);
            }
            value->sortChildren(0, Qt::AscendingOrder);
        }
        q->invisibleRootItem()->sortChildren(0, Qt::AscendingOrder);
    }

    
public:
    QList<QStandardItem*> _classes;
    
private:
    RcTreeModel *q;
};
} // namespace Internal
} // end namespace eDRC


/*! Constructor of the eDRC::RcTreeModel class */
RcTreeModel::RcTreeModel(QObject *parent) :
    QStandardItemModel(parent),
    d(new RcTreeModelPrivate(this))
{
    d->populateClasses();
}

/*! Destructor of the eDRC::RcTreeModel class */
RcTreeModel::~RcTreeModel()
{
    if (d)
        delete d;
    d = 0;
}

/*! Initializes the object with the default values. Return true if initialization was completed. */
bool RcTreeModel::initialize()
{
    return true;
}

int RcTreeModel::id(const QModelIndex &index) const
{
    QModelIndex rcIdIndex = this->index(index.row(), Id, index.parent());
    return data(rcIdIndex).toInt();
}

QString RcTreeModel::arguments(const QModelIndex &index) const
{
    return edrcBase().getRcArguments(id(index));
}

QStringList RcTreeModel::authorizedDiagnosis(const QModelIndex &index) const
{
    return edrcBase().getRcAuthprizedDiagnosis(id(index));
}