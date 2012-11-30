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
 *   Main Developper : Eric MAEKER, <eric.maeker@gmail.com>                *
 *   Contributors :                                                        *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 ***************************************************************************/
#ifndef FREETOOLBOX_FULLRELEASEPAGE_H
#define FREETOOLBOX_FULLRELEASEPAGE_H

#include <coreplugin/itoolpage.h>

#include <QLabel>
#include <QHash>
#include <QFutureWatcher>
QT_BEGIN_NAMESPACE
class QProgressDialog;
class QSpacerItem;
QT_END_NAMESPACE

/**
 * \file fullreleasepage.h
 * \author Eric MAEKER <eric.maeker@gmail.com>
 * \version 0.8.0
 * \date 30 Nov 2012
*/

namespace Core {
class IFullReleaseStep;

namespace Ui {
class FullReleasePage;
}

class FullReleasePageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FullReleasePageWidget(QWidget *parent);
    ~FullReleasePageWidget();

public Q_SLOTS:
    void createFullRelease();

private Q_SLOTS:
    void setProgressRange(qint64 min, qint64 max);
    void startNextDownload();
    void startNextProcess();
    void startNextPostProcessDownload();

private:
    void addDownloadingProcess(const QString &message, const QString &id);
    void endDownloadingProcess(const QString &id);

    void addRunningProcess(const QString &message);
    void endLastAddedProcess();

private:
    QHash<QString, QLabel *> m_IconLabels;
    Core::IFullReleaseStep *m_ActiveStep;
    QFutureWatcher<void> *m_Watcher;
    QProgressDialog *m_FullReleaseProgress;
    QList<Core::IFullReleaseStep*> m_Steps;
};

class FullReleasePage : public Core::IToolPage
{
public:
    FullReleasePage(QObject *parent = 0);
    ~FullReleasePage();

    QString id() const {return "FullReleasePage";}
    QString name() const;
    QString category() const;
    QIcon icon() const;

    // widget will be deleted after the show
    QWidget *createPage(QWidget *parent = 0);

    void addDownloadingProcess(const QString &message, const QString &id);
    void endDownloadingProcess(const QString &id);

    void addRunningProcess(const QString &message);
    void endLastAddedProcess();

private:
    QWidget *m_Widget, *m_CentralWidget;
    Ui::FullReleasePage *ui;
    QSpacerItem *m_Spacer;
};

}  // namespace Core

#endif // FREETOOLBOX_FULLRELEASEPAGE_H
