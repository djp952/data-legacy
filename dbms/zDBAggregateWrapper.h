//---------------------------------------------------------------------------
// zDBAggregateWrapper Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBAGGREGATEWRAPPER_H_
#define __ZDBAGGREGATEWRAPPER_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBAggregateWrapper (internal)
//
// zDBAggregateWrapper represents a wrapper around a registered aggregate
// class type.  This allows us to associate a SQLite database handle with
// the aggregate so the connection context is known at execution time.
// This kinda slows things down a tad, but it represents a significant
// improvement over my 1.1 provider in that the format of boolean, date,
// and GUID results can be set automatically for the application.
//---------------------------------------------------------------------------

ref class zDBAggregateWrapper
{
public:

	zDBAggregateWrapper(Type^ aggregateType) : m_type(aggregateType) {}

	//-----------------------------------------------------------------------
	// Public Properties

	// AggregateType
	//
	// Gets the type to create an instance of to implement the aggregate
	property Type^ AggregateType { Type^ get(void) { return m_type; } }

	// DatabaseHandle
	//
	// Gets/sets the database handle to associate with this function.  Changes
	// every time the connection is opened or closed, or at least that was the plan
	property sqlite3* DatabaseHandle
	{
		sqlite3* get(void) { return m_hDatabase; }
		void set(sqlite3* value) { m_hDatabase = value; }
	}

private:

	//-----------------------------------------------------------------------
	// Member Variables

	Type^						m_type;			// Aggregate class type
	sqlite3*					m_hDatabase;	// Active database handle
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBAGGREGATEWRAPPER_H_