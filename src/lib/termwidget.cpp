/****************************************************************************
 *
 * Copyright (c) 2010 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (c) 2008 e_k <e_k at users.sourceforge.net>
 *
 * All rights reserved.
 * Contact: Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * GNU General Public License Usage
 * This file may be used under the terms of the GNU General Public
 * License version 2 as published by the Free Software Foundation
 * and appearing in the file LICENSE.GPL included in the packaging
 * of this file.  Please review the following information to
 * ensure the GNU General Public License version 2 requirements
 * will be met: http://www.gnu.org/licenses/old-licenses/gpl-2.0.html.
 *
 ***************************************************************************/

#include "termwidget.h"
#include "session.h"
#include "terminaldisplay.h"

using namespace Terminal;

struct TermWidgetImpl {
    TermWidgetImpl(QWidget *parent = 0);

    TerminalDisplay *m_terminalDisplay;
    Session *m_session;

    Session *createSession();
    TerminalDisplay *createTerminalDisplay(Session *session, QWidget *parent);
};

TermWidgetImpl::TermWidgetImpl(QWidget *parent)
{
    this->m_session = createSession();
    this->m_terminalDisplay = createTerminalDisplay(this->m_session, parent);
}

Session *TermWidgetImpl::createSession()
{
    Session *session = new Session();
    session->setTitle(Session::NameRole, "TermWidget");
    session->setProgram("/bin/bash");
    QStringList args("");
    session->setArguments(args);
    session->setAutoClose(true);
    session->setCodec(QTextCodec::codecForName("UTF-8"));
    session->setFlowControlEnabled(true);
    session->setHistoryType(HistoryTypeBuffer(1000));
    session->setDarkBackground(true);
    session->setKeyBindings("");
    return session;
}

TerminalDisplay *TermWidgetImpl::createTerminalDisplay(Session *session, QWidget *parent)
{
    //    TerminalDisplay* display = new TerminalDisplay(this);
    TerminalDisplay *display = new TerminalDisplay(parent);
    display->setBellMode(TerminalDisplay::NotifyBell);
    display->setTerminalSizeHint(true);
    display->setTripleClickMode(TerminalDisplay::SelectWholeLine);
    display->setTerminalSizeStartup(true);
    display->setRandomSeed(session->sessionId() * 31);
    return display;
}


TermWidget::TermWidget(int startnow, QWidget *parent)
    : QWidget(parent)
{
    m_impl = new TermWidgetImpl(this);
    init();
    if (startnow && m_impl->m_session) {
        m_impl->m_session->run();
    }
    this->setFocus(Qt::OtherFocusReason);
    m_impl->m_terminalDisplay->resize(this->size());
    this->setFocusProxy(m_impl->m_terminalDisplay);
}

void TermWidget::startShellProgram()
{
    if (m_impl->m_session->isRunning())
        return;
    m_impl->m_session->run();
}

void TermWidget::init()
{
    m_impl->m_terminalDisplay->setSize(80, 40);
    QFont font = QApplication::font();
    font.setFamily("Monospace");
    font.setPointSize(10);
    font.setStyleHint(QFont::TypeWriter);
    setTerminalFont(font);
    setScrollBarPosition(NoScrollBar);
    m_impl->m_session->addView(m_impl->m_terminalDisplay);
    connect(m_impl->m_session, SIGNAL(finished()), this, SLOT(sessionFinished()));
}

TermWidget::~TermWidget()
{
    emit destroyed();
}

void TermWidget::setTerminalFont(QFont &font)
{
    if (!m_impl->m_terminalDisplay)
        return;
    m_impl->m_terminalDisplay->setVTFont(font);
}

void TermWidget::setShellProgram(QString &progname)
{
    if (!m_impl->m_session)
        return;
    m_impl->m_session->setProgram(progname);
}

void TermWidget::setArgs(QStringList &args)
{
    if (!m_impl->m_session)
        return;
    m_impl->m_session->setArguments(args);
}

void TermWidget::setTextCodec(QTextCodec *codec)
{
    if (!m_impl->m_session)
        return;
    m_impl->m_session->setCodec(codec);
}

void TermWidget::setColorScheme(int scheme)
{
    switch (scheme) {
        case COLOR_SCHEME_WHITE_ON_BLACK:
            m_impl->m_terminalDisplay->setColorTable(whiteonblack_color_table);
            break;
        case COLOR_SCHEME_GREEN_ON_BLACK:
            m_impl->m_terminalDisplay->setColorTable(greenonblack_color_table);
            break;
        case COLOR_SCHEME_BLACK_ON_LIGHT_YELLOW:
            m_impl->m_terminalDisplay->setColorTable(blackonlightyellow_color_table);
            break;
        default:
            break;
    };
}

void TermWidget::setSize(int h, int v)
{
    if (!m_impl->m_terminalDisplay)
        return;
    m_impl->m_terminalDisplay->setSize(h, v);
}

void TermWidget::setHistorySize(int lines)
{
    if (lines < 0)
        m_impl->m_session->setHistoryType(HistoryTypeFile());
    else
        m_impl->m_session->setHistoryType(HistoryTypeBuffer(lines));
}

void TermWidget::setScrollBarPosition(ScrollBarPosition pos)
{
    if (!m_impl->m_terminalDisplay)
        return;
    m_impl->m_terminalDisplay->setScrollBarPosition((TerminalDisplay::ScrollBarPosition) pos);
}

void TermWidget::sendText(QString &text)
{
    m_impl->m_session->sendText(text);
}

void TermWidget::resizeEvent(QResizeEvent *)
{
    //qDebug("global window resizing...with %d %d", this->size().width(), this->size().height());
    m_impl->m_terminalDisplay->resize(this->size());
}

void TermWidget::sessionFinished()
{
    emit finished();
}

void TermWidget::copyClipboard()
{
    m_impl->m_terminalDisplay->copyClipboard();
}

void TermWidget::pasteClipboard()
{
    m_impl->m_terminalDisplay->pasteClipboard();
}

void TermWidget::pasteSelection()
{
    m_impl->m_terminalDisplay->pasteSelection();
}

#include "moc_termwidget.cpp"
