//---------------------------------------------------------------------------
// zDBConstants.h
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBCONSTANTS_H_
#define __ZDBCONSTANTS_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBDataSource
//
// Provides a list of constants for use with the Data Source= connection
// string property.  Pretty short list, too ..
//---------------------------------------------------------------------------

public ref struct zDBDataSource abstract sealed
{
	static initonly String^	Memory = ":memory:";
};

//---------------------------------------------------------------------------
// Class zDBMetaDataCollectionNames
//
// Provides a list of constants for all of the provider specific metadata
// collection names accessible from zDBConnection::GetSchema
//---------------------------------------------------------------------------

public ref struct zDBMetaDataCollectionNames abstract sealed
{
	static initonly String^		Collations			= "Collations";
	static initonly String^		Columns				= "Columns";
	static initonly String^		Databases			= "Databases";
	static initonly String^		ForeignKeys			= "ForeignKeys";
	static initonly String^		Indexes				= "Indexes";
	static initonly String^		IndexColumns		= "IndexColumns";
	static initonly String^		Tables				= "Tables";
	static initonly String^		Triggers			= "Triggers";
	static initonly String^		Views				= "Views";
	static initonly String^		ViewColumns			= "ViewColumns";
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __ZDBCONSTANTS_H_
