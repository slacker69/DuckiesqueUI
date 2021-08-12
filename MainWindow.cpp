#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plainTextEdit->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    actionGroup = new QActionGroup(this);
    actionGroup->addAction(ui->actionDefault);
    actionGroup->addAction(ui->actionbe);
    actionGroup->addAction(ui->actionbr);
    actionGroup->addAction(ui->actionca);
    actionGroup->addAction(ui->actionch);
    actionGroup->addAction(ui->actionde);
    actionGroup->addAction(ui->actiondk);
    actionGroup->addAction(ui->actiones);
    actionGroup->addAction(ui->actionfi);
    actionGroup->addAction(ui->actionfr);
    actionGroup->addAction(ui->actiongb);
    actionGroup->addAction(ui->actionhr);
    actionGroup->addAction(ui->actionit);
    actionGroup->addAction(ui->actionno);
    actionGroup->addAction(ui->actionpl);
    actionGroup->addAction(ui->actionpt);
    actionGroup->addAction(ui->actionru);
    actionGroup->addAction(ui->actionsi);
    actionGroup->addAction(ui->actionsv);
    actionGroup->addAction(ui->actiontr);
    actionGroup->addAction(ui->actionus);
    ui->actionDefault->setChecked(true);

    init_props(0);
    connect(ui->plainTextEdit, &QPlainTextEdit::cursorPositionChanged, this, &MainWindow::highlight);
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::highlight);

    timeline = new QTimeLine(1, Q_NULLPTR);
    connect(timeline, &QTimeLine::frameChanged, this, &MainWindow::timeline_slot);
    connect(timeline, &QTimeLine::finished, this, &MainWindow::timeline_finished);
    connect(ui->pushButtonStop, &QPushButton::clicked, timeline, &QTimeLine::stop);
    connect(ui->pushButtonStop, &QPushButton::clicked, this, &MainWindow::timeline_finished);

    //WINDOWS
    scripts_map_win.insert("Open Run", ":/scripts/windows/open_run.ds");
    scripts_map_win.insert("CMD.EXE", ":/scripts/windows/cmd.exe.ds");
    scripts_map_win.insert("Delete Run History", ":/scripts/windows/delete_run_history.ds");
    scripts_map_win.insert("Download & Execute Powershell", ":/scripts/windows/dl_exec_powershell.ds");
    scripts_map_win.insert("Download & Execute Powershell 2", ":/scripts/windows/dl_exec_powershell2.ds");
    scripts_map_win.insert("Save to USB Drive", ":/scripts/windows/save_to_usb_drive.ds");
    scripts_map_win.insert("Clipboard", ":/scripts/windows/clipboard.ds");
    scripts_list_win
        << "Open Run"
        << "CMD.EXE"
        << "Delete Run History"
        << "Download & Execute Powershell"
        << "Download & Execute Powershell 2"
        << "Save to USB Drive"
        << "Clipboard";

    //MACOS
    scripts_map_mac.insert("Open Run", ":/scripts/macos/open_run.ds");
    scripts_map_mac.insert("Reverse Shell", ":/scripts/macos/reverse_shell.ds");
    scripts_map_mac.insert("Reverse Shell 2", ":/scripts/macos/reverse_shell2.ds");
    scripts_map_mac.insert("Bind Shell", ":/scripts/macos/bind_shell.ds");
    scripts_list_mac
        << "Open Run"
        << "Reverse Shell"
        << "Reverse Shell 2"
        << "Bind Shell";

    //LINUX
    scripts_map_linux.insert("Open Run", ":/scripts/linux/open_run.ds");
    scripts_map_linux.insert("Bind Shell", ":/scripts/linux/bind_shell.ds");
    scripts_map_linux.insert("Reverse Shell", ":/scripts/linux/reverse_shell.ds");
    scripts_map_linux.insert("Bash Aliases Prank", ":/scripts/linux/bash_aliases_prank.ds");
    scripts_list_linux
        << "Open Run"
        << "Bind Shell"
        << "Reverse Shell"
        << "Bash Aliases Prank";

    QStringListIterator i(scripts_list_win);
    while(i.hasNext()){
        QString item = i.next();
        ui->listWidgetWindows->addItem(item);
        if(scripts_map_win.contains(item)){
            QFile f(scripts_map_win.value(item));
            if(!f.open(QFile::ReadOnly))
                return;
            QString str = QString(f.readAll());
            f.close();
            ui->listWidgetWindows->item(ui->listWidgetWindows->count()-1)->setToolTip(str);
        }
    }

    i = scripts_list_mac;
    while(i.hasNext()){
        QString item = i.next();
        ui->listWidgetMac->addItem(item);
        if(scripts_map_mac.contains(item)){
            QFile f(scripts_map_mac.value(item));
            if(!f.open(QFile::ReadOnly))
                return;
            QString str = QString(f.readAll());
            f.close();
            ui->listWidgetMac->item(ui->listWidgetMac->count()-1)->setToolTip(str);
        }
    }

    i = scripts_list_linux;
    while(i.hasNext()){
        QString item = i.next();
        ui->listWidgetLinux->addItem(item);
        if(scripts_map_linux.contains(item)){
            QFile f(scripts_map_linux.value(item));
            if(!f.open(QFile::ReadOnly))
                return;
            QString str = QString(f.readAll());
            f.close();
            ui->listWidgetLinux->item(ui->listWidgetLinux->count()-1)->setToolTip(str);
        }
    }

#if defined(Q_OS_LINUX)
    typewriter = new TypeWriterLinux();
    ui->tabWidget->setCurrentIndex(2);
#elif defined(Q_OS_MACOS)
    typewriter = new TypeWriterMacOS();
    ui->tabWidget->setCurrentIndex(1);
#elif defined(Q_OS_WINDOWS)
    typewriter = new TypeWriterWindows();
    ui->tabWidget->setCurrentIndex(0);
#endif

    p = new Programmer();
    ui->actionProgrammer->setEnabled(p->hasProgrammer());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timeline;
    delete p;
}

