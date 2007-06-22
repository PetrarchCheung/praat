#ifndef _Thing_h_
#define _Thing_h_
/* Thing.h
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
 * pb 2002/03/07 GPL
 * pb 2002/03/11 replaced _I with void_me etc for compliance with new ctype.h
 * pb 2004/10/16 C++ compatible structs
 * pb 2004/10/25 C++ compatible assignments
 * pb 2006/12/10 update on "info" documentation
 * pb 2007/06/11 wchar_t
 */

/* The root class of all objects. */

/* Anyone who uses Thing can also use: */
	/* Arrays with any bounds and 1 or two indices, math, and numerics: */
		#include "NUM.h"   /* Including math.h */
	/* The messaging mechanism: */
		#include "melder.h"   /* Including stdio.h string.h etc. */
	/* Enumerated types: */
		#include "enum.h"
	/* The macros for struct and class definitions: */
		#include "oo.h"
	/* The input/output mechanism: */
		#include "abcio.h"
		#include "lispio.h"

/* Public. */

typedef void *Any;   /* Prevent compile-time type checking. */

/*
	Use the macros 'I' and 'thou' for objects in the formal parameter lists.
	Use the macros 'iam' and 'thouart'
	as the first declaration in a function definition.
	After this, the object 'me' or 'thee' has the right class (for the compiler),
	so that you can use the macros 'my' and 'thy' to refer to members,
	and 'our' and 'your' to refer to methods.
	Example: int Person_getAge (I) { iam (Person); return my age; }
*/
#define I  Any void_me
#define thou  Any void_thee
#define iam(klas)  klas me = (klas) void_me
#define thouart(klas)  klas thee = (klas) void_thee
#define my  me ->
#define thy  thee ->
#define his  him ->
#define our  my methods ->
#define your  thy methods ->

#define forget(thing)  _Thing_forget ((Thing *) & (thing))
/*
	Function:
		free all memory associated with 'thing'.
	Postconditions:
		thing == NULL;
*/

/* All functions with 'I' as the first argument assume that it is not NULL. */

char * Thing_className (I);
wchar_t * Thing_classNameW (I);
/* Return your class name. */

int Thing_member (I, void *klas);
/*
	return TRUE if you are a 'klas',
	i.e., if you are an object of the class 'klas' or of one of the classes derived from 'klas'.
	E.g., Thing_member (object, classThing) will always return TRUE.
*/

int Thing_subclass (void *klas, void *ancestor);
/*
	return TRUE if <klas> is a subclass of <ancestor>,
	i.e., if <klas> equals <ancestor>, or if the parent class of <klas> is a subclass of <ancestor>.
	E.g., Thing_subclass (classX, classThing) will always return TRUE.
*/

void Thing_info (I);

#define new(klas)  (klas) Thing_new ((void *) class##klas)
/*
	Function:
		return a new object of class 'klas'.
	Postconditions:
		result -> methods == class'klas';
		other members are 0;
		result -> methods -> destroy != NULL;   // Class table initialized.
*/

Any Thing_new (void *klas);
/*
	Function:
		return a new object of class 'klas'.
	Postconditions:
		result -> methods == 'klas';
		other members are 0;
		result -> methods -> destroy != NULL;   // Class table initialized.
*/

void Thing_recognizeClassesByName (void *readableClass, ...);
/*
	Function:
		make Thing_classFromClassName () and Thing_newFromClassName ()
		recognize a class from its name (a string).
	Arguments:
		as many classes as you want; finish with a NULL.
		It is not an error if a class occurs more than once in the list.
	Behaviour:
		calling this routine more than once, each time for different classes,
		has the same result as calling it once for all these classes together.
		Thing can remember up to 1000 string-readable classes.
	Usage:
		you should call this routine for all classes that you want to read by name,
		e.g., with Data_readFromTextFile () or Data_readFromBinaryFile (),
		or with Data_readText () or Data_readBinary () if the object is a Collection.
		Calls to this routine should preferably be put in the beginning of main ().
*/
void Thing_recognizeClassByOtherName (void *readableClass, const char *otherName);

Any Thing_newFromClassName (const char *className);
Any Thing_newFromClassNameW (const wchar_t *className);
/*
	Function:
		return a new object of class 'className', or NULL if the class name is not recognized.
	Postconditions:
		result -> methods == class'className';
		other members are 0;
		class'className' -> destroy != NULL;   // class'className' has been initialized.
	Side effect:
		see Thing_classFromClassName.
*/

void *Thing_classFromClassName (const char *className);
void *Thing_classFromClassNameW (const wchar_t *className);
/*
	Function:
		Return the class table of class 'className', or NULL if it is not recognized.
		E.g. the value returned from Thing_classFromClassName ("PietjePuk")
		will be equal to classPietjePuk.
	Postcondition:
		class'className' -> destroy != NULL;   // class'className' has been initialized.
	Side effect:
		Sets the global variable Thing_version.
		If 'className' equals "PietjePuk 300", the value returned will be classPietjePuk,
		and Thing_version will be set to 300.
*/

char * Thing_getName (I);
wchar_t * Thing_getNameW (I);
/* Return a pointer to your internal name (which can be NULL). */

void Thing_setName (I, const char *name);
void Thing_setNameW (I, const wchar_t *name);
/*
	Function:
		remember that you are called 'name'.
	Postconditions:
		my name *and* my nameW are copies of 'name'.
*/

