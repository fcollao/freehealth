/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2013 by Eric MAEKER, MD (France) <eric.maeker@gmail.com>      *
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
 *  Main Developer: Eric MAEKER, MD <eric.maeker@gmail.com>                *
 *  Contributors:                                                          *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 ***************************************************************************/
#ifndef INTERACTOREDITORPAGE_H
#define INTERACTOREDITORPAGE_H

#include <coreplugin/itoolpage.h>

class QModelIndex;

namespace DrugsDB {

class InteractorEditorPage : public Core::IToolPage
{
public:
    InteractorEditorPage(QObject *parent = 0) : IToolPage(parent) { setObjectName("InteractorEditorPage"); }

    virtual QString id() const {return "InteractorEditorPage";}
    virtual QString name() const {return "Interactors Editor";}
    virtual QString category() const;
    virtual QIcon icon() const {return QIcon();}

    // widget will be deleted after the show
    virtual QWidget *createPage(QWidget *parent = 0);
};

namespace Internal {
class InteractorEditorWidgetPrivate;
namespace Ui {
class InteractorEditorWidget;
}

class InteractorEditorWidget : public QWidget
{
    Q_OBJECT
public:
    InteractorEditorWidget(QWidget *parent = 0);
    ~InteractorEditorWidget();

private:
    void setEditorsEnabled(bool state);

private Q_SLOTS:
    void reformatOldSource();
    void save();
    void filterDrugInteractorModel(const QString &text);
    void createActionTriggered();
    void removeCurrent();
    void edit();
    void interactorActivated(const QModelIndex &index);
    void buttonActivated(QAction*);
    void bookmarkClassesFromCurrent();
    void updateCounts();
    void nextUnreviewedOrUnlinked();

private:
    void changeEvent(QEvent *e);

private:
//    bool event(QEvent *e);
//    void showEvent(QShowEvent *e);
//    void hideEvent(QHideEvent *e);

private:
    Internal::InteractorEditorWidgetPrivate *d;
};

}  // End namespace Internal
}  // End namespace DrugsDB

#endif // INTERACTOREDITORPAGE_H