void MainWindow::init_props(int locale){
    bool ok;
    int val, pos;
    QString in, line_str, locale_code;
    QStringList line_comps, in_lst;
    if(locale == 1){
        locale_code = "be";
    }else if(locale == 2){
        locale_code = "br";
    }else if(locale == 3){
        locale_code = "ca";
    }else if(locale == 4){
        locale_code = "ch";
    }else if(locale == 5){
        locale_code = "de";
    }else if(locale == 6){
        locale_code = "dk";
    }else if(locale == 7){
        locale_code = "es";
    }else if(locale == 8){
        locale_code = "fi";
    }else if(locale == 9){
        locale_code = "fr";
    }else if(locale == 10){
        locale_code = "gb";
    }else if(locale == 11){
        locale_code = "hr";
    }else if(locale == 12){
        locale_code = "it";
    }else if(locale == 13){
        locale_code = "no";
    }else if(locale == 14){
        locale_code = "pl";
    }else if(locale == 15){
        locale_code = "pt";
    }else if(locale == 16){
        locale_code = "ru";
    }else if(locale == 17){
        locale_code = "si";
    }else if(locale == 18){
        locale_code = "sv";
    }else if(locale == 19){
        locale_code = "tr";
    }else if(locale == 20){
        locale_code = "us";
    }else{
        if(QLocale() == QLocale(QLocale::French, QLocale::Belgium)){
            locale_code = "be";
        }else if(QLocale() == QLocale(QLocale::Portuguese, QLocale::Brazil)){
            locale_code = "br";
        }else if(QLocale().language() == QLocale::SwissGerman){
            locale_code = "ch";
        }else if(QLocale().language() == QLocale::German){
            locale_code = "de";
        }else if(QLocale().language() == QLocale::Danish){
            locale_code = "dk";
        }else if(QLocale().language() == QLocale::Spanish){
            locale_code = "es";
        }else if(QLocale().language() == QLocale::Finnish){
            locale_code = "fi";
        }else if(QLocale().language() == QLocale::French){
            locale_code = "fr";
        }else if(QLocale().language() == QLocale::Croatian){
            locale_code = "hr";
        }else if(QLocale().language() == QLocale::Italian){
            locale_code = "it";
        }else if(QLocale().language() == QLocale::Norwegian){
            locale_code = "no";
        }else if(QLocale().language() == QLocale::Polish){
            locale_code = "pl";
        }else if(QLocale().language() == QLocale::Portuguese){
            locale_code = "pt";
        }else if(QLocale().language() == QLocale::Russian){
            locale_code = "ru";
        }else if(QLocale().language() == QLocale::Slovenian){
            locale_code = "si";
        }else if(QLocale().language() == QLocale::Swedish){
            locale_code = "sv";
        }else if(QLocale().language() == QLocale::Turkish){
            locale_code = "tr";
        }else if(QLocale().country() == QLocale::Canada){
            locale_code = "ca";
        }else if(QLocale().country() == QLocale::UnitedKingdom){
            locale_code = "gb";
        }else if(QLocale().country() == QLocale::UnitedStates){
            locale_code = "us";
        }else{
            locale_code = QLocale().name().split("_").at(0); //try our luck
        }
    }

    keyprops.clear(); cmd_list.clear();
    QFile file(":/resources/keyboard.properties");
    if(QFileInfo(file.fileName()).exists() && file.open(QFile::ReadOnly)){
        in = file.readAll();
        file.close();
        in = in.replace("\\r", "");
        in_lst = in.split("\n");
        foreach(line_str, in_lst){
            line_comps = QStringList();
            line_str = line_str.trimmed();
            if(line_str.isEmpty() || line_str.mid(0,2) == QString("//"))
                continue;
            pos = line_str.indexOf('=');
            if(pos == -1)
                continue;
            line_comps = QStringList({line_str.split("=")[0].trimmed(), line_str.split("=")[1].trimmed()});
            val = line_comps.at(1).toInt(&ok, (line_comps.at(1).mid(0,2)==QString("0x"))?16:10);
            if(!ok)
                continue;
            keyprops.insert(line_comps.at(0), val);
        }
    }
    QHashIterator<QString, quint32> i(keyprops);
    while(i.hasNext()){
        i.next();
        QString key = i.key();
        QRegularExpression re;
        re.setPattern("^KEY_");
        key.replace(re, "");
        cmd_list.append(key);
    }
    cmd_list.append("ESCAPE");
    cmd_list.append("DEL");
    cmd_list.append("BREAK");
    cmd_list.append("CONTROL");
    cmd_list.append("DOWNARROW");
    cmd_list.append("UPARROW");
    cmd_list.append("LEFTARROW");
    cmd_list.append("RIGHTARROW");
    cmd_list.append("MENU");
    cmd_list.append("WINDOWS");
    cmd_list.append("STOP");
    cmd_list.append("MUTE");
    cmd_list.append("VOLUMEUP");
    cmd_list.append("VOLUMEDOWN");
    cmd_list.append("SCROLLLOCK");
    cmd_list.append("NUMLOCK");
    cmd_list.append("CAPSLOCK");
    cmd_list.append("PLAY");
    cmd_list.append("PAUSE");
    cmd_list.append("CTRL");
    cmd_list.append("ALT");
    cmd_list.append("ALT-TAB");
    cmd_list.append("SHIFT");
    cmd_list.append("CTRL-ALT");
    cmd_list.append("CTRL-ALT-SHIFT");
    cmd_list.append("CTRL-SHIFT");
    cmd_list.append("COMMAND-OPTION");
    cmd_list.append("ALT-SHIFT");
    cmd_list.append("GUI");
    cmd_list.append("GUI-SHIFT");
    cmd_list.append("STRING");
    cmd_list.append("STRING_DELAY");

    layprops.clear();
    QFile file2(":/resources/"+locale_code+".properties");
    if(QFileInfo(file2.fileName()).exists() && file2.open(QFile::ReadOnly)){
        QByteArray in_b = file2.readAll();
        QString in;
        if(locale_code == "ru"){
            in = QTextCodec::codecForMib(1015)->toUnicode(in_b);
        }else if(locale_code == "no"){
            in = QTextCodec::codecForMib(1016)->toUnicode(in_b);
        }else{
            in = in_b;
        }
        file2.close();
        in = in.replace("\\r", "");
        in_lst = in.split("\n");
        foreach(line_str, in_lst){
            line_comps = QStringList();
            if(line_str.indexOf(QString("//")) != -1)
                line_str = line_str.mid(0, line_str.indexOf(QString("//")));
            line_str = line_str.trimmed();
            if(line_str.isEmpty() || line_str.mid(0,2) == QString("//"))
                continue;
            pos = line_str.indexOf('=');
            if(pos == -1)
                continue;
            line_comps = line_str.split("=")[1].trimmed().split(",");
            for(val=0; val < line_comps.length(); val++)
                line_comps.replace(val, line_comps.at(val).trimmed());
            layprops.insert(line_str.split("=")[0].trimmed(), line_comps);
        }
    }
}

void MainWindow::on_actionNew_triggered(){
    ui->plainTextEdit->setPlainText("");
    savefile = "";
    setWindowTitle("DuckiesqueUI");
    highlight();
}

void MainWindow::on_actionOpen_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Select a DuckyScript file to open..."),
                                                    (!savefile.isEmpty())?savefile:QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
                                                    QString("DuckyScript (*.ds);;All (*.*)"));
    loadOpenFile(filename);
}

void MainWindow::loadOpenFile(QString filename){
    QFile file(filename);
    if(QFileInfo(filename).exists() && file.open(QFile::ReadOnly)){
        savefile = QFileInfo(filename).absoluteFilePath();
        setWindowTitle("DuckiesqueUI - "+filename);
        QString in = file.readAll();
        file.close();
        ui->plainTextEdit->setPlainText(in);
    }
    highlight();
}

bool MainWindow::c2a(QStringList *out, QChar c){
    QString keystring = QString();
    quint16 c_int = (quint16)c.unicode();
    if(c_int < 128){
        keystring = "ASCII_"+QString::number((ulong)c_int, 16).toUpper();
    }else if(c_int < 256){
        keystring = "ISO_8859_1_"+QString::number((ulong)c_int, 16).toUpper();
    }else{
        keystring = "UNICODE_"+QString::number((ulong)c_int, 16).toUpper();
    }
    if(!layprops.contains(keystring))
        return false;
    (*out) = layprops.value(keystring);
    return true;
}

