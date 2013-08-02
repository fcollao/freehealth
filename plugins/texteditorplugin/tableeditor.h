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
 *  Main developer: Eric MAEKER, <eric.maeker@gmail.com>                   *
 *  Contributors:                                                          *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 ***************************************************************************/
#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QWidget>
#include <QTextEdit>

/**
 * \file tableeditor.h
 * \author Eric MAEKER <eric.maeker@gmail.com>
 * \version 0.6.0
 * \date 22 Oct 2011
*/

namespace Editor {

class TableEditor : public QWidget
{
    Q_OBJECT
public:
    TableEditor(QWidget *parent = 0);
    virtual ~TableEditor();

    virtual QTextEdit *textEdit() const = 0;

public Q_SLOTS:
    void addTable();
    void tableProperties();
    void tableAddRow();
    void tableAddCol();
    void tableRemoveRow();
    void tableRemoveCol();
    void tableMergeCells();
    void tableSplitCells();

};

}  // End Editor

#endif // TABLEEDITOR_H
