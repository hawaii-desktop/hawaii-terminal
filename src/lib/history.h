/****************************************************************************
 *
 * Copyright (c) 2010 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (c) 1997-1998 Lars Doelle <lars.doelle@on-line.de>
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

#ifndef HISTORY_H
#define HISTORY_H

#include <QBitRef>
#include <QHash>
#include <QVector>
#include <QTemporaryFile>

#include "blockarray.h"
#include "character.h"

namespace Terminal
{
    /*
       An extendable tmpfile(1) based buffer.
    */
    class HistoryFile
    {
    public:
        HistoryFile();
        virtual ~HistoryFile();

        virtual void add(const unsigned char *bytes, int len);
        virtual void get(unsigned char *bytes, int len, int loc);
        virtual int  len();

        //mmaps the file in read-only mode
        void map();
        //un-mmaps the file
        void unmap();
        //returns true if the file is mmap'ed
        bool isMapped();


    private:
        int  ion;
        int  length;
        QTemporaryFile tmpFile;

        //pointer to start of mmap'ed file data, or 0 if the file is not mmap'ed
        char *fileMap;

        //incremented whenver 'add' is called and decremented whenever
        //'get' is called.
        //this is used to detect when a large number of lines are being read and processed from the history
        //and automatically mmap the file for better performance (saves the overhead of many lseek-read calls).
        int readWriteBalance;

        //when readWriteBalance goes below this threshold, the file will be mmap'ed automatically
        static const int MAP_THRESHOLD = -1000;
    };

    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // Abstract base class for file and buffer versions
    //////////////////////////////////////////////////////////////////////
    class HistoryType;

    class HistoryScroll
    {
    public:
        HistoryScroll(HistoryType *);
        virtual ~HistoryScroll();

        virtual bool hasScroll();

        // access to history
        virtual int  getLines() = 0;
        virtual int  getLineLen(int lineno) = 0;
        virtual void getCells(int lineno, int colno, int count, Character res[]) = 0;
        virtual bool isWrappedLine(int lineno) = 0;

        // backward compatibility (obsolete)
        Character   getCell(int lineno, int colno) {
            Character res;
            getCells(lineno, colno, 1, &res);
            return res;
        }

        // adding lines.
        virtual void addCells(const Character a[], int count) = 0;
        // convenience method - this is virtual so that subclasses can take advantage
        // of QVector's implicit copying
        virtual void addCellsVector(const QVector<Character>& cells) {
            addCells(cells.data(), cells.size());
        }

        virtual void addLine(bool previousWrapped = false) = 0;

        //
        // FIXME:  Passing around constant references to HistoryType instances
        // is very unsafe, because those references will no longer
        // be valid if the history scroll is deleted.
        //
        const HistoryType &getType() {
            return *m_histType;
        }

    protected:
        HistoryType *m_histType;

    };

    //////////////////////////////////////////////////////////////////////
    // File-based history (e.g. file log, no limitation in length)
    //////////////////////////////////////////////////////////////////////
    class HistoryScrollFile : public HistoryScroll
    {
    public:
        HistoryScrollFile(const QString &logFileName);
        virtual ~HistoryScrollFile();

        virtual int  getLines();
        virtual int  getLineLen(int lineno);
        virtual void getCells(int lineno, int colno, int count, Character res[]);
        virtual bool isWrappedLine(int lineno);

        virtual void addCells(const Character a[], int count);
        virtual void addLine(bool previousWrapped = false);

    private:
        int startOfLine(int lineno);

        QString m_logFileName;
        HistoryFile index; // lines Row(int)
        HistoryFile cells; // text  Row(Character)
        HistoryFile lineflags; // flags Row(unsigned char)
    };

    //////////////////////////////////////////////////////////////////////
    // Buffer-based history (limited to a fixed nb of lines)
    //////////////////////////////////////////////////////////////////////
    class HistoryScrollBuffer : public HistoryScroll
    {
    public:
        typedef QVector<Character> HistoryLine;

        HistoryScrollBuffer(unsigned int maxNbLines = 1000);
        virtual ~HistoryScrollBuffer();

        virtual int  getLines();
        virtual int  getLineLen(int lineno);
        virtual void getCells(int lineno, int colno, int count, Character res[]);
        virtual bool isWrappedLine(int lineno);

        virtual void addCells(const Character a[], int count);
        virtual void addCellsVector(const QVector<Character>& cells);
        virtual void addLine(bool previousWrapped = false);

        void setMaxNbLines(unsigned int nbLines);
        unsigned int maxNbLines() {
            return _maxLineCount;
        }

    private:
        int bufferIndex(int lineNumber);

        HistoryLine *_historyBuffer;
        QBitArray _wrappedLine;
        int _maxLineCount;
        int _usedLines;
        int _head;
    };

    //////////////////////////////////////////////////////////////////////
    // Nothing-based history (no history :-)
    //////////////////////////////////////////////////////////////////////
    class HistoryScrollNone : public HistoryScroll
    {
    public:
        HistoryScrollNone();
        virtual ~HistoryScrollNone();

        virtual bool hasScroll();

        virtual int  getLines();
        virtual int  getLineLen(int lineno);
        virtual void getCells(int lineno, int colno, int count, Character res[]);
        virtual bool isWrappedLine(int lineno);

        virtual void addCells(const Character a[], int count);
        virtual void addLine(bool previousWrapped = false);
    };

    //////////////////////////////////////////////////////////////////////
    // BlockArray-based history
    //////////////////////////////////////////////////////////////////////
    class HistoryScrollBlockArray : public HistoryScroll
    {
    public:
        HistoryScrollBlockArray(size_t size);
        virtual ~HistoryScrollBlockArray();

        virtual int  getLines();
        virtual int  getLineLen(int lineno);
        virtual void getCells(int lineno, int colno, int count, Character res[]);
        virtual bool isWrappedLine(int lineno);

        virtual void addCells(const Character a[], int count);
        virtual void addLine(bool previousWrapped = false);

    protected:
        BlockArray m_blockArray;
        QHash<int, size_t> m_lineLengths;
    };

    //////////////////////////////////////////////////////////////////////
    // History type
    //////////////////////////////////////////////////////////////////////

    class HistoryType
    {
    public:
        HistoryType();
        virtual ~HistoryType();

        /**
         * Returns true if the history is enabled ( can store lines of output )
         * or false otherwise.
         */
        virtual bool isEnabled()           const = 0;
        /**
         * Returns true if the history size is unlimited.
         */
        bool isUnlimited() const {
            return maximumLineCount() == 0;
        }
        /**
         * Returns the maximum number of lines which this history type
         * can store or 0 if the history can store an unlimited number of lines.
         */
        virtual int maximumLineCount()    const = 0;

        virtual HistoryScroll *scroll(HistoryScroll *) const = 0;
    };

    class HistoryTypeNone : public HistoryType
    {
    public:
        HistoryTypeNone();

        virtual bool isEnabled() const;
        virtual int maximumLineCount() const;

        virtual HistoryScroll *scroll(HistoryScroll *) const;
    };

    class HistoryTypeBlockArray : public HistoryType
    {
    public:
        HistoryTypeBlockArray(size_t size);

        virtual bool isEnabled() const;
        virtual int maximumLineCount() const;

        virtual HistoryScroll *scroll(HistoryScroll *) const;

    protected:
        size_t m_size;
    };

    class HistoryTypeFile : public HistoryType
    {
    public:
        HistoryTypeFile(const QString &fileName = QString());

        virtual bool isEnabled() const;
        virtual const QString &getFileName() const;
        virtual int maximumLineCount() const;

        virtual HistoryScroll *scroll(HistoryScroll *) const;

    protected:
        QString m_fileName;
    };


    class HistoryTypeBuffer : public HistoryType
    {
    public:
        HistoryTypeBuffer(unsigned int nbLines);

        virtual bool isEnabled() const;
        virtual int maximumLineCount() const;

        virtual HistoryScroll *scroll(HistoryScroll *) const;

    protected:
        unsigned int m_nbLines;
    };
}

#endif // HISTORY_H