bool MainWindow::k2b(QByteArray *out, QString key){
    bool ok;
    (*out) = QByteArray();
    if(keyprops.contains(key)){
        (*out).append(QByteArray(1, keyprops.value(key)));
    }else if(layprops.contains(key)){
        QStringList laypropsList = layprops.value(key);
        int n = laypropsList.length();
        QByteArray testOut;
        bool testList = true;
        for(int i = 0; i < n; i++){
            if(k2b(&testOut, laypropsList.at(i))){
                (*out).append(testOut);
            }else{
                testList = false;
            }
        }
        if(!testList){
            (*out) = QByteArray();
        }else{
            return true;
        }
        QString first_item = layprops.value(key).at(0);
        if(first_item.mid(0,2) == QString("0x")){
            (*out).append(QByteArray(1, first_item.mid(2).toInt(&ok, 16)));
        }else{
            (*out).append(QByteArray(1, first_item.toInt(&ok)));
        }
        if(!ok){
            (*out) = 0;
            return false;
        }
    }
    return true;
}

bool MainWindow::c2b(QByteArray *out, bool *parity, QChar c){
    QByteArray b;
    quint8 modifer = 0;
    (*parity) = false;
    QStringList layout_keys;

    if(!c2a(&layout_keys, c))
        return false;
    order_keypress_combination(&layout_keys);
qDebug() << layout_keys;
    foreach(QString layout_key, layout_keys){
        if(!k2b(&b, layout_key)){
            (*out) = QByteArray();
            return false;
        }
qDebug() << modifer << b.toHex() << is_mod(layout_key);
        if(!is_mod(layout_key))
            (*out).append(b);
        else
            modifer += (quint8)b.at(0);
    }
    (*out).append(QByteArray(1, modifer));
    (*parity) = (((*out).size()%2) != 0);
    return true;
}

bool MainWindow::c2w(QByteArray *out, QString str){
    bool parity;
    (*out) = QByteArray();
    QString keystring;
    for(int i = 0; i < str.length(); i++){
        keystring = QString();
        QChar c = str.at(i);
        if(!c2b(out, &parity, c)){
            return false;
        }
        if(parity)
            (*out).append(1,0);
    }
    return true;
}

bool MainWindow::c2wa(QList<QStringList> *out, QString str){
    (*out) = QList<QStringList>();
    QStringList keystringlist;
    for(int i = 0; i < str.length(); i++){
        keystringlist = QStringList();
        QChar c = str.at(i);
        if(!c2a(&keystringlist, c)){
            (*out).clear();
            return false;
        }
        order_keypress_combination(&keystringlist);
        (*out).append(keystringlist);
    }
    return true;
}

bool MainWindow::single_inst(quint8 *out, QString in){
    bool p;
    QString in_t;
    name_convert(&in_t, in);
    if(keyprops.contains("KEY_"+in_t.toUpper())){
        (*out) = keyprops.value("KEY_"+in_t.toUpper());
        return true;
    }
    QByteArray b = QByteArray();
    if(!c2b(&b, &p, in_t.at(0)) || b.length() < 1)
        return false;
    (*out) = b.at(0);
    return true;

}
bool MainWindow::name_convert(QString *out, QString in){
    (*out) = "";
    if(in == "ESCAPE"){
        *out = "ESC";
        return true;
    }else if(in == "DEL"){
        *out = "DELETE";
        return true;
    }else if(in == "BREAK"){
        *out = "PAUSE";
        return true;
    }else if(in == "CONTROL"){
        *out = "CTRL";
        return true;
    }else if(in == "DOWNARROW"){
        *out = "DOWN";
        return true;
    }else if(in == "UPARROW"){
        *out = "UP";
        return true;
    }else if(in == "LEFTARROW"){
        *out = "LEFT";
        return true;
    }else if(in == "RIGHTARROW"){
        *out = "RIGHT";
        return true;
    }else if(in == "MENU"){
        *out = "APP";
        return true;
    }else if(in == "WINDOWS"){
        *out = "GUI";
        return true;
    }else if(in == "PLAY" || in == "PAUSE"){
        *out = "MEDIA_PLAY_PAUSE";
        return true;
    }else if(in == "STOP"){
        *out = "MEDIA_STOP";
        return true;
    }else if(in == "MUTE"){
        *out = "MEDIA_MUTE";
        return true;
    }else if(in == "VOLUMEUP"){
        *out = "MEDIA_VOLUME_INC";
        return true;
    }else if(in == "VOLUMEDOWN"){
        *out = "MEDIA_VOLUME_DEC";
        return true;
    }else if(in == "SCROLLLOCK"){
        *out = "SCROLL_LOCK";
        return true;
    }else if(in == "NUMLOCK"){
        *out = "NUM_LOCK";
        return true;
    }else if(in == "CAPSLOCK"){
        *out = "CAPS_LOCK";
        return true;
    }else if(keyprops.contains("KEY_"+in.toUpper())){
        *out = in.toUpper();
        return true;
    }
    return false;
}

void MainWindow::on_actionSave_triggered(){
    if(QFileInfo(savefile).exists() && QFileInfo(savefile).isWritable()){
        QFile file(savefile);
        if(file.open(QFile::WriteOnly|QFile::Truncate)){
            file.write(ui->plainTextEdit->toPlainText().toLocal8Bit());
            file.close();
        }
    }else{
        on_actionSave_as_triggered();
    }
}

void MainWindow::on_actionSave_as_triggered(){
    QString tmp = QFileDialog::getSaveFileName(this, tr("Select a DuckyScript file to save..."),
                                               (!savefile.isEmpty())?savefile:QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
                                               QString("DuckyScript (*.ds);;All (*.*)"));
    if(tmp.isEmpty()){
        return;
    }
    savefile = QFileInfo(tmp).absoluteFilePath();
    QFile file(savefile);
    if(file.open(QFile::WriteOnly|QFile::Truncate)){
        setWindowTitle("DuckiesqueUI - "+savefile);
        file.write(ui->plainTextEdit->toPlainText().toLocal8Bit());
        file.close();
    }else{
        savefile = "";
    }
}

void MainWindow::on_actionExport_triggered(){
    if(errors_found){
        QMessageBox::warning(this, tr("DuckyScript Error"), tr("You need to correct the error before you can export it."));
    }else{
        QString filename = QFileDialog::getSaveFileName(this, tr("Save inject.bin file as..."),
                                                        QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+QString("/inject.bin"),
                                                        QString("Binary file (*.bin);;All (*.*)"));
        QByteArray filedata = QByteArray();
        quint64 rel_stamp = 0;
        if(filename.isEmpty() || !parse_bin_exec(&rel_stamp, &filedata) || !rel_stamp){
            return;
        }
        QFile f(filename);
        if(f.open(QFile::WriteOnly|QFile::Truncate)){
            f.write(filedata);
            f.close();
        }
    }
}

void MainWindow::on_actionRun_triggered(){
    on_pushButtonExec_clicked();
}

void MainWindow::on_actionExit_triggered(){
    QTimer::singleShot(250, qApp, &QApplication::quit);
}

void MainWindow::on_actionAbout_triggered(){
    QMessageBox::information(this, tr("DuckiequseUI"), tr("A tool for rapid protocoding DuckyScripts. Version: ")+DUSCKIESQUE_VERSION);
}

