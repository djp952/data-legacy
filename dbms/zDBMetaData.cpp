//---------------------------------------------------------------------------
// zDBMetaData Implementation
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#include "stdafx.h"					// Include project pre-compiled headers
#include "zDBMetaData.h"			// Include zDBMetaData declarations
#include "zDBConnection.h"			// Include zDBConnection declarations

#pragma warning(push, 4)			// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// zDBMetaData::Generate (static)
//
// Generates the requested database metadata for a zDBConnection
//
// Arguments:
//
//	conn		- zDBConnection requesting a metadata generation
//	schema		- Name of the schema to generate metadata for
//	args		- Arguments (restrictions) for the specified schema

DataTable^ zDBMetaData::Generate(zDBConnection^ conn, String^ schema, array<String^>^ args)
{
	if(conn == nullptr) throw gcnew ArgumentException();
	zDBUtil::CheckConnectionReady(conn);

	// The default schema set is the "MetaDataCollection", and the default arguments,
	// or restrictions if you prefer, is an empty array of strings

	if(schema == nullptr) schema = DbMetaDataCollectionNames::MetaDataCollections;
	if(args == nullptr) args = gcnew array<String^>(0);

	// Common: MetaDataCollections
	if(String::Compare(schema, DbMetaDataCollectionNames::MetaDataCollections, true) == 0)
		return s_metadata->Tables[DbMetaDataCollectionNames::MetaDataCollections]->Copy();

	// Common: DataSourceInformation
	else if(String::Compare(schema, DbMetaDataCollectionNames::DataSourceInformation, true) == 0)
		return s_metadata->Tables[DbMetaDataCollectionNames::DataSourceInformation]->Copy();

	// Common: DataTypes
	else if(String::Compare(schema, DbMetaDataCollectionNames::DataTypes, true) == 0)
		return s_metadata->Tables[DbMetaDataCollectionNames::DataTypes]->Copy();

	// Common: Restrictions
	else if(String::Compare(schema, DbMetaDataCollectionNames::Restrictions, true) == 0)
		return s_metadata->Tables[DbMetaDataCollectionNames::Restrictions]->Copy();

	// Common: ReservedWords
	else if(String::Compare(schema, DbMetaDataCollectionNames::ReservedWords, true) == 0)
		return s_metadata->Tables[DbMetaDataCollectionNames::ReservedWords]->Copy();

	// Anything else we don't understand generates an ArgumentException ...

	else throw gcnew ArgumentException(String::Format("The requested collection ({0}) "
		"is not defined.", schema));
}

//---------------------------------------------------------------------------
// zDBMetaData::LoadEmbeddedMetaData (private, static)
//
// Loads the embedded DataSet that contains all of the static metadata
//
// Arguments:
//
//	NONE

DataSet^ zDBMetaData::LoadEmbeddedMetaData(void)
{
	Assembly^			assembly;				// This assembly reference
	Stream^				schema = nullptr;		// The DataSet schema
	Stream^				data = nullptr;			// The DataSet data
	DataSet^			metadata;				// The generated DataSet

	assembly = zDBMetaData::typeid->Assembly;	// Grab the assembly reference
	
	try {
		
		// Acquire references to both the schema as well as the data resources.  They
		// were broken up so the VS XML editor could be used to work on the data as needed

		schema = assembly->GetManifestResourceStream(zDBMetaData::typeid, METADATA_XSD_RESOURCE);
		if(schema == nullptr) throw gcnew Exception("INTERNAL FAILURE: Cannot load embedded resource");

		data = assembly->GetManifestResourceStream(zDBMetaData::typeid, METADATA_XML_RESOURCE);
		if(data == nullptr) throw gcnew Exception("INTERNAL FAILURE: Cannot load embedded resource");

		metadata = gcnew DataSet();				// Create the new data set
		metadata->ReadXmlSchema(schema);		// Apply the embedded XML schema
		metadata->ReadXml(data);				// Apply the embedded XML data		
		return metadata;						// Return the completed data set
	}

	finally { 

		if(data != nullptr) delete data;		// Dispose of the stream
		if(schema != nullptr) delete schema;	// Dispose of the stream
	}
}

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)
