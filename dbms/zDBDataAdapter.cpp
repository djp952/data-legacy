//---------------------------------------------------------------------------
// zDBDataAdapter Implementation
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#include "stdafx.h"					// Include project pre-compiled headers
#include "zDBDataAdapter.h"			// Include zDBDataAdapter declarations

#pragma warning(push, 4)			// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// zDBDataAdapter Constructor
//
// Arguments:
//
//	NONE

zDBDataAdapter::zDBDataAdapter()
{
	Disposed += gcnew EventHandler(this, &zDBDataAdapter::OnDispose);
}

//---------------------------------------------------------------------------
// zDBDataAdapter Constructor
//
// Arguments:
//
//	command		- zDBCommand instance to apply to SelectCommand

zDBDataAdapter::zDBDataAdapter(zDBCommand^ command)
{
	Disposed += gcnew EventHandler(this, &zDBDataAdapter::OnDispose);
	SelectCommand = command;
}

//---------------------------------------------------------------------------
// zDBDataAdapter Constructor
//
// Arguments:
//
//	commandText		- SQL command to initialize SelectCommand with
//	connection		- zDBConnection instance to use

zDBDataAdapter::zDBDataAdapter(String^ commandText, zDBConnection^ connection)
{
	Disposed += gcnew EventHandler(this, &zDBDataAdapter::OnDispose);
	SelectCommand = gcnew zDBCommand(commandText, connection);
}

//---------------------------------------------------------------------------
// zDBDataAdapter Constructor
//
// Arguments:
//
//	commandText			- SQL command to initialize SelectCommand with
//	connectionString	- Connection string to initialize SelectCommand with

zDBDataAdapter::zDBDataAdapter(String^ commandText, String^ connectionString)
{
	Disposed += gcnew EventHandler(this, &zDBDataAdapter::OnDispose);
	SelectCommand = gcnew zDBCommand(commandText, gcnew zDBConnection(connectionString));
}

//---------------------------------------------------------------------------
// zDBDataAdapter::DeleteCommand::get
//
// Gets a reference to the contained DELETE command object

zDBCommand^ zDBDataAdapter::DeleteCommand::get(void)
{
	CHECK_DISPOSED(m_disposed);
	return m_delete;
}

//---------------------------------------------------------------------------
// zDBDataAdapter::DeleteCommand::set
//
// Changes the contained DELETE command object instance

void zDBDataAdapter::DeleteCommand::set(zDBCommand^ value)
{
	CHECK_DISPOSED(m_disposed);
	m_delete = value;
}

//---------------------------------------------------------------------------
// zDBDataAdapter::InsertCommand::get
//
// Gets a reference to the contained INSERT command object

zDBCommand^ zDBDataAdapter::InsertCommand::get(void)
{
	CHECK_DISPOSED(m_disposed);
	return m_insert;
}

//---------------------------------------------------------------------------
// zDBDataAdapter::InsertCommand::set
//
// Changes the contained INSERT command object instance

void zDBDataAdapter::InsertCommand::set(zDBCommand^ value)
{
	CHECK_DISPOSED(m_disposed);
	m_insert = value;
}

//---------------------------------------------------------------------------
// zDBDataAdapter::SelectCommand::get
//
// Gets a reference to the contained SELECT command object

zDBCommand^ zDBDataAdapter::SelectCommand::get(void)
{
	CHECK_DISPOSED(m_disposed);
	return m_select;
}

//---------------------------------------------------------------------------
// zDBDataAdapter::SelectCommand::set
//
// Changes the contained SELECT command object instance

void zDBDataAdapter::SelectCommand::set(zDBCommand^ value)
{
	CHECK_DISPOSED(m_disposed);
	m_select = value;
}

//---------------------------------------------------------------------------
// zDBDataAdapter::UpdateCommand::get
//
// Gets a reference to the contained UPDATE command object

zDBCommand^ zDBDataAdapter::UpdateCommand::get(void)
{
	CHECK_DISPOSED(m_disposed);
	return m_update;
}

//---------------------------------------------------------------------------
// zDBDataAdapter::UpdateCommand::set
//
// Changes the contained UPDATE command object instance

void zDBDataAdapter::UpdateCommand::set(zDBCommand^ value)
{
	CHECK_DISPOSED(m_disposed);
	m_update = value;
}

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)
