/***************************************************************************
 *   copyright       : (C) 2013 by Quentin BRAMAS                          *
 *   http://texiteasy.com                                                  *
 *                                                                         *
 *   This file is part of texiteasy.                                          *
 *                                                                         *
 *   texiteasy is free software: you can redistribute it and/or modify        *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   texiteasy is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with texiteasy.  If not, see <http://www.gnu.org/licenses/>.       *                         *
 *                                                                         *
 ***************************************************************************/



#include "mainwindow.h"
#include "application.h"
#include "configmanager.h"
#include <QSettings>
#include <QFontDatabase>
#include <QDebug>



int main(int argc, char *argv[])
{
#ifdef OS_MAC
    QCoreApplication::addLibraryPath("/Developer/Applications/Qt/plugins/sqldrivers");
#endif
    Application a(argc, argv);
    ConfigManager::Instance.init();

    QFontDatabase::addApplicationFont(":/data/fonts/consola.ttf");
    QFontDatabase::addApplicationFont(":/data/fonts/consolab.ttf");
    QFontDatabase::addApplicationFont(":/data/fonts/consolai.ttf");
    QFontDatabase::addApplicationFont(":/data/fonts/consolaz.ttf");

    qDebug()<<QString("Start ")+APPLICATION_NAME+QString(" version ")+CURRENT_VERSION;
    MainWindow w;
    a.connect(&a, SIGNAL(requestOpenFile(QString)), &w, SLOT(open(QString)));

    if(argc > 1)
    {
        QString filename = argv[1];
        w.open(filename);
    }

    w.show();
    
    return a.exec();
}
