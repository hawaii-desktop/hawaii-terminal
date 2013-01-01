/****************************************************************************
 * This file is part of Terminal.
 *
 * Copyright (C) 2010-2012 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QCoreApplication>
#include <QDebug>
#include <QLibraryInfo>
#include <QStandardPaths>
#include <QTranslator>

#include <VibeCore/VSettings>
#include <VAboutDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lib/qtermwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_translator(0)
{
    ui->setupUi(this);

    // Load translations
    loadTranslations();

    // Settings
    m_settings = new VSettings("org.hawaii.desktop");
    connect(m_settings, SIGNAL(changed()),
            this, SLOT(settingsChanged()));

    // Connect signals
    connect(ui->actionNewTab, SIGNAL(triggered()),
            this, SLOT(slotNewTab()));
    connect(ui->actionNewWindow, SIGNAL(triggered()),
            this, SLOT(slotNewWindow()));
    connect(ui->actionCloseTab, SIGNAL(triggered()),
            this, SLOT(slotCloseCurrentTab()));
    connect(ui->actionOpenFileManager, SIGNAL(triggered()),
            this, SLOT(slotOpenFileManager()));
    connect(ui->actionQuit, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(ui->actionCopy, SIGNAL(triggered()),
            this, SLOT(slotCopy()));
    connect(ui->actionPaste, SIGNAL(triggered()),
            this, SLOT(slotPaste()));
    connect(ui->actionFind, SIGNAL(triggered()),
            this, SLOT(slotFind()));
    connect(ui->actionAbout, SIGNAL(triggered()),
            this, SLOT(slotAbout()));
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(slotCloseTab(int)));

    // Start with a tab
    slotNewTab();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_settings;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);

    switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            loadTranslations();
            break;
        case QEvent::LocaleChange:
            loadTranslations();
            break;
        default:
            break;
    }
}

void MainWindow::loadTranslations()
{
    // Locale name
    const QString locale = QLocale::system().name();

    // Qt translations
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + locale,
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QCoreApplication::instance()->installTranslator(&qtTranslator);

    // Remove translation of the previously loaded locale
    if (m_translator) {
        QCoreApplication::instance()->removeTranslator(m_translator);
        delete m_translator;
    }

    // Load our translations for the current locale
    m_translator = new QTranslator(this);
    QString localeDir = QStandardPaths::locate(
                            QStandardPaths::GenericDataLocation,
                            QLatin1String("hawaii-terminal/translations"),
                            QStandardPaths::LocateDirectory);
    m_translator->load(locale, localeDir);
    QCoreApplication::instance()->installTranslator(m_translator);
}

void MainWindow::settingsChanged()
{
    for (int i = 0; i < ui->tabWidget->count(); i++) {
        QWidget *widget = ui->tabWidget->widget(i);
        QTermWidget *console = qobject_cast<QTermWidget *>(widget);
        if (console) {
            QFont font(m_settings->value("interface/monospace-font-name").toString());
            font.setPointSize(m_settings->value("interface/monospace-font-size").toInt());
            console->setTerminalFont(font);
        }
    }
}

void MainWindow::slotNewTab()
{
    QFont font(m_settings->value("interface/monospace-font-name").toString());
    font.setPointSize(m_settings->value("interface/monospace-font-size").toInt());

    QTermWidget *console = new QTermWidget();
    console->setTerminalFont(font);
    console->setColorScheme("WhiteOnBlack");
    console->setKeyBindings("linux");
    console->setScrollBarPosition(QTermWidget::ScrollBarRight);

    ui->tabWidget->addTab(console, "Shell");
    ui->tabWidget->setCurrentWidget(console);
    console->setFocus();

    connect(console, SIGNAL(finished()),
            this, SLOT(slotCloseCurrentTab()));
}

void MainWindow::slotNewWindow()
{
    MainWindow *newWindow = new MainWindow();
    newWindow->show();
}

void MainWindow::slotOpenFileManager()
{
}

void MainWindow::slotCloseCurrentTab()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());

    if (ui->tabWidget->count() == 0)
        close();
}

void MainWindow::slotCopy()
{
    QTermWidget *console =
        qobject_cast<QTermWidget *>(ui->tabWidget->currentWidget());
    console->copyClipboard();
}

void MainWindow::slotPaste()
{
    QTermWidget *console =
        qobject_cast<QTermWidget *>(ui->tabWidget->currentWidget());
    console->pasteClipboard();
}

void MainWindow::slotFind()
{
    QTermWidget *console =
        qobject_cast<QTermWidget *>(ui->tabWidget->currentWidget());
}

void MainWindow::slotCloseTab(int index)
{
    ui->tabWidget->removeTab(index);

    if (ui->tabWidget->count() == 0)
        close();
}

void MainWindow::slotAbout()
{
    QStringList authors;
    authors << "Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>";

    VAboutDialog dialog(this);
    dialog.setAuthors(authors);
    dialog.setCopyright("Pier Luigi Fiorini");
    dialog.setDescription("Hawaii Terminal Emulator.");
    dialog.setLink(QUrl("http://www.maui-project.org/"));

    QFile licenseFile(":/COPYING");
    if (licenseFile.open(QIODevice::ReadOnly)) {
        dialog.setLicenseText(licenseFile.readAll());
        licenseFile.close();
    }

    dialog.exec();
}

#include "moc_mainwindow.cpp"
