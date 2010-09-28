/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (ivan.frade@nokia.com)
**
** This file is part of the QtSparql module (not yet part of the Qt Toolkit).
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at ivan.frade@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSPARQL_TRACKER_SIGNALS_H
#define QSPARQL_TRACKER_SIGNALS_H

#include <QObject>

#ifdef QT_PLUGIN
#define Q_EXPORT_SPARQLDRIVER_TRACKER
#else
#define Q_EXPORT_SPARQLDRIVER_TRACKER Q_SPARQL_EXPORT
#endif

class QTrackerChangeNotifierPrivate;

class Q_EXPORT_SPARQLDRIVER_TRACKER QTrackerChangeNotifier : public QObject
{
    Q_OBJECT
public:
    struct Quad
    {
        int graph, subject, predicate, object;
    };
    QTrackerChangeNotifier(const QString& className,
                           QObject* parent = 0);
    ~QTrackerChangeNotifier();
    QString watchedClass() const;
signals:
    /// Emitted when tracker signals that triples have been deleted or inserted.
    /// \a deletes is the list of deleted triples, \a inserts is the list of
    /// inserted triples. The lists contain \a Quad objects, and each Quad
    /// object contains the tracker id's of a triple. If the object of the
    /// triple is a literal, the corresponding Quad will contain 0 as its
    /// object.
    void changed(QList<QTrackerChangeNotifier::Quad> deletes,
                 QList<QTrackerChangeNotifier::Quad> inserts);
private:
    QTrackerChangeNotifierPrivate* d;
    friend class QTrackerChangeNotifierPrivate;
};

#ifndef QT_NO_DEBUG_STREAM
Q_EXPORT_SPARQLDRIVER_TRACKER QDebug operator<<(QDebug, const QTrackerChangeNotifier::Quad &);
#endif

QT_END_NAMESPACE

QT_END_HEADER

#endif // QSPARQL_TRACKER_SIGNALS_H
