/****************************************************************************
 *
 * Copyright (c) 2010 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

/* Markus Kuhn -- 2001-01-12 -- public domain */
/* Adaptions for KDE by Waldo Bastian <bastian@kde.org> */
/*
    Rewritten for QT4 by e_k <e_k at users.sourceforge.net>
*/

#ifndef	WCWIDTH_H
#define WCWIDTH_H

#include <QString>

int terminal_wcwidth(quint16 ucs);
#if 0
int terminal_wcwidth_cjk(quint16 ucs);
#endif
int string_width(const QString &txt);

#endif // WCWIDTH_H
