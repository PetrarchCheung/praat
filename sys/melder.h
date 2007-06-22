#ifndef _melder_h_
#define _melder_h_
/* melder.h
 *
 * Copyright (C) 1992-2007 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * pb 2007/06/10
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	#define strequ  ! strcmp
	#define strnequ  ! strncmp
	#define wcsequ  ! wcscmp
	#define wcsnequ  ! wcsncmp
	#define Melder_strequ  ! Melder_strcmp
	#define Melder_strnequ  ! Melder_strncmp
	#define Melder_wcsequ  ! Melder_wcscmp
	#define Melder_wcsnequ  ! Melder_wcsncmp
#include <stdarg.h>
#include <stddef.h>
#include <wchar.h>
#include <stdbool.h>

#ifndef TRUE
	#define TRUE  1
#endif
#ifndef FALSE
	#define FALSE  0
#endif
#ifndef NULL
	#define NULL  ((void *) 0)
#endif

/********** NUMBER TO STRING CONVERSION **********/

/*
	The following routines return a static string, chosen from a circularly used set of 11 buffers.
	You can call at most 11 of them in one Melder_casual call, for instance.
*/
const char * Melder_integerA (long value);
const wchar_t * Melder_integerW (long value);
#define Melder_integer  Melder_integerA
const char * Melder_bigIntegerA (double value);
const wchar_t * Melder_bigIntegerW (double value);
#define Melder_bigInteger  Melder_bigIntegerA
const char * Melder_booleanA (bool value);   /* "yes" or "no" */
const wchar_t * Melder_booleanW (bool value);
#define Melder_boolean  Melder_booleanA
const char * Melder_doubleA (double value);   /* "--undefined--" or something in the "%.15g", "%.16g", or "%.17g" formats */
const wchar_t * Melder_doubleW (double value);
#define Melder_double  Melder_doubleA
const char * Melder_singleA (double value);   /* "--undefined--" or something in the "%.8g" format */
const wchar_t * Melder_singleW (double value);
#define Melder_single  Melder_singleA
const char * Melder_halfA (double value);   /* "--undefined--" or something in the "%.4g" format */
const wchar_t * Melder_halfW (double value);
#define Melder_half  Melder_halfA
const char * Melder_fixedA (double value, int precision);   /* "--undefined--" or something in the "%.*f" format*/
const wchar_t * Melder_fixedW (double value, int precision);
#define Melder_fixed  Melder_fixedA
const char * Melder_fixedExponentA (double value, int exponent, int precision);
const wchar_t * Melder_fixedExponentW (double value, int exponent, int precision);
	/* if exponent is -2 and precision is 2:   67E-2, 0.00024E-2 */
#define Melder_fixedExponent  Melder_fixedExponentA
const char * Melder_percentA (double value, int precision);
const wchar_t * Melder_percentW (double value, int precision);
	/* "--undefined--" or, if precision is 3: "0" or "34.400%" of "0.014%" or "0.001%" or "0.0000007%" */
#define Melder_percent  Melder_percentA

/********** STRING TO NUMBER CONVERSION **********/

int Melder_isStringNumeric (const char *string);
int Melder_isStringNumericW (const wchar_t *string);
double Melder_atof (const char *string);
double Melder_atofW (const wchar_t *string);
	/*
	 * "3.14e-3" -> 3.14e-3
	 * "15.6%" -> 0.156
	 * "fghfghj" -> NUMundefined
	 */

/********** ERROR **********/

int Melder_error (const char *format, ...);
bool Melder_error1 (const wchar_t *s1);
bool Melder_error2 (const wchar_t *s1, const wchar_t *s2);
bool Melder_error3 (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3);
bool Melder_error4 (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4);
bool Melder_error5 (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5);
bool Melder_error6 (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6);
bool Melder_error7 (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6, const wchar_t *s7);
bool Melder_error8 (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6, const wchar_t *s7, const wchar_t *s8);
bool Melder_error9 (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6, const wchar_t *s7, const wchar_t *s8, const wchar_t *s9);
	/* Generate, but do not yet show, an error message, return 0. */

void * Melder_errorp (const char *format, ...);
void * Melder_errorpW (const wchar_t *format, ...);
	/* Generate, but do not yet show, an error message, return NULL. */

void Melder_flushError (const char *format, ...);
void Melder_flushErrorW (const wchar_t *format, ...);
	/* Send all deferred error messages to stderr (batch) or to an "Error" dialog, */
	/* including, if 'format' is not NULL, the error message generated by this routine. */

int Melder_hasError (void);
	/* Returns 1 if there is an error message in store, otherwise 0. */
#define iferror  if (Melder_hasError ())
#define cherror  iferror goto end;

void Melder_clearError (void);
	/* Cancel all stored error messages. */

char * Melder_getError (void);
wchar_t * Melder_getErrorW (void);
	/* Returns the error string. Mainly used with strstr. */

int Melder_fatal (const char *format, ...);
	/* Give error message, abort program. */
	/* Should only be caused by programming errors. */

#ifdef NDEBUG
	#define Melder_assert(x)   ((void) 0)
