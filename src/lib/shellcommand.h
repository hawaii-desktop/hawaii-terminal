/****************************************************************************
 *
 * Copyright (c) 2010 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (c) 2007 Robert Knight <robertknight@gmail.com>
 * Copyright (c) 2008 e_k <e_k@users.sourceforge.net>
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

#ifndef SHELLCOMMAND_H
#define SHELLCOMMAND_H

#include <QStringList>

namespace Terminal
{
    /**
     * A class to parse and extract information about shell commands.
     *
     * ShellCommand can be used to:
     *
     * <ul>
     *      <li>Take a command-line (eg "/bin/sh -c /path/to/my/script") and split it
     *          into its component parts (eg. the command "/bin/sh" and the arguments
     *          "-c","/path/to/my/script")
     *      </li>
     *      <li>Take a command and a list of arguments and combine them to
     *          form a complete command line.
     *      </li>
     *      <li>Determine whether the binary specified by a command exists in the
     *          user's PATH.
     *      </li>
     *      <li>Determine whether a command-line specifies the execution of
     *          another command as the root user using su/sudo etc.
     *      </li>
     * </ul>
     */
    class ShellCommand
    {
    public:
        /**
         * Constructs a ShellCommand from a command line.
         *
         * @param fullCommand The command line to parse.
         */
        ShellCommand(const QString &fullCommand);
        /**
         * Constructs a ShellCommand with the specified @p command and @p arguments.
         */
        ShellCommand(const QString &command , const QStringList &arguments);

        /** Returns the command. */
        QString command() const;
        /** Returns the arguments. */
        QStringList arguments() const;

        /**
         * Returns the full command line.
         */
        QString fullCommand() const;

        /** Returns true if this is a root command. */
        bool isRootCommand() const;
        /** Returns true if the program specified by @p command() exists. */
        bool isAvailable() const;

        /** Expands environment variables in @p text .*/
        static QString expand(const QString &text);

        /** Expands environment variables in each string in @p list. */
        static QStringList expand(const QStringList &items);

    private:
        QStringList _arguments;
    };
}

#endif // SHELLCOMMAND_H