void Thing_overrideClass (I, void *klas);
/*
	Function:
		change my class to 'klas'.
	Postconditions:
		my methods == klas;
		klas -> destroy != NULL;   // 'klas' has been initialized.
	Usage:
		- Safe typecast if my methods is a subclass of 'klas',
			in which case you can also safely use "my methods = klas".
		- Safe typecast if 'klas' is a dummy subclass of my methods,
			i.e., if 'klas' does not add members or methods (so this is just a name change);
			in this case, you cannot just use "my methods = klas" if you are not sure whether
			'klas' has been initialized (by a previous 'new' or so).
			An application of this is giving a collection of objects of class "Foo"
			the name "Foos" instead of "Collection".
		- Unsafe in all other situations. Normally, 'I' should contain the members and methods of 'klas',
			perhaps with different names.
*/

void Thing_swap (I, thou);
/*
	Function:
		Swap my and thy contents.
	Precondition:
		my methods == thy methods;
	Postconditions:
		my xxx == thy old xxx;
		thy xxx == my old xxx;
	Usage:
		Swap two objects without changing any references to them.
*/

#define inherited(klas)  class##klas -> _parent ->

/* The inheritor should put one of the macros class_create or class_create_opaque */
/* after the definitions of the members and methods. */
/* There are two cases: */
/* 1. The declaration of the class members should be visible to the user. */
/*    In this case, use class_create in the klas.h header file. */
/* 2. The declaration of the class members should be opaque to the user, */
/*    but visible to the inheritor. */
/*    In this case, put the statement "typedef struct klas *klas;" in klas.h, */
/*    and use class_create_opaque in the klasP.h header file */
/*    (or in klas.c if there will not be any inheritors). */

#define class_create_opaque(klas,parentKlas) \
	typedef struct struct##klas##_Table *klas##_Table; \
	struct struct##klas##_Table { \
		void (* _initialize) (void *table); \
		char *_className; \
		wchar_t *_classNameW; \
		parentKlas##_Table	_parent; \
		long _size; \
		klas##_methods \
	}; \
	struct struct##klas { \
		klas##_Table methods; \
		klas##_members \
	}; \
	extern struct struct##klas##_Table theStruct##klas; \
	extern klas##_Table class##klas

#define class_create(klas,parentKlas) \
	typedef struct struct##klas *klas; \
	class_create_opaque (klas, parentKlas)

/* For klas.c, after the definitions of the methods. */

#define class_methods(klas,parentKlas) \
	static void _##klas##_initialize (void *table);   /* Forward declaration. */ \
	struct struct##klas##_Table theStruct##klas = { \
		_##klas##_initialize, #klas, L"" #klas,   /* Partial initialization because init and */ \
		& theStruct##parentKlas, sizeof (struct struct##klas) };   /* parent must be known. */ \
	klas##_Table class##klas = & theStruct##klas; \
	static void _##klas##_initialize (void *table) { \
		klas##_Table us = (klas##_Table) table; \
		if (! class##parentKlas -> destroy)   /* Parent class not initialized? */ \
			class##parentKlas -> _initialize (class##parentKlas); \
		class##parentKlas -> _initialize (us);   /* Inherit methods from parent class. */
#define class_method(method)  us -> method = method;   /* Override one method. */
#define class_method_local(klas,method)  us -> method = class##klas##_##method;
#define class_methods_end  }

/* For the inheritors. */

#define Thing_members \
	char *name; \
	wchar_t *nameW;
#define Thing_methods \
	long version; \
	void (*destroy) (I); \
	void (*info) (I); \
	void (*nameChanged) (I);
class_create (Thing, Thing);   /* Root class: no parent. */

/*
	Methods:

	void destroy (I)
		Message sent by _Thing_forget:
			destroy all of my members who are arrays or objects,
			except those who are NULL already (always check).
		Inheritor:
			Use NUMxvector_free and NUMxmatrix_free for destroying arrays;
			you do not have to set the array members to NULL.
			Use 'forget' for destroying objects.
			You can call the inherited 'destroy' last, for destroying the inherited arrays and objects.
		Example:
			iam (Miep);
			NUMfvector_free (my array);
			forget (my object);
			inherited (Miep) destroy (me);
		Thing::destroy does nothing.
		After exit:
			the memory associated with me will be freed,
			and one pointer to it will be set to NULL (see 'forget').

	void info (I)
		Message sent by Thing_info:
			use a sequence of MelderInfo_writeXXX to give some information about you;
			these are often preceded by classData -> info (me).
		Thing::info shows my class name.

	void nameChanged (I)
		Message sent by Thing_setName after setting the new name:
			if you are capable of showing your name, show your new name.
		Thing::nameChanged does nothing.
*/

/* For the macros. */

void _Thing_forget (Thing *me);
	/* Macro 'forget'. */
void * _Thing_check (I, void *table, const char *fileName, int line);
	/* Macros 'iam', 'thouart', 'heis'. */

/* For debugging. */

long Thing_getTotalNumberOfThings (void);
/* This number is 0 initially, increments at every successful `new', and decrements at every `forget'. */

extern long Thing_version;
/* Set by Thing_classFromClassName. */

/* End of file Thing.h */
#endif