#else
	/*
	#define Melder_assert(x)   ((void) ((x) || _Melder_assert (#x, __FILE__, __LINE__)))
	*/
	#define Melder_assert(x)   ((x) ? (void) (0) : (void) _Melder_assert (#x, __FILE__, __LINE__))
#endif
int _Melder_assert (const char *condition, const char *fileName, int lineNumber);
	/* Call Melder_fatal with a message based on the following template: */
	/*    "Assertion failed in file <fileName> on line <lineNumber>: <condition>" */

/********** MEMORY ALLOCATION ROUTINES **********/

/* These routines call malloc, free, realloc, and calloc. */
/* If out of memory, they queue an error message (like "Out of memory") and return NULL. */
/* These routines also maintain a count of the total number of blocks allocated. */

void * Melder_malloc (unsigned long size);
void * Melder_realloc (void *pointer, long size);
void * Melder_calloc (long numberOfElements, long elementSize);
char * Melder_strdup (const char *string);
wchar_t * Melder_wcsdup (const wchar_t *string);
int Melder_strcmp (const char *string1, const char *string2);   // regards null string as empty string
int Melder_wcscmp (const wchar_t *string1, const wchar_t *string2);   // regards null string as empty string
int Melder_strncmp (const char *string1, const char *string2, unsigned long n);
int Melder_wcsncmp (const wchar_t *string1, const wchar_t *string2, unsigned long n);
wchar_t * Melder_wcsdecompose (const wchar_t *string);
wchar_t * Melder_wcsprecompose (const wchar_t *string);
wchar_t * Melder_wcsExpandBackslashSequences (const wchar_t *string);
wchar_t * Melder_wcsReduceBackslashSequences (const wchar_t *string);
void Melder_wcsReduceBackslashSequences_inline (const wchar_t *string);

/*
 * Text encodings.
 */
void Melder_textEncoding_prefs (void);
#define Melder_INPUT_ENCODING_UTF8  1
#define Melder_INPUT_ENCODING_UTF8_THEN_ISO_LATIN1  2
#define Melder_INPUT_ENCODING_ISO_LATIN1  3
#define Melder_INPUT_ENCODING_UTF8_THEN_WINDOWS_LATIN1  4
#define Melder_INPUT_ENCODING_WINDOWS_LATIN1  5
#define Melder_INPUT_ENCODING_UTF8_THEN_MACROMAN  6
#define Melder_INPUT_ENCODING_MACROMAN  7
void Melder_setInputEncoding (int encoding);
int Melder_getInputEncoding (void);
#define Melder_OUTPUT_ENCODING_UTF8  1
#define Melder_OUTPUT_ENCODING_UTF16  2
#define Melder_OUTPUT_ENCODING_ASCII_THEN_UTF16  3
void Melder_setOutputEncoding (int encoding);
int Melder_getOutputEncoding (void);

/*
 * Non-text encodings. Although not used in the above set/get functions,
 * these constants should stay separate from the text encoding constants
 * because they occur in the same fields of struct MelderFile.
 */
#define Melder_INPUT_ENCODING_FLAC  0x464C4143
#define Melder_OUTPUT_ENCODING_FLAC  0x464C4143

bool Melder_isValidAscii (const wchar_t *string);
bool Melder_isValidUtf8 (const unsigned char *string);

long Melder_killReturns_inlineW (wchar_t *text);

int Melder_8bitToWcs_inline (const unsigned char *string, wchar_t *wcs, int inputEncoding);
wchar_t * Melder_8bitToWcs (const unsigned char *string, int inputEncoding);
wchar_t * Melder_utf8ToWcs (const unsigned char *string);
int Melder_wcsTo8bit_inline (const wchar_t *wcs, unsigned char *string, int outputEncoding);
char * Melder_wcsTo8bit (const wchar_t *string, int outputEncoding);

wchar_t * Melder_asciiToWcs (const char *string);
void Melder_asciiToWcs_inline (const char *ascii, wchar_t *wcs);
char * Melder_wcsToAscii (const wchar_t *string);
void Melder_wcsToAscii_inline (const wchar_t *wcs, char *ascii);
char * Melder_wcsToUtf8 (const wchar_t *string);
void Melder_wcsToUtf8_inline (const wchar_t *wcs, unsigned char *utf8);
void Melder_wcsTo8bitFileRepresentation_inline (const wchar_t *wcs, unsigned char *utf8);
void Melder_8bitFileRepresentationToWcs_inline (const unsigned char *utf8, wchar_t *wcs);
wchar_t * Melder_peekAsciiToWcs (const char *string);
wchar_t * Melder_peekUtf8ToWcs (const unsigned char *string);
char * Melder_peekWcsToAscii (const wchar_t *string);
char * Melder_peekWcsToUtf8 (const wchar_t *string);
void Melder_fwriteWcsAsUtf8 (const wchar_t *ptr, size_t n, FILE *f);

/*
 * Some often used characters.
 */
#define L_LEFT_SINGLE_QUOTE  L"\u2018"
#define L_RIGHT_SINGLE_QUOTE  L"\u2019"
#define L_LEFT_DOUBLE_QUOTE  L"\u201c"
#define L_RIGHT_DOUBLE_QUOTE  L"\u201d"
#define L_LEFT_GUILLEMET  L"\u00ab"
#define L_RIGHT_GUILLEMET  L"\u00bb"

