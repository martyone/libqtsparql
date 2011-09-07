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

#ifndef QSPARQL_TRACKER_DIRECT_RESULT_P_H
#define QSPARQL_TRACKER_DIRECT_RESULT_P_H

#include <QtSparql/qsparqlresult.h>
#include <QtSparql/qsparqlqueryoptions.h>
#include <QtCore/qrunnable.h>
#include <QtCore/qthreadpool.h>
#include <QtCore/qsemaphore.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QTrackerDirectDriverPrivate;
class QTrackerDirectQueryRunner;

class QTrackerDirectResult : public QSparqlResult
{
    Q_OBJECT
    friend class QTrackerDirectQueryRunner;
public:
    QTrackerDirectResult(const QSparqlQueryOptions& options);
    ~QTrackerDirectResult();

    virtual bool isFinished() const;
    QSparqlQueryOptions options;
private:
    // Will be called by the query runner to execute the query, results that don't
    // need a thread to run in (sync) do not need to implement this
    virtual void run() {}
    virtual void stopAndWait() = 0;

protected:
    QTrackerDirectDriverPrivate *driverPrivate;
    QAtomicInt resultFinished;
    QTrackerDirectQueryRunner *queryRunner;

public Q_SLOTS:
    virtual void exec() = 0;
    void driverClosing();

};

class QTrackerDirectQueryRunner : public QRunnable
{
public:
    QTrackerDirectResult *result;
    QAtomicInt runFinished;
    QSemaphore runSemaphore;
    bool started;

    QTrackerDirectQueryRunner(QTrackerDirectResult *result);
    void runOrWait();
    void queue(QThreadPool& threadPool);
    void wait();

private:
    void run();
    bool acquireRunSemaphore();

};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QSPARQL_TRACKER_DIRECT_RESULT_P_H
