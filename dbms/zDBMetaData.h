//---------------------------------------------------------------------------
// zDBMetaData Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBMETADATA_H_
#define __ZDBMETADATA_H_
#pragma once

#include "zDBConstants.h"				// Include zDB constant declarations
#include "zDBUtil.h"					// Include zDBUtil declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Data;
using namespace System::Data::Common;
using namespace System::IO;
using namespace System::Reflection;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Forward Class Declarations
//---------------------------------------------------------------------------

ref class zDBConnection;				// zDBConnection.h

//---------------------------------------------------------------------------
// Class zDBMetaData (static, internal)
//
// zDBMetaData implements all of the nastiness that has to occur behind the
// scenes to generate the information returned by zDBConnection.GetSchema.
//---------------------------------------------------------------------------

ref class zDBMetaData abstract sealed
{
public:

	//-----------------------------------------------------------------------
	// Member Functions

	// Generate
	//
	// Generates the database metadata information for the specified collection
	// and list of restrictions.  See DbConnection::GetSchema() in MSDN
	static DataTable^ Generate(zDBConnection^ conn, String^ schema, array<String^>^ args);

private:

	// STATIC CONSTRUCTOR
	static zDBMetaData()
	{
		s_metadata = LoadEmbeddedMetaData();	// Load the static metadata
		
		// Change the SQLite engine version number immediately after the data is loaded
		// so we don't have to worry about doing it each time the table is copied

		DataTable^ dt = s_metadata->Tables[DbMetaDataCollectionNames::DataSourceInformation];
		dt->Rows[0][DbMetaDataColumnNames::DataSourceProductVersion] = SQLITE_VERSION;
		dt->Rows[0][DbMetaDataColumnNames::DataSourceProductVersionNormalized] = SQLITE_VERSION_NUMBER;
	}

	//-----------------------------------------------------------------------
	// Private Constants

	// METADATA_XSD_RESOURCE
	// METADATA_XML_RESOURCE
	//
	// Defines the names of the embedded metadata information.  Prefix these
	// with the proper namespace in order to load them from the assembly
	static initonly String^ METADATA_XSD_RESOURCE = "metadata.xsd";
	static initonly String^ METADATA_XML_RESOURCE = "metadata.xml";

	//-----------------------------------------------------------------------
	// Private Member Functions

	static DataSet^ LoadEmbeddedMetaData(void);

	//-----------------------------------------------------------------------
	// Member Variables

	static DataSet^			s_metadata;		// Cached metadata data set
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBMETADATA_H_