#define Melder_free(pointer)  _Melder_free ((void **) & (pointer))
void _Melder_free (void **pointer);
/*
	Preconditions:
		none (*pointer may be NULL).
	Postconditions:
		*pointer == NULL;
*/

double Melder_allocationCount (void);
/*
	Returns the total number of successful calls to
	Melder_malloc, Melder_realloc (if 'ptr' is NULL), Melder_calloc, and Melder_strdup,
	since the start of the process. Mainly for debugging purposes.
*/

double Melder_deallocationCount (void);
/*
	Returns the total number of successful calls to Melder_free,
	since the start of the process. Mainly for debugging purposes.
*/

double Melder_allocationSize (void);
/*
	Returns the total number of bytes allocated in calls to
	Melder_malloc, Melder_realloc (if moved), Melder_calloc, and Melder_strdup,
	since the start of the process. Mainly for debugging purposes.
*/

/********** STRINGS **********/

/* These are routines for never having to check string boundaries again. */

typedef struct {
	unsigned long length;
	unsigned long bufferSize;
	char *string;   // a growing buffer, never shrunk (can only be freed by MelderStringA_free)
} MelderStringA;
typedef struct {
	unsigned long length;
	unsigned long bufferSize;
	wchar_t *string;   // a growing buffer, never shrunk (can only be freed by MelderStringW_free)
} MelderStringW;

void MelderStringA_free (MelderStringA *me);   // frees the "string" attribute only (and sets other attributes to zero)
void MelderStringW_free (MelderStringW *me);   // frees the "string" attribute only (and sets other attributes to zero)
void MelderStringA_empty (MelderStringA *me);   // sets to empty string (buffer not freed)
void MelderStringW_empty (MelderStringW *me);   // sets to empty string (buffer not freed)
bool MelderStringA_copyA (MelderStringA *me, const char *source);
bool MelderStringA_copyW (MelderStringA *me, const wchar_t *source);   // performs no data range checking
bool MelderStringW_copyA (MelderStringW *me, const char *source);
bool MelderStringW_copyW (MelderStringW *me, const wchar_t *source);
bool MelderStringA_ncopyA (MelderStringA *me, const char *source, unsigned long n);
bool MelderStringW_ncopyW (MelderStringW *me, const wchar_t *source, unsigned long n);
bool MelderStringA_appendA (MelderStringA *me, const char *source);
bool MelderStringW_appendW (MelderStringW *me, const wchar_t *source);
bool MelderStringW_appendA (MelderStringW *me, const char *source);
bool MelderStringA_appendCharacter (MelderStringA *me, char character);
bool MelderStringW_appendCharacter (MelderStringW *me, wchar_t character);
bool MelderStringA_getA (MelderStringA *me, char *destination);   // performs no boundary checking
bool MelderStringW_getA (MelderStringW *me, char *destination);   // performs no boundary checking and no data range checking
bool MelderStringW_getW (MelderStringW *me, wchar_t *destination);   // performs no boundary checking
double MelderString_allocationCount (void);
double MelderString_deallocationCount (void);
double MelderString_allocationSize (void);

/********** FILES **********/

#if defined (_WIN32)
	#define Melder_DIRECTORY_SEPARATOR  '\\'
#else
	#define Melder_DIRECTORY_SEPARATOR  '/'
#endif

struct FLAC__StreamDecoder;
struct FLAC__StreamEncoder;

typedef struct {
	FILE *filePointer;
	wchar_t wpath [260];
	bool openForReading, openForWriting, verbose, requiresCRLF;
	unsigned long inputEncoding, outputEncoding;
	int indent;
	struct FLAC__StreamEncoder *flacEncoder;
} structMelderFile, *MelderFile;
typedef struct {
	wchar_t wpath [260];
} structMelderDir, *MelderDir;

/********** NUMBER AND STRING COMPARISON **********/

#define Melder_NUMBER_min  1
#define Melder_NUMBER_EQUAL_TO  1
#define Melder_NUMBER_NOT_EQUAL_TO  2
#define Melder_NUMBER_LESS_THAN  3
#define Melder_NUMBER_LESS_THAN_OR_EQUAL_TO  4
#define Melder_NUMBER_GREATER_THAN  5
#define Melder_NUMBER_GREATER_THAN_OR_EQUAL_TO  6
#define Melder_NUMBER_max  6
const char * Melder_NUMBER_text_adjective (int which_Melder_NUMBER);
const wchar_t * Melder_NUMBER_text_adjectiveW (int which_Melder_NUMBER);
int Melder_numberMatchesCriterion (double value, int which_Melder_NUMBER, double criterion);

#define Melder_STRING_min  1
#define Melder_STRING_EQUAL_TO  1
#define Melder_STRING_NOT_EQUAL_TO  2
#define Melder_STRING_CONTAINS  3
#define Melder_STRING_DOES_NOT_CONTAIN  4
#define Melder_STRING_STARTS_WITH  5
#define Melder_STRING_DOES_NOT_START_WITH  6
#define Melder_STRING_ENDS_WITH  7
#define Melder_STRING_DOES_NOT_END_WITH  8
#define Melder_STRING_MATCH_REGEXP  9
#define Melder_STRING_max  9
const char * Melder_STRING_text_finiteVerb (int which_Melder_STRING);
const wchar_t * Melder_STRING_text_finiteVerbW (int which_Melder_STRING);
int Melder_stringMatchesCriterion (const char *value, int which_Melder_STRING, const char *criterion);
int Melder_stringMatchesCriterionW (const wchar_t *value, int which_Melder_STRING, const wchar_t *criterion);

