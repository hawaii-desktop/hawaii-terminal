/*
 * Copyright (C) 2014 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author : Arto Jalkanen <ajalkane@gmail.com>
 */

#ifndef PAMAUTHENTICATION_H
#define PAMAUTHENTICATION_H

#include <QObject>
#include <QAbstractListModel>
#include <QStandardPaths>
#include <QSettings>

// Forward declarations
struct pam_handle;
struct pam_message;
struct pam_response;

// TODO: documentation
class PamAuthentication : public QObject
{
    Q_OBJECT

public:
    explicit PamAuthentication(QObject *parent = 0);
    ~PamAuthentication();

    Q_INVOKABLE bool requireAuthentication();

    Q_INVOKABLE bool validatePasswordToken(const QString &token);

    Q_PROPERTY(QString serviceName READ serviceName WRITE setServiceName NOTIFY serviceNameChanged)
    inline const QString &serviceName() const {
        return m_serviceName;
    }

    void setServiceName(const QString &serviceName);
signals:
    void serviceNameChanged();

public slots:
private:
    static int ConversationFunction(int num_msg,
                                    const pam_message** msg,
                                    pam_response** resp,
                                    void* appdata_ptr);

    bool initPam(pam_handle **pamHandle);
    int validateAccount(pam_handle *pamHandle);

    QString m_passwordToken;
    QString m_serviceName;
    QString m_userLogin;
};

#endif // PAMAUTHENTICATION_H



