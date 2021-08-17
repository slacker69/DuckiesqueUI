#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocale>
#include <QTimer>
#include <QTimeLine>
#include <QMutex>
#include <QHash>
#include <QFileDialog>
#include <QFileInfo>
#include <QActionGroup>
#include <QTextCodec>
#include <QMessageBox>
#include <QStandardPaths>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QStringListIterator>

#include <cmath>

#include "Programmer.h"

#if defined(Q_OS_LINUX)
#include "TypeWriterLinux.h"
#elif defined(Q_OS_MACOS)
#include "TypeWriterMacOS.h"
#elif defined(Q_OS_WINDOWS)
#include "TypeWriterWindows.h"
#endif

#include "var.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionExport_triggered();
    void on_actionRun_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_pushButtonExec_clicked();
    void highlight();

    void on_actionDefault_triggered();
    void on_actionbe_triggered();
    void on_actionbr_triggered();
    void on_actionca_triggered();
    void on_actionch_triggered();
    void on_actionde_triggered();
    void on_actiondk_triggered();
    void on_actiones_triggered();
    void on_actionfi_triggered();
    void on_actionfr_triggered();
    void on_actiongb_triggered();
    void on_actionhr_triggered();
    void on_actionit_triggered();
    void on_actionno_triggered();
    void on_actionpl_windows_triggered();
    void on_actionpl_linux_triggered();
    void on_actionpt_triggered();
    void on_actionru_triggered();
    void on_actionsi_triggered();
    void on_actionsv_triggered();
    void on_actiontr_triggered();
    void on_actionus_triggered();
    void on_actionProgrammer_triggered();
    void on_actionList_Functions_triggered();
    void timeline_slot(quint64 value);
    void timeline_finished();

    void on_listWidgetWindows_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidgetMac_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidgetLinux_itemDoubleClicked(QListWidgetItem *item);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init_props(int locale);
    void loadOpenFile(QString filename);
    bool c2a(QStringList *out, QChar c);
    bool k2b(QByteArray *out, QString key);
    bool c2b(QByteArray *out, bool *parity, QChar c);
    bool c2w(QByteArray *out, QString str);
    bool c2wa(QList<QStringList> *out, QString str);
    bool single_inst(quint8 *out, QString in);
    bool name_convert(QString *out, QString in);
    bool parse_bin_exec(quint64 *rel_stamp, QByteArray *out);
    void order_keypress_combination(QStringList *list);
    bool is_mod(QString in);
    Ui::MainWindow *ui;
    int mainlist_count = 0;

#if defined(Q_OS_LINUX)
    TypeWriterLinux *typewriter;
#elif defined(Q_OS_MACOS)
    TypeWriterMacOS *typewriter;
#elif defined(Q_OS_WINDOWS)
    TypeWriterWindows *typewriter;
#endif

    QTimeLine *timeline;
    QMutex mutex;

    QActionGroup *actionGroup;
    bool errors_found = false;
    QString savefile;
    QList<QPair<QString, QString> > main_sequence;
    QMap<quint64, QStringList> main_seq_indexed;
    QStringList cmd_list;
    QHash<QString, quint32> keyprops;
    QHash<QString, QStringList> layprops;
    QMap<QString, QString> scripts_map_win;
    QStringList scripts_list_win;
    QMap<QString, QString> scripts_map_mac;
    QStringList scripts_list_mac;
    QMap<QString, QString> scripts_map_linux;
    QStringList scripts_list_linux;

    Programmer *p = nullptr;
};
#endif // MAINWINDOW_H