/********** STRING PARSING **********/

/*
	These functions regard a string as a sequence of tokens,
	separated (and perhaps preceded and followed) by white space.
	The tokens cannot contain spaces themselves (there are no escapes).
	Typical use:
		for (token = Melder_firstToken (string); token != NULL; token = Melder_nextToken ()) {
			... do something with the token ...
		}
*/

long Melder_countTokens (const char *string);
char *Melder_firstToken (const char *string);
char *Melder_nextToken (void);

/********** MESSAGING ROUTINES **********/

/* These functions are called like printf ().
	Default Melder does fprintf to stderr,
	except Melder_information, which does fprintf to stdout.
	These functions show generic, native, and mixed strings correctly,
	and perform quote conversion, if that flag is not off; see under "NON-ASCII CHARACTERS".
	The alphabet is Roman, so that symbols from the Symbol and Phonetic alphabets
	are not translated (by default, \mu is shown as \mu and \as as a).
*/

void Melder_casual (const char *format, ...);
/*
	Function:
		Sends a message without user interference.
	Behaviour:
		Writes to stderr on Unix, otherwise to a special window.
*/

/* Give information to stdout (batch), or to an "Info" window (interactive), or to a diverted string. */

void MelderInfo_open (void);   /* Clear the Info window in the background. */
void MelderInfo_write1 (const char *s1);   /* Write a string to the Info window in the background. */
void MelderInfo_write2 (const char *s1, const char *s2);   /* Write two strings to the Info window in the background. */
void MelderInfo_write3 (const char *s1, const char *s2, const char *s3);
void MelderInfo_write4 (const char *s1, const char *s2, const char *s3, const char *s4);
void MelderInfo_write5 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5);
void MelderInfo_write6 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6);
void MelderInfo_write7 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6, const char *s7);
void MelderInfo_write8 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6, const char *s7, const char *s8);
void MelderInfo_write9 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6, const char *s7, const char *s8, const char *s9);
void MelderInfo_write1W (const wchar_t *s1);   /* Write a string to the Info window in the background. */
void MelderInfo_write2W (const wchar_t *s1, const wchar_t *s2);   /* Write two strings to the Info window in the background. */
void MelderInfo_write3W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3);
void MelderInfo_write4W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4);
void MelderInfo_write5W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5);
void MelderInfo_write6W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6);
void MelderInfo_write7W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6, const wchar_t *s7);
void MelderInfo_write8W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6, const wchar_t *s7, const wchar_t *s8);
void MelderInfo_write9W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6, const wchar_t *s7, const wchar_t *s8, const wchar_t *s9);
void MelderInfo_writeLine1 (const char *s1);   /* Write a string to the Info window in the background; add a new-line. */
void MelderInfo_writeLine2 (const char *s1, const char *s2);
void MelderInfo_writeLine3 (const char *s1, const char *s2, const char *s3);
void MelderInfo_writeLine4 (const char *s1, const char *s2, const char *s3, const char *s4);
void MelderInfo_writeLine5 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5);
void MelderInfo_writeLine6 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6);
void MelderInfo_writeLine7 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6, const char *s7);
void MelderInfo_writeLine8 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6, const char *s7, const char *s8);
void MelderInfo_writeLine9 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6, const char *s7, const char *s8, const char *s9);
void MelderInfo_writeLine1W (const wchar_t *s1);   /* Write a string to the Info window in the background; add a new-line. */
void MelderInfo_writeLine2W (const wchar_t *s1, const wchar_t *s2);
void MelderInfo_writeLine3W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3);
void MelderInfo_writeLine4W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4);
void MelderInfo_writeLine5W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5);
void MelderInfo_writeLine6W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6);
void MelderInfo_writeLine7W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6, const wchar_t *s7);
void MelderInfo_writeLine8W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6, const wchar_t *s7, const wchar_t *s8);
void MelderInfo_writeLine9W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6, const wchar_t *s7, const wchar_t *s8, const wchar_t *s9);
void MelderInfo_close (void);   /* Flush the background info to the Info window. */

void Melder_information1 (const char *s1);
void Melder_information2 (const char *s1, const char *s2);
void Melder_information3 (const char *s1, const char *s2, const char *s3);
void Melder_information4 (const char *s1, const char *s2, const char *s3, const char *s4);
void Melder_information5 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5);
void Melder_information6 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6);
void Melder_information7 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6, const char *s7);
void Melder_information8 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6, const char *s7, const char *s8);
void Melder_information9 (const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6, const char *s7, const char *s8, const char *s9);
void Melder_information1W (const wchar_t *s1);
void Melder_information2W (const wchar_t *s1, const wchar_t *s2);
void Melder_information3W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3);
void Melder_information4W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4);
void Melder_information5W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5);
void Melder_information6W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6);
void Melder_information7W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6, const wchar_t *s7);
void Melder_information8W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6, const wchar_t *s7, const wchar_t *s8);
void Melder_information9W (const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const wchar_t *s4, const wchar_t *s5, const wchar_t *s6, const wchar_t *s7, const wchar_t *s8, const wchar_t *s9);

