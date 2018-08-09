#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

class QProcess;
class QPushButton;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);

private:
	QProcess *m_directShell;
	QPushButton *m_btnSend;

private slots:
	void onSend();
	void onStateChanged(QProcess::ProcessState state);
	void onReadyRead();
	void onFinished(int exitCode, QProcess::ExitStatus exitStatus);
	void onError(QProcess::ProcessError error);
};

#endif // MAINWINDOW_H
