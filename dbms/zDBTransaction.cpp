//---------------------------------------------------------------------------
// zDBTransaction Implementation
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#include "stdafx.h"					// Include project pre-compiled headers
#include "zDBTransaction.h"			// Include zDBTransaction declarations
#include "zDBConnection.h"			// Include zDBConnection declarations

#pragma warning(push, 4)			// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// zDBTransaction Constructor
//
// Arguments:
//
//	conn		- Parent zDBConnection object instance

zDBTransaction::zDBTransaction(zDBConnection^ conn) : m_conn(conn) {}

//---------------------------------------------------------------------------
// zDBTransaction Destructor

zDBTransaction::~zDBTransaction()
{
	if(!m_closed) Rollback();			// Rollback on disposal
	m_disposed = true;					// Object is now disposed of
}

//---------------------------------------------------------------------------
// zDBTransaction::Commit
//
// Commits this outstanding transaction
//
// Arguments:
//
//	NONE

void zDBTransaction::Commit(void)
{
	CHECK_DISPOSED(m_disposed);
	zDBUtil::CheckConnectionValid(m_conn);
	if(m_closed) throw gcnew InvalidOperationException();

	m_conn->CommitTransaction(this);		// Commit the transaction
	m_closed = true;						// We're done now
}

//---------------------------------------------------------------------------
// zDBTransaction::Connection::get
//
// Gets a reference to the connection that owns this transaction

zDBConnection^ zDBTransaction::Connection::get(void)
{
	CHECK_DISPOSED(m_disposed);
	return m_conn;
}

//---------------------------------------------------------------------------
// zDBTransaction::DbConnection::get (protected)
//
// Gets a reference to the connection that owns this transaction, on it's
// generic interface

DbConnection^ zDBTransaction::DbConnection::get(void)
{
	CHECK_DISPOSED(m_disposed);
	return m_conn;
}

//---------------------------------------------------------------------------
// zDBTransaction::IsolationLevel::get
//
// Returns the isolation level of the transaction.  Not supported in SQLite

Data::IsolationLevel zDBTransaction::IsolationLevel::get(void)
{
	CHECK_DISPOSED(m_disposed);
	return Data::IsolationLevel::Unspecified;
}

//---------------------------------------------------------------------------
// zDBTransaction::Rollback
//
// Rolls back this outstanding transaction
//
// Arguments:
//
//	NONE

void zDBTransaction::Rollback(void)
{
	CHECK_DISPOSED(m_disposed);
	zDBUtil::CheckConnectionValid(m_conn);
	if(m_closed) throw gcnew InvalidOperationException();

	m_conn->RollbackTransaction(this);		// Roll back the transaction
	m_closed = true;						// We're done now
}

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)