void Melder_informationReal (double value, const char *units);   /* %.17g or --undefined--; units may be NULL */
void Melder_informationRealW (double value, const wchar_t *units);   /* %.17g or --undefined--; units may be NULL */

void Melder_divertInfo (MelderStringW *buffer);   /* NULL = back to normal. */

void Melder_print (const wchar_t *s);
	/* Write formatted text to the Info window without clearing it, and without adding a new-line symbol at the end. */

void Melder_clearInfo (void);   /* Clear the Info window. */
wchar_t * Melder_getInfo (void);
void Melder_help (const char *query);

void Melder_search (void);

void Melder_warning (const char *format, ...);
	/* Give warning to stderr (batch) or to a "Warning" dialog. */
void Melder_warningOff (void);
void Melder_warningOn (void);
	
void Melder_beep (void);

extern int Melder_debug;

/********** PROGRESS ROUTINES **********/

int Melder_progress (double progress, const char *format, ...);
void Melder_progressOff (void);
void Melder_progressOn (void);
/*
	Function:
		Show the progress of a time-consuming process.
	Arguments:
		'format' may be NULL.
	Batch behaviour:
		Does nothing, always returns 1.
	Interactive behaviour:
		Shows the progress of a time-consuming process:
		- if 'progress' <= 0.0, show a window with text and a Cancel button, and return 1;
		- if 0.0 < 'progress' < 1.0, show text and a partially filled progress bar,
		  and return 0 if user interrupts, else return 1;
		- if 'progress' >= 1, hide the window.
	Usage:
		- call with 'progress' = 0.0 before the process starts:
			  (void) Melder_progress (0.0, "Starting work...");
		- at every turn in your loop, call with 'progress' between 0 and 1,
		  and check the return value to see if the user clicked the Cancel button:
			  if (! Melder_progress (i / (n + 1.0), "Working on part %d out of %d...", i, n))
			  {
				  forget (me);   // Clean up.
				  return Melder_errorp ("Work interrupted, not finished");   // Interrupt.
			  }
		- after the process has finished, call with 'progress' = 1.0:
			  (void) Melder_progress (1.0, NULL);
*/
	
void * Melder_monitor (double progress, const char *format, ...);
/*
	Function:
		Show the progress of a time-consuming process.
	Arguments:
		'format' may be NULL.
	Batch behaviour:
		Does nothing, returns NULL if 'progress' <= 0.0 and a non-NULL pointer otherwise.
	Interactive behaviour:
		Shows the progress of a time-consuming process:
		- if 'progress' <= 0.0, show a window with text and a Cancel button and
		  room for a square drawing, and return a Graphics;
		- if 0.0 < 'progress' < 1.0, show text and a partially filled progress bar,
		  and return NULL if user interrupts, else return a non-NULL pointer;
		- if 'progress' >= 1, hide the window.
	Usage:
		- call with 'progress' = 0.0 before the process starts.
		- assign the return value to a Graphics:
			Graphics graphics = Melder_monitor (0.0, "Starting work...");
		- at every turn of your loop, draw something in the Graphics:
			if (graphics) {   // Always check; might be batch.
				Graphics_clearWs (graphics);   // Only if you redraw all every time.
				Graphics_polyline (graphics, ...);
				Graphics_printf (graphics, ...);
			}
		- immediately after this in your loop, call with 'progress' between 0 and 1,
		  and check the return value to see if the user clicked the Cancel button:
			if (! Melder_monitor (i / (n + 1.0), "Working on part %d out of %d...", i, n)) {
				forget (me);   // Clean up.
				return Melder_errorp ("Work interrupted, not finished");   // Interrupt.
			}
		- after the process has finished, call with 'progress' = 1.0:
			(void) Melder_monitor (1.0, NULL);
*/

int Melder_pause (const char *format, ...);
/*
	Function:
		Pause the progress of a process.
	Arguments:
		'format' may be NULL.
	Batch behaviour:
		Writes a prompt "Pause:" to stderr, followed by the message text,
		and followed by the line "Press 'q' to stop, or any other key to continue.".
		Waits for the user to hit a key to stdin.
		Returns 0 if the user hits 'q' or 'Q', otherwise 1.
	Interactive behaviour:
		Shows a window titled "Pause" with the message text and two buttons named Continue and Stop.
		Waits for the user to click one of these.
		Returns 1 if user clicks Continue, 0 if user clicks Stop.
	Usage:
		Check the return value to see if the user clicked the Stop button:
			nextPicture ();
			if (! Melder_pause ("See this beautiful picture"))
				return Melder_errorp ("Demo interrupted.");
			nextPicture ();
*/

/********** RECORD AND PLAY ROUTINES **********/

int Melder_publish (void *anything);

int Melder_record (double duration);
int Melder_recordFromFile (MelderFile fs);
void Melder_play (void);
void Melder_playReverse (void);
int Melder_publishPlayed (void);

/********** SYSTEM VERSION **********/

