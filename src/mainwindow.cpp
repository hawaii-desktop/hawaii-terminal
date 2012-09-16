/****************************************************************************
 * This file is part of Terminal
 *
 * Copyright (c) 2010-2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Terminal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Terminal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Terminal.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lib/qtermwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(slotCloseTab(int)));

    // Start with a tab
    slotNewTab();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);

    switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void MainWindow::slotNewTab()
{
    QFont font("Monospace", 12);

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

    qDebug() << "* INFO *************************";
    qDebug() << " availableKeyBindings:" << console->availableKeyBindings();
    qDebug() << " keyBindings:" << console->keyBindings();
    qDebug() << " availableColorSchemes:" << console->availableColorSchemes();
    qDebug() << "* INFO END *********************";
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

#include "moc_mainwindow.cpp"
