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

#ifndef TERMWIDGET_H
#define TERMWIDGET_H

#include <QTextCodec>
#include <QApplication>
#include <QWidget>

struct TermWidgetImpl;

enum COLOR_SCHEME {     COLOR_SCHEME_WHITE_ON_BLACK	= 1,
                        COLOR_SCHEME_GREEN_ON_BLACK,
                        COLOR_SCHEME_BLACK_ON_LIGHT_YELLOW
                  };

namespace Terminal
{
    class TerminalDisplay;
    class Session;

    class TermWidget : public QWidget
    {
        Q_OBJECT
    public:
        enum ScrollBarPosition {
            /** Do not show the scroll bar. */
            NoScrollBar = 0,
            /** Show the scroll bar on the left side of the display. */
            ScrollBarLeft = 1,
            /** Show the scroll bar on the right side of the display. */
            ScrollBarRight = 2
        };

        TermWidget(int startnow = 1, QWidget *parent = 0);
        ~TermWidget();

        //start shell program if it was not started in constructor
        void startShellProgram();

        //look-n-feel, if you don`t like defaults

        //	Terminal font
        // Default is application font with family Monospace, size 10
        void setTerminalFont(QFont &font);

        //	Shell program, default is /bin/bash
        void setShellProgram(QString &progname);

        // Shell program args, default is none
        void setArgs(QStringList &args);

        //Text codec, default is UTF-8
        void setTextCodec(QTextCodec *codec);

        //Color scheme, default is white on black
        void setColorScheme(int scheme);

        //set size
        void setSize(int h, int v);

        // History size for scrolling
        void setHistorySize(int lines);  //infinite if lines < 0

        // Presence of scrollbar
        void setScrollBarPosition(ScrollBarPosition);

        // Send some text to terminal
        void sendText(QString &text);

        /** Copies the selected text to the clipboard. */
        void copyClipboard();

        /**
         * Pastes the content of the clipboard into the
         * display.
         */
        void pasteClipboard();

        /**
         * Pastes the content of the selection into the
         * display.
         */
        void pasteSelection();

    signals:
        void finished();

    protected:
        virtual void resizeEvent(QResizeEvent *);

    protected slots:
        void sessionFinished();

    private:
        void init();
        TermWidgetImpl *m_impl;
    };
}

#endif // TERMWIDGET_H