extern unsigned long Melder_systemVersion;
/*
	For Macintosh, this is set in the Motif emulator.
*/

/********** SCRATCH TEXT BUFFERS **********/

extern char Melder_buffer1 [30001], Melder_buffer2 [30001];
/*
	Every Melder routine uses both of these buffers:
	one for sprintfing the message,
	and one for translating this message to a native string.
	You can use these buffers,
	but be careful not to call any other routines that use them at the same time;
	the following routines are guaranteed not to call the Melder library:
	 - Mac Toolbox, XWindows, X Toolkit, Motif, and XVT routines,
		except those who dispatch events (XtDispatchEvent, xvt_process_pending_events).
	 - Longchar_*
	This means that you can use these buffers for reading and writing with
	the Longchar library.
*/

/********** ENFORCE INTERACTIVE BEHAVIOUR **********/

/* Procedures to enforce interactive behaviour of the Melder_XXXXXX routines. */

void MelderMotif_create (/* XtAppContext* */ void *appContext, /* Widget */ void *parent);
/*
	'appContext' is the XtAppContext* output from Xt(Va)AppInitialize;
		if you used Xt(Va)Initialize it should be NULL.
	'parent' is the top-level widget returned by Xt(Va)(App)Initialize.
*/

extern int Melder_batch;   /* True if run from the batch or from an interactive command-line interface. */
extern int Melder_backgrounding;   /* True if running a script. */
#ifndef CONTROL_APPLICATION
	extern void *Melder_appContext;   /* XtAppContext* */
	extern void *Melder_topShell;   /* Widget */
#endif

/********** OVERRIDE DEFAULT BEHAVIOUR **********/

/* Procedures to override default message methods. */
/* They may chage the string arguments. */
/* Many of these routines are called by MelderMotif_create and MelderXvt_create. */

void Melder_setCasualProc (void (*casualProc) (char *message));
void Melder_setProgressProc (int (*progressProc) (double progress, char *message));
void Melder_setMonitorProc (void * (*monitorProc) (double progress, char *message));
void Melder_setPauseProc (int (*pauseProc) (char *message));
void Melder_setInformationProc (void (*informationProc) (wchar_t *message));
void Melder_setHelpProc (void (*help) (const char *query));
void Melder_setSearchProc (void (*search) (void));
void Melder_setWarningProc (void (*warningProc) (char *message));
void Melder_setErrorProc (void (*errorProc) (wchar_t *message));
void Melder_setFatalProc (void (*fatalProc) (char *message));
void Melder_setPublishProc (int (*publish) (void *));
void Melder_setRecordProc (int (*record) (double));
void Melder_setRecordFromFileProc (int (*recordFromFile) (MelderFile));
void Melder_setPlayProc (void (*play) (void));
void Melder_setPlayReverseProc (void (*playReverse) (void));
void Melder_setPublishPlayedProc (int (*publishPlayed) (void));

/********** FILE ROUTINES **********/

#if defined (macintosh)
	void Melder_machToFile (void *void_fsref, MelderFile file);
	int Melder_fileToMach (MelderFile file, void *void_fsref);
	int Melder_fileToMac (MelderFile file, void *void_fspec);
#endif
char * MelderFile_name (MelderFile file);
wchar_t * MelderFile_nameW (MelderFile file);
char * MelderDir_name (MelderDir dir);
wchar_t * MelderDir_nameW (MelderDir dir);
int Melder_pathToDir (const char *path, MelderDir dir);
int Melder_pathToDirW (const wchar_t *path, MelderDir dir);
int Melder_pathToFile (const char *path, MelderFile file);
int Melder_pathToFileW (const wchar_t *path, MelderFile file);
int Melder_relativePathToFile (const char *path, MelderFile file);
int Melder_relativePathToFileW (const wchar_t *path, MelderFile file);
char * Melder_dirToPath (MelderDir dir);
wchar_t * Melder_dirToPathW (MelderDir dir);
	/* Returns a pointer internal to 'dir', like "/u/paul/praats" or "D:\Paul\Praats" */
char * Melder_fileToPath (MelderFile file);
wchar_t * Melder_fileToPathW (MelderFile file);
void MelderFile_copy (MelderFile file, MelderFile copy);
void MelderDir_copy (MelderDir dir, MelderDir copy);
int MelderFile_equal (MelderFile file1, MelderFile file2);
int MelderDir_equal (MelderDir dir1, MelderDir dir2);
void MelderFile_setToNull (MelderFile file);
int MelderFile_isNull (MelderFile file);
void MelderDir_setToNull (MelderDir dir);
int MelderDir_isNull (MelderDir dir);
void MelderDir_getFileW (MelderDir parent, const wchar_t *fileName, MelderFile file);
void MelderDir_relativePathToFile (MelderDir dir, const char *path, MelderFile file);
void MelderDir_relativePathToFileW (MelderDir dir, const wchar_t *path, MelderFile file);
void MelderFile_getParentDir (MelderFile file, MelderDir parent);
void MelderDir_getParentDir (MelderDir file, MelderDir parent);
int MelderDir_isDesktop (MelderDir dir);
int MelderDir_getSubdirW (MelderDir parent, const wchar_t *subdirName, MelderDir subdir);
void Melder_rememberShellDirectory (void);
wchar_t * Melder_getShellDirectory (void);
void Melder_getHomeDir (MelderDir homeDir);
void Melder_getPrefDir (MelderDir prefDir);
void Melder_getTempDir (MelderDir tempDir);

