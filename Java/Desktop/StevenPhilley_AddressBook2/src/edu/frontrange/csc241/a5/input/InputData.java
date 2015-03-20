/*-	This software is the work of Paladin Software International, Incorporated,
 * 	and all rights and intellectual property remain the property of that
 *	Company.
 *
 *	Rights to view or use this software as source code, or for execution, are
 *	only granted via one or more licences at the discretion of Paladin Software
 *	International, Incorporated. In any event, the grant to the "Licensee" shall
 *	be for a non-exclusive, non-transferable license to view or use this
 *	software version (hereafter, "the Software") according to the terms of the
 *	licence and contract executed between the Licensee and Paladin Software
 *	International, Incorporated. Licensee agrees that the copyright notice and
 *	this statement will appear on all copies of the Software, packaging, and
 *	documentation or portions thereof made under the terms of the license and
 *	contract.
 *
 *	Please refer to the your license and contract for further important
 *	copyright and licensing information. If you are reading this, and you do not
 *	have a signed, current license or confidentiality agreement executed with
 *	Paladin Software International, Incorporated, it is because someone has
 *	violated the terms of an agreement, an act to which you may be held to be a
 *	party.
 *
 *	Paladin Software International, Incorporated makes no representations or
 *	warranties about the suitability of the Software, either express or implied,
 *	including but not limited to the implied warranties of merchantability,
 *	fitness for particular purposes, or non-infringement, other than those
 *	contained in the Licensee's license and contract documents. Paladin Software
 *	International, Incorporated, shall not be liable for any damages suffered by
 *	the Licensee as a result of using, modifying or distributing this software
 *	or its derivatives.
 */

package edu.frontrange.csc241.a5.input;

import java.io.BufferedReader;
import java.io.EOFException;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.nio.charset.Charset;
import java.nio.charset.IllegalCharsetNameException;
import java.nio.charset.UnsupportedCharsetException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

/**
 * Class to input lines of values from a given file or resource.
 * <p>
 * Given the name of the file or resource from which to input lines of values,
 * the values on the lines are found delimited by a given regular expressions,
 * and returned in an array of String values. </p>
 * <p>
 * An iterator is defined to iterate over the lines. Each line of the file is
 * returned in the form of an array of Strings. Example of such a file is a
 * "csv" (comma-separated-value) file. End-on-line is always treated as an
 * acceptable delimiter. </p>
 * <p>
 * The content of the files is as defined for Java sources files, allowing
 * Unicode escapes. Further, if enabled, a character escaped with reverse slash
 * is returned "as-is" (and cannot be recognized as being part of a delimiting
 * sequence), and if a line separator is immediately preceded by a reverse
 * slash, then that line separator is ignored (including any following white
 * space). This processing is enabled by default.</p>
 * <p>
 * Blank lines are ignored, as are, if enabled, comments introduced by the
 * defined characters terminated by an line separator (or end-of-file). By
 * default, this is enabled, and the comment character is "#". (Use null to
 * disable comment processing). </p>
 * <p>
 * End-of-line may be any of the Unicode characters carriage return, line feed,
 * carriage return followed by line feed, vertical tab, form feed, next line
 * (0x85), line separator (0x2028), or paragraph separator (0x2029). </p>
 * <p>
 * &copy; 2013 Paladin Software International, Incorporated.
 *
 * @author	Dr. Bruce K. Haddon, Paladin Software International Incorporated
 * @version	1.0.1, 2014-01-13
 * @since 1.7
 */