void MainWindow::on_pushButtonExec_clicked(){
    quint64 rel_stamp = 0;
    QByteArray null;
    if(!parse_bin_exec(&rel_stamp, &null) || !rel_stamp){
        return;
    }

    ui->pushButtonStop->setEnabled(true);
    setWindowState(Qt::WindowMinimized);
    timeline->setFrameRange(0, rel_stamp);
    timeline->setDuration(rel_stamp);
    timeline->setCurrentTime(0);
    timeline->start();
}

void MainWindow::timeline_slot(quint64 value){
    mutex.lock();
    quint64 counted_run = 0;
    QMap<quint64, QStringList>::iterator i;
    for(i = main_seq_indexed.begin(); i != main_seq_indexed.end(); ++i){
        if(i.key() > value)
            break;
        counted_run++;
        QStringList taken = main_seq_indexed.value(i.key());
        typewriter->type_key(taken);
    }
    for(quint64 j = 0; j < counted_run; j++)
        main_seq_indexed.remove(main_seq_indexed.begin().key());
    mutex.unlock();
}

void MainWindow::timeline_finished(){
    setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    raise();
    activateWindow();
    ui->pushButtonStop->setEnabled(false);
    timeline->setFrameRange(0, 1);
    timeline->setDuration(1);
    timeline->setCurrentTime(0);
    highlight();
}

void MainWindow::on_listWidgetWindows_itemDoubleClicked(QListWidgetItem *item){
    if(scripts_map_win.contains(item->text())){
        QFile f(scripts_map_win.value(item->text()));
        if(!f.open(QFile::ReadOnly))
            return;
        QString str = QString(f.readAll());
        f.close();
        ui->plainTextEdit->insertPlainText(str);
    }
}

void MainWindow::on_listWidgetMac_itemDoubleClicked(QListWidgetItem *item){
    if(scripts_map_mac.contains(item->text())){
        QFile f(scripts_map_mac.value(item->text()));
        if(!f.open(QFile::ReadOnly))
            return;
        QString str = QString(f.readAll());
        f.close();
        ui->plainTextEdit->insertPlainText(str);
    }
}

void MainWindow::on_listWidgetLinux_itemDoubleClicked(QListWidgetItem *item){
    if(scripts_map_linux.contains(item->text())){
        QFile f(scripts_map_linux.value(item->text()));
        if(!f.open(QFile::ReadOnly))
            return;
        QString str = QString(f.readAll());
        f.close();
        ui->plainTextEdit->insertPlainText(str);
    }
}

