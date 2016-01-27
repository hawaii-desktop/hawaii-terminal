/****************************************************************************
 * This file is part of Terminal.
 *
 * Copyright (C) 2010-2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtWidgets/QApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>

#include "config.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Terminal");
    app.setApplicationVersion(TERMINAL_VERSION);
    app.setOrganizationDomain("hawaiios.org");
    app.setOrganizationName("Hawaii");
#if QT_VERSION >= QT_VERSION_CHECK(5, 7, 0)
    app.setDesktopFileName(QLatin1String("org.hawaiios.terminal.desktop"));
#endif

    QQuickWindow::setDefaultAlphaBuffer(true);

    QQmlApplicationEngine engine(QUrl("qrc:/qml/main.qml"));
    QObject *main = engine.rootObjects().at(0);
    QMetaObject::invokeMethod(main, "newWindow");

    return app.exec();
}
