/****************************************************************************
 *
 * Copyright (c) 2010 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (c) 2008 e_k <e_k@users.sourceforge.net>
 * Copyright (c) 2003-2007 Oswald Buddenhagen <ossi@kde.org>
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

#ifndef KPTYP_H
#define KPTYP_H

#include <QByteArray>

#include "kpty.h"

struct KPtyPrivate {
    Q_DECLARE_PUBLIC(KPty)

    KPtyPrivate();
    bool chownpty(bool grant);

    int masterFd;
    int slaveFd;

    QByteArray ttyName;

    KPty *q_ptr;
};

#endif // KPTYP_H
