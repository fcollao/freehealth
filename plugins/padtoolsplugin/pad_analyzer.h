/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2012 by Eric MAEKER, MD (France) <eric.maeker@gmail.com>      *
 *  All rights reserved.                                                   *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program (COPYING.FREEMEDFORMS file).                   *
 *  If not, see <http://www.gnu.org/licenses/>.                            *
 ***************************************************************************/
/***************************************************************************
 *  Main Developers : Eric Maeker <eric.maeker@gmail.com>,                *
 *                    Guillaume Denry <guillaume.denry@gmail.com>          *
 *  Contributors :                                                         *
 *      NAME <MAIL@ADRESS>                                                 *
 ***************************************************************************/
#ifndef PAD_ANALYZER_H
#define PAD_ANALYZER_H

#include <QString>
#include <QStack>

#include <coreplugin/ipadtools.h>

#include "pad_fragment.h"
#include "pad_core.h"
#include "pad_string.h"
#include "pad.h"
#include "pad_item.h"

class PadAnalyzer
{
public:
	static const char coreDelimiter = '~';
	static const char padOpenDelimiter = '[';
	static const char padCloseDelimiter = ']';

	PadAnalyzer();

	/**
	 * Analyzes a mask text
	 */
	Pad *analyze(const QString &text);

	const QList<Core::PadAnalyzerError> lastErrors() const { return _lastErrors; }

private:
	enum LexemType {
		Lexem_Null = 0,
		Lexem_String,
		Lexem_PadOpenDelimiter,
		Lexem_PadCloseDelimiter,
		Lexem_CoreDelimiter
	};

	struct Lexem {
		LexemType type;		// type of the lexem
		QString value;		// value (can be empty) of the lexem
		QString rawValue;	// raw value of the lexem (never empty)
		int start;			// start index in the analyzed text
		int end;			// end index in the analyzed text
	};

	Lexem _lexemNull;

	const QString *_text;
	int _length;
	int _curPos; // contains the current position in the analyzed text
	QList<Core::PadAnalyzerError> _lastErrors;

	bool atEnd(); // returns true if current position is at the text end
	PadItem *nextPadItem();
	PadCore *nextCore(); // tries to parse a core ("~...~")

	int getLine(int curPos = -1) const;
	int getPos(int curPos = -1) const;

	static bool isSpecial(const QChar &c);

	// returns the next lexem in the stream
	Lexem nextLexem();
};

#endif
