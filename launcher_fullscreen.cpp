#include "launcher_fullscreen.h"
#include"fullscreenshowtablelabel.h"
using namespace std;
Launcher_FullScreen::Launcher_FullScreen(QWidget *parent)
    :QWidget(parent)
{
    QFile file(":/image/image/chinese.txt");
    if (file.open(QFile::ReadOnly|QFile::Text))
    {
        QString str=file.readAll();
        listPYfullscreen=str.split(" ");
    }
    result_menu->addAction(open_action);
    result_menu->addAction(set_auto_start);
    result_menu->addAction(send_to_desktop);
    result_menu_auto->addAction(open_action);
    result_menu_auto->addAction(unset_auto_start);
    result_menu_auto->addAction(send_to_desktop);
    result_menu_desktop->addAction(open_action);
    result_menu_desktop->addAction(set_auto_start);
    result_menu_desktop->addAction(remove_to_desktop);
    result_menu_auto_desktop->addAction(open_action);
    result_menu_auto_desktop->addAction(unset_auto_start);
    result_menu_auto_desktop->addAction(remove_to_desktop);
    move(0,0);
    resize(QApplication::desktop()->width(),QApplication::desktop()->height());
    fullscreen_movie->setFileName(":/image/image/fullscreen_background.jpg");
    fullscreen_movie->setScaledSize(QSize(QApplication::desktop()->width(),QApplication::desktop()->height()));
    show_movie->setMovie(fullscreen_movie);
    show_movie->move(0,0);
    show_movie->resize(QApplication::desktop()->width(),QApplication::desktop()->height());
    fullscreen_movie->start();
    show_movie->setStyleSheet("QLabel{background-color:rgba(255,255,255,25)}");
    setWindowFlags(Qt::Tool|Qt::FramelessWindowHint|Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setAutoFillBackground(false);
    setting_this->move(30,10);
    setting_this->resize(40,40);
    setting_this->setIcon(QIcon(":/image/image/setting_this.svg"));
    setting_this->setStyleSheet("QPushButton{border-radius:10px 10px;background:rgba(255,255,255,25)}"
                                "QPushButton:hover{border-radius:10px 10px;background:rgba(0,0,0,75)}"
                                "QPushButton:pressed{border-radius:10px 10px;background:rgba(255,255,255,25)}");
    back_to_simple->move(QApplication::desktop()->width()-50-20,10);
    back_to_simple->resize(40,40);
    back_to_simple->setIcon(QIcon(":/image/image/back_simple.svg"));
    back_to_simple->setStyleSheet("QPushButton{border-radius:10px 10px;background:rgba(255,255,255,25)}"
                                  "QPushButton:hover{border-radius:10px 10px;background:rgba(0,0,0,75)}"
                                  "QPushButton:pressed{border-radius:10px 10px;background:rgba(255,255,255,25)}");
    search_line->move(QApplication::desktop()->width()/2-360/2,10);
    search_line->resize(360,40);
    search_line->setStyleSheet("QLineEdit{border-radius:10px 10px;background:rgba(0,0,0,25);font-size:15px}");
    search_line->setPlaceholderText("搜索");
    search_img_action->setIcon(QIcon(":/image/image/search.svg"));
    search_line->addAction(search_img_action,QLineEdit::LeadingPosition);
    make_show_label->move(0,60);
    make_show_label->resize(QApplication::desktop()->width(),QApplication::desktop()->height()-150);
    search_del_action->setIcon(QIcon(":/image/image/del.svg"));
    connect(search_del_action,SIGNAL(triggered()),this,SLOT(del_search_text()));
    get_desktop_file();
    //
    int desktop_number=desktop_files_list.size();
    QHBoxLayout *layout=new QHBoxLayout();
    if (float(desktop_number/28)==float(desktop_number)/28)
    {
        make_show_label->set_end_page(desktop_number/28);
    }
    else
    {
        make_show_label->set_end_page(desktop_number/28+1);
    }
    make_show_label->button_update();
    delete make_show_label->show_desktop_label->layout();
    for (int i=0;i<make_view_list.size();i++)
    {
        for (int k=0;k<28;k++)
        {
            if (k<make_view_list[i]->model()->children().size())
            {
                delete make_view_list[i]->model()->children()[k];
            }
        }
        delete make_view_list[i];
    }
    make_view_list.clear();
    //7*4
    make_show_label->show_desktop_label->resize(QApplication::desktop()->width()*(desktop_number/28+1),QApplication::desktop()->height()-170);
    make_show_label->show_desktop_label->move(80,0);
    for (int i=0;i<desktop_number/28+1;i++)
    {
        OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
        Show_Desktop_Table_View->resize(QApplication::desktop()->width()-80,QApplication::desktop()->height()-170);
        Show_Desktop_Table_View->move((QApplication::desktop()->width()-80)*i,0);
        Show_Desktop_Table_View->setWrapping(true);
        Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
        Show_Desktop_Table_View->setViewMode(QListView::IconMode);
        Show_Desktop_Table_View->setIconSize(QSize((QApplication::desktop()->width()-170)/14,(QApplication::desktop()->width()-170)/14));
        Show_Desktop_Table_View->setGridSize(QSize((QApplication::desktop()->width()-170)/7,(QApplication::desktop()->height()-170)/4-5));
        Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
        Show_Desktop_Table_View->setWordWrap(true);
        Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
        Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(0,50)).x(),mapToGlobal(QPoint(0,50)).y());
        make_view_list.append(Show_Desktop_Table_View);
        layout->addWidget(Show_Desktop_Table_View);
        QStandardItemModel *model_table=new QStandardItemModel;
        QList<QStringList> desktop_list;
        QList<QStandardItem *> item_list;
        if (desktop_number!=0)
        {
        for (int k=0;k<28;k++)
        {
            if (desktop_files_list.size()<i*28+k+1)
            {
                k=28;
            }
            else
            {
                QStandardItem *item;
                bool is_auto=false;
                for (int j=0;j<auto_start_program_list.size();j++)
                {
                    if (desktop_files_list[i*28+k][0]==auto_start_program_list[j])
                    {
                        is_auto=true;
                    }
                }
                if (is_auto)
                {
                    QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                    QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*28+k][1]).pixmap(QSize(99,99));
                    QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                    result_image.fill(Qt::transparent);
                    QPainter *painter=new QPainter(&result_image);
                    painter->setPen(Qt::NoPen);
                    painter->setBrush(Qt::NoBrush);
                    painter->drawPixmap(0,0,theme_icon);
                    painter->drawPixmap(0,50,auto_start_img);
                    delete painter;
                    QPixmap result_pixmap=QPixmap::fromImage(result_image);
                    item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*28+k][0]);
                }
                else
                {
                    item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*28+k][1]),desktop_files_list[i*28+k][0]);
                }
                item->setSizeHint(QSize((QApplication::desktop()->width()-170)/7,(QApplication::desktop()->height()-170)/4-5));
                item_list.append(item);
                desktop_list.append(desktop_files_list[i*28+k]);
                model_table->appendRow(item);
            }
        }
        }
        Show_Desktop_Table_View->setModel(model_table);
        Show_Desktop_Table_View->set_information(item_list,desktop_list);
    }
    make_show_label->show_desktop_label->setLayout(layout);
    delete layout;
    //show
    show();
    timer->setInterval(30);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_update()));
    timer->start();
}
void Launcher_FullScreen::set_fullscreen_movie(QString movie_url)
{
    show_movie->setMovie(nullptr);
    fullscreen_movie->stop();
    QString filesname=movie_url;
    if (filesname.contains("file:///"))
    {
        filesname.remove(0,7);
    }
    if (filesname==nullptr)
    {
        fullscreen_movie->setFileName(":/image/image/fullscreen_background.jpg");
    }
    else
    {
        QFile file(filesname);
        if (file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            fullscreen_movie->setFileName(filesname);
        }
        else
        {
            fullscreen_movie->setFileName(":/image/image/fullscreen_background.jpg");
        }
    }
    fullscreen_movie->setScaledSize(QSize(QApplication::desktop()->width(),QApplication::desktop()->height()));
    show_movie->setMovie(fullscreen_movie);
    fullscreen_movie->start();
}
void Launcher_FullScreen::get_desktop_file()
{
    QDirIterator it("/usr/share/applications",{"*.desktop"},QDir::NoFilter,QDirIterator::FollowSymlinks);
    desktop_files_list.clear();
    while(it.hasNext())
    {
        const auto filename=it.next();
        QSettings desktopFile(filename,QSettings::IniFormat);
        desktopFile.setIniCodec(QTextCodec::codecForName("utf-8"));
        if (desktopFile.childGroups().contains("Desktop Entry"))
        {
            desktopFile.beginReadArray("Desktop Entry");
            bool can_pass=true;
            if (desktopFile.contains("NoDisplay"))
            {
                if (desktopFile.value("NoDisplay").toBool())
                {
                    can_pass=false;
                }
            }
            if (desktopFile.contains("OnlyShowIn"))
            {
                if (desktopFile.value("OnlyShowIn")!="Deepin"&&desktopFile.value("OnlyShowIn")!="KDE")
                {
                    can_pass=false;
                }
            }
            if (desktopFile.contains("NotShowIn"))
            {
                if (desktopFile.value("NotShowIn")!="GNOME")
                {
                    can_pass=false;
                }
            }
            if (can_pass)
            {
                QString name,icon,exec;
                if (desktopFile.contains("Name[zh_CN]"))
                {
                    name=desktopFile.value("Name[zh_CN]").toString();
                }
                else if (desktopFile.contains("Name[zh]"))
                {
                    name=desktopFile.value("Name[zh]").toString();
                }
                else if (desktopFile.contains("Name"))
                {
                    name=desktopFile.value("Name").toString();
                }
                else
                {
                    name="nullptr";
                }
                if (desktopFile.contains("Icon"))
                {
                    icon=desktopFile.value("Icon","application").toString();
                }
                else
                {
                    icon=":/image/image/demo.gif";
                }
                if (desktopFile.contains("Exec"))
                {
                    exec=desktopFile.value("Exec").toString().remove("\"").remove(QRegExp("%."));
                }
                else
                {
                    exec=nullptr;
                }
                QStringList desktop_information;
                desktop_information<<name<<icon<<exec<<filename;
                desktop_files_list.append(desktop_information);
            }
        }
    }
    QDirIterator it_home(QDir::homePath()+"/.local/share/applications",{"*.desktop"},QDir::NoFilter,QDirIterator::FollowSymlinks);
    while(it_home.hasNext())
    {
        const auto filename=it_home.next();
        QSettings desktopFile(filename,QSettings::IniFormat);
        desktopFile.setIniCodec(QTextCodec::codecForName("utf-8"));
        if (desktopFile.childGroups().contains("Desktop Entry"))
        {
            desktopFile.beginReadArray("Desktop Entry");
            bool can_pass=true;
            if (desktopFile.contains("NoDisplay"))
            {
                if (desktopFile.value("NoDisplay").toBool())
                {
                    can_pass=false;
                }
            }
            if (desktopFile.contains("OnlyShowIn"))
            {
                if (desktopFile.value("OnlyShowIn")!="Deepin"&&desktopFile.value("OnlyShowIn")!="KDE")
                {
                    can_pass=false;
                }
            }
            if (desktopFile.contains("NotShowIn"))
            {
                if (desktopFile.value("NotShowIn")!="GNOME")
                {
                    can_pass=false;
                }
            }
            if (can_pass)
            {
                QString name,icon,exec;
                if (desktopFile.contains("Name[zh_CN]"))
                {
                    name=desktopFile.value("Name[zh_CN]").toString();
                }
                else if (desktopFile.contains("Name[zh]"))
                {
                    name=desktopFile.value("Name[zh]").toString();
                }
                else if (desktopFile.contains("Name"))
                {
                    name=desktopFile.value("Name").toString();
                }
                else
                {
                    name="nullptr";
                }
                if (desktopFile.contains("Icon"))
                {
                    icon=desktopFile.value("Icon","application").toString();
                }
                else
                {
                    icon=":/image/image/demo.gif";
                }
                if (desktopFile.contains("Exec"))
                {
                    exec=desktopFile.value("Exec").toString().remove("\"").remove(QRegExp("%."));
                }
                else
                {
                    exec=nullptr;
                }
                QStringList desktop_information;
                desktop_information<<name<<icon<<exec<<filename;
                desktop_files_list.append(desktop_information);
            }
        }
    }
    QDirIterator it_auto_start(QDir::homePath()+"/.config/autostart",{"*.desktop"},QDir::NoFilter,QDirIterator::FollowSymlinks);
    auto_start_program_list.clear();
    while(it_auto_start.hasNext())
    {
        const auto filename=it_auto_start.next();
        QSettings desktopFile(filename,QSettings::IniFormat);
        desktopFile.setIniCodec(QTextCodec::codecForName("utf-8"));
        if (desktopFile.childGroups().contains("Desktop Entry"))
        {
            desktopFile.beginReadArray("Desktop Entry");
            bool can_pass=true;
            if (desktopFile.contains("Hidden"))
            {
                if (desktopFile.value("Hidden").toBool())
                {
                    can_pass=false;
                }
            }
            if (can_pass)
            {
                QString name=nullptr;
                if (desktopFile.contains("Name[zh_CN]"))
                {
                    name=desktopFile.value("Name[zh_CN]").toString();
                }
                else if (desktopFile.contains("Name[zh]"))
                {
                    name=desktopFile.value("Name[zh]").toString();
                }
                else if (desktopFile.contains("Name"))
                {
                    name=desktopFile.value("Name").toString();
                }
                if (name!=nullptr)
                {
                    auto_start_program_list<<name;
                }
            }
        }
    }
    QDirIterator it_get_desktop(QDir::homePath()+"/Desktop",{"*.desktop"},QDir::NoFilter,QDirIterator::FollowSymlinks);
    desktop_desktop_list.clear();
    while(it_get_desktop.hasNext())
    {
        const auto filename=it_get_desktop.next();
        QSettings desktopFile(filename,QSettings::IniFormat);
        desktopFile.setIniCodec(QTextCodec::codecForName("utf-8"));
        if (desktopFile.childGroups().contains("Desktop Entry"))
        {
            desktopFile.beginReadArray("Desktop Entry");
            bool can_pass=true;
            if (desktopFile.contains("NoDisplay"))
            {
                if (desktopFile.value("NoDisplay").toBool())
                {
                    can_pass=false;
                }
            }
            if (desktopFile.contains("OnlyShowIn"))
            {
                if (desktopFile.value("OnlyShowIn")!="Deepin"&&desktopFile.value("OnlyShowIn")!="KDE")
                {
                    can_pass=false;
                }
            }
            if (desktopFile.contains("NotShowIn"))
            {
                if (desktopFile.value("NotShowIn")!="GNOME")
                {
                    can_pass=false;
                }
            }
            if (can_pass)
            {
                QString name=nullptr;
                if (desktopFile.contains("Name[zh_CN]"))
                {
                    name=desktopFile.value("Name[zh_CN]").toString();
                }
                else if (desktopFile.contains("Name[zh]"))
                {
                    name=desktopFile.value("Name[zh]").toString();
                }
                else if (desktopFile.contains("Name"))
                {
                    name=desktopFile.value("Name").toString();
                }
                if (name!=nullptr)
                {
                    desktop_desktop_list<<name;
                }
            }
        }
    }
    sort(desktop_files_list.begin(),desktop_files_list.end(),sort_data);
}
bool sort_data(QStringList list1,QStringList list2)
{
    QString string1=list1[0],string2=list2[0];
    QString new_string1=nullptr,new_string2=nullptr;
    for (int i=0;i<string1.length();i++)
    {
        int unicode=QString::number(string1.at(i).unicode(),10).toInt();
        if (unicode>=0x4E00&&unicode<=0x9FA5)
        {
            new_string1.append(listPYfullscreen.at(unicode-0x4E00));
        }
        else
        {
            new_string1.append(string1.at(i));
        }
    }
    for (int i=0;i<string2.length();i++)
    {
        int unicode=QString::number(string2.at(i).unicode(),10).toInt();
        if (unicode>=0x4E00&&unicode<=0x9FA5)
        {
            new_string2.append(listPYfullscreen.at(unicode-0x4E00));
        }
        else
        {
            new_string2.append(string2.at(i));
        }
    }
    return new_string1.toLower()<new_string2.toLower();
}
void Launcher_FullScreen::timer_update()
{
    if (search_line->text().isEmpty())
    {
        if (!already_remove_del)
        {
            search_line->removeAction(search_del_action);
            already_remove_del=true;
        }
    }
    else
    {
        if (already_remove_del)
        {
            search_line->addAction(search_del_action,QLineEdit::TrailingPosition);
            already_remove_del=false;
        }
    }
    search_line->setFocus();
    if (search_words!=search_line->text())
    {
        search_words=search_line->text();
        get_desktop_file();
        if (search_line->text()!=nullptr)
        {
            search_get_desktop.clear();
            for (int i=0;i<desktop_files_list.size();i++)
            {
                if (desktop_files_list[i][0].contains(search_words,Qt::CaseInsensitive))
                {
                    search_get_desktop<<desktop_files_list[i];
                }
            }
            int desktop_number=search_get_desktop.size();
            QHBoxLayout *layout=new QHBoxLayout();
            if (float(desktop_number/28)==float(desktop_number)/28)
            {
                make_show_label->set_end_page(desktop_number/28);
            }
            else
            {
                make_show_label->set_end_page(desktop_number/28+1);
            }
            make_show_label->button_update();
            delete make_show_label->show_desktop_label->layout();
            for (int i=0;i<make_view_list.size();i++)
            {
                for (int k=0;k<28;k++)
                {
                    if (k<make_view_list[i]->model()->children().size())
                    {
                        delete make_view_list[i]->model()->children()[k];
                    }
                }
                delete make_view_list[i];
            }
            make_view_list.clear();
            //7*4
            make_show_label->show_desktop_label->resize(QApplication::desktop()->width()*(desktop_number/28+1),QApplication::desktop()->height()-170);
            make_show_label->show_desktop_label->move(80,0);
            for (int i=0;i<desktop_number/28+1;i++)
            {
                OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                Show_Desktop_Table_View->resize(QApplication::desktop()->width()-80,QApplication::desktop()->height()-170);
                Show_Desktop_Table_View->move((QApplication::desktop()->width()-80)*i,0);
                Show_Desktop_Table_View->setWrapping(true);
                Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                Show_Desktop_Table_View->setIconSize(QSize((QApplication::desktop()->width()-170)/14,(QApplication::desktop()->width()-170)/14));
                Show_Desktop_Table_View->setGridSize(QSize((QApplication::desktop()->width()-170)/7,(QApplication::desktop()->height()-170)/4-5));
                Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                Show_Desktop_Table_View->setWordWrap(true);
                Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(0,50)).x(),mapToGlobal(QPoint(0,50)).y());
                make_view_list.append(Show_Desktop_Table_View);
                layout->addWidget(Show_Desktop_Table_View);
                QStandardItemModel *model_table=new QStandardItemModel;
                QList<QStringList> desktop_list;
                QList<QStandardItem *> item_list;
                if (desktop_number!=0)
                {
                for (int k=0;k<28;k++)
                {
                    if (search_get_desktop.size()<i*28+k+1)
                    {
                        k=28;
                    }
                    else
                    {
                        QStandardItem *item;
                        bool is_auto=false;
                        for (int j=0;j<auto_start_program_list.size();j++)
                        {
                            if (search_get_desktop[i*28+k][0]==auto_start_program_list[j])
                            {
                                is_auto=true;
                            }
                        }
                        if (is_auto)
                        {
                            QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                            QPixmap theme_icon=QIcon::fromTheme(search_get_desktop[i*28+k][1]).pixmap(QSize(99,99));
                            QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                            result_image.fill(Qt::transparent);
                            QPainter *painter=new QPainter(&result_image);
                            painter->setPen(Qt::NoPen);
                            painter->setBrush(Qt::NoBrush);
                            painter->drawPixmap(0,0,theme_icon);
                            painter->drawPixmap(0,50,auto_start_img);
                            delete painter;
                            QPixmap result_pixmap=QPixmap::fromImage(result_image);
                            item=new QStandardItem(QIcon(result_pixmap),search_get_desktop[i*28+k][0]);
                        }
                        else
                        {
                            item=new QStandardItem(QIcon::fromTheme(search_get_desktop[i*28+k][1]),search_get_desktop[i*28+k][0]);
                        }
                        item->setSizeHint(QSize((QApplication::desktop()->width()-170)/7,(QApplication::desktop()->height()-170)/4-5));
                        item_list.append(item);
                        desktop_list.append(search_get_desktop[i*28+k]);
                        model_table->appendRow(item);
                    }
                }
                }
                Show_Desktop_Table_View->setModel(model_table);
                Show_Desktop_Table_View->set_information(item_list,desktop_list);
            }
            make_show_label->show_desktop_label->setLayout(layout);
            delete layout;
        }
        else
        {
            int desktop_number=desktop_files_list.size();
            QHBoxLayout *layout=new QHBoxLayout();
            if (float(desktop_number/28)==float(desktop_number)/28)
            {
                make_show_label->set_end_page(desktop_number/28);
            }
            else
            {
                make_show_label->set_end_page(desktop_number/28+1);
            }
            make_show_label->button_update();
            delete make_show_label->show_desktop_label->layout();
            for (int i=0;i<make_view_list.size();i++)
            {
                for (int k=0;k<28;k++)
                {
                    if (k<make_view_list[i]->model()->children().size())
                    {
                        delete make_view_list[i]->model()->children()[k];
                    }
                }
                delete make_view_list[i];
            }
            make_view_list.clear();
            //7*4
            make_show_label->show_desktop_label->resize(QApplication::desktop()->width()*(desktop_number/28+1),QApplication::desktop()->height()-170);
            make_show_label->show_desktop_label->move(80,0);
            for (int i=0;i<desktop_number/28+1;i++)
            {
                OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                Show_Desktop_Table_View->resize(QApplication::desktop()->width()-80,QApplication::desktop()->height()-170);
                Show_Desktop_Table_View->move((QApplication::desktop()->width()-80)*i,0);
                Show_Desktop_Table_View->setWrapping(true);
                Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                Show_Desktop_Table_View->setIconSize(QSize((QApplication::desktop()->width()-170)/14,(QApplication::desktop()->width()-170)/14));
                Show_Desktop_Table_View->setGridSize(QSize((QApplication::desktop()->width()-170)/7,(QApplication::desktop()->height()-170)/4-5));
                Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                Show_Desktop_Table_View->setWordWrap(true);
                Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(0,50)).x(),mapToGlobal(QPoint(0,50)).y());
                make_view_list.append(Show_Desktop_Table_View);
                layout->addWidget(Show_Desktop_Table_View);
                QStandardItemModel *model_table=new QStandardItemModel;
                QList<QStringList> desktop_list;
                QList<QStandardItem *> item_list;
                if (desktop_number!=0)
                {
                for (int k=0;k<28;k++)
                {
                    if (desktop_files_list.size()<i*28+k+1)
                    {
                        k=28;
                    }
                    else
                    {
                        QStandardItem *item;
                        bool is_auto=false;
                        for (int j=0;j<auto_start_program_list.size();j++)
                        {
                            if (desktop_files_list[i*28+k][0]==auto_start_program_list[j])
                            {
                                is_auto=true;
                            }
                        }
                        if (is_auto)
                        {
                            QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                            QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*28+k][1]).pixmap(QSize(99,99));
                            QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                            result_image.fill(Qt::transparent);
                            QPainter *painter=new QPainter(&result_image);
                            painter->setPen(Qt::NoPen);
                            painter->setBrush(Qt::NoBrush);
                            painter->drawPixmap(0,0,theme_icon);
                            painter->drawPixmap(0,50,auto_start_img);
                            delete painter;
                            QPixmap result_pixmap=QPixmap::fromImage(result_image);
                            item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*28+k][0]);
                        }
                        else
                        {
                            item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*28+k][1]),desktop_files_list[i*28+k][0]);
                        }
                        item->setSizeHint(QSize((QApplication::desktop()->width()-170)/7,(QApplication::desktop()->height()-170)/4-5));
                        item_list.append(item);
                        desktop_list.append(desktop_files_list[i*28+k]);
                        model_table->appendRow(item);
                    }
                }
                }
                Show_Desktop_Table_View->setModel(model_table);
                Show_Desktop_Table_View->set_information(item_list,desktop_list);
            }
            make_show_label->show_desktop_label->setLayout(layout);
            delete layout;
        }
    }
}
void Launcher_FullScreen::del_search_text()
{
    if (!search_line->text().isEmpty())
    {
        search_line->setText(nullptr);
    }
}
bool Launcher_FullScreen::get_pos_in(int pos_x,int pos_y,int in_x,int in_y,int in_size_x,int in_size_y)
{
    if (pos_x>=in_x&&pos_x<=in_x+in_size_x&&pos_y>=in_y&&pos_y<=in_y+in_size_y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Launcher_FullScreen::contextMenuEvent(QContextMenuEvent *event)
{
    if (get_pos_in(event->pos().x(),event->pos().y(),make_show_label->pos().x(),make_show_label->pos().y(),make_show_label->width(),make_show_label->height()))
    {
        if (make_view_list.size()>make_show_label->now_page-1)
        {
            int row=make_view_list[make_show_label->now_page-1]->currentIndex().row();
            if (row!=-1)
            {
                if (make_view_list[make_show_label->now_page-1]->desktop_files_list[row].size()==4)
                {
                    bool has_autostart=false,has_desktop=false;
                    for (int i=0;i<auto_start_program_list.size();i++)
                    {
                        if (make_view_list[make_show_label->now_page-1]->desktop_files_list[row][0]==auto_start_program_list[i])
                        {
                            has_autostart=true;
                        }
                    }
                    for (int i=0;i<desktop_desktop_list.size();i++)
                    {
                        if (make_view_list[make_show_label->now_page-1]->desktop_files_list[row][0]==desktop_desktop_list[i])
                        {
                            has_desktop=true;
                        }
                    }
                    QAction *know_what;
                    if (!has_autostart&&!has_desktop)
                    {
                        know_what=result_menu->exec(mapToGlobal(event->pos()));
                    }
                    else if (has_autostart&&!has_desktop)
                    {
                        know_what=result_menu_auto->exec(mapToGlobal(event->pos()));
                    }
                    else if (!has_autostart&&has_desktop)
                    {
                        know_what=result_menu_desktop->exec(mapToGlobal(event->pos()));
                    }
                    else if (has_autostart&&has_desktop)
                    {
                        know_what=result_menu_auto_desktop->exec(mapToGlobal(event->pos()));
                    }
                    if (know_what==open_action)
                    {
                        QString run="/bin/bash -c \"cd ~;"+make_view_list[make_show_label->now_page-1]->desktop_files_list[row][2]+"\"";
                        QProcess::startDetached(run);//could not open libreoffice*;//!!!java;
                        to_close_all=true;
                    }
                    if (know_what==set_auto_start)
                    {
                        QFileInfo fileinfo(make_view_list[make_show_label->now_page-1]->desktop_files_list[row][3]);
                        QString run="cp '"+make_view_list[make_show_label->now_page-1]->desktop_files_list[row][3]+"' '"+QDir::homePath()+"/.config/autostart/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                    if (know_what==send_to_desktop)
                    {
                        QFileInfo fileinfo(make_view_list[make_show_label->now_page-1]->desktop_files_list[row][3]);
                        QString run="cp '"+make_view_list[make_show_label->now_page-1]->desktop_files_list[row][3]+"' '"+QDir::homePath()+"/Desktop/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                    if (know_what==unset_auto_start)
                    {
                        QFileInfo fileinfo(make_view_list[make_show_label->now_page-1]->desktop_files_list[row][3]);
                        QString run="rm '"+QDir::homePath()+"/.config/autostart/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                    if (know_what==remove_to_desktop)
                    {
                        QFileInfo fileinfo(make_view_list[make_show_label->now_page-1]->desktop_files_list[row][3]);
                        QString run="rm '"+QDir::homePath()+"/Desktop/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                }
            }
        }
    }
}
void Launcher_FullScreen::all_update()
{
    get_desktop_file();
    if (search_line->text()!=nullptr)
    {
        search_get_desktop.clear();
        for (int i=0;i<desktop_files_list.size();i++)
        {
            if (desktop_files_list[i][0].contains(search_words,Qt::CaseInsensitive))
            {
                search_get_desktop<<desktop_files_list[i];
            }
        }
        int desktop_number=search_get_desktop.size();
        QHBoxLayout *layout=new QHBoxLayout();
        if (float(desktop_number/28)==float(desktop_number)/28)
        {
            make_show_label->set_end_page(desktop_number/28);
        }
        else
        {
            make_show_label->set_end_page(desktop_number/28+1);
        }
        make_show_label->button_update();
        delete make_show_label->show_desktop_label->layout();
        for (int i=0;i<make_view_list.size();i++)
        {
            for (int k=0;k<28;k++)
            {
                if (k<make_view_list[i]->model()->children().size())
                {
                    delete make_view_list[i]->model()->children()[k];
                }
            }
            delete make_view_list[i];
        }
        make_view_list.clear();
        //7*4
        make_show_label->show_desktop_label->resize(QApplication::desktop()->width()*(desktop_number/28+1),QApplication::desktop()->height()-170);
        make_show_label->show_desktop_label->move(80,0);
        for (int i=0;i<desktop_number/28+1;i++)
        {
            OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
            Show_Desktop_Table_View->resize(QApplication::desktop()->width()-80,QApplication::desktop()->height()-170);
            Show_Desktop_Table_View->move((QApplication::desktop()->width()-80)*i,0);
            Show_Desktop_Table_View->setWrapping(true);
            Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
            Show_Desktop_Table_View->setViewMode(QListView::IconMode);
            Show_Desktop_Table_View->setIconSize(QSize((QApplication::desktop()->width()-170)/14,(QApplication::desktop()->width()-170)/14));
            Show_Desktop_Table_View->setGridSize(QSize((QApplication::desktop()->width()-170)/7,(QApplication::desktop()->height()-170)/4-5));
            Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
            Show_Desktop_Table_View->setWordWrap(true);
            Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
            Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(0,50)).x(),mapToGlobal(QPoint(0,50)).y());
            make_view_list.append(Show_Desktop_Table_View);
            layout->addWidget(Show_Desktop_Table_View);
            QStandardItemModel *model_table=new QStandardItemModel;
            QList<QStringList> desktop_list;
            QList<QStandardItem *> item_list;
            if (desktop_number!=0)
            {
            for (int k=0;k<28;k++)
            {
                if (search_get_desktop.size()<i*28+k+1)
                {
                    k=28;
                }
                else
                {
                    QStandardItem *item;
                    bool is_auto=false;
                    for (int j=0;j<auto_start_program_list.size();j++)
                    {
                        if (search_get_desktop[i*28+k][0]==auto_start_program_list[j])
                        {
                            is_auto=true;
                        }
                    }
                    if (is_auto)
                    {
                        QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                        QPixmap theme_icon=QIcon::fromTheme(search_get_desktop[i*28+k][1]).pixmap(QSize(99,99));
                        QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                        result_image.fill(Qt::transparent);
                        QPainter *painter=new QPainter(&result_image);
                        painter->setPen(Qt::NoPen);
                        painter->setBrush(Qt::NoBrush);
                        painter->drawPixmap(0,0,theme_icon);
                        painter->drawPixmap(0,50,auto_start_img);
                        delete painter;
                        QPixmap result_pixmap=QPixmap::fromImage(result_image);
                        item=new QStandardItem(QIcon(result_pixmap),search_get_desktop[i*28+k][0]);
                    }
                    else
                    {
                        item=new QStandardItem(QIcon::fromTheme(search_get_desktop[i*28+k][1]),search_get_desktop[i*28+k][0]);
                    }
                    item->setSizeHint(QSize((QApplication::desktop()->width()-170)/7,(QApplication::desktop()->height()-170)/4-5));
                    item_list.append(item);
                    desktop_list.append(search_get_desktop[i*28+k]);
                    model_table->appendRow(item);
                }
            }
            }
            Show_Desktop_Table_View->setModel(model_table);
            Show_Desktop_Table_View->set_information(item_list,desktop_list);
        }
        make_show_label->show_desktop_label->setLayout(layout);
        delete layout;
    }
    else
    {
        int desktop_number=desktop_files_list.size();
        QHBoxLayout *layout=new QHBoxLayout();
        if (float(desktop_number/28)==float(desktop_number)/28)
        {
            make_show_label->set_end_page(desktop_number/28);
        }
        else
        {
            make_show_label->set_end_page(desktop_number/28+1);
        }
        make_show_label->button_update();
        delete make_show_label->show_desktop_label->layout();
        for (int i=0;i<make_view_list.size();i++)
        {
            for (int k=0;k<28;k++)
            {
                if (k<make_view_list[i]->model()->children().size())
                {
                    delete make_view_list[i]->model()->children()[k];
                }
            }
            delete make_view_list[i];
        }
        make_view_list.clear();
        //7*4
        make_show_label->show_desktop_label->resize(QApplication::desktop()->width()*(desktop_number/28+1),QApplication::desktop()->height()-170);
        make_show_label->show_desktop_label->move(80,0);
        for (int i=0;i<desktop_number/28+1;i++)
        {
            OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
            Show_Desktop_Table_View->resize(QApplication::desktop()->width()-80,QApplication::desktop()->height()-170);
            Show_Desktop_Table_View->move((QApplication::desktop()->width()-80)*i,0);
            Show_Desktop_Table_View->setWrapping(true);
            Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
            Show_Desktop_Table_View->setViewMode(QListView::IconMode);
            Show_Desktop_Table_View->setIconSize(QSize((QApplication::desktop()->width()-170)/14,(QApplication::desktop()->width()-170)/14));
            Show_Desktop_Table_View->setGridSize(QSize((QApplication::desktop()->width()-170)/7,(QApplication::desktop()->height()-170)/4-5));
            Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
            Show_Desktop_Table_View->setWordWrap(true);
            Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
            Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(0,50)).x(),mapToGlobal(QPoint(0,50)).y());
            make_view_list.append(Show_Desktop_Table_View);
            layout->addWidget(Show_Desktop_Table_View);
            QStandardItemModel *model_table=new QStandardItemModel;
            QList<QStringList> desktop_list;
            QList<QStandardItem *> item_list;
            if (desktop_number!=0)
            {
            for (int k=0;k<28;k++)
            {
                if (desktop_files_list.size()<i*28+k+1)
                {
                    k=28;
                }
                else
                {
                    QStandardItem *item;
                    bool is_auto=false;
                    for (int j=0;j<auto_start_program_list.size();j++)
                    {
                        if (desktop_files_list[i*28+k][0]==auto_start_program_list[j])
                        {
                            is_auto=true;
                        }
                    }
                    if (is_auto)
                    {
                        QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                        QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*28+k][1]).pixmap(QSize(99,99));
                        QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                        result_image.fill(Qt::transparent);
                        QPainter *painter=new QPainter(&result_image);
                        painter->setPen(Qt::NoPen);
                        painter->setBrush(Qt::NoBrush);
                        painter->drawPixmap(0,0,theme_icon);
                        painter->drawPixmap(0,50,auto_start_img);
                        delete painter;
                        QPixmap result_pixmap=QPixmap::fromImage(result_image);
                        item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*28+k][0]);
                    }
                    else
                    {
                        item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*28+k][1]),desktop_files_list[i*28+k][0]);
                    }
                    item->setSizeHint(QSize((QApplication::desktop()->width()-170)/7,(QApplication::desktop()->height()-170)/4-5));
                    item_list.append(item);
                    desktop_list.append(desktop_files_list[i*28+k]);
                    model_table->appendRow(item);
                }
            }
            }
            Show_Desktop_Table_View->setModel(model_table);
            Show_Desktop_Table_View->set_information(item_list,desktop_list);
        }
        make_show_label->show_desktop_label->setLayout(layout);
        delete layout;
    }
}
