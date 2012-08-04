/****************************************************************************
 *
 * Copyright (c) 2010 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (c) 2007 Robert Knight <robertknight@gmail.com>
 * Copyright (c) 2008 e_k <e_k at users.sourceforge.net>
 * Copyright (c) 2000 Stephan Kulow <coolo@kde.org>
 * Copyright (c) 1997-1998 Lars Doelle <lars.doelle@on-line.de>
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

#ifndef CHARACTER_H
#define CHARACTER_H

#include <QHash>

#include "charactercolor.h"

namespace Terminal
{
    typedef unsigned char LineProperty;

    static const int LINE_DEFAULT		= 0;
    static const int LINE_WRAPPED 	 	= (1 << 0);
    static const int LINE_DOUBLEWIDTH  	= (1 << 1);
    static const int LINE_DOUBLEHEIGHT	= (1 << 2);

#define DEFAULT_RENDITION  0
#define RE_BOLD            (1 << 0)
#define RE_BLINK           (1 << 1)
#define RE_UNDERLINE       (1 << 2)
#define RE_REVERSE         (1 << 3) // Screen only
#define RE_INTENSIVE       (1 << 3) // Widget only
#define RE_CURSOR          (1 << 4)
#define RE_EXTENDED_CHAR   (1 << 5)

    /**
     * A single character in the terminal which consists of a unicode character
     * value, foreground and background colors and a set of rendition attributes
     * which specify how it should be drawn.
     */
    class Character
    {
    public:
        /**
         * Constructs a new character.
         *
         * @param _c The unicode character value of this character.
         * @param _f The foreground color used to draw the character.
         * @param _b The color used to draw the character's background.
         * @param _r A set of rendition flags which specify how this character is to be drawn.
         */
        inline Character(quint16 _c = ' ',
                         CharacterColor  _f = CharacterColor(COLOR_SPACE_DEFAULT, DEFAULT_FORE_COLOR),
                         CharacterColor  _b = CharacterColor(COLOR_SPACE_DEFAULT, DEFAULT_BACK_COLOR),
                         quint8  _r = DEFAULT_RENDITION)
            : character(_c), rendition(_r), foregroundColor(_f), backgroundColor(_b) {}

        union {
            /** The unicode character value for this character. */
            quint16 character;
            /**
             * Experimental addition which allows a single Character instance to contain more than
             * one unicode character.
             *
             * charSequence is a hash code which can be used to look up the unicode
             * character sequence in the ExtendedCharTable used to create the sequence.
             */
            quint16 charSequence;
        };

        /** A combination of RENDITION flags which specify options for drawing the character. */
        quint8  rendition;

        /** The foreground color used to draw this character. */
        CharacterColor  foregroundColor;
        /** The color used to draw this character's background. */
        CharacterColor  backgroundColor;

        /**
         * Returns true if this character has a transparent background when
         * it is drawn with the specified @p palette.
         */
        bool   isTransparent(const ColorEntry *palette) const;
        /**
         * Returns true if this character should always be drawn in bold when
         * it is drawn with the specified @p palette, independent of whether
         * or not the character has the RE_BOLD rendition flag.
         */
        bool   isBold(const ColorEntry *base) const;

        /**
         * Compares two characters and returns true if they have the same unicode character value,
         * rendition and colors.
         */
        friend bool operator == (const Character &a, const Character &b);
        /**
         * Compares two characters and returns true if they have different unicode character values,
         * renditions or colors.
         */
        friend bool operator != (const Character &a, const Character &b);
    };

    inline bool operator == (const Character &a, const Character &b)
    {
        return a.character == b.character &&
               a.rendition == b.rendition &&
               a.foregroundColor == b.foregroundColor &&
               a.backgroundColor == b.backgroundColor;
    }

    inline bool operator != (const Character &a, const Character &b)
    {
        return    a.character != b.character ||
                  a.rendition != b.rendition ||
                  a.foregroundColor != b.foregroundColor ||
                  a.backgroundColor != b.backgroundColor;
    }

    inline bool Character::isTransparent(const ColorEntry *base) const
    {
        return ((backgroundColor._colorSpace == COLOR_SPACE_DEFAULT) &&
                base[backgroundColor._u + 0 + (backgroundColor._v ? BASE_COLORS : 0)].transparent)
               || ((backgroundColor._colorSpace == COLOR_SPACE_SYSTEM) &&
                   base[backgroundColor._u + 2 + (backgroundColor._v ? BASE_COLORS : 0)].transparent);
    }

    inline bool Character::isBold(const ColorEntry *base) const
    {
        return ((backgroundColor._colorSpace == COLOR_SPACE_DEFAULT) &&
                base[backgroundColor._u + 0 + (backgroundColor._v ? BASE_COLORS : 0)].bold)
               || ((backgroundColor._colorSpace == COLOR_SPACE_SYSTEM) &&
                   base[backgroundColor._u + 2 + (backgroundColor._v ? BASE_COLORS : 0)].bold);
    }

    extern unsigned short vt100_graphics[32];


    /**
     * A table which stores sequences of unicode characters, referenced
     * by hash keys.  The hash key itself is the same size as a unicode
     * character ( ushort ) so that it can occupy the same space in
     * a structure.
     */
    class ExtendedCharTable
    {
    public:
        /** Constructs a new character table. */
        ExtendedCharTable();
        ~ExtendedCharTable();

        /**
         * Adds a sequences of unicode characters to the table and returns
         * a hash code which can be used later to look up the sequence
         * using lookupExtendedChar()
         *
         * If the same sequence already exists in the table, the hash
         * of the existing sequence will be returned.
         *
         * @param unicodePoints An array of unicode character points
         * @param length Length of @p unicodePoints
         */
        ushort createExtendedChar(ushort *unicodePoints , ushort length);
        /**
         * Looks up and returns a pointer to a sequence of unicode characters
         * which was added to the table using createExtendedChar().
         *
         * @param hash The hash key returned by createExtendedChar()
         * @param length This variable is set to the length of the
         * character sequence.
         *
         * @return A unicode character sequence of size @p length.
         */
        ushort *lookupExtendedChar(ushort hash , ushort &length) const;

        /** The global ExtendedCharTable instance. */
        static ExtendedCharTable instance;
    private:
        // calculates the hash key of a sequence of unicode points of size 'length'
        ushort extendedCharHash(ushort *unicodePoints , ushort length) const;
        // tests whether the entry in the table specified by 'hash' matches the
        // character sequence 'unicodePoints' of size 'length'
        bool extendedCharMatch(ushort hash , ushort *unicodePoints , ushort length) const;
        // internal, maps hash keys to character sequence buffers.  The first ushort
        // in each value is the length of the buffer, followed by the ushorts in the buffer
        // themselves.
        QHash<ushort, ushort *> extendedCharTable;
    };

}

#endif // CHARACTER_H

