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
 *  Main Developer: Eric MAEKER, <eric.maeker@gmail.com>                   *
 *  Contributors:                                                          *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 ***************************************************************************/
#ifndef ALERT_PLUGIN_H
#define ALERT_PLUGIN_H

#include <extensionsystem/iplugin.h>

#include <QtCore/QObject>

/**
 * \file alertplugin.h
 * \author Eric Maeker
 * \version 0.8.0
 * \date 25 July 2012
*/

namespace Alert {
namespace Internal {
class AlertPreferencesPage;
class PatientBarAlertPlaceHolder;

class AlertPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.freemedforms.FreeMedForms.AlertPlugin" FILE "Alert.json")

public:
    AlertPlugin();
    ~AlertPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private Q_SLOTS:
    void postCoreInitialization();
    void coreAboutToClose();

#ifdef WITH_TESTS
private Q_SLOTS:

#endif

private:
    AlertPreferencesPage *_prefPage;
    PatientBarAlertPlaceHolder *_patientPlaceHolder;
};

}  // End namespace Internal
}  // End namespace Alert

#endif  // End ALERT_PLUGIN_H