int MelderFile_exists (MelderFile file);
int MelderFile_readable (MelderFile file);
long MelderFile_length (MelderFile file);
int MelderFile_delete (MelderFile file);

/* The following two should be combined with each other and with Windows extension setting: */
FILE * Melder_fopen (MelderFile file, const char *type);
FILE * Melder_fopenW (MelderFile file, const wchar_t *type);
#if defined (macintosh)
	void MelderFile_setMacTypeAndCreator (MelderFile file, long fileType, long creator);
	unsigned long MelderFile_getMacType (MelderFile file);
#else
	#define MelderFile_setMacTypeAndCreator(f,t,c)  (void) 0
#endif
int Melder_fclose (MelderFile file, FILE *stream);
void Melder_files_cleanUp (void);

/* So these will be the future replacements for the above, as soon as we rid of text files: */
void MelderFile_open (MelderFile file);
void MelderFile_append (MelderFile file);
void MelderFile_create (MelderFile file, const char *macType, const char *macCreator, const char *winExtension);
void MelderFile_createW (MelderFile file, const wchar_t *macType, const wchar_t *macCreator, const wchar_t *winExtension);
void * MelderFile_read (MelderFile file, long nbytes);
char * MelderFile_readLine (MelderFile file);
void MelderFile_write (MelderFile file, char *buffer, long nchars);
void MelderFile_writeW (MelderFile file, wchar_t *buffer, long nchars);
void MelderFile_writeLine (MelderFile file, char *buffer);
void MelderFile_writeLineW (MelderFile file, wchar_t *buffer);
void MelderFile_rewind (MelderFile file);
void MelderFile_seek (MelderFile file, long position, int direction);
long MelderFile_tell (MelderFile file);
void MelderFile_close (MelderFile file);
/* If one of these routines fails, it closes the file and generates an error. */
/* It is often sufficient to call cherror only before other tests that could */
/* result in Melder_error (), and to call iferror at the end. */

/* A global for writing text files. Affects MelderFile_writeLine () only. */
#define MelderFile_NATIVE  1
#define MelderFile_MACINTOSH  2
#define MelderFile_UNIX  3
#define MelderFile_WINDOWS  4
void MelderFile_setLineSeparator (int systemType);

/* Read and write whole text files. */
char * MelderFile_readText (MelderFile file);
wchar_t * MelderFile_readTextW (MelderFile file);
int MelderFile_writeText (MelderFile file, const char *text);
int MelderFile_writeTextW (MelderFile file, const wchar_t *text);
int MelderFile_appendText (MelderFile file, const char *text);
int MelderFile_appendTextW (MelderFile file, const wchar_t *text);

int Melder_createDirectory (MelderDir parent, const char *subdirName, int mode);
int Melder_createDirectoryW (MelderDir parent, const wchar_t *subdirName, int mode);

void Melder_getDefaultDir (MelderDir dir);
void Melder_setDefaultDir (MelderDir dir);
void MelderFile_setDefaultDir (MelderFile file);
void MelderFile_nativizePath (char *path);   /* Convert from Unix-style slashes. */
void MelderFile_nativizePathW (wchar_t *path);   /* Convert from Unix-style slashes. */

/* Use the following functions to pass unchanged text or file names to Melder_* functions. */
/* Backslashes are replaced by "\bs". */
/* The trick is that Melder_asciiMessage returns one of 11 cyclically used static strings, */
/* so you can use up to 11 strings in a single Melder_* call. */
char * Melder_asciiMessage (const char *message);
wchar_t * Melder_peekExpandBackslashes (const wchar_t *message);
char * MelderFile_messageName (MelderFile file);   // Calls Melder_asciiMessage ().
wchar_t * MelderFile_messageNameW (MelderFile file);   // Calls Melder_peekExpandBackslashes ().

double Melder_stopwatch (void);

long Melder_killReturns_inline (char *text);
/*
	 Replaces all bare returns (Mac) or return / linefeed sequences (Win) with bare linefeeds (generic = Unix).
	 Returns new length of string (equal to or less than old length).
*/

/********** AUDIO **********/

void Melder_setUseInternalSpeaker (int useInternalSpeaker);
int Melder_getUseInternalSpeaker (void);
void Melder_setOutputGain (double gain);
double Melder_getOutputGain (void);
void Melder_audio_prefs (void);
long Melder_getBestSampleRate (long fsamp);
extern int Melder_isPlaying;
int Melder_play16 (const short *buffer, long sampleRate, long numberOfSamples, int numberOfChannels,
	int (*playCallback) (void *playClosure, long numberOfSamplesPlayed), void *playClosure);
int Melder_stopPlaying (int explicit);   /* Returns 1 if sound was playing. */
#define Melder_IMPLICIT  0
#define Melder_EXPLICIT  1
long Melder_getSamplesPlayed (void);
int Melder_stopWasExplicit (void);