bool MainWindow::parse_bin_exec(quint64 *rel_stamp, QByteArray *out){
    bool ok, isArgInteger;
    quint64 default_delay = 0, num_arg = 0, arg_int = 0;
    QPair<QString, QString> tmp;
    QStringList tmp2;
    QString conv_first;
    QByteArray old_entry = QByteArray();
    quint8 byte;
    main_seq_indexed.clear();
    (*out) = QByteArray();
    (*rel_stamp) = (quint64)std::floor(ui->doubleSpinBox->value()*1000.0);
    foreach(tmp, main_sequence){
        arg_int = tmp.second.toUInt(&isArgInteger);
        if(tmp.first == "DELAY"){
            old_entry = QByteArray();
            num_arg = tmp.second.toInt(&ok);
            (*rel_stamp) += num_arg;
            if(!ok)
                return false;
            for(quint64 i = 0; i < (num_arg/255); i++){
                (*out).append("\x00\xff", 2);
                old_entry.append("\x00\xff", 2);
            }
            if(num_arg%256){
                (*out).append("\x00", 1);
                (*out).append((char)(num_arg%255));
                old_entry.append("\x00", 1);
                old_entry.append((char)(num_arg%255));
            }
        }else if(tmp.first == "DEFAULT_DELAY" || tmp.first == "DEFAULTDELAY"){
            default_delay = tmp.second.toInt(&ok);
            if(!ok)
                return false;
        }else{
            QStringList key_ext_guard = QStringList();
            if(tmp.first == "GUI" || tmp.first == "WINDOWS"){
                old_entry = QByteArray();
                if(tmp.second.trimmed().isEmpty()){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_LEFT_GUI");
                    (*rel_stamp) += default_delay+1;
                    (*out).append(1, keyprops.value("MODIFIERKEY_LEFT_GUI"));
                    (*out).append("\x00", 1);
                    old_entry.append(1, keyprops.value("MODIFIERKEY_LEFT_GUI"));
                    old_entry.append("\x00", 1);
                }else{
                    if(!single_inst(&byte, tmp.second.toUpper().trimmed()))
                        return false;
                    (*out).append(1, byte);
                    (*out).append(1, keyprops.value("MODIFIERKEY_LEFT_GUI"));
                    old_entry.append(1, byte);
                    old_entry.append(1, keyprops.value("MODIFIERKEY_LEFT_GUI"));
                    if(keyprops.contains("KEY_"+tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_LEFT_GUI" << "KEY_"+tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }else if(layprops.contains(tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_LEFT_GUI" << tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }
                }
            }else if(tmp.first == "GUI-SHIFT"){
                old_entry = QByteArray();
                if(tmp.second.trimmed().isEmpty()){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_SHIFT" << "KEY_LEFT_GUI");
                    (*rel_stamp) += default_delay+1;
                    (*out).append(1, keyprops.value("KEY_LEFT_GUI"));
                    (*out).append(1, keyprops.value("MODIFIERKEY_LEFT_GUI") | keyprops.value("MODIFIERKEY_SHIFT"));
                    old_entry.append(1, keyprops.value("KEY_LEFT_GUI"));
                    old_entry.append(1, keyprops.value("MODIFIERKEY_LEFT_GUI") | keyprops.value("MODIFIERKEY_SHIFT"));
                }else{
                    old_entry = QByteArray();
                    if(!single_inst(&byte, tmp.second.toUpper().trimmed()))
                        return false;
                    (*out).append(1, byte);
                    (*out).append(1, keyprops.value("MODIFIERKEY_LEFT_GUI") | keyprops.value("MODIFIERKEY_SHIFT"));
                    old_entry.append(1, byte);
                    old_entry.append(1, keyprops.value("MODIFIERKEY_LEFT_GUI") | keyprops.value("MODIFIERKEY_SHIFT"));
                    if(keyprops.contains("KEY_"+tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_SHIFT" << "MODIFIERKEY_LEFT_GUI" << "KEY_"+tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }else if(layprops.contains(tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_SHIFT" << "MODIFIERKEY_LEFT_GUI" << tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }
                }
            }else if(tmp.first == "COMMAND"){
                old_entry = QByteArray();
                if(tmp.second.trimmed().isEmpty()){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "KEY_COMMAND");
                    (*rel_stamp) += default_delay+1;
                    (*out).append(1, keyprops.value("KEY_COMMAND"));
                    (*out).append("\x00", 1);
                    old_entry.append(1, keyprops.value("KEY_COMMAND"));
                    old_entry.append("\x00", 1);
                }else{
                    if(!single_inst(&byte, tmp.second.toUpper().trimmed()))
                        return false;
                    (*out).append(1, byte);
                    (*out).append(1, keyprops.value("MODIFIERKEY_LEFT_GUI"));
                    old_entry.append(1, byte);
                    old_entry.append(1, keyprops.value("MODIFIERKEY_LEFT_GUI"));
                    if(keyprops.contains("KEY_"+tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_LEFT_GUI" << "KEY_"+tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }else if(layprops.contains(tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_LEFT_GUI" << tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }
                }
            }else if(tmp.first == "ALT-TAB"){
                if(!tmp.second.trimmed().isEmpty())
                    return false;
                old_entry = QByteArray();
                main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_LEFT_ALT" << "KEY_TAB");
                (*rel_stamp) += default_delay+1;
                (*out).append(1, keyprops.value("KEY_TAB"));
                (*out).append(1, keyprops.value("MODIFIERKEY_LEFT_ALT"));
                old_entry.append(1, keyprops.value("KEY_TAB"));
                old_entry.append(1, keyprops.value("MODIFIERKEY_LEFT_ALT"));
            }else if(tmp.first == "ALT-SHIFT"){
                old_entry = QByteArray();
                if(tmp.second.trimmed().isEmpty()){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_SHIFT" << "KEY_LEFT_ALT");
                    (*rel_stamp) += default_delay+1;
                    (*out).append(1, keyprops.value("KEY_LEFT_ALT"));
                    (*out).append(1, keyprops.value("MODIFIERKEY_LEFT_ALT") | keyprops.value("MODIFIERKEY_SHIFT"));
                    old_entry.append(1, keyprops.value("KEY_LEFT_ALT"));
                    old_entry.append(1, keyprops.value("MODIFIERKEY_LEFT_ALT") | keyprops.value("MODIFIERKEY_SHIFT"));
                }else{
                    old_entry = QByteArray();
                    if(!single_inst(&byte, tmp.second.toUpper().trimmed()))
                        return false;
                    (*out).append(1, byte);
                    (*out).append(1, keyprops.value("MODIFIERKEY_LEFT_ALT") | keyprops.value("MODIFIERKEY_SHIFT"));
                    old_entry.append(1, byte);
                    old_entry.append(1, keyprops.value("MODIFIERKEY_LEFT_ALT") | keyprops.value("MODIFIERKEY_SHIFT"));
                    if(keyprops.contains("KEY_"+tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_SHIFT" << "MODIFIERKEY_LEFT_ALT" << "KEY_"+tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }else if(layprops.contains(tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_SHIFT" << "MODIFIERKEY_LEFT_ALT" << tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }
                }
            }else if(tmp.first == "COMMAND-OPTION"){
                if(tmp.second.trimmed().isEmpty())
                    return false;
                if(!single_inst(&byte, tmp.second.toUpper().trimmed()))
                    return false;
                old_entry = QByteArray();
                (*out).append(1, byte);
                (*out).append(1, keyprops.value("MODIFIERKEY_LEFT_GUI") | keyprops.value("MODIFIERKEY_ALT"));
                old_entry.append(1, byte);
                old_entry.append(1, keyprops.value("MODIFIERKEY_LEFT_GUI") | keyprops.value("MODIFIERKEY_ALT"));
                if(keyprops.contains("KEY_"+tmp.second.toUpper().trimmed())){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_ALT" << "MODIFIERKEY_LEFT_GUI" << "KEY_"+tmp.second.toUpper().trimmed());
                    (*rel_stamp) += default_delay+1;
                }else if(layprops.contains(tmp.second.toUpper().trimmed())){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_ALT" << "MODIFIERKEY_LEFT_GUI" << tmp.second.toUpper().trimmed());
                    (*rel_stamp) += default_delay+1;
                }
            }else if(tmp.first == "CTRL-SHIFT"){
                if(tmp.second.trimmed().isEmpty())
                    return false;
                if(!single_inst(&byte, tmp.second.toUpper().trimmed()))
                    return false;
                old_entry = QByteArray();
                (*out).append(1, byte);
                (*out).append(1, keyprops.value("MODIFIERKEY_CTRL") | keyprops.value("MODIFIERKEY_SHIFT"));
                old_entry.append(1, byte);
                old_entry.append(1, keyprops.value("MODIFIERKEY_CTRL") | keyprops.value("MODIFIERKEY_SHIFT"));
                if(keyprops.contains("KEY_"+tmp.second.toUpper().trimmed())){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_SHIFT" << "MODIFIERKEY_CTRL" << "KEY_"+tmp.second.toUpper().trimmed());
                    (*rel_stamp) += default_delay+1;
                }else if(layprops.contains(tmp.second.toUpper().trimmed())){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_SHIFT" << "MODIFIERKEY_CTRL" << tmp.second.toUpper().trimmed());
                    (*rel_stamp) += default_delay+1;
                }
            }else if(tmp.first == "CTRL-ALT"){
                if(tmp.second.trimmed().isEmpty())
                    continue;
                if(!single_inst(&byte, tmp.second.toUpper().trimmed()))
                    return false;
                old_entry = QByteArray();
                (*out).append(1, byte);
                (*out).append(1, keyprops.value("MODIFIERKEY_CTRL") | keyprops.value("MODIFIERKEY_ALT"));
                old_entry.append(1, byte);
                old_entry.append(1, keyprops.value("MODIFIERKEY_CTRL") | keyprops.value("MODIFIERKEY_ALT"));
                if(keyprops.contains("KEY_"+tmp.second.toUpper().trimmed())){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_CTRL" << "MODIFIERKEY_ALT" << "KEY_"+tmp.second.toUpper().trimmed());
                    (*rel_stamp) += default_delay+1;
                }else if(layprops.contains(tmp.second.toUpper().trimmed())){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_CTRL" << "MODIFIERKEY_ALT" << tmp.second.toUpper().trimmed());
                    (*rel_stamp) += default_delay+1;
                }
            }else if(tmp.first == "CTRL-ALT-SHIFT"){
                if(tmp.second.trimmed().isEmpty())
                    continue;
                if(!single_inst(&byte, tmp.second.toUpper().trimmed()))
                    return false;
                old_entry = QByteArray();
                (*out).append(1, byte);
                (*out).append(1, keyprops.value("MODIFIERKEY_CTRL") | keyprops.value("MODIFIERKEY_ALT") | keyprops.value("MODIFIERKEY_SHIFT"));
                old_entry.append(1, byte);
                old_entry.append(1, keyprops.value("MODIFIERKEY_CTRL") | keyprops.value("MODIFIERKEY_ALT") | keyprops.value("MODIFIERKEY_SHIFT"));
                if(keyprops.contains("KEY_"+tmp.second.toUpper().trimmed())){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_CTRL" << "MODIFIERKEY_ALT" << "MODIFIERKEY_SHIFT" << "KEY_"+tmp.second.toUpper().trimmed());
                    (*rel_stamp) += default_delay+1;
                }else if(layprops.contains(tmp.second.toUpper().trimmed())){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_CTRL" << "MODIFIERKEY_ALT" << "MODIFIERKEY_SHIFT" << tmp.second.toUpper().trimmed());
                    (*rel_stamp) += default_delay+1;
                }
            }else if(tmp.first == "SHIFT"){
                old_entry = QByteArray();
                if(tmp.second.trimmed().isEmpty()){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "KEY_LEFT_SHIFT");
                    (*rel_stamp) += default_delay+1;
                    (*out).append(1, keyprops.value("KEY_LEFT_SHIFT"));
                    (*out).append(1, 0);
                    old_entry.append(1, keyprops.value("KEY_LEFT_SHIFT"));
                    old_entry.append(1, 0);
                }else{
                    if(!single_inst(&byte, tmp.second.toUpper().trimmed()))
                        return false;
                    (*out).append(1, byte);
                    (*out).append(1, keyprops.value("MODIFIERKEY_SHIFT"));
                    old_entry.append(1, byte);
                    old_entry.append(1, keyprops.value("MODIFIERKEY_SHIFT"));
                    if(keyprops.contains("KEY_"+tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_SHIFT" << "KEY_"+tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }else if(layprops.contains(tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_SHIFT" << tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }
                }
            }else if(tmp.first == "ALT"){
                old_entry = QByteArray();
                if(tmp.second.trimmed().isEmpty()){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "KEY_LEFT_ALT");
                    (*rel_stamp) += default_delay+1;
                    (*out).append(1, keyprops.value("KEY_LEFT_ALT"));
                    (*out).append(1, 0);
                    old_entry.append(1, keyprops.value("KEY_LEFT_ALT"));
                    old_entry.append(1, 0);
                }else{
                    if(!single_inst(&byte, tmp.second.toUpper().trimmed()))
                        return false;
                    (*out).append(1, byte);
                    (*out).append(1, keyprops.value("MODIFIERKEY_ALT"));
                    old_entry.append(1, byte);
                    old_entry.append(1, keyprops.value("MODIFIERKEY_ALT"));
                    if(keyprops.contains("KEY_"+tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_ALT" << "KEY_"+tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }else if(layprops.contains(tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_ALT" << tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }
                }
            }else if(tmp.first == "CONTROL" || tmp.first == "CTRL"){
                old_entry = QByteArray();
                if(tmp.second.trimmed().isEmpty()){
                    main_seq_indexed.insert((*rel_stamp), QStringList() << "KEY_LEFT_CTRL");
                    (*rel_stamp) += default_delay+1;
                    (*out).append(1, keyprops.value("KEY_LEFT_CTRL"));
                    (*out).append(1, 0);
                    old_entry.append(1, keyprops.value("KEY_LEFT_CTRL"));
                    old_entry.append(1, 0);
                }else{
                    if(!single_inst(&byte, tmp.second.toUpper().trimmed()))
                        return false;
                    (*out).append(1, byte);
                    (*out).append(1, keyprops.value("MODIFIERKEY_CTRL"));
                    old_entry.append(1, byte);
                    old_entry.append(1, keyprops.value("MODIFIERKEY_CTRL"));
                    if(keyprops.contains("KEY_"+tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_CTRL" << "KEY_"+tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }else if(layprops.contains(tmp.second.toUpper().trimmed())){
                        main_seq_indexed.insert((*rel_stamp), QStringList() << "MODIFIERKEY_CTRL" << tmp.second.toUpper().trimmed());
                        (*rel_stamp) += default_delay+1;
                    }
                }
            }else if(name_convert(&conv_first, tmp.first) && tmp.second.trimmed().isEmpty() && keyprops.contains("KEY_"+conv_first.toUpper().trimmed())){
                old_entry = QByteArray();
                main_seq_indexed.insert((*rel_stamp), QStringList() << "KEY_"+conv_first.toUpper().trimmed());
                (*rel_stamp) += default_delay+1;
                (*out).append(1, keyprops.value("KEY_"+conv_first.toUpper().trimmed()));
                (*out).append(1, 0);
                old_entry.append(1, keyprops.value("KEY_"+conv_first.toUpper().trimmed()));
                old_entry.append(1, 0);
                conv_first = "";
            }else if(keyprops.contains("KEY_"+tmp.first.toUpper().trimmed()) && tmp.second.trimmed().isEmpty()){
                old_entry = QByteArray();
                main_seq_indexed.insert((*rel_stamp), QStringList() << "KEY_"+tmp.first.toUpper().trimmed());
                (*rel_stamp) += default_delay+1;
                (*out).append(1, keyprops.value("KEY_"+tmp.first.toUpper().trimmed()));
                (*out).append(1, 0);
                old_entry.append(1, keyprops.value("KEY_"+tmp.first.toUpper().trimmed()));
                old_entry.append(1, 0);
            }else if(keyprops.contains(tmp.first.toUpper().trimmed()) && tmp.second.trimmed().isEmpty()){
                old_entry = QByteArray();
                main_seq_indexed.insert((*rel_stamp), QStringList() << tmp.first.toUpper().trimmed());
                (*rel_stamp) += default_delay+1;
                (*out).append(1, 0);
                (*out).append(1, keyprops.value(tmp.first.toUpper().trimmed()));
                old_entry.append(1, 0);
                old_entry.append(1, keyprops.value(tmp.first.toUpper().trimmed()));
            }else if(tmp.first == "STRING" && !tmp.second.trimmed().isEmpty()){
                old_entry = QByteArray();
                QList<QStringList> tmp3 = QList<QStringList>{};
                if(!c2wa(&tmp3, tmp.second)){
                    return false;
                }
                foreach(tmp2, tmp3){
                    order_keypress_combination(&tmp2);
                    main_seq_indexed.insert((*rel_stamp), QStringList() << tmp2);
                    (*rel_stamp) += default_delay+1;
                }
                QByteArray tmp_b;
                if(!c2w(&tmp_b, tmp.second))
                    return false;
                (*out).append(tmp_b);
                old_entry.append(tmp_b);
            }else if(tmp.first == "REPEAT" && !tmp.second.trimmed().isEmpty() && isArgInteger && !old_entry.isEmpty() && !main_seq_indexed.isEmpty()){
                QStringList last_entry = main_seq_indexed.last();
                for(quint64 i = 0; i < arg_int; i++){
                    main_seq_indexed.insert((*rel_stamp), last_entry);
                    (*rel_stamp) += default_delay+1;
                    (*out).append(old_entry);
                }
            }else{
                return false;
            }
        }
    }
    return true;
}

void MainWindow::order_keypress_combination(QStringList *list){
    int val = 0, oldModifer = 3, n = (*list).length();
    int reset = true;
    while(val<n){
        int isModifer = 0;
        if(is_mod((*list).at(val)))
            isModifer = 1;
        if(oldModifer < isModifer && reset)
            reset = false;
        if(isModifer && !reset){
            QString tmp = (*list).at(val);
            (*list).removeAt(val);
            (*list).prepend(tmp);
            val = 0;
            oldModifer = 3;
            reset = true;
            continue;
        }
        val++;
        oldModifer = isModifer;
    }
}

bool MainWindow::is_mod(QString in){
    return in == "MODIFIERKEY_RIGHT_SHIFT" || in == "MODIFIERKEY_SHIFT" ||
        in == "MODIFIERKEY_LEFT_SHIFT" ||
        in == "MODIFIERKEY_RIGHT_ALT" || in == "MODIFIERKEY_ALT" ||
        in == "MODIFIERKEY_LEFT_ALT" ||
        in == "MODIFIERKEY_RIGHT_CTRL" || in == "MODIFIERKEY_CTRL" ||
        in == "MODIFIERKEY_LEFT_CTRL" ||
        in == "MODIFIERKEY_RIGHT_GUI" || in == "MODIFIERKEY_GUI" ||
        in == "MODIFIERKEY_LEFT_GUI";
}

void MainWindow::highlight(){
    main_sequence.clear();
    errors_found = false;
    int i, num_of_lines = ui->plainTextEdit->toPlainText().split("\n").length();
    QList<int> linePosNums;
    QColor highlight = QColor(Qt::lightGray).lighter(125);

    QTextEdit::ExtraSelection selection_current_line;
    QTextCursor cursor = ui->plainTextEdit->textCursor();
    QTextEdit::ExtraSelection selection_instruction_type;
    QList<QTextEdit::ExtraSelection> extraSelections;
    QColor red = QColor(Qt::red);
    QColor blue = QColor(Qt::blue);
    QColor magenta = QColor(Qt::magenta);
    QColor orange = QColor("orange");
    QColor green = QColor(Qt::green).darker(150);
    QColor black = QColor(Qt::black);
    QColor white = QColor(Qt::white);

    selection_current_line.format.setBackground(highlight);
    selection_current_line.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection_current_line.cursor = ui->plainTextEdit->textCursor();
    selection_current_line.cursor.clearSelection();
    extraSelections.append(selection_current_line);

    cursor.setPosition(0, QTextCursor::MoveAnchor);
    for(i=0; i<num_of_lines; i++){
        bool second_word_is_num, end = false;
        int fst_word_Line_pos = -1, sec_word_Line_pos = -1;
        QString firstword = QString(), secondword = QString(), testLine;
        QStringList lineDelimited;
        selection_instruction_type.cursor = cursor;
        selection_instruction_type.format.setBackground(white);
        selection_instruction_type.cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
        linePosNums.append(selection_instruction_type.cursor.position());
        selection_instruction_type.cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
        testLine = selection_instruction_type.cursor.selectedText();
        if(testLine.trimmed().isEmpty()){
            cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
            continue;
        }
        lineDelimited = testLine.split(QLatin1Char(' '));
        while(!end){
            int n = lineDelimited.length(), j;
            for(j=0; j<n; j++){
                if(lineDelimited.at(j).isEmpty()){
                    lineDelimited.removeAt(j);
                    break;
                }
                if(j==n-1)
                    end = true;
            }
        }

        firstword = lineDelimited.at(0).trimmed();
        fst_word_Line_pos = testLine.indexOf(firstword);

        if(lineDelimited.length() > 1){
            secondword = lineDelimited.at(1).trimmed();
            sec_word_Line_pos = testLine.indexOf(" "+secondword)+1;
        }
        secondword.toInt(&second_word_is_num);

        selection_instruction_type.cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
        if(firstword == QString("REM") || testLine.mid(0,3) == QString("REM")){
            selection_instruction_type.cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
            selection_instruction_type.format.setForeground(blue);
            extraSelections.append(selection_instruction_type);
        }else if(firstword == QString("ALT") && sec_word_Line_pos > 1 && (secondword.toLower() == QString("y") || secondword.toLower() == QString("j"))){
            selection_instruction_type.format.setForeground(white);
            selection_instruction_type.format.setBackground(black);
            selection_instruction_type.cursor.setPosition(linePosNums.at(i)+sec_word_Line_pos+secondword.length(), QTextCursor::KeepAnchor);
            extraSelections.append(selection_instruction_type);
            if(sec_word_Line_pos>0)
                main_sequence.append(QPair<QString, QString>(firstword.toUpper(), testLine.mid(sec_word_Line_pos)));
            else
                main_sequence.append(QPair<QString, QString>(firstword.toUpper(), testLine.mid(firstword.length()+((fst_word_Line_pos<0)?0:fst_word_Line_pos))));
        }else if( ( firstword == QString("DELAY") || firstword == QString("DEFAULT_DELAY") || firstword == QString("DEFAULTDELAY") ) && !secondword.isEmpty() && second_word_is_num && sec_word_Line_pos > 1){
            selection_instruction_type.format.setForeground(orange);
            selection_instruction_type.cursor.setPosition(linePosNums.at(i)+sec_word_Line_pos+secondword.length(), QTextCursor::KeepAnchor);
            extraSelections.append(selection_instruction_type);
            main_sequence.append(QPair<QString, QString>(firstword, testLine.mid(firstword.length()+((fst_word_Line_pos<0)?0:fst_word_Line_pos)).trimmed()));
        }else if(( firstword == QString("DELAY") || firstword == QString("DEFAULT_DELAY") || firstword == QString("DEFAULTDELAY") ) && secondword.isEmpty()){
            selection_instruction_type.format.setForeground(orange);
            selection_instruction_type.cursor.setPosition(linePosNums.at(i)+firstword.length(), QTextCursor::KeepAnchor);
            extraSelections.append(selection_instruction_type);
            main_sequence.append(QPair<QString, QString>(firstword, QString()));
        }else if(firstword == QString("REPEAT") && !secondword.isEmpty() && second_word_is_num && sec_word_Line_pos > 1){
            selection_instruction_type.format.setForeground(green);
            selection_instruction_type.cursor.setPosition(linePosNums.at(i)+sec_word_Line_pos+secondword.length(), QTextCursor::KeepAnchor);
            extraSelections.append(selection_instruction_type);
            if(sec_word_Line_pos>0)
                main_sequence.append(QPair<QString, QString>(firstword.toUpper(), testLine.mid(sec_word_Line_pos)));
            else
                main_sequence.append(QPair<QString, QString>(firstword.toUpper(), testLine.mid(firstword.length()+((fst_word_Line_pos<0)?0:fst_word_Line_pos))));
        }else if(cmd_list.contains(firstword.toUpper()) || keyprops.contains("KEY_"+firstword.toUpper())){
            selection_instruction_type.format.setForeground(red);
            selection_instruction_type.cursor.setPosition(linePosNums.at(i)+firstword.length()+((fst_word_Line_pos<0)?0:fst_word_Line_pos), QTextCursor::KeepAnchor);
            extraSelections.append(selection_instruction_type);
            if(firstword.toUpper() == "STRING")
                main_sequence.append(QPair<QString, QString>(firstword.toUpper(), testLine.mid(firstword.length()+1)));
            else if(sec_word_Line_pos>0)
                main_sequence.append(QPair<QString, QString>(firstword.toUpper(), testLine.mid(sec_word_Line_pos)));
            else
                main_sequence.append(QPair<QString, QString>(firstword.toUpper(), testLine.mid(firstword.length()+((fst_word_Line_pos<0)?0:fst_word_Line_pos))));
        }else if(!firstword.trimmed().isEmpty()){
            selection_instruction_type.format.setForeground(magenta);
            selection_instruction_type.format.setBackground(QColor(Qt::blue).lighter(160));
            selection_instruction_type.cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
            extraSelections.append(selection_instruction_type);
            errors_found = true;
        }
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
    }
    ui->plainTextEdit->setExtraSelections(extraSelections);
    if(errors_found)
        main_sequence.clear();
}

void MainWindow::on_actionDefault_triggered(){
    init_props(0);
}

void MainWindow::on_actionbe_triggered(){
    init_props(1);
}

void MainWindow::on_actionbr_triggered(){
    init_props(2);
}

void MainWindow::on_actionca_triggered(){
    init_props(3);
}

void MainWindow::on_actionch_triggered(){
    init_props(4);
}

void MainWindow::on_actionde_triggered(){
    init_props(5);
}

void MainWindow::on_actiondk_triggered(){
    init_props(6);
}

void MainWindow::on_actiones_triggered(){
    init_props(7);
}

void MainWindow::on_actionfi_triggered(){
    init_props(8);
}

void MainWindow::on_actionfr_triggered(){
    init_props(9);
}

void MainWindow::on_actiongb_triggered(){
    init_props(10);
}

void MainWindow::on_actionhr_triggered(){
    init_props(11);
}

void MainWindow::on_actionit_triggered(){
    init_props(12);
}

void MainWindow::on_actionno_triggered(){
    init_props(13);
}

void MainWindow::on_actionpl_triggered(){
    init_props(14);
}

void MainWindow::on_actionpt_triggered(){
    init_props(15);
}

void MainWindow::on_actionru_triggered(){
    init_props(16);
}

void MainWindow::on_actionsi_triggered(){
    init_props(17);
}

void MainWindow::on_actionsv_triggered(){
    init_props(18);
}

void MainWindow::on_actiontr_triggered(){
    init_props(19);
}

void MainWindow::on_actionus_triggered(){
    init_props(20);
}

void MainWindow::on_actionProgrammer_triggered(){
    QDialog *d = new QDialog(this);
    d->show();
    d->setWindowTitle("Programmer - "+windowTitle());
    d->setFixedSize(640,480);

    QVBoxLayout *qvblo = new QVBoxLayout();
    d->setLayout(qvblo);

    QHBoxLayout *qhblo1 = new QHBoxLayout();
    qvblo->addLayout(qhblo1);
    QLabel *labelInstructions = new QLabel(
                "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">WARNING: "
                "</span>This programmer is used to overwrite the USB Rubber Ducky's firmware, it i"
                "s not used to load DuckyScript onto the rubber ducky. You only need to use this p"
                "rogrammer when changing the USB Rubber Ducky's firmware to the &quot;Twin Duck&qu"
                "ot; or the &quot;Composite Duck&quot; or back the default USB Rubber Ducky's firm"
                "ware, or the like. To put the USB Rubber Ducky into firmware update mode, </p><p>"
                "<br/></p><p>1) With the USB Rubber Ducky not plugged in yet, Hold the little blac"
                "k button down.</p><p>2) Insert the USB Rubber Ducky into the USB slot on the comp"
                "uter.</p><p>3) Release the little black button</p><p>4) Select the .hex file cont"
                "aining the firmware you would like to upload the the USB Rubber Ducky</p><p>5) Pr"
                "ess the FIRMWARE UPDATE button</p></body></html>");
    labelInstructions->setWordWrap(true);
    qhblo1->addWidget(labelInstructions);

    QHBoxLayout *qhblo2 = new QHBoxLayout();
    qvblo->addLayout(qhblo2);
    QLineEdit *lineEditHexFilename = new QLineEdit();
    QPushButton *pushButtonFilenameDialog = new QPushButton("Open File");
    qhblo2->addWidget(lineEditHexFilename);
    qhblo2->addWidget(pushButtonFilenameDialog);

    QHBoxLayout *qhblo3 = new QHBoxLayout();
    qvblo->addLayout(qhblo3);
    QPushButton *pushButtonFirmwareUpdate = new QPushButton("FIRMWARE UPDATE");
    qhblo3->addStretch();
    qhblo3->addWidget(pushButtonFirmwareUpdate);

    QHBoxLayout *qhblo4 = new QHBoxLayout();
    qvblo->addLayout(qhblo4);
    QLabel *labelOutput = new QLabel();
    qhblo4->addWidget(labelOutput);

    qvblo->addStretch();

    QProcess *p1 = new QProcess();
    QProcess *p2 = new QProcess();
    QProcess *p3 = new QProcess();

    QFileDialog *openFile = new QFileDialog();
    openFile->setAcceptMode(QFileDialog::AcceptOpen);
    openFile->setFileMode(QFileDialog::ExistingFile);
    openFile->setNameFilters(QStringList() << "Hex Files (*.hex)" << "All Files (*)");
    connect(pushButtonFilenameDialog, &QPushButton::clicked, openFile, &QFileDialog::show);
    connect(openFile, &QFileDialog::accepted, [=](){
        QString filename = openFile->selectedFiles().at(0);
        if(QFileInfo(filename).exists())
            lineEditHexFilename->setText(filename);
        openFile->hide();
    });
    connect(openFile, &QFileDialog::rejected, openFile, &QFileDialog::hide);

    connect(pushButtonFirmwareUpdate, &QPushButton::clicked, [=](){
        labelOutput->setText("");
        if(QFileInfo(lineEditHexFilename->text()).exists() && QFileInfo(p->getProgrammer()).isExecutable()){
#if defined(Q_OS_LINUX)
            p1->start(p->getPkexec(), QStringList() << p->getProgrammer() << "at32uc3b1256" << "erase");
#elif defined(Q_OS_MACOS)
#elif defined(Q_OS_WINDOWS)
#endif
            if(p1->waitForFinished()){
                labelOutput->setText(p1->readAll()+"\r\n");
#if defined(Q_OS_LINUX)
                p2->start(p->getPkexec(), QStringList() << p->getProgrammer() << "at32uc3b1256" << "flash" << "--suppress-bootloader-mem" << lineEditHexFilename->text());
#elif defined(Q_OS_MACOS)
#elif defined(Q_OS_WINDOWS)
#endif
                if(p2->waitForFinished()){
                    labelOutput->setText(labelOutput->text()+"\r\n"+p2->readAll()+"\r\n");
#if defined(Q_OS_LINUX)
                    p3->start(p->getPkexec(), QStringList() << p->getProgrammer() << "at32uc3b1256" << "reset");
#elif defined(Q_OS_MACOS)
#elif defined(Q_OS_WINDOWS)
#endif
                    p3->waitForFinished();
                    labelOutput->setText(labelOutput->text()+"\r\n"+p3->readAll()+"\r\n");
                }
            }
        }else if(!QFileInfo(lineEditHexFilename->text()).exists()){
            labelOutput->setText("Hex File does not exist.");
        }else if(!QFileInfo(p->getProgrammer()).isExecutable()){
            labelOutput->setText("dfu-programmer does not exist or is not executable.");
        }
    });
}

void MainWindow::on_actionList_Functions_triggered(){
    QDialog *d = new QDialog(this);
    d->show();
    d->setWindowTitle("List Functions - "+windowTitle());
    d->setFixedSize(300, 200);

    QListWidget *listWidget = new QListWidget();
    QStringList sorted_list = cmd_list;
    sorted_list.sort();
    QStringListIterator i(sorted_list);
    while(i.hasNext())
        listWidget->addItem(i.next());

    QVBoxLayout *qvbl = new QVBoxLayout();
    d->setLayout(qvbl);
    qvbl->addWidget(listWidget);

    QHBoxLayout *qhbl1 = new QHBoxLayout();
    QPushButton *pushButtonClose = new QPushButton("Ok");

    qhbl1->addStretch();
    qhbl1->addWidget(pushButtonClose);
    qvbl->addLayout(qhbl1);

    connect(pushButtonClose, &QPushButton::clicked, [=](){
        d->close();
    });

}



