public final class InputData implements Iterable<String[]>, AutoCloseable
{
/**
 * Unicode character null.
 */
private static final char U_NULL = '\u0000';

/**
 * Unicode character line feed, also known as "new line". (Hex 000A.)
 */
private static final char U_LINE_FEED = '\n';

/**
 * Unicode character vertical tab. (Hex 000B.)
 */
private static final char U_VERTICAL_TAB = '\u000B';

/**
 * Unicode character form feed. (Hex 000C.)
 */
private static final char U_FORM_FEED = '\f';

/**
 * Unicode character return. (Hex 000D.)
 */
private static final char U_CARRIAGE_RETURN = '\r';

/**
 * Unicode character space. (Hex 0020.)
 */
private static final char U_SPACE = ' ';

/**
 * Unicode character backslash, used as the escape character. (Hex 005C.)
 */
private static final char ESCAPE = '\\';

/**
 * Unicode character Unicode marker, the letter 'u'. (Hex 0075.)
 */
private static final char MARKER = 'u';

/**
 * Unicode character next line. (Hex 0085.)
 */
private static final char U_NEXT_LINE = '\u0085';

/**
 * Unicode character line separator.
 */
private static final char U_LINE_SEPARATOR = '\u2028';

/**
 * Unicode character paragraph separator.
 */
private static final char U_PARAGRAPH_SEPARATOR = '\u2029';

/**
 * The initial capacity for the StringBuilder holding a line.
 */
private static final int INITIAL_CAPACITY_LINE_LENGTH = 80;

/**
 * The initial capacity for the ArrayList holding values from a line.
 */
private static final int INITIAL_CAPACITY_VALUES = 5;

/**
 * The Reader for the input stream using the file/resource with the given name.
 */
private final Reader input;

/**
 * The number of values expected per line (or zero, if no check is to be made)
 */
private final int limit;

/**
 * A array of delimiters for each of the values expected on the line.
 */
private String[] regex;

/**
 * Count of the lines input, for error reporting purposes.
 */
private int count;

/**
 * The values accumulated from the line.
 */
private final ArrayList<String> values;

/**
 * OK is set to false if the current line contains an error
 */
private boolean OK;

/**
 * Singleton iterator for this instance of this class.
 */
private Iterator<String[]> inputIterator;

/**
 * Map a character that has been escaped with the character being used to
 * represent that character while the line is being constructed.
 */
private final Map<Character, Character> forwardescapes = new HashMap<>(0);

/**
 * Map the characters that are being used to represent escaped characters back
 * to that character (which is put back without the escape).
 */
private final Map<Character, Character> reversescapes = new HashMap<>(0);

/**
 * The next character to be used to represent an escaped character.
 */
private char escapesource = 0xEFFF;			// middle of private use area

/**
 * The flag that enables the processing of escapes.
 */
private boolean escapesEnabled = true;

/**
 * The character currently being processed (or waiting to be processed next).
 */
private int ichar;

/**
 * A copy of the input line for error reporting purposes.
 */
private String copy = "";					// Guaranteed not null.

/**
 * The StringBuilder for the accumulation of the initial input line.
 */
private StringBuilder aline = new StringBuilder(INITIAL_CAPACITY_LINE_LENGTH);

/**
 * The sequence of characters to introduce comments. Enabled if not not null.
 */
private String commentSequence = "#";

/**
 * This instance has been closed.
 */
private boolean closed;

/**
 * Constructor. Initializes an instance for input from the given file or
 * resource.
 *
 * @param name		   the name of a file or resource from which to read
 * @param location	a class name if the name is of a resource, otherwise null. If
 *                 the name is of a resource, then the name should follow the
 *                 rules of getResourceAsStream of class Class. Otherwise, the
 *                 name should follow the rules of the class File
 * @param encoding	the name of the expected encoding of the resource or file. If
 *                 null, then "ISO-8859-1" (Latin-1) is assumed
 * @param limit		  number of expected values per line of input (or zero if this
 *                 is not to be checked)
 * @param regex		  array of regular expressions defining the expected delimiters
 *                 (in order) within the line (spaces around values will be
 *                 ignored and removed). If the list is used completely,
 *                 matching starts over again with the first delimiter
 * @throws NullPointerException        if the given name of file or resource is
 *                                     null
 * @throws IllegalCharsetNameException if the given encoding name is illegal
 * @throws UnsupportedCharsetException if no support for the named encoding is
 *                                     available in this instance of the Java
 *                                     virtual machine
 * @throws IllegalArgumentException    if the file or resource with given name
 *                                     cannot be found
 */
public InputData(String name, Class<?> location, String encoding,
		int limit, String... regex) throws NullPointerException,
		IllegalCharsetNameException, UnsupportedCharsetException,
		IllegalArgumentException
{
	/* Is there an encoding? */
	if( encoding == null ) encoding = "ISO-8859-1";
	Charset charset = Charset.forName(encoding);

	InputStream in;
	if( location == null )
		try
		{
			in = new FileInputStream(name);
		} catch( FileNotFoundException ex )
		{
			throw new IllegalArgumentException("Cannot find file " + name, ex);
		}
	else 
		/* Find the file in the same folder as this class. */ 
		if( (in = location.
			getResourceAsStream(name)) == null )
		throw new IllegalArgumentException(
				"Cannot find resource " + name + " in location " +
				location.getName());

	/* Set up for reading from the file/resource. */
	input = new BufferedReader(new InputStreamReader(in, charset));
	this.limit = limit;
	this.regex = regex;
	this.ichar = U_NULL;
	this.closed = false;

	/* If regex is null, match a whole line. */
	if( this.regex == null ) this.regex = new String[] { "$" };
	values = new ArrayList<>(limit == 0 ? INITIAL_CAPACITY_VALUES : limit);
}

/**
 * Enable the processing of escape characters in the input. Any character
 * following the reverse slash escape character is transmitted without change
 * (and will not be recognized as a matching character for any regular
 * expression that may be being used to identify delimiters. Note that Unicode
 * escape processing is not turned off by this control&mdash;Unicode escapes are
 * always processed.
 *
 * @param escapesEnabled	the escape state to set (true to enable)
 * @return	the previous state
 */
public boolean enableEscapes(boolean escapesEnabled)
{
	boolean temp = this.escapesEnabled;
	this.escapesEnabled = escapesEnabled;
	return temp;
}

/**
 * Enable the processing of comments in the input. Comments may be introduced by
 * a designated sequence of characters, and that sequence, including all
 * characters to the following end of line, are ignored.
 *
 * @param commentSequence	the comment sequence to be set
 * @return					the previous commentSequence
 */
public String enableComments(String commentSequence)
{
	String previous = this.commentSequence;
	this.commentSequence = commentSequence;
	if( commentSequence.isEmpty() ) this.commentSequence = null;
	return previous;
}

/**
 * Return an iterator for the InputData class. This iterator provides two
 * methods: one to test whether there is another line available, and another
 * that returns each line of the input in the form of an array of Strings, where
 * each String represents a delimited and trimmed substring from each line from
 * the file.
 *
 * @return	the iterator that sequences through the lines of the file
 */
@Override
public synchronized Iterator<String[]> iterator()
{
	return inputIterator == null ?
			(inputIterator = new InputIterator<>()) : inputIterator;
}

/**
 * The class implementing the iterator over the lines, where for each line of
 * the input is returned in the form of an array of Strings, where each String
 * represents a delimited substring of each line from the file.
 *
 * @param <T>	the type of the iterator (here String[])
 */
private class InputIterator<T> implements Iterator<String[]>
{
/**
 * Check that there is another line of input.
 *
 * @return	true if there is another line of input
 */
@Override
@SuppressWarnings({	"AssignmentToForLoopParameter", "fallthrough" })
public synchronized boolean hasNext()
{
	/* If there are values already available, the say so. */
	if( !values.isEmpty() ) return true;
	if( closed ) return false;

	/* Otherwise look ahead, to see if there is a line that can be processed.*/
	try
	{
		/* Loop for continuing to read lines, if lines are found to be empty. */
		String line;
		while( true )
		{
			/* Start accumulating a new line (throw out any garbage in the line
			   accumulator). Assume all will be OK. Count the new line and
			   remove any previous character that was under consideration. */
			aline.setLength(0);
			OK = true;
			++count;
			/* Loop for reading characters, to accumulate a line. */
			character_loop:
			while( true )
			{
				/* Skip until a character is found (or there may be one left
				   over from the previous iteration of the character_loop. */
				while( ichar == U_NULL ) ichar = input.read();

				/* Main switch, checking for end-of-file, an end-of-line, or a
				   Unicode escape. An "escaped" character that is not one of
				   these possibilities is just copied. */
				switch( ichar )
				{
				case -1:
					/* End of file while at beginning of line indicates that the
					   end-of-file may now be recognized. */
					if( aline.length() == 0 ) throw new EOFException();
					/* End of file, with characters in the line. Go process the
					   line as a line. */
					break character_loop;

				case U_CARRIAGE_RETURN:
					ichar = input.read();
					/* If the carriage return is not followed by line feed, keep
					   the examined character for the next line. */
					if( ichar != U_LINE_FEED ) break character_loop;

				case U_LINE_FEED:
				case U_VERTICAL_TAB:
				case U_FORM_FEED:
				case U_NEXT_LINE:
				case U_LINE_SEPARATOR:
				case U_PARAGRAPH_SEPARATOR:
					/* End of line: ensure moving on to next line next time. */
					ichar = U_NULL;
					break character_loop;

				case ESCAPE:
					/* Potentially an escape character. Need to look at next
					   character. */
					int backup = aline.length();
					aline.append((char) ichar);		// keep copy of the escape
					ichar = input.read();

					/* Switch for escape possibilities, including end-of-file,
					   an additional 'u', a Unicode value, or end-of-line (which
					   may be ignored). */
					switch( ichar )
					{
					case -1:
						/* An escape character exists at the end-of-file. If
						   escapes are not enabled, just leave the escape. */
						if( escapesEnabled ) aline.setLength(backup);
						/* Leave it with that end-of-file, so that it will be
						   seen on the next iteration. */
						continue;						//  character_loop

					case MARKER:
						/* If the escape is followed by a u (i.e., a MARKER), it
						   is potentially a Unicode escape. An escape followed
						   by a MARKER at end of file is an error--ignore the
						   characters. */
						boolean previousOK = OK;
						OK = false;
						aline.append((char) ichar); // keep copy of u
						if( (ichar = input.read()) == -1 )
							/* Leave ichar with that end-of-file, so that it
							   will be seen on the next iteration. The line
							   contains the escaped MARKER (the character u that
							   has been seen, and marked as an error. */
							continue;					//  character_loop

						if( ichar == MARKER )
							/* An escape followed by two 'u' characters is
							   replaced by an escape and one less 'u' 
							   character.*/
							continue;					//  character_loop
						/* Now looking for four hexadecimal characters. */
						int v = -1;
						int value = 0;
						int j = 0;
						do
						{
							if( (v = Character.digit(ichar, 16)) < 0 ) break;
							value = value * 16 + v;
							/* This character has been accepted: keep it. */
							aline.append((char) ichar);
						} while( ++j != 4 && (ichar = input.read()) != -1 );
						if( ichar == -1 ) continue;		//  character_loop
						if( v < 0 ) continue;			//  character_loop
						if( j != 4 ) continue;			//  character_loop
						OK = previousOK;
						ichar = value;
						aline.setLength(backup);
						if( ichar == ESCAPE )
						{
							/* An escape character given by a Unicode escape
							   cannot be used again in a Unicode escape. */
							aline.append(ESCAPE);
							ichar = 0;
						}
						continue;					//  character_loop

					case ESCAPE:
						/* A second escape means that there is no Unicode
						   escape. */
						aline.append(ESCAPE);
						ichar = 0;
						continue;					//  character_loop

					case U_LINE_FEED:
					case U_VERTICAL_TAB:
					case U_FORM_FEED:
					case U_CARRIAGE_RETURN:
					case U_NEXT_LINE:
					case U_LINE_SEPARATOR:
					case U_PARAGRAPH_SEPARATOR:
						/* Is this an escaped end of line? */
						if( escapesEnabled )
						{
							do
								ichar = input.read();
							while( Character.isWhitespace(ichar) );
							continue;				//  character_loop
						}
						break character_loop;

					default:
					/* Fall out of switch. */
					}
				default:
					aline.append((char) ichar);
					ichar = 0;
				}
			}

			/* Now have the line assembled. If escapes are enabled, then any
			   character following an ESCAPE is replaced by a marker character.
			   The same character always uses the same marker (see
			   forwardescapes). The reversescapes mapping is kept so as to be
			   able to replace the escaped character with itself when values are
			   broken out of the line. */
			copy = aline.toString();
			if( copy.isEmpty() ) continue;

			if( escapesEnabled )
				for( int j = 0; j != aline.length(); ++j )
					if( aline.charAt(j) == ESCAPE )
						if( j != aline.length() - 1 )
						{
							char next = aline.charAt(j + 1);
							/* If this escaped character has not been seen
							   before, assign it a marker character, and record
							   the reverse mapping. Advance the source of
							   markers. */
							if( !forwardescapes.containsKey(next) )
							{
								forwardescapes.put(next, escapesource);
								reversescapes.put(escapesource, next);
								--escapesource;
							}
							/* Get the marker character. */
							aline.setCharAt(j, forwardescapes.get(next));
							aline.deleteCharAt(j + 1);
						}

			/* If there is a sequence defined that introduces comments, then 
			   use it to find an end-of-line comment. */
			if( commentSequence != null )
			{
				int index = aline.indexOf(commentSequence);
				if( index >= 0 ) aline.delete(index, aline.length());
			}

			if( (line = aline.toString().trim()).isEmpty() && OK ) continue;

			if( !OK )
			{
				values.add(copy);
				return true;
			}

			/* Index of which regular expresssion to use for each match. */
			int index = 0;

			/* So there is a line, no errors, so proceed to scan across it. */
			while( !line.isEmpty() )
			{
				/* Split the line up into a value and the rest of the line using
				   the current delimiter. */
				String[] valuePlusRest = line.split(regex[index], 2);

				/* If escapes are being processed, check to see if there are any
				   markers in this value, and, if so, replace them by the
				   correct character (that was escaped). */
				if( escapesEnabled )
				{
					StringBuilder sb = new StringBuilder(valuePlusRest[0]);
					for( int i = 0; i != sb.length(); ++i )
					{
						Character next = sb.charAt(i);
						if( (next = reversescapes.get(next)) != null )
							sb.setCharAt(i, next);
					}
					valuePlusRest[0] = sb.toString();
				}

				/* The first returned String is the one found with the current
				   delimiter, and this is a value. */
				values.add(valuePlusRest[0].trim());

				/* The second returned String is the remainder of the line, if
				   there is any remainder. */
				line = valuePlusRest.length == 1 ? "" : valuePlusRest[1].trim();

				/* Increment the index, modulo the length of the array of
				   regular expressions. I.e, start over if the end is
				   reached. */
				index = (index + 1) % regex.length;
			}

			/* Line has been processed. Check whether the line was nothing but
			   delimiters, in which case treat is as being empty. */
			boolean empty = true;
			for( String value : values )
				if( !value.isEmpty() ) empty = false;
			if( empty ) continue;
			return true;
		}
	} catch( IOException ex )
	{
		/* Treat any exception reading the file as end-of-file. */
		close();
	}
	/* Have run out of lines, so report that there are no more lines. */
	return false;
}

/**
 * Get the array of Strings representing the next line of input.
 *
 * @return	an array of Strings, representing the delimited substrings of the
 *         next line of input.
 * @throws IllegalStateException if there is no next line with content, has an
 *                               ill-formed Unicode escape, or does not have the
 *                               expected number of values
 */
@Override
public synchronized String[] next() throws IllegalStateException
{
	boolean hasNext = hasNext();
	/* OK if there is no limit, or if the size is equal to the limit. */
	OK &= ( limit == 0 || values.size() == limit);

	/* Any problem along the way? Report the line. */
	if( !(hasNext && OK) )
		throw new IllegalStateException("Error in line " + count + ": " + copy);
	/* Get an array to return for the values from the ArrayList. */
	String[] result = values.toArray(new String[values.size()]);
	values.clear();
	return result;
}

/**
 * Skip the next input line (no matter what is on it).
 */
@Override
public synchronized void remove()
{
	/* If there is no line readahead, then if there is one read it. */
	if( values.isEmpty() && iterator().hasNext() ) iterator().next();
	/* Throw the line away. */
	values.clear();
}
}

/**
 * Close the InputData class (and the classes it is using)
 */
@Override
public void close()
{
	if( !closed )
		try(Reader reader = input )
		{
			reader.getClass();			// just to show a use of reader
		}
		catch( IOException ex )
		{
			assert false: ex.getMessage();
		}
			
	values.clear();
	aline = null;
	ichar = 0;
	closed = true;
}
}
