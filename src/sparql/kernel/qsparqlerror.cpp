/****************************************************************************
**
** Copyright (C) 2010-2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (ivan.frade@nokia.com)
**
** This file is part of the QtSparql module (not yet part of the Qt Toolkit).
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at ivan.frade@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qsparqlerror.h"
#include "qdebug.h"

QT_BEGIN_NAMESPACE

#ifndef QT_NO_DEBUG_STREAM
// LCOV_EXCL_START
QDebug operator<<(QDebug dbg, const QSparqlError &s)
{
    dbg.nospace() << "QSparqlError(" << s.number() << ", " << s.message() << ", " << s.type() << ")";
    return dbg.space();
}
// LCOV_EXCL_STOP
#endif

/*!
    \class QSparqlError
    \brief The QSparqlError class provides SPARQL error information.

    A QSparqlError object can provide driver-specific error data, including the
    error message(), number() and type(). The functions all have setters so that
    you can create and return QSparqlError objects from your own classes, for
    example from your own SPARQL drivers.

    \sa QSparqlConnection::lastError(), QSparqlResult::lastError()
*/

/*!
    \enum QSparqlError::ErrorType

    This enum type describes the context in which the error occurred.

    \var QSparqlError::ErrorType QSparqlError::NoError

    No error occurred.

    \var QSparqlError::ErrorType QSparqlError::ConnectionError

    Connection error.

    \var QSparqlError::ErrorType QSparqlError::StatementError

    SPARQL statement syntax error.

    \var QSparqlError::ErrorType QSparqlError::TransactionError

    Transaction failed error.

    \var QSparqlError::ErrorType QSparqlError::BackendError

    Other backend-specific error

    \var QSparqlError::ErrorType QSparqlError::UnknownError

    Unknown error.
*/

/*!
    Constructs an error containing the driver error \a message, the
    type \a type and the optional error number \a number.
*/

QSparqlError::QSparqlError(const QString& message,
                           ErrorType type, int number)
    : errorMessage(message), errorType(type), errorNumber(number)
{
}

/*!
    Creates a copy of \a other.
*/
QSparqlError::QSparqlError(const QSparqlError& other)
    : errorMessage(other.errorMessage), errorType(other.errorType),
      errorNumber(other.errorNumber)
{
}

/*!
    Assigns the \a other error's values to this error.
*/

QSparqlError& QSparqlError::operator=(const QSparqlError& other)
{
    errorMessage = other.errorMessage;
    errorType = other.errorType;
    errorNumber = other.errorNumber;
    return *this;
}

/*!
    Destroys the object and frees any allocated resources.
*/

QSparqlError::~QSparqlError()
{
}

/*!
    Sets the error message to the value of \a message.

    \sa message()
*/

void QSparqlError::setMessage(const QString& message)
{
    errorMessage = message;
}

/*!
    Returns the error type, or -1 if the type cannot be determined.

    \sa setType()
*/

QSparqlError::ErrorType QSparqlError::type() const
{
    return errorType;
}

/*!
    Sets the error type to the value of \a type.

    \sa type()
*/

void QSparqlError::setType(ErrorType type)
{
    errorType = type;
}

/*!
    Returns the error message.

    \sa setMessage()
*/

QString QSparqlError::message() const
{
    return errorMessage;
}


/*!
    Returns the connection-specific error number, or -1 if it cannot be
    determined.

    \sa setNumber()
*/

int QSparqlError::number() const
{
    return errorNumber;
}

/*!
    Sets the connection-specific error number to \a number.

    \sa number()
*/

void QSparqlError::setNumber(int number)
{
    errorNumber = number;
}

/*!
    Returns true if an error is set, otherwise false.

    \sa type()
*/
bool QSparqlError::isValid() const
{
    return errorType != NoError;
}

QT_END_NAMESPACE