void Melder_setMaximumAsynchronicity (int maximumAsynchronicity);
#define Melder_SYNCHRONOUS  0
#define Melder_CALLING_BACK  1
#define Melder_INTERRUPTABLE  2
#define Melder_ASYNCHRONOUS  3
int Melder_getMaximumAsynchronicity (void);

void Melder_setZeroPadding (double zeroPadding);   /* Seconds of silence before and after playing. */
double Melder_getZeroPadding (void);

/********** AUDIO FILES **********/

/* Audio file types. */
#define Melder_AIFF  1
#define Melder_AIFC  2
#define Melder_WAV  3
#define Melder_NEXT_SUN  4
#define Melder_NIST  5
#define Melder_SOUND_DESIGNER_TWO  6
#define Melder_FLAC 7
#define Melder_MP3 8
#define Melder_NUMBER_OF_AUDIO_FILE_TYPES  8
char * Melder_audioFileTypeString (int audioFileType);   /* "AIFF", "AIFC", "WAV", "NeXT/Sun", "NIST", "Sound Designer II", "FLAC", "MP3" */
char * Melder_macAudioFileType (int audioFileType);   /* "AIFF", "AIFC", "WAVE", "ULAW", "NIST", "Sd2f", "FLAC", "MP3" */
char * Melder_winAudioFileExtension (int audioFileType);   /* ".aiff", ".aifc", ".wav", ".au", ".nist", ".sd2", ".flac", ".mp3" */
/* Audio encodings. */
#define Melder_LINEAR_8_SIGNED  1
#define Melder_LINEAR_8_UNSIGNED  2
#define Melder_LINEAR_16_BIG_ENDIAN  3
#define Melder_LINEAR_16_LITTLE_ENDIAN  4
#define Melder_LINEAR_24_BIG_ENDIAN  5
#define Melder_LINEAR_24_LITTLE_ENDIAN  6
#define Melder_LINEAR_32_BIG_ENDIAN  7
#define Melder_LINEAR_32_LITTLE_ENDIAN  8
#define Melder_MULAW  9
#define Melder_ALAW  10
#define Melder_SHORTEN  11
#define Melder_POLYPHONE  12
#define Melder_IEEE_FLOAT_32_BIG_ENDIAN  13
#define Melder_IEEE_FLOAT_32_LITTLE_ENDIAN  14
#define Melder_FLAC_COMPRESSION 15
#define Melder_MPEG_COMPRESSION 16
int Melder_defaultAudioFileEncoding16 (int audioFileType);   /* BIG_ENDIAN, BIG_ENDIAN, LITTLE_ENDIAN, BIG_ENDIAN, LITTLE_ENDIAN, BIG_ENDIAN */
int MelderFile_writeAudioFileHeader16 (MelderFile file, int audioFileType, long sampleRate, long numberOfSamples, int numberOfChannels);
int MelderFile_writeAudioFile16 (MelderFile file, int audioFileType, const short *buffer, long sampleRate, long numberOfSamples, int numberOfChannels);

int MelderFile_checkSoundFile (MelderFile file, int *numberOfChannels, int *encoding,
	double *sampleRate, long *startOfData, long *numberOfSamples);
/* Returns information about a just opened audio file.
 * The return value is the audio file type, or 0 if it is not a sound file or in case of error.
 * The data start at 'startOfData' bytes from the start of the file.
 */
int Melder_bytesPerSamplePoint (int encoding);
int Melder_readAudioToFloat (FILE *f, int numberOfChannels, int encoding,
	float *leftBuffer, float *rightBuffer, long numberOfSamples);
/* If rightBuffer is NULL, reads mono data or averaged stereo data into leftBuffer.
 * If rightBuffer exists, read mono data into leftBuffer or stereo data into leftBuffer and rightBuffer.
 * Buffers are base-1.
 */
int Melder_readAudioToShort (FILE *f, int numberOfChannels, int encoding, short *buffer, long numberOfSamples);
/* If stereo, buffer will contain alternating left and right values.
 * Buffer is base-0.
 */
int MelderFile_writeFloatToAudio (MelderFile file, int encoding, const float *left, long nleft, const float *right, long nright, int warnIfClipped);
int MelderFile_writeShortToAudio (MelderFile file, int numberOfChannels, int encoding, const short *buffer, long numberOfSamples);

void Melder_audioTrigger (void);

/********** QUANTITY **********/

#define MelderQuantity_NONE  0
#define MelderQuantity_TIME_SECONDS  1
#define MelderQuantity_FREQUENCY_HERTZ  2
#define MelderQuantity_FREQUENCY_BARK  3
#define MelderQuantity_DISTANCE_FROM_GLOTTIS_METRES  4
#define MelderQuantity_NUMBER_OF_QUANTITIES  4
const char * MelderQuantity_getText (int quantity);   // e.g. "Time"
const char * MelderQuantity_getWithUnitText (int quantity);   // e.g. "Time (s)"
const char * MelderQuantity_getLongUnitText (int quantity);   // e.g. "seconds"
const char * MelderQuantity_getShortUnitText (int quantity);   // e.g. "s"

/********** MISCELLANEOUS **********/

char * Melder_getenv (const char *variableName);
int Melder_system (const char *command);   /* Spawn a system command; return 0 if error. */

/* End of file melder.h */
#endif
