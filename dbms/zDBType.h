//---------------------------------------------------------------------------
// zDBType Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBTYPE_H_
#define __ZDBTYPE_H_
#pragma once

#include "zDBEnumerations.h"			// Include zDB enumeration decls

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Data;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBType
//
// Defines the zDB specific data types of a field, property or parameter.
// Also provides a means to convert to and from a standard DbType code.  I
// changed this from a simple enum to group the conversions along with it.
//---------------------------------------------------------------------------

public value class zDBType
{
public:

	//-----------------------------------------------------------------------
	// Overloaded Operators

	bool operator ==(zDBType rhs) { return rhs.m_code == this->m_code; }
	bool operator !=(zDBType rhs) { return rhs.m_code != this->m_code; }

	//-----------------------------------------------------------------------
	// Member Functions

	// FromDbType
	//
	// Converts a DbType code into a zDBType code
	static zDBType FromDbType(DbType dbtype);

	// ToDbType
	//
	// Converts this zDBType into a DbType. If the Object^ overload is used,
	// a "best fit" representation for the object passed will be generated
	DbType ToDbType(void) { return ToDbType(nullptr); }
	DbType ToDbType(Object^ value);

	//-----------------------------------------------------------------------
	// Fields

	static initonly zDBType Binary		= zDBType(zDBTypeCode::Binary);
	static initonly zDBType Boolean		= zDBType(zDBTypeCode::Boolean);
	static initonly zDBType DateTime	= zDBType(zDBTypeCode::DateTime);
	static initonly zDBType Float		= zDBType(zDBTypeCode::Float);
	static initonly zDBType Guid		= zDBType(zDBTypeCode::Guid);
	static initonly zDBType Integer		= zDBType(zDBTypeCode::Integer);
	static initonly zDBType Long		= zDBType(zDBTypeCode::Long);
	static initonly zDBType Null		= zDBType(zDBTypeCode::Null);
	static initonly zDBType String		= zDBType(zDBTypeCode::String);

internal:

	//-----------------------------------------------------------------------
	// Internal Member Functions

	// FromType
	//
	// Converts from a Type^ reference into a zDBType
	static zDBType FromType(Type^ type);

	//-----------------------------------------------------------------------
	// Internal Properties

	// Value
	//
	// Gets the underlying zDBTypeCode value
	property zDBTypeCode Value { zDBTypeCode get(void) { return m_code; } }

	//-----------------------------------------------------------------------
	// Internal Fields

	// Auto
	//
	// Used by zDBParameter to indicate an auto-detect data type
	static initonly zDBType Auto = zDBType(zDBTypeCode::Auto);

private:

	// PRIVATE CONSTRUCTOR
	zDBType(zDBTypeCode code) : m_code(code) {}

	//-----------------------------------------------------------------------
	// Member Variables
	
	initonly zDBTypeCode		m_code;			// The underlying type code
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBTYPE_H_