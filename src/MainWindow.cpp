#include "MainWindow.h"
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	m_directShell(new QProcess(this)),
	m_btnSend(new QPushButton(tr("Send"), this))
{
	m_btnSend->setDisabled(true);
	setCentralWidget(m_btnSend);

	connect(m_btnSend, &QPushButton::clicked, this, &MainWindow::onSend);
	connect(m_directShell, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &MainWindow::onFinished);
	connect(m_directShell, &QProcess::stateChanged, this, &MainWindow::onStateChanged);
	connect(m_directShell, &QProcess::readyRead, this, &MainWindow::onReadyRead);
	connect(m_directShell, &QProcess::errorOccurred, this, &MainWindow::onError);

	m_directShell->start("adb.exe shell");
}

void MainWindow::onSend()
{
	qDebug() << m_directShell->write("ls\r\n");
}

void MainWindow::onStateChanged(QProcess::ProcessState state)
{
	qDebug() << state;

	if (state == QProcess::Running) {
		qDebug() << "started";
		m_btnSend->setEnabled(true);
	}
}

void MainWindow::onReadyRead()
{
	qDebug() << m_directShell->readAllStandardOutput();
}

void MainWindow::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	qDebug() << exitCode << exitStatus;
}

void MainWindow::onError(QProcess::ProcessError error)
{
	qDebug() << error;
}
