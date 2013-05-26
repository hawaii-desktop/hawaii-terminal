/****************************************************************************
 * This file is part of Terminal.
 *
 * Copyright (C) 2010-2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlContext>

#include "windowcontroller.h"
#include "terminal_item.h"
#include "yat_pty.h"

WindowController::WindowController(QObject *parent)
    : QObject(parent)
    , m_engine(new QQmlEngine())
{
    connect(m_engine, SIGNAL(quit()),
            QGuiApplication::instance(), SLOT(quit()));
}

QQuickWindow *WindowController::create()
{
    QQmlComponent component(m_engine);
    component.loadUrl(QUrl("qrc:/qml/main.qml"));
    if (!component.isReady()) {
        qWarning("%s", qPrintable(component.errorString()));
        return 0;
    }

    QObject *topLevel = component.create();
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    if (!window) {
        qWarning("Error: Your root item has to be a Window.");
        return 0;
    }

#if 0
    TerminalItem *terminal = topLevel->findChild<TerminalItem *>("terminal");
    terminal->createScreen(m_engine);
    m_engine->rootContext()->setContextProperty("engine", m_engine);
#endif
    connect(topLevel, SIGNAL(viewCreated(QVariant)),
            this, SLOT(viewCreated(QVariant)));

    window->show();
    return window;
}

void WindowController::viewCreated(const QVariant &item)
{
    TerminalItem *terminal = qobject_cast<TerminalItem *>(item.value<QObject *>());
qWarning() << terminal;
    terminal->createScreen(m_engine);
}
