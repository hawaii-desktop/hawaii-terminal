/****************************************************************************
 * This file is part of Terminal
 *
 * Copyright (c) 2010-2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Terminal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Terminal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Terminal.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <VApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    VApplication app(argc, argv);
    app.setApplicationName("Terminal");
    app.setApplicationVersion("0.0.0");
    app.setOrganizationDomain("maui.org");
    app.setOrganizationName("Maui");
    app.setIdentifier("org.maui.Terminal");
    app.setWindowIcon(QIcon::fromTheme("utilities-terminal"));

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();

    return app.exec();
}
