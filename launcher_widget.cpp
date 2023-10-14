#include "launcher_widget.h"
#include"onlydraglistview.h"
#include<KWindowEffects>
#include<QApplication>
#include<iostream>
#include<fstream>
using namespace std;
Launcher_Widget::Launcher_Widget(QWidget *parent)
    :QWidget(parent)
{
    system("mkdir ~/.local/lib/my_launcher_data/love_desktop");
    result_menu->addAction(open_action);
    result_menu->addAction(add_to_love);
    result_menu->addAction(set_auto_start);
    result_menu->addAction(send_to_desktop);
    love_menu->addAction(open_action);
    love_menu->addAction(remove_to_love);
    love_menu->addAction(set_auto_start);
    love_menu->addAction(send_to_desktop);
    result_menu_auto->addAction(open_action);
    result_menu_auto->addAction(add_to_love);
    result_menu_auto->addAction(unset_auto_start);
    result_menu_auto->addAction(send_to_desktop);
    love_menu_auto->addAction(open_action);
    love_menu_auto->addAction(remove_to_love);
    love_menu_auto->addAction(unset_auto_start);
    love_menu_auto->addAction(send_to_desktop);
    result_menu_desktop->addAction(open_action);
    result_menu_desktop->addAction(add_to_love);
    result_menu_desktop->addAction(set_auto_start);
    result_menu_desktop->addAction(remove_to_desktop);
    love_menu_desktop->addAction(open_action);
    love_menu_desktop->addAction(remove_to_love);
    love_menu_desktop->addAction(set_auto_start);
    love_menu_desktop->addAction(remove_to_desktop);
    result_menu_auto_desktop->addAction(open_action);
    result_menu_auto_desktop->addAction(add_to_love);
    result_menu_auto_desktop->addAction(unset_auto_start);
    result_menu_auto_desktop->addAction(remove_to_desktop);
    love_menu_auto_desktop->addAction(open_action);
    love_menu_auto_desktop->addAction(remove_to_love);
    love_menu_auto_desktop->addAction(unset_auto_start);
    love_menu_auto_desktop->addAction(remove_to_desktop);
    setAcceptDrops(true);
    QFile file(":/image/image/chinese.txt");
    if (file.open(QFile::ReadOnly|QFile::Text))
    {
        QString str=file.readAll();
        listPY=str.split(" ");
    }
    resize(600,400);
    move(5,QApplication::desktop()->height()-40-5-400);
    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool|Qt::FramelessWindowHint|Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setAutoFillBackground(false);
    QPainterPath PP;
    PP.addRoundedRect(rect(),20,20);
    KWindowEffects::enableBlurBehind(winId(),true,PP.toFillPolygon().toPolygon());
    show_user_img->move(5,5);
    show_user_img->resize(40,40);
    user_img_movie->setFileName(":/image/image/demo.gif");
    user_img_movie->setScaledSize(QSize(40,40));
    show_user_img->setMovie(user_img_movie);
    user_img_movie->start();
    show_user_img->setStyleSheet("QLabel{border-radius:10px 10px;background:rgba(255,255,255,25)}");
    show_user_name->move(50,5);
    show_user_name->resize(150,40);
    user_name=qgetenv("USER");
    if (user_name.isEmpty())
    {
        user_name=qgetenv("USERNAME");
    }
    show_user_name->setText(user_name);
    show_user_name->setStyleSheet("QLabel{border-radius:10px 10px;background:rgba(255,255,255,25);font-size:20px;color:rgb(0,0,0)}");
    show_user_name->setAlignment(Qt::AlignCenter);
    to_full_screen->move(555,5);
    to_full_screen->resize(40,40);
    to_full_screen->setIcon(QIcon(":/image/image/fullscreen.svg"));
    to_full_screen->setStyleSheet("QPushButton{border-radius:10px 10px;background:rgba(255,255,255,25)}"
                                  "QPushButton:hover{border-radius:10px 10px;background:rgba(0,0,0,75)}"
                                  "QPushButton:pressed{border-radius:10px 10px;background:rgba(255,255,255,25)}");
    search_line->move(205,5);
    search_line->resize(345,40);
    search_line->setStyleSheet("QLineEdit{border-radius:10px 10px;background:rgba(0,0,0,25);font-size:15px}");
    search_line->setPlaceholderText("搜索");
    search_img_action->setIcon(QIcon(":/image/image/search.svg"));
    search_line->addAction(search_img_action,QLineEdit::LeadingPosition);
    search_del_action->setIcon(QIcon(":/image/image/del.svg"));
    connect(search_del_action,SIGNAL(triggered()),this,SLOT(del_search_text()));
    shutdown->move(565,365);
    shutdown->resize(30,30);
    shutdown->setIcon(QIcon(":/image/image/shutdown.svg"));
    shutdown->setStyleSheet("QPushButton{border-radius:10px 10px;background:rgba(0,0,0,25)}"
                            "QPushButton:hover{border-radius:10px 10px;background:rgba(0,0,0,75)}"
                            "QPushButton:pressed{border-radius:10px 10px;background:rgba(0,0,0,25)}");
    setting_dde->move(530,365);
    setting_dde->resize(30,30);
    setting_dde->setIcon(QIcon(":/image/image/setting_dde.svg"));
    setting_dde->setStyleSheet("QPushButton{border-radius:10px 10px;background:rgba(0,0,0,25)}"
                               "QPushButton:hover{border-radius:10px 10px;background:rgba(0,0,0,75)}"
                               "QPushButton:pressed{border-radius:10px 10px;background:rgba(0,0,0,25)}");
    setting_this->move(495,365);
    setting_this->resize(30,30);
    setting_this->setIcon(QIcon(":/image/image/setting_this.svg"));
    setting_this->setStyleSheet("QPushButton{border-radius:10px 10px;background:rgba(0,0,0,25)}"
                                "QPushButton:hover{border-radius:10px 10px;background:rgba(0,0,0,75)}"
                                "QPushButton:pressed{border-radius:10px 10px;background:rgba(0,0,0,25)}");
    connect(shutdown,SIGNAL(clicked()),this,SLOT(shut_down_click()));
    connect(setting_dde,SIGNAL(clicked()),this,SLOT(setting_dde_click()));
    show_class->move(5,50);
    show_class->resize(351,40);
    show_class->setStyleSheet("QLabel{border-radius:10px 10px;background:rgba(255,255,255,25);font-size:17px;color:rgb(0,0,0)}");
    show_class->setText("分类");
    show_love->move(361,50);
    show_love->resize(234,40);
    show_love->setStyleSheet("QLabel{border-radius:10px 10px;background:rgba(255,255,255,25);font-size:17px;color:rgb(0,0,0)}");
    show_love->setText("收藏");
    show_class_result->move(5,95);
    show_class_result->resize(351,300);
    show_class_result->setStyleSheet("QLabel{border-radius:10px 10px;background:rgba(255,255,255,25)}");
    show_love_result->move(361,95);
    show_love_result->resize(234,265);
    show_love_result->setStyleSheet("QLabel{border-radius:10px 10px;background:rgba(255,255,255,25)}");
    choose_love_button->move(560,55);
    choose_love_button->resize(30,30);
    choose_love_button->setIcon(QIcon(":/image/image/love.svg"));
    choose_love_button->setStyleSheet("QPushButton{border-radius:10px 10px;background:rgba(0,0,0,25)}"
                                      "QPushButton:hover{border-radius:10px 10px;background:rgba(0,0,0,75)}"
                                      "QPushButton:pressed{border-radius:10px 10px;background:rgba(0,0,0,25)}");
    choose_list_button->move(251,55);
    choose_list_button->resize(30,30);
    choose_list_button->setIcon(QIcon(":/image/image/list.svg"));
    choose_list_button->setStyleSheet("QPushButton{border-radius:10px 10px;background:rgba(0,0,0,25)}"
                                      "QPushButton:hover{border-radius:10px 10px;background:rgba(0,0,0,75)}"
                                      "QPushButton:pressed{border-radius:10px 10px;background:rgba(0,0,0,25)}");
    choose_table_button->move(286,55);
    choose_table_button->resize(30,30);
    choose_table_button->setIcon(QIcon(":/image/image/table.svg"));
    choose_table_button->setStyleSheet("QPushButton{border-radius:10px 10px;background:rgba(0,0,0,25)}"
                                       "QPushButton:hover{border-radius:10px 10px;background:rgba(0,0,0,75)}"
                                       "QPushButton:pressed{border-radius:10px 10px;background:rgba(0,0,0,25)}");
    choose_table_table_button->move(321,55);
    choose_table_table_button->resize(30,30);
    choose_table_table_button->setIcon(QIcon(":/image/image/table_table.svg"));
    choose_table_table_button->setStyleSheet("QPushButton{border-radius:10px 10px;background:rgba(0,0,0,25)}"
                                             "QPushButton:hover{border-radius:10px 10px;background:rgba(0,0,0,75)}"
                                             "QPushButton:pressed{border-radius:10px 10px;background:rgba(0,0,0,25)}");
    connect(choose_list_button,SIGNAL(clicked()),this,SLOT(choose_list_slot()));
    connect(choose_table_button,SIGNAL(clicked()),this,SLOT(choose_table_slot()));
    connect(choose_table_table_button,SIGNAL(clicked()),this,SLOT(choose_table_table_slot()));
    Show_Desktop_List_View->move(5,95);
    Show_Desktop_List_View->resize(351,300);
    Show_Desktop_List_View->setStyleSheet("QListView{background:rgba(0,0,0,0);color:rgb(0,0,0);border-radius:10px 10px}"
                                          "QListView::item:hover{background:rgba(255,255,255,100);border-left:3px solid rgb(0,85,255);color:rgb(0,0,0);border-radius:10px 10px}"
                                          "QListView::item:selected{background:rgba(0,170,255,255);color:rgb(255,255,255);border-radius:10px 10px}");
    Show_Desktop_List_View->setAlternatingRowColors(true);
    Show_Desktop_List_View->setIconSize(QSize(30,30));
    Show_Desktop_List_View->setGridSize(QSize(31,31));
    Show_Desktop_List_View->setLayoutDirection(Qt::LeftToRight);
    Show_Desktop_List_View->setEditTriggers(QListView::NoEditTriggers);
    get_desktop_file();
    model->clear();
    List_View_Item_List.clear();
    for (int i=0;i<desktop_files_list.size();i++)
    {
        QStandardItem *item;
        if (desktop_files_list[i].size()==4)
        {
            bool is_auto=false;
            for (int k=0;k<auto_start_program_list.size();k++)
            {
                if (desktop_files_list[i][0]==auto_start_program_list[k])
                {
                    is_auto=true;
                }
            }
            if (is_auto)
            {
                QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(15,15));
                QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i][1]).pixmap(QSize(30,30));
                QImage result_image(QSize(30,30),QImage::Format_RGBA8888);
                result_image.fill(Qt::transparent);
                QPainter *painter=new QPainter(&result_image);
                painter->setPen(Qt::NoPen);
                painter->setBrush(Qt::NoBrush);
                painter->drawPixmap(0,0,theme_icon);
                painter->drawPixmap(0,15,auto_start_img);
                delete painter;
                QPixmap result_pixmap=QPixmap::fromImage(result_image);
                item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i][0]);
            }
            else
            {
                item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i][1]),desktop_files_list[i][0]);
            }
        }
        else
        {
            item=new QStandardItem(desktop_files_list[i][0]);
            item->setSizeHint(QSize(35,35));
            item->setDragEnabled(false);
        }
        List_View_Item_List.append(item);
        model->appendRow(item);
    }
    Show_Desktop_List_View->setModel(model);
    connect(Show_Desktop_List_View,SIGNAL(clicked(QModelIndex)),this,SLOT(click_run_class()));
    show_table_label->move(5,95);
    show_table_label->resize(351,300);
    show_table_label->hide();
    Show_Desktop_List_View->set_information(List_View_Item_List,desktop_files_list);
    Show_Desktop_Table_Table_View->move(5,95);
    Show_Desktop_Table_Table_View->resize(351,300);
    Show_Desktop_Table_Table_View->setStyleSheet("QListView{background:rgba(0,0,0,0);color:rgb(0,0,0);border-radius:10px 10px}"
                                                 "QListView::item:hover{background:rgba(255,255,255,100);border-left:3px solid rgb(0,85,255);color:rgb(0,0,0);border-radius:10px 10px}"
                                                 "QListView::item:selected{background:rgba(0,170,255,255);color:rgb(255,255,255);border-radius:10px 10px}");
    Show_Desktop_Table_Table_View->setAlternatingRowColors(true);
    Show_Desktop_Table_Table_View->setIconSize(QSize(30,30));
    Show_Desktop_Table_Table_View->setGridSize(QSize(31,31));
    Show_Desktop_Table_Table_View->setLayoutDirection(Qt::LeftToRight);
    Show_Desktop_Table_Table_View->setEditTriggers(QListView::NoEditTriggers);
    Show_Desktop_Table_Table_View->set_information(Table_Table_View_Item_List,desktop_type_list);
    connect(Show_Desktop_Table_Table_View,SIGNAL(clicked(QModelIndex)),this,SLOT(click_run_class_table()));
    Show_Desktop_Table_Table_View->hide();
    show_love_label->move(361,95);
    show_love_label->resize(234,265);
    //
    int desktop_number=love_desktop_list.size();
    QHBoxLayout *layout=new QHBoxLayout();
    make_show_love_label->resize(234,265);
    make_show_love_label->show_desktop_label->resize((desktop_number/9+1)*234,255);
    if (float(desktop_number/9)==float(desktop_number)/9)
    {
        make_show_love_label->set_end_x(18*(desktop_number/9));
    }
    else
    {
        make_show_love_label->set_end_x(18*(desktop_number/9+1));
    }
    make_show_love_label->button_update();
    delete make_show_love_label->show_desktop_label->layout();
    for (int i=0;i<Love_view_list.size();i++)
    {
        for (int k=0;k<9;k++)
        {
            if (k<Love_view_list[i]->model()->children().size())
            {
                delete Love_view_list[i]->model()->children()[k];
            }
        }
        delete Love_view_list[i];
    }
    Love_view_list.clear();
    int no_pass_number=0;
    //3*3
    for (int i=0;i<desktop_number/9+1;i++)
    {
        OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
        Show_Desktop_Table_View->resize(234,255);
        Show_Desktop_Table_View->move(234*i,0);
        Show_Desktop_Table_View->setWrapping(true);
        Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
        Show_Desktop_Table_View->setViewMode(QListView::IconMode);
        Show_Desktop_Table_View->setIconSize(QSize(50,50));
        Show_Desktop_Table_View->setGridSize(QSize(77,85));
        Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
        Show_Desktop_Table_View->setWordWrap(true);
        Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
        Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
        Love_view_list.append(Show_Desktop_Table_View);
        layout->addWidget(Show_Desktop_Table_View);
        QStandardItemModel *model_table=new QStandardItemModel;
        QList<QStringList> desktop_list;
        QList<QStandardItem *> item_list;
        int number_k=0;
        if (desktop_number!=0)
        {
        int help_no_pass_number=0;
        for (int k=0;number_k<9;k++)
        {
            if (desktop_files_list.size()<i*9+k+no_pass_number+1)
            {
                number_k=k;
            }
            else
            {
            bool in_love=false;
            for (int l=0;l<love_desktop_list.size();l++)
            {
                if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number][0])
                {
                    in_love=true;
                }
            }
            if (desktop_files_list[i*9+k+no_pass_number].size()==4&&in_love)
            {
                number_k++;
                QStandardItem *item;
                bool is_auto=false;
                for (int j=0;j<auto_start_program_list.size();j++)
                {
                    if (desktop_files_list[i*9+k+no_pass_number][0]==auto_start_program_list[j])
                    {
                        is_auto=true;
                    }
                }
                if (is_auto)
                {
                    QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                    QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]).pixmap(QSize(99,99));
                    QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                    result_image.fill(Qt::transparent);
                    QPainter *painter=new QPainter(&result_image);
                    painter->setPen(Qt::NoPen);
                    painter->setBrush(Qt::NoBrush);
                    painter->drawPixmap(0,0,theme_icon);
                    painter->drawPixmap(0,50,auto_start_img);
                    delete painter;
                    QPixmap result_pixmap=QPixmap::fromImage(result_image);
                    item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number][0]);
                }
                else
                {
                    item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]),desktop_files_list[i*9+k+no_pass_number][0]);
                }
                item->setSizeHint(QSize(77,85));
                item_list.append(item);
                desktop_list.append(desktop_files_list[i*9+k+no_pass_number]);
                model_table->appendRow(item);
            }
            else
            {
                help_no_pass_number++;
            }
            }
        }
        no_pass_number+=help_no_pass_number;
        }
        Show_Desktop_Table_View->setModel(model_table);
        Show_Desktop_Table_View->set_information(item_list,desktop_list);
    }
    make_show_love_label->show_desktop_label->setLayout(layout);
    delete layout;
    for (int i=0;i<Table_view_list.size();i++)
    {
        Table_view_list[i]->Get_Now_Choose_type(choose_list_or_table);
    }
    //show
    timer->setInterval(30);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_update()));
    timer->start();
    show();
}
void Launcher_Widget::del_search_text()
{
    if (!search_line->text().isEmpty())
    {
        search_line->setText(nullptr);
    }
}
void Launcher_Widget::timer_update()
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
    if (choose_list_or_table==1)
    {
        choose_list_button->setIcon(QIcon(":/image/image/list_choose.svg"));
        choose_table_button->setIcon(QIcon(":/image/image/table.svg"));
        choose_table_table_button->setIcon(QIcon(":/image/image/table_table.svg"));
    }
    else if (choose_list_or_table==2)
    {
        choose_list_button->setIcon(QIcon(":/image/image/list.svg"));
        choose_table_button->setIcon(QIcon(":/image/image/table_choose.svg"));
        choose_table_table_button->setIcon(QIcon(":/image/image/table_table.svg"));
    }
    else if (choose_list_or_table==3)
    {
        choose_list_button->setIcon(QIcon(":/image/image/list.svg"));
        choose_table_button->setIcon(QIcon(":/image/image/table.svg"));
        choose_table_table_button->setIcon(QIcon(":/image/image/table_table_choose.svg"));
    }
    if (Search_string!=search_line->text())
    {
        Search_string=search_line->text();
        if (search_line->text()==nullptr)
        {
            get_desktop_file();
            for (int i=0;i<desktop_files_list.size();i++)
            {
                Show_Desktop_List_View->setRowHidden(i,false);
            }
            int desktop_number=0;
            for (int i=0;i<desktop_files_list.size();i++)
            {
                if (desktop_files_list[i].size()==4)
                {
                    desktop_number++;
                }
            }
            QHBoxLayout *layout=new QHBoxLayout();
            make_show_way_label->resize(351,300);
            make_show_way_label->show_desktop_label->resize((desktop_number/15+1)*351,290);
            if (float(desktop_number/15)==float(desktop_number)/15)
            {
                make_show_way_label->set_end_x(27*(desktop_number/15));
            }
            else
            {
                make_show_way_label->set_end_x(27*(desktop_number/15+1));
            }
            make_show_way_label->button_update();
            delete make_show_way_label->show_desktop_label->layout();
            for (int i=0;i<Table_view_list.size();i++)
            {
                for (int k=0;k<15;k++)
                {
                    if (k<Table_view_list[i]->model()->children().size())
                    {
                        delete Table_view_list[i]->model()->children()[k];
                    }
                }
                delete Table_view_list[i];
            }
            Table_view_list.clear();
            int no_pass_number=0;
            for (int i=0;i<desktop_number/15+1;i++)
            {
                OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                Show_Desktop_Table_View->resize(351,290);
                Show_Desktop_Table_View->move(351*i,0);
                Show_Desktop_Table_View->setWrapping(true);
                Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                Show_Desktop_Table_View->setIconSize(QSize(50,50));
                Show_Desktop_Table_View->setGridSize(QSize(69,95));
                Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                Show_Desktop_Table_View->setWordWrap(true);
                Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(5,95)).x(),mapToGlobal(QPoint(5,95)).y());
                Show_Desktop_Table_View->Get_Now_Choose_type(choose_list_or_table);
                Table_view_list.append(Show_Desktop_Table_View);
                layout->addWidget(Show_Desktop_Table_View);
                QStandardItemModel *model_table=new QStandardItemModel;
                QList<QStringList> desktop_list;
                QList<QStandardItem *> item_list;
                int number_k=0;
                if (desktop_number!=0)
                {
                int help_no_pass_number=0;
                for (int k=0;number_k<15;k++)
                {
                    if (desktop_files_list.size()<i*15+k+no_pass_number+1)
                    {
                        number_k=k;
                    }
                    else
                    {
                    if (desktop_files_list[i*15+k+no_pass_number].size()==4)
                    {
                        number_k++;
                        QStandardItem *item;
                        bool is_auto=false;
                        for (int j=0;j<auto_start_program_list.size();j++)
                        {
                            if (desktop_files_list[i*15+k+no_pass_number][0]==auto_start_program_list[j])
                            {
                                is_auto=true;
                            }
                        }
                        if (is_auto)
                        {
                            QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                            QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]).pixmap(QSize(99,99));
                            QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                            result_image.fill(Qt::transparent);
                            QPainter *painter=new QPainter(&result_image);
                            painter->setPen(Qt::NoPen);
                            painter->setBrush(Qt::NoBrush);
                            painter->drawPixmap(0,0,theme_icon);
                            painter->drawPixmap(0,50,auto_start_img);
                            delete painter;
                            QPixmap result_pixmap=QPixmap::fromImage(result_image);
                            item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*15+k+no_pass_number][0]);
                        }
                        else
                        {
                            item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]),desktop_files_list[i*15+k+no_pass_number][0]);
                        }
                        item->setSizeHint(QSize(69,95));
                        item_list.append(item);
                        desktop_list.append(desktop_files_list[i*15+k+no_pass_number]);
                        model_table->appendRow(item);
                    }
                    else
                    {
                        help_no_pass_number++;
                    }
                    }
                }
                no_pass_number+=help_no_pass_number;
                }
                Show_Desktop_Table_View->setModel(model_table);
                Show_Desktop_Table_View->set_information(item_list,desktop_list);
            }
            make_show_way_label->show_desktop_label->setLayout(layout);
            delete layout;
            for (int i=0;i<desktop_type_list.size();i++)
            {
                Show_Desktop_Table_Table_View->setRowHidden(i,false);
            }
            int desktop_number_love=love_desktop_list.size();
            QHBoxLayout *layout_love=new QHBoxLayout();
            make_show_love_label->resize(234,265);
            make_show_love_label->show_desktop_label->resize((desktop_number_love/9+1)*234,255);
            if (float(desktop_number_love/9)==float(desktop_number_love)/9)
            {
                make_show_love_label->set_end_x(18*(desktop_number_love/9));
            }
            else
            {
                make_show_love_label->set_end_x(18*(desktop_number_love/9+1));
            }
            make_show_love_label->button_update();
            delete make_show_love_label->show_desktop_label->layout();
            for (int i=0;i<Love_view_list.size();i++)
            {
                for (int k=0;k<9;k++)
                {
                    if (k<Love_view_list[i]->model()->children().size())
                    {
                        delete Love_view_list[i]->model()->children()[k];
                    }
                }
                delete Love_view_list[i];
            }
            Love_view_list.clear();
            int no_pass_number_love=0;
            //3*3
            for (int i=0;i<desktop_number_love/9+1;i++)
            {
                OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                Show_Desktop_Table_View->resize(234,255);
                Show_Desktop_Table_View->move(234*i,0);
                Show_Desktop_Table_View->setWrapping(true);
                Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                Show_Desktop_Table_View->setIconSize(QSize(50,50));
                Show_Desktop_Table_View->setGridSize(QSize(77,85));
                Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                Show_Desktop_Table_View->setWordWrap(true);
                Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
                Love_view_list.append(Show_Desktop_Table_View);
                layout_love->addWidget(Show_Desktop_Table_View);
                QStandardItemModel *model_table=new QStandardItemModel;
                QList<QStringList> desktop_list;
                QList<QStandardItem *> item_list;
                int number_k=0;
                if (desktop_number_love!=0)
                {
                int help_no_pass_number=0;
                for (int k=0;number_k<9;k++)
                {
                    if (desktop_files_list.size()<i*9+k+no_pass_number_love+1)
                    {
                        number_k=k;
                    }
                    else
                    {
                    bool in_love=false;
                    for (int l=0;l<love_desktop_list.size();l++)
                    {
                        if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number_love][0])
                        {
                            in_love=true;
                        }
                    }
                    if (desktop_files_list[i*9+k+no_pass_number_love].size()==4&&in_love)
                    {
                        number_k++;
                        QStandardItem *item;
                        bool is_auto=false;
                        for (int j=0;j<auto_start_program_list.size();j++)
                        {
                            if (desktop_files_list[i*9+k+no_pass_number_love][0]==auto_start_program_list[j])
                            {
                                is_auto=true;
                            }
                        }
                        if (is_auto)
                        {
                            QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                            QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number_love][1]).pixmap(QSize(99,99));
                            QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                            result_image.fill(Qt::transparent);
                            QPainter *painter=new QPainter(&result_image);
                            painter->setPen(Qt::NoPen);
                            painter->setBrush(Qt::NoBrush);
                            painter->drawPixmap(0,0,theme_icon);
                            painter->drawPixmap(0,50,auto_start_img);
                            delete painter;
                            QPixmap result_pixmap=QPixmap::fromImage(result_image);
                            item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number_love][0]);
                        }
                        else
                        {
                            item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number_love][1]),desktop_files_list[i*9+k+no_pass_number_love][0]);
                        }
                        item->setSizeHint(QSize(77,85));
                        item_list.append(item);
                        desktop_list.append(desktop_files_list[i*9+k+no_pass_number_love]);
                        model_table->appendRow(item);
                    }
                    else
                    {
                        help_no_pass_number++;
                    }
                    }
                }
                no_pass_number_love+=help_no_pass_number;
                }
                Show_Desktop_Table_View->setModel(model_table);
                Show_Desktop_Table_View->set_information(item_list,desktop_list);
            }
            make_show_love_label->show_desktop_label->setLayout(layout_love);
            delete layout_love;
        }
        else
        {
            if (choose_list_or_table==1)
            {
                for (int i=0;i<desktop_files_list.size();i++)
                {
                    if (desktop_files_list[i].size()==4)
                    {
                        QString desktop_name=desktop_files_list[i][0];
                        QString desktop_name2=from_way_to_name(desktop_files_list[i][3]);
                        if (desktop_name.contains(Search_string,Qt::CaseInsensitive)||desktop_name2.contains(Search_string,Qt::CaseInsensitive))
                        {
                            Show_Desktop_List_View->setRowHidden(i,false);
                        }
                        else
                        {
                            Show_Desktop_List_View->setRowHidden(i,true);
                        }
                    }
                }
            }
            else if (choose_list_or_table==2)
            {
                int desktop_number=0;
                for (int i=0;i<desktop_files_list.size();i++)
                {
                    if (desktop_files_list[i].size()==4&&(desktop_files_list[i][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i][3]).contains(Search_string,Qt::CaseInsensitive)))
                    {
                        desktop_number++;
                    }
                }
                QHBoxLayout *layout=new QHBoxLayout();
                make_show_way_label->resize(351,300);
                make_show_way_label->show_desktop_label->resize((desktop_number/15+1)*351,290);
                if (float(desktop_number/15)==float(desktop_number)/15)
                {
                    make_show_way_label->set_end_x(27*(desktop_number/15));
                }
                else
                {
                    make_show_way_label->set_end_x(27*(desktop_number/15+1));
                }
                make_show_way_label->set_now_page(1);
                make_show_way_label->button_update();
                delete make_show_way_label->show_desktop_label->layout();
                for (int i=0;i<Table_view_list.size();i++)
                {
                    for (int k=0;k<15;k++)
                    {
                        if (k<Table_view_list[i]->model()->children().size())
                        {
                            delete Table_view_list[i]->model()->children()[k];
                        }
                    }
                    delete Table_view_list[i];
                }
                Table_view_list.clear();
                int no_pass_number=0;
                for (int i=0;i<desktop_number/15+1;i++)
                {
                    OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                    Show_Desktop_Table_View->resize(351,290);
                    Show_Desktop_Table_View->move(351*i,0);
                    Show_Desktop_Table_View->setWrapping(true);
                    Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                    Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                    Show_Desktop_Table_View->setIconSize(QSize(50,50));
                    Show_Desktop_Table_View->setGridSize(QSize(69,95));
                    Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                    Show_Desktop_Table_View->setWordWrap(true);
                    Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                    Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(5,95)).x(),mapToGlobal(QPoint(5,95)).y());
                    Show_Desktop_Table_View->Get_Now_Choose_type(choose_list_or_table);
                    Table_view_list.append(Show_Desktop_Table_View);
                    layout->addWidget(Show_Desktop_Table_View);
                    QStandardItemModel *model_table=new QStandardItemModel;
                    QList<QStringList> desktop_list;
                    QList<QStandardItem *> item_list;
                    int number_k=0;
                    if (desktop_number!=0)
                    {
                    int help_no_pass_number=0;
                    for (int k=0;number_k<15;k++)
                    {
                        if (desktop_files_list.size()<i*15+k+no_pass_number+1)
                        {
                            number_k=k;
                        }
                        else
                        {
                        if (desktop_files_list[i*15+k+no_pass_number].size()==4&&(desktop_files_list[i*15+k+no_pass_number][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i*15+k+no_pass_number][3]).contains(Search_string,Qt::CaseInsensitive)))
                        {
                            number_k++;
                            QStandardItem *item;
                            bool is_auto=false;
                            for (int j=0;j<auto_start_program_list.size();j++)
                            {
                                if (desktop_files_list[i*15+k+no_pass_number][0]==auto_start_program_list[j])
                                {
                                    is_auto=true;
                                }
                            }
                            if (is_auto)
                            {
                                QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                                QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]).pixmap(QSize(99,99));
                                QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                                result_image.fill(Qt::transparent);
                                QPainter *painter=new QPainter(&result_image);
                                painter->setPen(Qt::NoPen);
                                painter->setBrush(Qt::NoBrush);
                                painter->drawPixmap(0,0,theme_icon);
                                painter->drawPixmap(0,50,auto_start_img);
                                delete painter;
                                QPixmap result_pixmap=QPixmap::fromImage(result_image);
                                item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*15+k+no_pass_number][0]);
                            }
                            else
                            {
                                item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]),desktop_files_list[i*15+k+no_pass_number][0]);
                            }
                            item->setSizeHint(QSize(69,95));
                            item_list.append(item);
                            desktop_list.append(desktop_files_list[i*15+k+no_pass_number]);
                            model_table->appendRow(item);
                        }
                        else
                        {
                            help_no_pass_number++;
                        }
                        }
                    }
                    no_pass_number+=help_no_pass_number;
                    }
                    Show_Desktop_Table_View->setModel(model_table);
                    Show_Desktop_Table_View->set_information(item_list,desktop_list);
                }
                make_show_way_label->show_desktop_label->setLayout(layout);
                delete layout;
            }
            else if (choose_list_or_table==3)
            {
                for (int i=0;i<desktop_type_list.size();i++)
                {
                    if (desktop_type_list[i].size()==4)
                    {
                        QString desktop_name=desktop_type_list[i][0];
                        QString desktop_name2=from_way_to_name(desktop_type_list[i][3]);
                        if (desktop_name.contains(Search_string,Qt::CaseInsensitive)||desktop_name2.contains(Search_string,Qt::CaseInsensitive))
                        {
                            Show_Desktop_Table_Table_View->setRowHidden(i,false);
                        }
                        else
                        {
                            Show_Desktop_Table_Table_View->setRowHidden(i,true);
                        }
                    }
                }
            }
            show_love_label->move(361,95);
            show_love_label->resize(234,265);
            //
            int desktop_number=0;
            for (int i=0;i<desktop_files_list.size();i++)
            {
                if (desktop_files_list[i].size()==4)
                {
                    for (int k=0;k<love_desktop_list.size();k++)
                    {
                        if (desktop_files_list[i][0]==love_desktop_list[k])
                        {
                            if (desktop_files_list[i][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i][3]).contains(Search_string,Qt::CaseInsensitive))
                            {
                                desktop_number++;
                            }
                        }
                    }
                }
            }
            QHBoxLayout *layout=new QHBoxLayout();
            make_show_love_label->resize(234,265);
            make_show_love_label->show_desktop_label->resize((desktop_number/9+1)*234,255);
            if (float(desktop_number/9)==float(desktop_number)/9)
            {
                make_show_love_label->set_end_x(18*(desktop_number/9));
            }
            else
            {
                make_show_love_label->set_end_x(18*(desktop_number/9+1));
            }
            make_show_love_label->set_now_page(1);
            make_show_love_label->button_update();
            delete make_show_love_label->show_desktop_label->layout();
            for (int i=0;i<Love_view_list.size();i++)
            {
                for (int k=0;k<9;k++)
                {
                    if (k<Love_view_list[i]->model()->children().size())
                    {
                        delete Love_view_list[i]->model()->children()[k];
                    }
                }
                delete Love_view_list[i];
            }
            Love_view_list.clear();
            int no_pass_number=0;
            //3*3
            for (int i=0;i<desktop_number/9+1;i++)
            {
                OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                Show_Desktop_Table_View->resize(234,255);
                Show_Desktop_Table_View->move(234*i,0);
                Show_Desktop_Table_View->setWrapping(true);
                Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                Show_Desktop_Table_View->setIconSize(QSize(50,50));
                Show_Desktop_Table_View->setGridSize(QSize(77,85));
                Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                Show_Desktop_Table_View->setWordWrap(true);
                Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
                Love_view_list.append(Show_Desktop_Table_View);
                layout->addWidget(Show_Desktop_Table_View);
                QStandardItemModel *model_table=new QStandardItemModel;
                QList<QStringList> desktop_list;
                QList<QStandardItem *> item_list;
                int number_k=0;
                if (desktop_number!=0)
                {
                int help_no_pass_number=0;
                for (int k=0;number_k<9;k++)
                {
                    if (desktop_files_list.size()<i*9+k+no_pass_number+1)
                    {
                        number_k=k;
                    }
                    else
                    {
                    bool in_love=false;
                    for (int l=0;l<love_desktop_list.size();l++)
                    {
                        if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number][0]&&(desktop_files_list[i*9+k+no_pass_number][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i*9+k+no_pass_number][3]).contains(Search_string,Qt::CaseInsensitive)))
                        {
                            in_love=true;
                        }
                    }
                    if (desktop_files_list[i*9+k+no_pass_number].size()==4&&in_love)
                    {
                        number_k++;
                        QStandardItem *item;
                        bool is_auto=false;
                        for (int j=0;j<auto_start_program_list.size();j++)
                        {
                            if (desktop_files_list[i*9+k+no_pass_number][0]==auto_start_program_list[j])
                            {
                                is_auto=true;
                            }
                        }
                        if (is_auto)
                        {
                            QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                            QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]).pixmap(QSize(99,99));
                            QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                            result_image.fill(Qt::transparent);
                            QPainter *painter=new QPainter(&result_image);
                            painter->setPen(Qt::NoPen);
                            painter->setBrush(Qt::NoBrush);
                            painter->drawPixmap(0,0,theme_icon);
                            painter->drawPixmap(0,50,auto_start_img);
                            delete painter;
                            QPixmap result_pixmap=QPixmap::fromImage(result_image);
                            item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number][0]);
                        }
                        else
                        {
                            item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]),desktop_files_list[i*9+k+no_pass_number][0]);
                        }
                        item->setSizeHint(QSize(77,85));
                        item_list.append(item);
                        desktop_list.append(desktop_files_list[i*9+k+no_pass_number]);
                        model_table->appendRow(item);
                    }
                    else
                    {
                        help_no_pass_number++;
                    }
                    }
                }
                no_pass_number+=help_no_pass_number;
                }
                Show_Desktop_Table_View->setModel(model_table);
                Show_Desktop_Table_View->set_information(item_list,desktop_list);
            }
            make_show_love_label->show_desktop_label->setLayout(layout);
            delete layout;
        }
    }
}
void Launcher_Widget::shut_down_click()
{
    QStringList list;
    list<<"--shutdown";
    QProcess::startDetached("dde-lock",list);
}
void Launcher_Widget::setting_dde_click()
{
    QStringList list;
    list<<"--show";
    QProcess::startDetached("dde-control-center",list);
}
void Launcher_Widget::choose_list_slot()
{
    choose_list_or_table=1;
    choose_list_button->setIcon(QIcon(":/image/image/list_choose.svg"));
    choose_table_button->setIcon(QIcon(":/image/image/table.svg"));
    choose_table_table_button->setIcon(QIcon(":/image/image/table_table.svg"));
    Show_Desktop_List_View->show();
    show_table_label->hide();
    Show_Desktop_Table_Table_View->hide();
    get_desktop_file();
    for (int i=0;i<List_View_Item_List.size();i++)
    {
        delete List_View_Item_List[i];
    }
    model->clear();
    List_View_Item_List.clear();
    for (int i=0;i<desktop_files_list.size();i++)
    {
        QStandardItem *item;
        if (desktop_files_list[i].size()==4)
        {
            bool is_auto=false;
            for (int k=0;k<auto_start_program_list.size();k++)
            {
                if (desktop_files_list[i][0]==auto_start_program_list[k])
                {
                    is_auto=true;
                }
            }
            if (is_auto)
            {
                QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(15,15));
                QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i][1]).pixmap(QSize(30,30));
                QImage result_image(QSize(30,30),QImage::Format_RGBA8888);
                result_image.fill(Qt::transparent);
                QPainter *painter=new QPainter(&result_image);
                painter->setPen(Qt::NoPen);
                painter->setBrush(Qt::NoBrush);
                painter->drawPixmap(0,0,theme_icon);
                painter->drawPixmap(0,15,auto_start_img);
                delete painter;
                QPixmap result_pixmap=QPixmap::fromImage(result_image);
                item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i][0]);
            }
            else
            {
                item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i][1]),desktop_files_list[i][0]);
            }
        }
        else
        {
            item=new QStandardItem(desktop_files_list[i][0]);
            item->setSizeHint(QSize(35,35));
        }
        List_View_Item_List.append(item);
        model->appendRow(item);
    }
    Show_Desktop_List_View->setModel(model);
    if (search_line->text()!=nullptr)
    {
        for (int i=0;i<desktop_files_list.size();i++)
        {
            if (desktop_files_list[i].size()==4)
            {
                QString desktop_name=desktop_files_list[i][0];
                QString desktop_name2=from_way_to_name(desktop_files_list[i][3]);
                if (desktop_name.contains(Search_string,Qt::CaseInsensitive)||desktop_name2.contains(Search_string,Qt::CaseInsensitive))
                {
                    Show_Desktop_List_View->setRowHidden(i,false);
                }
                else
                {
                    Show_Desktop_List_View->setRowHidden(i,true);
                }
            }
        }
    }
    Show_Desktop_List_View->set_information(List_View_Item_List,desktop_files_list);
    for (int i=0;i<Table_view_list.size();i++)
    {
        Table_view_list[i]->Get_Now_Choose_type(choose_list_or_table);
    }
}
void Launcher_Widget::choose_table_slot()
{
    choose_list_or_table=2;
    choose_list_button->setIcon(QIcon(":/image/image/list.svg"));
    choose_table_button->setIcon(QIcon(":/image/image/table_choose.svg"));
    choose_table_table_button->setIcon(QIcon(":/image/image/table_table.svg"));
    Show_Desktop_List_View->hide();
    show_table_label->show();
    Show_Desktop_Table_Table_View->hide();
    get_desktop_file();
    //5*3
    int desktop_number=0;
    for (int i=0;i<desktop_files_list.size();i++)
    {
        if (desktop_files_list[i].size()==4)
        {
            desktop_number++;
        }
    }
    QHBoxLayout *layout=new QHBoxLayout();
    make_show_way_label->resize(351,300);
    make_show_way_label->show_desktop_label->resize((desktop_number/15+1)*351,290);
    if (float(desktop_number/15)==float(desktop_number)/15)
    {
        make_show_way_label->set_end_x(27*(desktop_number/15));
    }
    else
    {
        make_show_way_label->set_end_x(27*(desktop_number/15+1));
    }
    make_show_way_label->button_update();
    delete make_show_way_label->show_desktop_label->layout();
    for (int i=0;i<Table_view_list.size();i++)
    {
        for (int k=0;k<15;k++)
        {
            if (k<Table_view_list[i]->model()->children().size())
            {
                delete Table_view_list[i]->model()->children()[k];
            }
        }
        delete Table_view_list[i];
    }
    Table_view_list.clear();
    int no_pass_number=0;
    for (int i=0;i<desktop_number/15+1;i++)
    {
        OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
        Show_Desktop_Table_View->resize(351,290);
        Show_Desktop_Table_View->move(351*i,0);
        Show_Desktop_Table_View->setWrapping(true);
        Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
        Show_Desktop_Table_View->setViewMode(QListView::IconMode);
        Show_Desktop_Table_View->setIconSize(QSize(50,50));
        Show_Desktop_Table_View->setGridSize(QSize(69,95));
        Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
        Show_Desktop_Table_View->setWordWrap(true);
        Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
        Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(5,95)).x(),mapToGlobal(QPoint(5,95)).y());
        Show_Desktop_Table_View->Get_Now_Choose_type(choose_list_or_table);
        Table_view_list.append(Show_Desktop_Table_View);
        layout->addWidget(Show_Desktop_Table_View);
        QStandardItemModel *model_table=new QStandardItemModel;
        QList<QStringList> desktop_list;
        QList<QStandardItem *> item_list;
        int number_k=0;
        if (desktop_number!=0)
        {
        int help_no_pass_number=0;
        for (int k=0;number_k<15;k++)
        {
            if (desktop_files_list.size()<i*15+k+no_pass_number+1)
            {
                number_k=k;
            }
            else
            {
            if (desktop_files_list[i*15+k+no_pass_number].size()==4)
            {
                number_k++;
                QStandardItem *item;
                bool is_auto=false;
                for (int j=0;j<auto_start_program_list.size();j++)
                {
                    if (desktop_files_list[i*15+k+no_pass_number][0]==auto_start_program_list[j])
                    {
                        is_auto=true;
                    }
                }
                if (is_auto)
                {
                    QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                    QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]).pixmap(QSize(99,99));
                    QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                    result_image.fill(Qt::transparent);
                    QPainter *painter=new QPainter(&result_image);
                    painter->setPen(Qt::NoPen);
                    painter->setBrush(Qt::NoBrush);
                    painter->drawPixmap(0,0,theme_icon);
                    painter->drawPixmap(0,50,auto_start_img);
                    delete painter;
                    QPixmap result_pixmap=QPixmap::fromImage(result_image);
                    item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*15+k+no_pass_number][0]);
                }
                else
                {
                    item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]),desktop_files_list[i*15+k+no_pass_number][0]);
                }
                item->setSizeHint(QSize(69,95));
                item_list.append(item);
                desktop_list.append(desktop_files_list[i*15+k+no_pass_number]);
                model_table->appendRow(item);
            }
            else
            {
                help_no_pass_number++;
            }
            }
        }
        no_pass_number+=help_no_pass_number;
        }
        Show_Desktop_Table_View->setModel(model_table);
        Show_Desktop_Table_View->set_information(item_list,desktop_list);
    }
    make_show_way_label->show_desktop_label->setLayout(layout);
    delete layout;
    if (search_line->text()!=nullptr)
    {
        int desktop_number=0;
        for (int i=0;i<desktop_files_list.size();i++)
        {
            if (desktop_files_list[i].size()==4&&(desktop_files_list[i][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i][3]).contains(Search_string,Qt::CaseInsensitive)))
            {
                desktop_number++;
            }
        }
        QHBoxLayout *layout=new QHBoxLayout();
        make_show_way_label->resize(351,300);
        make_show_way_label->show_desktop_label->resize((desktop_number/15+1)*351,290);
        if (float(desktop_number/15)==float(desktop_number)/15)
        {
            make_show_way_label->set_end_x(27*(desktop_number/15));
        }
        else
        {
            make_show_way_label->set_end_x(27*(desktop_number/15+1));
        }
        make_show_way_label->set_now_page(1);
        make_show_way_label->button_update();
        delete make_show_way_label->show_desktop_label->layout();
        for (int i=0;i<Table_view_list.size();i++)
        {
            for (int k=0;k<15;k++)
            {
                if (k<Table_view_list[i]->model()->children().size())
                {
                    delete Table_view_list[i]->model()->children()[k];
                }
            }
            delete Table_view_list[i];
        }
        Table_view_list.clear();
        int no_pass_number=0;
        for (int i=0;i<desktop_number/15+1;i++)
        {
            OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
            Show_Desktop_Table_View->resize(351,290);
            Show_Desktop_Table_View->move(351*i,0);
            Show_Desktop_Table_View->setWrapping(true);
            Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
            Show_Desktop_Table_View->setViewMode(QListView::IconMode);
            Show_Desktop_Table_View->setIconSize(QSize(50,50));
            Show_Desktop_Table_View->setGridSize(QSize(69,95));
            Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
            Show_Desktop_Table_View->setWordWrap(true);
            Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
            Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(5,95)).x(),mapToGlobal(QPoint(5,95)).y());
            Show_Desktop_Table_View->Get_Now_Choose_type(choose_list_or_table);
            Table_view_list.append(Show_Desktop_Table_View);
            layout->addWidget(Show_Desktop_Table_View);
            QStandardItemModel *model_table=new QStandardItemModel;
            QList<QStringList> desktop_list;
            QList<QStandardItem *> item_list;
            int number_k=0;
            if (desktop_number!=0)
            {
            int help_no_pass_number=0;
            for (int k=0;number_k<15;k++)
            {
                if (desktop_files_list.size()<i*15+k+no_pass_number+1)
                {
                    number_k=k;
                }
                else
                {
                if (desktop_files_list[i*15+k+no_pass_number].size()==4&&(desktop_files_list[i*15+k+no_pass_number][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i*15+k+no_pass_number][3]).contains(Search_string,Qt::CaseInsensitive)))
                {
                    number_k++;
                    QStandardItem *item;
                    bool is_auto=false;
                    for (int j=0;j<auto_start_program_list.size();j++)
                    {
                        if (desktop_files_list[i*15+k+no_pass_number][0]==auto_start_program_list[j])
                        {
                            is_auto=true;
                        }
                    }
                    if (is_auto)
                    {
                        QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                        QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]).pixmap(QSize(99,99));
                        QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                        result_image.fill(Qt::transparent);
                        QPainter *painter=new QPainter(&result_image);
                        painter->setPen(Qt::NoPen);
                        painter->setBrush(Qt::NoBrush);
                        painter->drawPixmap(0,0,theme_icon);
                        painter->drawPixmap(0,50,auto_start_img);
                        delete painter;
                        QPixmap result_pixmap=QPixmap::fromImage(result_image);
                        item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*15+k+no_pass_number][0]);
                    }
                    else
                    {
                        item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]),desktop_files_list[i*15+k+no_pass_number][0]);
                    }
                    item->setSizeHint(QSize(69,95));
                    item_list.append(item);
                    desktop_list.append(desktop_files_list[i*15+k+no_pass_number]);
                    model_table->appendRow(item);
                }
                else
                {
                    help_no_pass_number++;
                }
                }
            }
            no_pass_number+=help_no_pass_number;
            }
            Show_Desktop_Table_View->setModel(model_table);
            Show_Desktop_Table_View->set_information(item_list,desktop_list);
        }
        make_show_way_label->show_desktop_label->setLayout(layout);
        delete layout;
    }
}
void Launcher_Widget::choose_table_table_slot()
{
    choose_list_or_table=3;
    choose_list_button->setIcon(QIcon(":/image/image/list.svg"));
    choose_table_button->setIcon(QIcon(":/image/image/table.svg"));
    choose_table_table_button->setIcon(QIcon(":/image/image/table_table_choose.svg"));
    Show_Desktop_List_View->hide();
    show_table_label->hide();
    Show_Desktop_Table_Table_View->show();
    get_desktop_file();
    for (int i=0;i<Table_Table_View_Item_List.size();i++)
    {
        delete Table_Table_View_Item_List[i];
    }
    model_table_table->clear();
    Table_Table_View_Item_List.clear();
    for (int i=0;i<desktop_type_list.size();i++)
    {
        QStandardItem *item;
        if (desktop_type_list[i].size()==4)
        {
            bool is_auto=false;
            for (int k=0;k<auto_start_program_list.size();k++)
            {
                if (desktop_type_list[i][0]==auto_start_program_list[k])
                {
                    is_auto=true;
                }
            }
            if (is_auto)
            {
                QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(15,15));
                QPixmap theme_icon=QIcon::fromTheme(desktop_type_list[i][1]).pixmap(QSize(30,30));
                QImage result_image(QSize(30,30),QImage::Format_RGBA8888);
                result_image.fill(Qt::transparent);
                QPainter *painter=new QPainter(&result_image);
                painter->setPen(Qt::NoPen);
                painter->setBrush(Qt::NoBrush);
                painter->drawPixmap(0,0,theme_icon);
                painter->drawPixmap(0,15,auto_start_img);
                delete painter;
                QPixmap result_pixmap=QPixmap::fromImage(result_image);
                item=new QStandardItem(QIcon(result_pixmap),desktop_type_list[i][0]);
            }
            else
            {
                item=new QStandardItem(QIcon::fromTheme(desktop_type_list[i][1]),desktop_type_list[i][0]);
            }
        }
        else
        {
            item=new QStandardItem(desktop_type_list[i][0]);
            item->setSizeHint(QSize(35,35));
        }
        Table_Table_View_Item_List.append(item);
        model_table_table->appendRow(item);
    }
    Show_Desktop_Table_Table_View->setModel(model_table_table);
    if (search_line->text()!=nullptr)
    {
        for (int i=0;i<desktop_type_list.size();i++)
        {
            if (desktop_type_list[i].size()==4)
            {
                QString desktop_name=desktop_type_list[i][0];
                QString desktop_name2=from_way_to_name(desktop_type_list[i][3]);
                if (desktop_name.contains(Search_string,Qt::CaseInsensitive)||desktop_name2.contains(Search_string,Qt::CaseInsensitive))
                {
                    Show_Desktop_Table_Table_View->setRowHidden(i,false);
                }
                else
                {
                    Show_Desktop_Table_Table_View->setRowHidden(i,true);
                }
            }
        }
    }
    Show_Desktop_Table_Table_View->set_information(Table_Table_View_Item_List,desktop_type_list);
    for (int i=0;i<Table_view_list.size();i++)
    {
        Table_view_list[i]->Get_Now_Choose_type(choose_list_or_table);
    }
}
void Launcher_Widget::get_desktop_file()
{
    QList<QStringList> Network_type,Chat_type,Audio_type,Video_type,Graphics_type,Game_type,Office_type/*add Utility*/,Translation_type,Development_type,System_type,Other_type;
    QDirIterator it("/usr/share/applications",{"*.desktop"},QDir::NoFilter,QDirIterator::FollowSymlinks);
    desktop_files_list.clear();
    desktop_type_list.clear();
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
                if (desktopFile.contains("Terminal"))
                {
                    if (desktopFile.value("Terminal").toString()=="true")
                    {
                        exec.append("|terminal|");
                    }
                }
                QStringList desktop_information;
                desktop_information<<name<<icon<<exec<<filename;
                desktop_files_list.append(desktop_information);
                if (desktopFile.contains("Categories"))
                {
                    ifstream load_data;
                    load_data.open(filename.toStdString(),ios::in);
                    string s;
                    QString result_qstring;
                    while(getline(load_data,s))
                    {
                        if (QString::fromStdString(s).contains("Categories="))
                        {
                            result_qstring=QString::fromStdString(s);
                            result_qstring.remove(0,11);
                        }
                    }
                    if (result_qstring.contains("Network",Qt::CaseInsensitive)||result_qstring.contains("downloader",Qt::CaseInsensitive))
                    {
                        Network_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Chat",Qt::CaseInsensitive))
                    {
                        Chat_type.append(desktop_information);
                    }
                    else if ((result_qstring.contains("Video",Qt::CaseInsensitive)&&!result_qstring.contains("AudioVideo",Qt::CaseInsensitive))||((result_qstring.contains("Player",Qt::CaseInsensitive)||result_qstring.contains("Recorder",Qt::CaseInsensitive))&&result_qstring.contains("AudioVideo",Qt::CaseInsensitive))||(result_qstring.contains("AudioVideoEditing",Qt::CaseInsensitive)&&!result_qstring.contains("Audio;",Qt::CaseInsensitive)))
                    {
                        Video_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Audio",Qt::CaseInsensitive))
                    {
                        Audio_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Graphics",Qt::CaseInsensitive))
                    {
                        Graphics_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Game",Qt::CaseInsensitive))
                    {
                        Game_type.append(desktop_information);
                    }
                    else if ((result_qstring.contains("Office",Qt::CaseInsensitive)||result_qstring.contains("Documentation",Qt::CaseInsensitive)||result_qstring.contains("TextEditor",Qt::CaseInsensitive))&&!result_qstring.contains("System",Qt::CaseInsensitive)&&!result_qstring.contains("IDE",Qt::CaseInsensitive))
                    {
                        Office_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("System",Qt::CaseInsensitive)||result_qstring.contains("Utility",Qt::CaseInsensitive)||result_qstring.contains("Compression",Qt::CaseInsensitive)||result_qstring.contains("KDE",Qt::CaseInsensitive))
                    {
                        System_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Translation",Qt::CaseInsensitive))
                    {
                        Translation_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Development",Qt::CaseInsensitive))
                    {
                        Development_type.append(desktop_information);
                    }
                    else
                    {
                        Other_type.append(desktop_information);
                    }
                }
                else
                {
                    Other_type.append(desktop_information);
                }
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
                if (desktopFile.contains("Terminal"))
                {
                    if (desktopFile.value("Terminal").toString()=="true")
                    {
                        exec.append("|terminal|");
                    }
                }
                QStringList desktop_information;
                desktop_information<<name<<icon<<exec<<filename;
                desktop_files_list.append(desktop_information);
                if (desktopFile.contains("Categories"))
                {
                    ifstream load_data;
                    load_data.open(filename.toStdString(),ios::in);
                    string s;
                    QString result_qstring;
                    while(getline(load_data,s))
                    {
                        if (QString::fromStdString(s).contains("Categories="))
                        {
                            result_qstring=QString::fromStdString(s);
                            result_qstring.remove(0,11);
                        }
                    }
                    if (result_qstring.contains("Network",Qt::CaseInsensitive)||result_qstring.contains("downloader",Qt::CaseInsensitive))
                    {
                        Network_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Chat",Qt::CaseInsensitive))
                    {
                        Chat_type.append(desktop_information);
                    }
                    else if ((result_qstring.contains("Video",Qt::CaseInsensitive)&&!result_qstring.contains("AudioVideo",Qt::CaseInsensitive))||((result_qstring.contains("Player",Qt::CaseInsensitive)||result_qstring.contains("Recorder",Qt::CaseInsensitive))&&result_qstring.contains("AudioVideo",Qt::CaseInsensitive))||(result_qstring.contains("AudioVideoEditing",Qt::CaseInsensitive)&&!result_qstring.contains("Audio;",Qt::CaseInsensitive)))
                    {
                        Video_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Audio",Qt::CaseInsensitive))
                    {
                        Audio_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Graphics",Qt::CaseInsensitive))
                    {
                        Graphics_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Game",Qt::CaseInsensitive))
                    {
                        Game_type.append(desktop_information);
                    }
                    else if ((result_qstring.contains("Office",Qt::CaseInsensitive)||result_qstring.contains("Documentation",Qt::CaseInsensitive)||result_qstring.contains("TextEditor",Qt::CaseInsensitive))&&!result_qstring.contains("System",Qt::CaseInsensitive)&&!result_qstring.contains("IDE",Qt::CaseInsensitive))
                    {
                        Office_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("System",Qt::CaseInsensitive)||result_qstring.contains("Utility",Qt::CaseInsensitive)||result_qstring.contains("Compression",Qt::CaseInsensitive)||result_qstring.contains("KDE",Qt::CaseInsensitive))
                    {
                        System_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Translation",Qt::CaseInsensitive))
                    {
                        Translation_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Development",Qt::CaseInsensitive))
                    {
                        Development_type.append(desktop_information);
                    }
                    else
                    {
                        Other_type.append(desktop_information);
                    }
                }
                else
                {
                    Other_type.append(desktop_information);
                }
            }
        }
    }
    QDirIterator it_linglong("/data/linglong/entries/share/applications",{"*.desktop"},QDir::NoFilter,QDirIterator::FollowSymlinks);
    while(it_linglong.hasNext())
    {
        const auto filename=it_linglong.next();
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
                if (desktopFile.contains("Terminal"))
                {
                    if (desktopFile.value("Terminal").toString()=="true")
                    {
                        exec.append("|terminal|");
                    }
                }
                QStringList desktop_information;
                desktop_information<<name<<icon<<exec<<filename;
                desktop_files_list.append(desktop_information);
                if (desktopFile.contains("Categories"))
                {
                    ifstream load_data;
                    load_data.open(filename.toStdString(),ios::in);
                    string s;
                    QString result_qstring;
                    while(getline(load_data,s))
                    {
                        if (QString::fromStdString(s).contains("Categories="))
                        {
                            result_qstring=QString::fromStdString(s);
                            result_qstring.remove(0,11);
                        }
                    }
                    if (result_qstring.contains("Network",Qt::CaseInsensitive)||result_qstring.contains("downloader",Qt::CaseInsensitive))
                    {
                        Network_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Chat",Qt::CaseInsensitive))
                    {
                        Chat_type.append(desktop_information);
                    }
                    else if ((result_qstring.contains("Video",Qt::CaseInsensitive)&&!result_qstring.contains("AudioVideo",Qt::CaseInsensitive))||((result_qstring.contains("Player",Qt::CaseInsensitive)||result_qstring.contains("Recorder",Qt::CaseInsensitive))&&result_qstring.contains("AudioVideo",Qt::CaseInsensitive))||(result_qstring.contains("AudioVideoEditing",Qt::CaseInsensitive)&&!result_qstring.contains("Audio;",Qt::CaseInsensitive)))
                    {
                        Video_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Audio",Qt::CaseInsensitive))
                    {
                        Audio_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Graphics",Qt::CaseInsensitive))
                    {
                        Graphics_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Game",Qt::CaseInsensitive))
                    {
                        Game_type.append(desktop_information);
                    }
                    else if ((result_qstring.contains("Office",Qt::CaseInsensitive)||result_qstring.contains("Documentation",Qt::CaseInsensitive)||result_qstring.contains("TextEditor",Qt::CaseInsensitive))&&!result_qstring.contains("System",Qt::CaseInsensitive)&&!result_qstring.contains("IDE",Qt::CaseInsensitive))
                    {
                        Office_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("System",Qt::CaseInsensitive)||result_qstring.contains("Utility",Qt::CaseInsensitive)||result_qstring.contains("Compression",Qt::CaseInsensitive)||result_qstring.contains("KDE",Qt::CaseInsensitive))
                    {
                        System_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Translation",Qt::CaseInsensitive))
                    {
                        Translation_type.append(desktop_information);
                    }
                    else if (result_qstring.contains("Development",Qt::CaseInsensitive))
                    {
                        Development_type.append(desktop_information);
                    }
                    else
                    {
                        Other_type.append(desktop_information);
                    }
                }
                else
                {
                    Other_type.append(desktop_information);
                }
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
    QDirIterator it_love_desktop(QDir::homePath()+"/.local/lib/my_launcher_data/love_desktop",{"*.desktop"},QDir::NoFilter,QDirIterator::FollowSymlinks);
    love_desktop_list.clear();
    while(it_love_desktop.hasNext())
    {
        const auto filename=it_love_desktop.next();
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
                    love_desktop_list<<name;
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
    for (int i=0;i<desktop_files_list.size();i++)
    {
        if(i==0)
        {
            QStringList easy_find_string;
            int unicode=QString::number(desktop_files_list[i][0][0].unicode(),10).toInt();
            if (unicode>=0x4E00&&unicode<=0x9FA5)
            {
                easy_find_string<<listPY.at(unicode-0x4E00)[0].toUpper();
            }
            else
            {
                easy_find_string<<desktop_files_list[i][0].at(0).toUpper();
            }
            easy_find_string<<""<<""<<""<<"find";
            desktop_files_list.insert(i,easy_find_string);
        }
        else
        {
            if (desktop_files_list[i-1].size()==4)
            {
                QString old_str=nullptr,new_str=nullptr;
                int unicode=QString::number(desktop_files_list[i][0][0].unicode(),10).toInt();
                if (unicode>=0x4E00&&unicode<=0x9FA5)
                {
                    new_str=listPY.at(unicode-0x4E00)[0].toUpper();
                }
                else
                {
                    new_str=desktop_files_list[i][0].at(0).toUpper();
                }
                int unicode_old=QString::number(desktop_files_list[i-1][0][0].unicode(),10).toInt();
                if (unicode_old>=0x4E00&&unicode_old<=0x9FA5)
                {
                    old_str=listPY.at(unicode_old-0x4E00)[0].toUpper();
                }
                else
                {
                    old_str=desktop_files_list[i-1][0].at(0).toUpper();
                }
                if (old_str!=new_str)
                {
                    QStringList easy_find_string;
                    easy_find_string<<new_str<<""<<""<<""<<"find";
                    desktop_files_list.insert(i,easy_find_string);
                }
            }
        }
    }
    //Network_type,Chat_type,Audio_type,Video_type,Graphics_type,Game_type,Office_type/*add Utility*/,Translation_type,Development_type,System_type,Other_type
    sort(Network_type.begin(),Network_type.end(),sort_data);
    if (!Network_type.isEmpty())
    {
        Network_type.push_front(QStringList()<<"网络应用"<<""<<""<<""<<"Categories");
        desktop_type_list+=Network_type;
    }
    //
    sort(Chat_type.begin(),Chat_type.end(),sort_data);
    if (!Chat_type.isEmpty())
    {
        Chat_type.push_front(QStringList()<<"社交沟通"<<""<<""<<""<<"Categories");
        desktop_type_list+=Chat_type;
    }
    sort(Audio_type.begin(),Audio_type.end(),sort_data);
    if (!Audio_type.isEmpty())
    {
        Audio_type.push_front(QStringList()<<"音乐欣赏"<<""<<""<<""<<"Categories");
        desktop_type_list+=Audio_type;
    }
    sort(Video_type.begin(),Video_type.end(),sort_data);
    if (!Video_type.isEmpty())
    {
        Video_type.push_front(QStringList()<<"视频播放"<<""<<""<<""<<"Categories");
        desktop_type_list+=Video_type;
    }
    sort(Graphics_type.begin(),Graphics_type.end(),sort_data);
    if (!Graphics_type.isEmpty())
    {
        Graphics_type.push_front(QStringList()<<"图形图像"<<""<<""<<""<<"Categories");
        desktop_type_list+=Graphics_type;
    }
    sort(Game_type.begin(),Game_type.end(),sort_data);
    if (!Game_type.isEmpty())
    {
        Game_type.push_front(QStringList()<<"游戏娱乐"<<""<<""<<""<<"Categories");
        desktop_type_list+=Game_type;
    }
    sort(Office_type.begin(),Office_type.end(),sort_data);
    if (!Office_type.isEmpty())
    {
        Office_type.push_front(QStringList()<<"办公学习"<<""<<""<<""<<"Categories");
        desktop_type_list+=Office_type;
    }
    sort(Translation_type.begin(),Translation_type.end(),sort_data);
    if (!Translation_type.isEmpty())
    {
        Translation_type.push_front(QStringList()<<"阅读翻译"<<""<<""<<""<<"Categories");
        desktop_type_list+=Translation_type;
    }
    sort(Development_type.begin(),Development_type.end(),sort_data);
    if (!Development_type.isEmpty())
    {
        Development_type.push_front(QStringList()<<"编程开发"<<""<<""<<""<<"Categories");
        desktop_type_list+=Development_type;
    }
    sort(System_type.begin(),System_type.end(),sort_data);
    if (!System_type.isEmpty())
    {
        System_type.push_front(QStringList()<<"系统管理"<<""<<""<<""<<"Categories");
        desktop_type_list+=System_type;
    }
    sort(Other_type.begin(),Other_type.end(),sort_data);
    if (!Other_type.isEmpty())
    {
        Other_type.push_front(QStringList()<<"其他"<<""<<""<<""<<"Categories");
        desktop_type_list+=Other_type;
    }
    Show_Desktop_List_View->set_information(List_View_Item_List,desktop_files_list);
    Show_Desktop_Table_Table_View->set_information(Table_Table_View_Item_List,desktop_type_list);
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
            new_string1.append(listPY.at(unicode-0x4E00));
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
            new_string2.append(listPY.at(unicode-0x4E00));
        }
        else
        {
            new_string2.append(string2.at(i));
        }
    }
    return new_string1.toLower()<new_string2.toLower();
}
void Launcher_Widget::click_run_class()
{
    int row=Show_Desktop_List_View->currentIndex().row();
    if (row!=-1)
    {
        QModelIndex index=model->index(-1,0);
        Show_Desktop_List_View->setCurrentIndex(index);
        if (desktop_files_list[row].size()==4)
        {
            if (!desktop_files_list[row][2].contains("|terminal|"))
            {
                QString run="/bin/bash -c \"cd ~;"+desktop_files_list[row][2]+"\"";
                QProcess::startDetached(run);//could not open libreoffice*;//!!!java in QC;
            }
            else
            {
                QString new_exec=desktop_files_list[row][2];
                new_exec.chop(10);
                QString run="/bin/bash -c \"cd ~;deepin-terminal -e "+new_exec+"\"";
                QProcess::startDetached(run);
            }
            to_close_all=true;
        }
    }
}
void Launcher_Widget::click_run_class_table()
{
    int row=Show_Desktop_Table_Table_View->currentIndex().row();
    if (row!=-1)
    {
        QModelIndex index=model_table_table->index(-1,0);
        Show_Desktop_Table_Table_View->setCurrentIndex(index);
        if (desktop_type_list[row].size()==4)
        {
            if (!desktop_type_list[row][2].contains("|terminal|"))
            {
                QString run="/bin/bash -c \"cd ~;"+desktop_type_list[row][2]+"\"";
                QProcess::startDetached(run);//could not open libreoffice*;//!!!java in QC;
            }
            else
            {
                QString new_exec=desktop_type_list[row][2];
                new_exec.chop(10);
                QString run="/bin/bash -c \"cd ~;deepin-terminal -e "+new_exec+"\"";
                QProcess::startDetached(run);
            }
            to_close_all=true;
        }
    }
}
void Launcher_Widget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()&&event->pos().x()>=361&&event->pos().x()<=595&&event->pos().y()>=95&&event->pos().y()<=360)
    {
        QList<QUrl> urls=event->mimeData()->urls();
        for(int i=0;i<urls.size();i++)
        {
            QFileInfo fileinfo(urls[i].toString());
            if (fileinfo.suffix()=="desktop")
            {
                event->acceptProposedAction();
            }
        }
    }
    else
    {
        event->ignore();
    }
}
void Launcher_Widget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        QList<QUrl> urls=event->mimeData()->urls();
        for(int i=0;i<urls.size();i++)
        {
            QFileInfo fileinfo(urls[i].toString());
            if (fileinfo.suffix()=="desktop")
            {
                QString filesname=urls[i].toString();
                QString run;
                if (filesname.contains("file:///"))
                {
                    filesname.remove(0,7);
                }
                run="cp '"+filesname+"' '"+QDir::homePath()+"/.local/lib/my_launcher_data/love_desktop/"+fileinfo.fileName()+"'";
                string run2=run.toStdString();
                const char* run3=run2.c_str();
                system(run3);
                get_desktop_file();
                if (search_line->text()==nullptr)
                {
                    int desktop_number_love=love_desktop_list.size();
                    QHBoxLayout *layout_love=new QHBoxLayout();
                    make_show_love_label->resize(234,265);
                    make_show_love_label->show_desktop_label->resize((desktop_number_love/9+1)*234,255);
                    make_show_love_label->set_end_x(18*(desktop_number_love/9+1));
                    make_show_love_label->button_update();
                    delete make_show_love_label->show_desktop_label->layout();
                    for (int i=0;i<Love_view_list.size();i++)
                    {
                        for (int k=0;k<9;k++)
                        {
                            if (k<Love_view_list[i]->model()->children().size())
                            {
                                delete Love_view_list[i]->model()->children()[k];
                            }
                        }
                        delete Love_view_list[i];
                    }
                    Love_view_list.clear();
                    int no_pass_number_love=0;
                    //3*3
                    for (int i=0;i<desktop_number_love/9+1;i++)
                    {
                        OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                        Show_Desktop_Table_View->resize(234,255);
                        Show_Desktop_Table_View->move(234*i,0);
                        Show_Desktop_Table_View->setWrapping(true);
                        Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                        Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                        Show_Desktop_Table_View->setIconSize(QSize(50,50));
                        Show_Desktop_Table_View->setGridSize(QSize(77,85));
                        Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                        Show_Desktop_Table_View->setWordWrap(true);
                        Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                        Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
                        Love_view_list.append(Show_Desktop_Table_View);
                        layout_love->addWidget(Show_Desktop_Table_View);
                        QStandardItemModel *model_table=new QStandardItemModel;
                        QList<QStringList> desktop_list;
                        QList<QStandardItem *> item_list;
                        int number_k=0;
                        if (desktop_number_love!=0)
                        {
                        int help_no_pass_number=0;
                        for (int k=0;number_k<9;k++)
                        {
                            if (desktop_files_list.size()<i*9+k+no_pass_number_love+1)
                            {
                                number_k=k;
                            }
                            else
                            {
                            bool in_love=false;
                            for (int l=0;l<love_desktop_list.size();l++)
                            {
                                if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number_love][0])
                                {
                                    in_love=true;
                                }
                            }
                            if (desktop_files_list[i*9+k+no_pass_number_love].size()==4&&in_love)
                            {
                                number_k++;
                                QStandardItem *item;
                                bool is_auto=false;
                                for (int j=0;j<auto_start_program_list.size();j++)
                                {
                                    if (desktop_files_list[i*9+k+no_pass_number_love][0]==auto_start_program_list[j])
                                    {
                                        is_auto=true;
                                    }
                                }
                                if (is_auto)
                                {
                                    QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                                    QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number_love][1]).pixmap(QSize(99,99));
                                    QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                                    result_image.fill(Qt::transparent);
                                    QPainter *painter=new QPainter(&result_image);
                                    painter->setPen(Qt::NoPen);
                                    painter->setBrush(Qt::NoBrush);
                                    painter->drawPixmap(0,0,theme_icon);
                                    painter->drawPixmap(0,50,auto_start_img);
                                    delete painter;
                                    QPixmap result_pixmap=QPixmap::fromImage(result_image);
                                    item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number_love][0]);
                                }
                                else
                                {
                                    item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number_love][1]),desktop_files_list[i*9+k+no_pass_number_love][0]);
                                }
                                item->setSizeHint(QSize(77,85));
                                item_list.append(item);
                                desktop_list.append(desktop_files_list[i*9+k+no_pass_number_love]);
                                model_table->appendRow(item);
                            }
                            else
                            {
                                help_no_pass_number++;
                            }
                            }
                        }
                        no_pass_number_love+=help_no_pass_number;
                        }
                        Show_Desktop_Table_View->setModel(model_table);
                        Show_Desktop_Table_View->set_information(item_list,desktop_list);
                    }
                    make_show_love_label->show_desktop_label->setLayout(layout_love);
                    delete layout_love;
                }
                else
                {
                    show_love_label->move(361,95);
                    show_love_label->resize(234,265);
                    //
                    int desktop_number=0;
                    for (int i=0;i<desktop_files_list.size();i++)
                    {
                        if (desktop_files_list[i].size()==4)
                        {
                            for (int k=0;k<love_desktop_list.size();k++)
                            {
                                if (desktop_files_list[i][0]==love_desktop_list[k])
                                {
                                    if (desktop_files_list[i][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i][3]).contains(Search_string,Qt::CaseInsensitive))
                                    {
                                        desktop_number++;
                                    }
                                }
                            }
                        }
                    }
                    QHBoxLayout *layout=new QHBoxLayout();
                    make_show_love_label->resize(234,265);
                    make_show_love_label->show_desktop_label->resize((desktop_number/9+1)*234,255);
                    if (float(desktop_number/9)==float(desktop_number)/9)
                    {
                        make_show_love_label->set_end_x(18*(desktop_number/9));
                    }
                    else
                    {
                        make_show_love_label->set_end_x(18*(desktop_number/9+1));
                    }
                    make_show_love_label->set_now_page(1);
                    make_show_love_label->button_update();
                    delete make_show_love_label->show_desktop_label->layout();
                    for (int i=0;i<Love_view_list.size();i++)
                    {
                        for (int k=0;k<9;k++)
                        {
                            if (k<Love_view_list[i]->model()->children().size())
                            {
                                delete Love_view_list[i]->model()->children()[k];
                            }
                        }
                        delete Love_view_list[i];
                    }
                    Love_view_list.clear();
                    int no_pass_number=0;
                    //3*3
                    for (int i=0;i<desktop_number/9+1;i++)
                    {
                        OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                        Show_Desktop_Table_View->resize(234,255);
                        Show_Desktop_Table_View->move(234*i,0);
                        Show_Desktop_Table_View->setWrapping(true);
                        Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                        Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                        Show_Desktop_Table_View->setIconSize(QSize(50,50));
                        Show_Desktop_Table_View->setGridSize(QSize(77,85));
                        Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                        Show_Desktop_Table_View->setWordWrap(true);
                        Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                        Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
                        Love_view_list.append(Show_Desktop_Table_View);
                        layout->addWidget(Show_Desktop_Table_View);
                        QStandardItemModel *model_table=new QStandardItemModel;
                        QList<QStringList> desktop_list;
                        QList<QStandardItem *> item_list;
                        int number_k=0;
                        if (desktop_number!=0)
                        {
                        int help_no_pass_number=0;
                        for (int k=0;number_k<9;k++)
                        {
                            if (desktop_files_list.size()<i*9+k+no_pass_number+1)
                            {
                                number_k=k;
                            }
                            else
                            {
                            bool in_love=false;
                            for (int l=0;l<love_desktop_list.size();l++)
                            {
                                if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number][0]&&(desktop_files_list[i*9+k+no_pass_number][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i*9+k+no_pass_number][3]).contains(Search_string,Qt::CaseInsensitive)))
                                {
                                    in_love=true;
                                }
                            }
                            if (desktop_files_list[i*9+k+no_pass_number].size()==4&&in_love)
                            {
                                number_k++;
                                QStandardItem *item;
                                bool is_auto=false;
                                for (int j=0;j<auto_start_program_list.size();j++)
                                {
                                    if (desktop_files_list[i*9+k+no_pass_number][0]==auto_start_program_list[j])
                                    {
                                        is_auto=true;
                                    }
                                }
                                if (is_auto)
                                {
                                    QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                                    QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]).pixmap(QSize(99,99));
                                    QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                                    result_image.fill(Qt::transparent);
                                    QPainter *painter=new QPainter(&result_image);
                                    painter->setPen(Qt::NoPen);
                                    painter->setBrush(Qt::NoBrush);
                                    painter->drawPixmap(0,0,theme_icon);
                                    painter->drawPixmap(0,50,auto_start_img);
                                    delete painter;
                                    QPixmap result_pixmap=QPixmap::fromImage(result_image);
                                    item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number][0]);
                                }
                                else
                                {
                                    item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]),desktop_files_list[i*9+k+no_pass_number][0]);
                                }
                                item->setSizeHint(QSize(77,85));
                                item_list.append(item);
                                desktop_list.append(desktop_files_list[i*9+k+no_pass_number]);
                                model_table->appendRow(item);
                            }
                            else
                            {
                                help_no_pass_number++;
                            }
                            }
                        }
                        no_pass_number+=help_no_pass_number;
                        }
                        Show_Desktop_Table_View->setModel(model_table);
                        Show_Desktop_Table_View->set_information(item_list,desktop_list);
                    }
                    make_show_love_label->show_desktop_label->setLayout(layout);
                    delete layout;
                }
            }
        }
    }
}
bool Launcher_Widget::get_pos_in(int pos_x,int pos_y,int in_x,int in_y,int in_size_x,int in_size_y)
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
void Launcher_Widget::contextMenuEvent(QContextMenuEvent *event)
{
    //result
    if (get_pos_in(event->pos().x(),event->pos().y(),show_class_result->pos().x(),show_class_result->pos().y(),show_class_result->width(),show_class_result->height()))
    {
        if (choose_list_or_table==1)
        {
            int row=Show_Desktop_List_View->currentIndex().row();
            if (row!=-1)
            {
                if (desktop_files_list[row].size()==4)
                {
                    bool has_autostart=false,has_desktop=false;
                    for (int i=0;i<auto_start_program_list.size();i++)
                    {
                        if (desktop_files_list[row][0]==auto_start_program_list[i])
                        {
                            has_autostart=true;
                        }
                    }
                    for (int i=0;i<desktop_desktop_list.size();i++)
                    {
                        if (desktop_files_list[row][0]==desktop_desktop_list[i])
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
                        QString run="/bin/bash -c \"cd ~;"+desktop_files_list[row][2]+"\"";
                        QProcess::startDetached(run);//could not open libreoffice*;//!!!java;
                        to_close_all=true;
                    }
                    if (know_what==add_to_love)
                    {
                        QFileInfo fileinfo(desktop_files_list[row][3]);
                        QString run="cp '"+desktop_files_list[row][3]+"' '"+QDir::homePath()+"/.local/lib/my_launcher_data/love_desktop/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        get_desktop_file();
                        if (search_line->text()==nullptr)
                        {
                            int desktop_number_love=love_desktop_list.size();
                            QHBoxLayout *layout_love=new QHBoxLayout();
                            make_show_love_label->resize(234,265);
                            make_show_love_label->show_desktop_label->resize((desktop_number_love/9+1)*234,255);
                            make_show_love_label->set_end_x(18*(desktop_number_love/9+1));
                            make_show_love_label->button_update();
                            delete make_show_love_label->show_desktop_label->layout();
                            for (int i=0;i<Love_view_list.size();i++)
                            {
                                for (int k=0;k<9;k++)
                                {
                                    if (k<Love_view_list[i]->model()->children().size())
                                    {
                                        delete Love_view_list[i]->model()->children()[k];
                                    }
                                }
                                delete Love_view_list[i];
                            }
                            Love_view_list.clear();
                            int no_pass_number_love=0;
                            //3*3
                            for (int i=0;i<desktop_number_love/9+1;i++)
                            {
                                OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                                Show_Desktop_Table_View->resize(234,255);
                                Show_Desktop_Table_View->move(234*i,0);
                                Show_Desktop_Table_View->setWrapping(true);
                                Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                                Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                                Show_Desktop_Table_View->setIconSize(QSize(50,50));
                                Show_Desktop_Table_View->setGridSize(QSize(77,85));
                                Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                                Show_Desktop_Table_View->setWordWrap(true);
                                Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                                Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
                                Love_view_list.append(Show_Desktop_Table_View);
                                layout_love->addWidget(Show_Desktop_Table_View);
                                QStandardItemModel *model_table=new QStandardItemModel;
                                QList<QStringList> desktop_list;
                                QList<QStandardItem *> item_list;
                                int number_k=0;
                                if (desktop_number_love!=0)
                                {
                                int help_no_pass_number=0;
                                for (int k=0;number_k<9;k++)
                                {
                                    if (desktop_files_list.size()<i*9+k+no_pass_number_love+1)
                                    {
                                        number_k=k;
                                    }
                                    else
                                    {
                                    bool in_love=false;
                                    for (int l=0;l<love_desktop_list.size();l++)
                                    {
                                        if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number_love][0])
                                        {
                                            in_love=true;
                                        }
                                    }
                                    if (desktop_files_list[i*9+k+no_pass_number_love].size()==4&&in_love)
                                    {
                                        number_k++;
                                        QStandardItem *item;
                                        bool is_auto=false;
                                        for (int j=0;j<auto_start_program_list.size();j++)
                                        {
                                            if (desktop_files_list[i*9+k+no_pass_number_love][0]==auto_start_program_list[j])
                                            {
                                                is_auto=true;
                                            }
                                        }
                                        if (is_auto)
                                        {
                                            QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                                            QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number_love][1]).pixmap(QSize(99,99));
                                            QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                                            result_image.fill(Qt::transparent);
                                            QPainter *painter=new QPainter(&result_image);
                                            painter->setPen(Qt::NoPen);
                                            painter->setBrush(Qt::NoBrush);
                                            painter->drawPixmap(0,0,theme_icon);
                                            painter->drawPixmap(0,50,auto_start_img);
                                            delete painter;
                                            QPixmap result_pixmap=QPixmap::fromImage(result_image);
                                            item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number_love][0]);
                                        }
                                        else
                                        {
                                            item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number_love][1]),desktop_files_list[i*9+k+no_pass_number_love][0]);
                                        }
                                        item->setSizeHint(QSize(77,85));
                                        item_list.append(item);
                                        desktop_list.append(desktop_files_list[i*9+k+no_pass_number_love]);
                                        model_table->appendRow(item);
                                    }
                                    else
                                    {
                                        help_no_pass_number++;
                                    }
                                    }
                                }
                                no_pass_number_love+=help_no_pass_number;
                                }
                                Show_Desktop_Table_View->setModel(model_table);
                                Show_Desktop_Table_View->set_information(item_list,desktop_list);
                            }
                            make_show_love_label->show_desktop_label->setLayout(layout_love);
                            delete layout_love;
                        }
                        else
                        {
                            show_love_label->move(361,95);
                            show_love_label->resize(234,265);
                            //
                            int desktop_number=0;
                            for (int i=0;i<desktop_files_list.size();i++)
                            {
                                if (desktop_files_list[i].size()==4)
                                {
                                    for (int k=0;k<love_desktop_list.size();k++)
                                    {
                                        if (desktop_files_list[i][0]==love_desktop_list[k])
                                        {
                                            if (desktop_files_list[i][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i][3]).contains(Search_string,Qt::CaseInsensitive))
                                            {
                                                desktop_number++;
                                            }
                                        }
                                    }
                                }
                            }
                            QHBoxLayout *layout=new QHBoxLayout();
                            make_show_love_label->resize(234,265);
                            make_show_love_label->show_desktop_label->resize((desktop_number/9+1)*234,255);
                            if (float(desktop_number/9)==float(desktop_number)/9)
                            {
                                make_show_love_label->set_end_x(18*(desktop_number/9));
                            }
                            else
                            {
                                make_show_love_label->set_end_x(18*(desktop_number/9+1));
                            }
                            make_show_love_label->set_now_page(1);
                            make_show_love_label->button_update();
                            delete make_show_love_label->show_desktop_label->layout();
                            for (int i=0;i<Love_view_list.size();i++)
                            {
                                for (int k=0;k<9;k++)
                                {
                                    if (k<Love_view_list[i]->model()->children().size())
                                    {
                                        delete Love_view_list[i]->model()->children()[k];
                                    }
                                }
                                delete Love_view_list[i];
                            }
                            Love_view_list.clear();
                            int no_pass_number=0;
                            //3*3
                            for (int i=0;i<desktop_number/9+1;i++)
                            {
                                OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                                Show_Desktop_Table_View->resize(234,255);
                                Show_Desktop_Table_View->move(234*i,0);
                                Show_Desktop_Table_View->setWrapping(true);
                                Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                                Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                                Show_Desktop_Table_View->setIconSize(QSize(50,50));
                                Show_Desktop_Table_View->setGridSize(QSize(77,85));
                                Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                                Show_Desktop_Table_View->setWordWrap(true);
                                Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                                Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
                                Love_view_list.append(Show_Desktop_Table_View);
                                layout->addWidget(Show_Desktop_Table_View);
                                QStandardItemModel *model_table=new QStandardItemModel;
                                QList<QStringList> desktop_list;
                                QList<QStandardItem *> item_list;
                                int number_k=0;
                                if (desktop_number!=0)
                                {
                                int help_no_pass_number=0;
                                for (int k=0;number_k<9;k++)
                                {
                                    if (desktop_files_list.size()<i*9+k+no_pass_number+1)
                                    {
                                        number_k=k;
                                    }
                                    else
                                    {
                                    bool in_love=false;
                                    for (int l=0;l<love_desktop_list.size();l++)
                                    {
                                        if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number][0]&&(desktop_files_list[i*9+k+no_pass_number][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i*9+k+no_pass_number][3]).contains(Search_string,Qt::CaseInsensitive)))
                                        {
                                            in_love=true;
                                        }
                                    }
                                    if (desktop_files_list[i*9+k+no_pass_number].size()==4&&in_love)
                                    {
                                        number_k++;
                                        QStandardItem *item;
                                        bool is_auto=false;
                                        for (int j=0;j<auto_start_program_list.size();j++)
                                        {
                                            if (desktop_files_list[i*9+k+no_pass_number][0]==auto_start_program_list[j])
                                            {
                                                is_auto=true;
                                            }
                                        }
                                        if (is_auto)
                                        {
                                            QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                                            QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]).pixmap(QSize(99,99));
                                            QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                                            result_image.fill(Qt::transparent);
                                            QPainter *painter=new QPainter(&result_image);
                                            painter->setPen(Qt::NoPen);
                                            painter->setBrush(Qt::NoBrush);
                                            painter->drawPixmap(0,0,theme_icon);
                                            painter->drawPixmap(0,50,auto_start_img);
                                            delete painter;
                                            QPixmap result_pixmap=QPixmap::fromImage(result_image);
                                            item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number][0]);
                                        }
                                        else
                                        {
                                            item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]),desktop_files_list[i*9+k+no_pass_number][0]);
                                        }
                                        item->setSizeHint(QSize(77,85));
                                        item_list.append(item);
                                        desktop_list.append(desktop_files_list[i*9+k+no_pass_number]);
                                        model_table->appendRow(item);
                                    }
                                    else
                                    {
                                        help_no_pass_number++;
                                    }
                                    }
                                }
                                no_pass_number+=help_no_pass_number;
                                }
                                Show_Desktop_Table_View->setModel(model_table);
                                Show_Desktop_Table_View->set_information(item_list,desktop_list);
                            }
                            make_show_love_label->show_desktop_label->setLayout(layout);
                            delete layout;
                        }
                        all_update();
                    }
                    if (know_what==set_auto_start)
                    {
                        QFileInfo fileinfo(desktop_files_list[row][3]);
                        QString run="cp '"+desktop_files_list[row][3]+"' '"+QDir::homePath()+"/.config/autostart/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                    if (know_what==send_to_desktop)
                    {
                        QFileInfo fileinfo(desktop_files_list[row][3]);
                        QString run="cp '"+desktop_files_list[row][3]+"' '"+QDir::homePath()+"/Desktop/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                    if (know_what==unset_auto_start)
                    {
                        QFileInfo fileinfo(desktop_files_list[row][3]);
                        QString run="rm '"+QDir::homePath()+"/.config/autostart/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                    if (know_what==remove_to_desktop)
                    {
                        QFileInfo fileinfo(desktop_files_list[row][3]);
                        QString run="rm '"+QDir::homePath()+"/Desktop/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                }
            }
        }
        else if (choose_list_or_table==2)
        {
            if (Table_view_list.size()>make_show_way_label->now_page-1)
            {
                int row=Table_view_list[make_show_way_label->now_page-1]->currentIndex().row();
                if (row!=-1)
                {
                    if (Table_view_list[make_show_way_label->now_page-1]->desktop_files_list[row].size()==4)
                    {
                        bool has_autostart=false,has_desktop=false;
                        for (int i=0;i<auto_start_program_list.size();i++)
                        {
                            if (Table_view_list[make_show_way_label->now_page-1]->desktop_files_list[row][0]==auto_start_program_list[i])
                            {
                                has_autostart=true;
                            }
                        }
                        for (int i=0;i<desktop_desktop_list.size();i++)
                        {
                            if (Table_view_list[make_show_way_label->now_page-1]->desktop_files_list[row][0]==desktop_desktop_list[i])
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
                            QString run="/bin/bash -c \"cd ~;"+Table_view_list[make_show_way_label->now_page-1]->desktop_files_list[row][2]+"\"";
                            QProcess::startDetached(run);//could not open libreoffice*;//!!!java;
                            to_close_all=true;
                        }
                        if (know_what==add_to_love)
                        {
                            QFileInfo fileinfo(Table_view_list[make_show_way_label->now_page-1]->desktop_files_list[row][3]);
                            QString run="cp '"+Table_view_list[make_show_way_label->now_page-1]->desktop_files_list[row][3]+"' '"+QDir::homePath()+"/.local/lib/my_launcher_data/love_desktop/"+fileinfo.fileName()+"'";
                            string run2=run.toStdString();
                            const char* run3=run2.c_str();
                            system(run3);
                            get_desktop_file();
                            if (search_line->text()==nullptr)
                            {
                                int desktop_number_love=love_desktop_list.size();
                                QHBoxLayout *layout_love=new QHBoxLayout();
                                make_show_love_label->resize(234,265);
                                make_show_love_label->show_desktop_label->resize((desktop_number_love/9+1)*234,255);
                                make_show_love_label->set_end_x(18*(desktop_number_love/9+1));
                                make_show_love_label->button_update();
                                delete make_show_love_label->show_desktop_label->layout();
                                for (int i=0;i<Love_view_list.size();i++)
                                {
                                    for (int k=0;k<9;k++)
                                    {
                                        if (k<Love_view_list[i]->model()->children().size())
                                        {
                                            delete Love_view_list[i]->model()->children()[k];
                                        }
                                    }
                                    delete Love_view_list[i];
                                }
                                Love_view_list.clear();
                                int no_pass_number_love=0;
                                //3*3
                                for (int i=0;i<desktop_number_love/9+1;i++)
                                {
                                    OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                                    Show_Desktop_Table_View->resize(234,255);
                                    Show_Desktop_Table_View->move(234*i,0);
                                    Show_Desktop_Table_View->setWrapping(true);
                                    Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                                    Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                                    Show_Desktop_Table_View->setIconSize(QSize(50,50));
                                    Show_Desktop_Table_View->setGridSize(QSize(77,85));
                                    Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                                    Show_Desktop_Table_View->setWordWrap(true);
                                    Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                                    Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
                                    Love_view_list.append(Show_Desktop_Table_View);
                                    layout_love->addWidget(Show_Desktop_Table_View);
                                    QStandardItemModel *model_table=new QStandardItemModel;
                                    QList<QStringList> desktop_list;
                                    QList<QStandardItem *> item_list;
                                    int number_k=0;
                                    if (desktop_number_love!=0)
                                    {
                                    int help_no_pass_number=0;
                                    for (int k=0;number_k<9;k++)
                                    {
                                        if (desktop_files_list.size()<i*9+k+no_pass_number_love+1)
                                        {
                                            number_k=k;
                                        }
                                        else
                                        {
                                        bool in_love=false;
                                        for (int l=0;l<love_desktop_list.size();l++)
                                        {
                                            if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number_love][0])
                                            {
                                                in_love=true;
                                            }
                                        }
                                        if (desktop_files_list[i*9+k+no_pass_number_love].size()==4&&in_love)
                                        {
                                            number_k++;
                                            QStandardItem *item;
                                            bool is_auto=false;
                                            for (int j=0;j<auto_start_program_list.size();j++)
                                            {
                                                if (desktop_files_list[i*9+k+no_pass_number_love][0]==auto_start_program_list[j])
                                                {
                                                    is_auto=true;
                                                }
                                            }
                                            if (is_auto)
                                            {
                                                QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                                                QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number_love][1]).pixmap(QSize(99,99));
                                                QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                                                result_image.fill(Qt::transparent);
                                                QPainter *painter=new QPainter(&result_image);
                                                painter->setPen(Qt::NoPen);
                                                painter->setBrush(Qt::NoBrush);
                                                painter->drawPixmap(0,0,theme_icon);
                                                painter->drawPixmap(0,50,auto_start_img);
                                                delete painter;
                                                QPixmap result_pixmap=QPixmap::fromImage(result_image);
                                                item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number_love][0]);
                                            }
                                            else
                                            {
                                                item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number_love][1]),desktop_files_list[i*9+k+no_pass_number_love][0]);
                                            }
                                            item->setSizeHint(QSize(77,85));
                                            item_list.append(item);
                                            desktop_list.append(desktop_files_list[i*9+k+no_pass_number_love]);
                                            model_table->appendRow(item);
                                        }
                                        else
                                        {
                                            help_no_pass_number++;
                                        }
                                        }
                                    }
                                    no_pass_number_love+=help_no_pass_number;
                                    }
                                    Show_Desktop_Table_View->setModel(model_table);
                                    Show_Desktop_Table_View->set_information(item_list,desktop_list);
                                }
                                make_show_love_label->show_desktop_label->setLayout(layout_love);
                                delete layout_love;
                            }
                            else
                            {
                                show_love_label->move(361,95);
                                show_love_label->resize(234,265);
                                //
                                int desktop_number=0;
                                for (int i=0;i<desktop_files_list.size();i++)
                                {
                                    if (desktop_files_list[i].size()==4)
                                    {
                                        for (int k=0;k<love_desktop_list.size();k++)
                                        {
                                            if (desktop_files_list[i][0]==love_desktop_list[k])
                                            {
                                                if (desktop_files_list[i][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i][3]).contains(Search_string,Qt::CaseInsensitive))
                                                {
                                                    desktop_number++;
                                                }
                                            }
                                        }
                                    }
                                }
                                QHBoxLayout *layout=new QHBoxLayout();
                                make_show_love_label->resize(234,265);
                                make_show_love_label->show_desktop_label->resize((desktop_number/9+1)*234,255);
                                if (float(desktop_number/9)==float(desktop_number)/9)
                                {
                                    make_show_love_label->set_end_x(18*(desktop_number/9));
                                }
                                else
                                {
                                    make_show_love_label->set_end_x(18*(desktop_number/9+1));
                                }
                                make_show_love_label->set_now_page(1);
                                make_show_love_label->button_update();
                                delete make_show_love_label->show_desktop_label->layout();
                                for (int i=0;i<Love_view_list.size();i++)
                                {
                                    for (int k=0;k<9;k++)
                                    {
                                        if (k<Love_view_list[i]->model()->children().size())
                                        {
                                            delete Love_view_list[i]->model()->children()[k];
                                        }
                                    }
                                    delete Love_view_list[i];
                                }
                                Love_view_list.clear();
                                int no_pass_number=0;
                                //3*3
                                for (int i=0;i<desktop_number/9+1;i++)
                                {
                                    OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                                    Show_Desktop_Table_View->resize(234,255);
                                    Show_Desktop_Table_View->move(234*i,0);
                                    Show_Desktop_Table_View->setWrapping(true);
                                    Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                                    Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                                    Show_Desktop_Table_View->setIconSize(QSize(50,50));
                                    Show_Desktop_Table_View->setGridSize(QSize(77,85));
                                    Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                                    Show_Desktop_Table_View->setWordWrap(true);
                                    Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                                    Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
                                    Love_view_list.append(Show_Desktop_Table_View);
                                    layout->addWidget(Show_Desktop_Table_View);
                                    QStandardItemModel *model_table=new QStandardItemModel;
                                    QList<QStringList> desktop_list;
                                    QList<QStandardItem *> item_list;
                                    int number_k=0;
                                    if (desktop_number!=0)
                                    {
                                    int help_no_pass_number=0;
                                    for (int k=0;number_k<9;k++)
                                    {
                                        if (desktop_files_list.size()<i*9+k+no_pass_number+1)
                                        {
                                            number_k=k;
                                        }
                                        else
                                        {
                                        bool in_love=false;
                                        for (int l=0;l<love_desktop_list.size();l++)
                                        {
                                            if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number][0]&&(desktop_files_list[i*9+k+no_pass_number][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i*9+k+no_pass_number][3]).contains(Search_string,Qt::CaseInsensitive)))
                                            {
                                                in_love=true;
                                            }
                                        }
                                        if (desktop_files_list[i*9+k+no_pass_number].size()==4&&in_love)
                                        {
                                            number_k++;
                                            QStandardItem *item;
                                            bool is_auto=false;
                                            for (int j=0;j<auto_start_program_list.size();j++)
                                            {
                                                if (desktop_files_list[i*9+k+no_pass_number][0]==auto_start_program_list[j])
                                                {
                                                    is_auto=true;
                                                }
                                            }
                                            if (is_auto)
                                            {
                                                QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                                                QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]).pixmap(QSize(99,99));
                                                QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                                                result_image.fill(Qt::transparent);
                                                QPainter *painter=new QPainter(&result_image);
                                                painter->setPen(Qt::NoPen);
                                                painter->setBrush(Qt::NoBrush);
                                                painter->drawPixmap(0,0,theme_icon);
                                                painter->drawPixmap(0,50,auto_start_img);
                                                delete painter;
                                                QPixmap result_pixmap=QPixmap::fromImage(result_image);
                                                item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number][0]);
                                            }
                                            else
                                            {
                                                item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]),desktop_files_list[i*9+k+no_pass_number][0]);
                                            }
                                            item->setSizeHint(QSize(77,85));
                                            item_list.append(item);
                                            desktop_list.append(desktop_files_list[i*9+k+no_pass_number]);
                                            model_table->appendRow(item);
                                        }
                                        else
                                        {
                                            help_no_pass_number++;
                                        }
                                        }
                                    }
                                    no_pass_number+=help_no_pass_number;
                                    }
                                    Show_Desktop_Table_View->setModel(model_table);
                                    Show_Desktop_Table_View->set_information(item_list,desktop_list);
                                }
                                make_show_love_label->show_desktop_label->setLayout(layout);
                                delete layout;
                            }
                            all_update();
                        }
                        if (know_what==set_auto_start)
                        {
                            QFileInfo fileinfo(Table_view_list[make_show_way_label->now_page-1]->desktop_files_list[row][3]);
                            QString run="cp '"+Table_view_list[make_show_way_label->now_page-1]->desktop_files_list[row][3]+"' '"+QDir::homePath()+"/.config/autostart/"+fileinfo.fileName()+"'";
                            string run2=run.toStdString();
                            const char* run3=run2.c_str();
                            system(run3);
                            all_update();
                        }
                        if (know_what==send_to_desktop)
                        {
                            QFileInfo fileinfo(Table_view_list[make_show_way_label->now_page-1]->desktop_files_list[row][3]);
                            QString run="cp '"+Table_view_list[make_show_way_label->now_page-1]->desktop_files_list[row][3]+"' '"+QDir::homePath()+"/Desktop/"+fileinfo.fileName()+"'";
                            string run2=run.toStdString();
                            const char* run3=run2.c_str();
                            system(run3);
                            all_update();
                        }
                        if (know_what==unset_auto_start)
                        {
                            QFileInfo fileinfo(Table_view_list[make_show_way_label->now_page-1]->desktop_files_list[row][3]);
                            QString run="rm '"+QDir::homePath()+"/.config/autostart/"+fileinfo.fileName()+"'";
                            string run2=run.toStdString();
                            const char* run3=run2.c_str();
                            system(run3);
                            all_update();
                        }
                        if (know_what==remove_to_desktop)
                        {
                            QFileInfo fileinfo(Table_view_list[make_show_way_label->now_page-1]->desktop_files_list[row][3]);
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
        else if (choose_list_or_table==3)
        {
            int row=Show_Desktop_Table_Table_View->currentIndex().row();
            if (row!=-1)
            {
                if (desktop_type_list[row].size()==4)
                {
                    bool has_autostart=false,has_desktop=false;
                    for (int i=0;i<auto_start_program_list.size();i++)
                    {
                        if (desktop_type_list[row][0]==auto_start_program_list[i])
                        {
                            has_autostart=true;
                        }
                    }
                    for (int i=0;i<desktop_desktop_list.size();i++)
                    {
                        if (desktop_type_list[row][0]==desktop_desktop_list[i])
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
                        QString run="/bin/bash -c \"cd ~;"+desktop_type_list[row][2]+"\"";
                        QProcess::startDetached(run);//could not open libreoffice*;//!!!java;
                        to_close_all=true;
                    }
                    if (know_what==add_to_love)
                    {
                        QFileInfo fileinfo(desktop_type_list[row][3]);
                        QString run="cp '"+desktop_type_list[row][3]+"' '"+QDir::homePath()+"/.local/lib/my_launcher_data/love_desktop/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        get_desktop_file();
                        if (search_line->text()==nullptr)
                        {
                            int desktop_number_love=love_desktop_list.size();
                            QHBoxLayout *layout_love=new QHBoxLayout();
                            make_show_love_label->resize(234,265);
                            make_show_love_label->show_desktop_label->resize((desktop_number_love/9+1)*234,255);
                            make_show_love_label->set_end_x(18*(desktop_number_love/9+1));
                            make_show_love_label->button_update();
                            delete make_show_love_label->show_desktop_label->layout();
                            for (int i=0;i<Love_view_list.size();i++)
                            {
                                for (int k=0;k<9;k++)
                                {
                                    if (k<Love_view_list[i]->model()->children().size())
                                    {
                                        delete Love_view_list[i]->model()->children()[k];
                                    }
                                }
                                delete Love_view_list[i];
                            }
                            Love_view_list.clear();
                            int no_pass_number_love=0;
                            //3*3
                            for (int i=0;i<desktop_number_love/9+1;i++)
                            {
                                OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                                Show_Desktop_Table_View->resize(234,255);
                                Show_Desktop_Table_View->move(234*i,0);
                                Show_Desktop_Table_View->setWrapping(true);
                                Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                                Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                                Show_Desktop_Table_View->setIconSize(QSize(50,50));
                                Show_Desktop_Table_View->setGridSize(QSize(77,85));
                                Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                                Show_Desktop_Table_View->setWordWrap(true);
                                Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                                Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
                                Love_view_list.append(Show_Desktop_Table_View);
                                layout_love->addWidget(Show_Desktop_Table_View);
                                QStandardItemModel *model_table=new QStandardItemModel;
                                QList<QStringList> desktop_list;
                                QList<QStandardItem *> item_list;
                                int number_k=0;
                                if (desktop_number_love!=0)
                                {
                                int help_no_pass_number=0;
                                for (int k=0;number_k<9;k++)
                                {
                                    if (desktop_files_list.size()<i*9+k+no_pass_number_love+1)
                                    {
                                        number_k=k;
                                    }
                                    else
                                    {
                                    bool in_love=false;
                                    for (int l=0;l<love_desktop_list.size();l++)
                                    {
                                        if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number_love][0])
                                        {
                                            in_love=true;
                                        }
                                    }
                                    if (desktop_files_list[i*9+k+no_pass_number_love].size()==4&&in_love)
                                    {
                                        number_k++;
                                        QStandardItem *item;
                                        bool is_auto=false;
                                        for (int j=0;j<auto_start_program_list.size();j++)
                                        {
                                            if (desktop_files_list[i*9+k+no_pass_number_love][0]==auto_start_program_list[j])
                                            {
                                                is_auto=true;
                                            }
                                        }
                                        if (is_auto)
                                        {
                                            QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                                            QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number_love][1]).pixmap(QSize(99,99));
                                            QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                                            result_image.fill(Qt::transparent);
                                            QPainter *painter=new QPainter(&result_image);
                                            painter->setPen(Qt::NoPen);
                                            painter->setBrush(Qt::NoBrush);
                                            painter->drawPixmap(0,0,theme_icon);
                                            painter->drawPixmap(0,50,auto_start_img);
                                            delete painter;
                                            QPixmap result_pixmap=QPixmap::fromImage(result_image);
                                            item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number_love][0]);
                                        }
                                        else
                                        {
                                            item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number_love][1]),desktop_files_list[i*9+k+no_pass_number_love][0]);
                                        }
                                        item->setSizeHint(QSize(77,85));
                                        item_list.append(item);
                                        desktop_list.append(desktop_files_list[i*9+k+no_pass_number_love]);
                                        model_table->appendRow(item);
                                    }
                                    else
                                    {
                                        help_no_pass_number++;
                                    }
                                    }
                                }
                                no_pass_number_love+=help_no_pass_number;
                                }
                                Show_Desktop_Table_View->setModel(model_table);
                                Show_Desktop_Table_View->set_information(item_list,desktop_list);
                            }
                            make_show_love_label->show_desktop_label->setLayout(layout_love);
                            delete layout_love;
                        }
                        else
                        {
                            show_love_label->move(361,95);
                            show_love_label->resize(234,265);
                            //
                            int desktop_number=0;
                            for (int i=0;i<desktop_files_list.size();i++)
                            {
                                if (desktop_files_list[i].size()==4)
                                {
                                    for (int k=0;k<love_desktop_list.size();k++)
                                    {
                                        if (desktop_files_list[i][0]==love_desktop_list[k])
                                        {
                                            if (desktop_files_list[i][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i][3]).contains(Search_string,Qt::CaseInsensitive))
                                            {
                                                desktop_number++;
                                            }
                                        }
                                    }
                                }
                            }
                            QHBoxLayout *layout=new QHBoxLayout();
                            make_show_love_label->resize(234,265);
                            make_show_love_label->show_desktop_label->resize((desktop_number/9+1)*234,255);
                            if (float(desktop_number/9)==float(desktop_number)/9)
                            {
                                make_show_love_label->set_end_x(18*(desktop_number/9));
                            }
                            else
                            {
                                make_show_love_label->set_end_x(18*(desktop_number/9+1));
                            }
                            make_show_love_label->set_now_page(1);
                            make_show_love_label->button_update();
                            delete make_show_love_label->show_desktop_label->layout();
                            for (int i=0;i<Love_view_list.size();i++)
                            {
                                for (int k=0;k<9;k++)
                                {
                                    if (k<Love_view_list[i]->model()->children().size())
                                    {
                                        delete Love_view_list[i]->model()->children()[k];
                                    }
                                }
                                delete Love_view_list[i];
                            }
                            Love_view_list.clear();
                            int no_pass_number=0;
                            //3*3
                            for (int i=0;i<desktop_number/9+1;i++)
                            {
                                OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                                Show_Desktop_Table_View->resize(234,255);
                                Show_Desktop_Table_View->move(234*i,0);
                                Show_Desktop_Table_View->setWrapping(true);
                                Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                                Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                                Show_Desktop_Table_View->setIconSize(QSize(50,50));
                                Show_Desktop_Table_View->setGridSize(QSize(77,85));
                                Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                                Show_Desktop_Table_View->setWordWrap(true);
                                Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                                Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
                                Love_view_list.append(Show_Desktop_Table_View);
                                layout->addWidget(Show_Desktop_Table_View);
                                QStandardItemModel *model_table=new QStandardItemModel;
                                QList<QStringList> desktop_list;
                                QList<QStandardItem *> item_list;
                                int number_k=0;
                                if (desktop_number!=0)
                                {
                                int help_no_pass_number=0;
                                for (int k=0;number_k<9;k++)
                                {
                                    if (desktop_files_list.size()<i*9+k+no_pass_number+1)
                                    {
                                        number_k=k;
                                    }
                                    else
                                    {
                                    bool in_love=false;
                                    for (int l=0;l<love_desktop_list.size();l++)
                                    {
                                        if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number][0]&&(desktop_files_list[i*9+k+no_pass_number][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i*9+k+no_pass_number][3]).contains(Search_string,Qt::CaseInsensitive)))
                                        {
                                            in_love=true;
                                        }
                                    }
                                    if (desktop_files_list[i*9+k+no_pass_number].size()==4&&in_love)
                                    {
                                        number_k++;
                                        QStandardItem *item;
                                        bool is_auto=false;
                                        for (int j=0;j<auto_start_program_list.size();j++)
                                        {
                                            if (desktop_files_list[i*9+k+no_pass_number][0]==auto_start_program_list[j])
                                            {
                                                is_auto=true;
                                            }
                                        }
                                        if (is_auto)
                                        {
                                            QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                                            QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]).pixmap(QSize(99,99));
                                            QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                                            result_image.fill(Qt::transparent);
                                            QPainter *painter=new QPainter(&result_image);
                                            painter->setPen(Qt::NoPen);
                                            painter->setBrush(Qt::NoBrush);
                                            painter->drawPixmap(0,0,theme_icon);
                                            painter->drawPixmap(0,50,auto_start_img);
                                            delete painter;
                                            QPixmap result_pixmap=QPixmap::fromImage(result_image);
                                            item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number][0]);
                                        }
                                        else
                                        {
                                            item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]),desktop_files_list[i*9+k+no_pass_number][0]);
                                        }
                                        item->setSizeHint(QSize(77,85));
                                        item_list.append(item);
                                        desktop_list.append(desktop_files_list[i*9+k+no_pass_number]);
                                        model_table->appendRow(item);
                                    }
                                    else
                                    {
                                        help_no_pass_number++;
                                    }
                                    }
                                }
                                no_pass_number+=help_no_pass_number;
                                }
                                Show_Desktop_Table_View->setModel(model_table);
                                Show_Desktop_Table_View->set_information(item_list,desktop_list);
                            }
                            make_show_love_label->show_desktop_label->setLayout(layout);
                            delete layout;
                        }
                        all_update();
                    }
                    if (know_what==set_auto_start)
                    {
                        QFileInfo fileinfo(desktop_type_list[row][3]);
                        QString run="cp '"+desktop_type_list[row][3]+"' '"+QDir::homePath()+"/.config/autostart/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                    if (know_what==send_to_desktop)
                    {
                        QFileInfo fileinfo(desktop_type_list[row][3]);
                        QString run="cp '"+desktop_type_list[row][3]+"' '"+QDir::homePath()+"/Desktop/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                    if (know_what==unset_auto_start)
                    {
                        QFileInfo fileinfo(desktop_type_list[row][3]);
                        QString run="rm '"+QDir::homePath()+"/.config/autostart/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                    if (know_what==remove_to_desktop)
                    {
                        QFileInfo fileinfo(desktop_type_list[row][3]);
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
    //love
    if (get_pos_in(event->pos().x(),event->pos().y(),show_love_result->pos().x(),show_love_result->pos().y(),show_love_result->width(),show_love_result->height()))
    {
        if (Love_view_list.size()>make_show_love_label->now_page-1)
        {
            int row=Love_view_list[make_show_love_label->now_page-1]->currentIndex().row();
            if (row!=-1)
            {
                if (Love_view_list[make_show_love_label->now_page-1]->desktop_files_list[row].size()==4)
                {
                    bool has_autostart=false,has_desktop=false;
                    for (int i=0;i<auto_start_program_list.size();i++)
                    {
                        if (Love_view_list[make_show_love_label->now_page-1]->desktop_files_list[row][0]==auto_start_program_list[i])
                        {
                            has_autostart=true;
                        }
                    }
                    for (int i=0;i<desktop_desktop_list.size();i++)
                    {
                        if (Love_view_list[make_show_love_label->now_page-1]->desktop_files_list[row][0]==desktop_desktop_list[i])
                        {
                            has_desktop=true;
                        }
                    }
                    QAction *know_what;
                    if (!has_autostart&&!has_desktop)
                    {
                        know_what=love_menu->exec(mapToGlobal(event->pos()));
                    }
                    else if (has_autostart&&!has_desktop)
                    {
                        know_what=love_menu_auto->exec(mapToGlobal(event->pos()));
                    }
                    else if (!has_autostart&&has_desktop)
                    {
                        know_what=love_menu_desktop->exec(mapToGlobal(event->pos()));
                    }
                    else if (has_autostart&&has_desktop)
                    {
                        know_what=love_menu_auto_desktop->exec(mapToGlobal(event->pos()));
                    }
                    if (know_what==open_action)
                    {
                        QString run="/bin/bash -c \"cd ~;"+Love_view_list[make_show_love_label->now_page-1]->desktop_files_list[row][2]+"\"";
                        QProcess::startDetached(run);//could not open libreoffice*;//!!!java;
                        to_close_all=true;
                    }
                    if (know_what==remove_to_love)
                    {
                        QFileInfo fileinfo(Love_view_list[make_show_love_label->now_page-1]->desktop_files_list[row][3]);
                        QString run="rm '"+QDir::homePath()+"/.local/lib/my_launcher_data/love_desktop/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        get_desktop_file();
                        if (search_line->text()==nullptr)
                        {
                            int desktop_number_love=love_desktop_list.size();
                            QHBoxLayout *layout_love=new QHBoxLayout();
                            make_show_love_label->resize(234,265);
                            make_show_love_label->show_desktop_label->resize((desktop_number_love/9+1)*234,255);
                            make_show_love_label->set_end_x(18*(desktop_number_love/9+1));
                            make_show_love_label->button_update();
                            delete make_show_love_label->show_desktop_label->layout();
                            for (int i=0;i<Love_view_list.size();i++)
                            {
                                for (int k=0;k<9;k++)
                                {
                                    if (k<Love_view_list[i]->model()->children().size())
                                    {
                                        delete Love_view_list[i]->model()->children()[k];
                                    }
                                }
                                delete Love_view_list[i];
                            }
                            Love_view_list.clear();
                            int no_pass_number_love=0;
                            //3*3
                            for (int i=0;i<desktop_number_love/9+1;i++)
                            {
                                OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                                Show_Desktop_Table_View->resize(234,255);
                                Show_Desktop_Table_View->move(234*i,0);
                                Show_Desktop_Table_View->setWrapping(true);
                                Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                                Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                                Show_Desktop_Table_View->setIconSize(QSize(50,50));
                                Show_Desktop_Table_View->setGridSize(QSize(77,85));
                                Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                                Show_Desktop_Table_View->setWordWrap(true);
                                Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                                Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
                                Love_view_list.append(Show_Desktop_Table_View);
                                layout_love->addWidget(Show_Desktop_Table_View);
                                QStandardItemModel *model_table=new QStandardItemModel;
                                QList<QStringList> desktop_list;
                                QList<QStandardItem *> item_list;
                                int number_k=0;
                                if (desktop_number_love!=0)
                                {
                                int help_no_pass_number=0;
                                for (int k=0;number_k<9;k++)
                                {
                                    if (desktop_files_list.size()<i*9+k+no_pass_number_love+1)
                                    {
                                        number_k=k;
                                    }
                                    else
                                    {
                                    bool in_love=false;
                                    for (int l=0;l<love_desktop_list.size();l++)
                                    {
                                        if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number_love][0])
                                        {
                                            in_love=true;
                                        }
                                    }
                                    if (desktop_files_list[i*9+k+no_pass_number_love].size()==4&&in_love)
                                    {
                                        number_k++;
                                        QStandardItem *item;
                                        bool is_auto=false;
                                        for (int j=0;j<auto_start_program_list.size();j++)
                                        {
                                            if (desktop_files_list[i*9+k+no_pass_number_love][0]==auto_start_program_list[j])
                                            {
                                                is_auto=true;
                                            }
                                        }
                                        if (is_auto)
                                        {
                                            QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                                            QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number_love][1]).pixmap(QSize(99,99));
                                            QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                                            result_image.fill(Qt::transparent);
                                            QPainter *painter=new QPainter(&result_image);
                                            painter->setPen(Qt::NoPen);
                                            painter->setBrush(Qt::NoBrush);
                                            painter->drawPixmap(0,0,theme_icon);
                                            painter->drawPixmap(0,50,auto_start_img);
                                            delete painter;
                                            QPixmap result_pixmap=QPixmap::fromImage(result_image);
                                            item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number_love][0]);
                                        }
                                        else
                                        {
                                            item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number_love][1]),desktop_files_list[i*9+k+no_pass_number_love][0]);
                                        }
                                        item->setSizeHint(QSize(77,85));
                                        item_list.append(item);
                                        desktop_list.append(desktop_files_list[i*9+k+no_pass_number_love]);
                                        model_table->appendRow(item);
                                    }
                                    else
                                    {
                                        help_no_pass_number++;
                                    }
                                    }
                                }
                                no_pass_number_love+=help_no_pass_number;
                                }
                                Show_Desktop_Table_View->setModel(model_table);
                                Show_Desktop_Table_View->set_information(item_list,desktop_list);
                            }
                            make_show_love_label->show_desktop_label->setLayout(layout_love);
                            delete layout_love;
                        }
                        else
                        {
                            show_love_label->move(361,95);
                            show_love_label->resize(234,265);
                            //
                            int desktop_number=0;
                            for (int i=0;i<desktop_files_list.size();i++)
                            {
                                if (desktop_files_list[i].size()==4)
                                {
                                    for (int k=0;k<love_desktop_list.size();k++)
                                    {
                                        if (desktop_files_list[i][0]==love_desktop_list[k])
                                        {
                                            if (desktop_files_list[i][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i][3]).contains(Search_string,Qt::CaseInsensitive))
                                            {
                                                desktop_number++;
                                            }
                                        }
                                    }
                                }
                            }
                            QHBoxLayout *layout=new QHBoxLayout();
                            make_show_love_label->resize(234,265);
                            make_show_love_label->show_desktop_label->resize((desktop_number/9+1)*234,255);
                            if (float(desktop_number/9)==float(desktop_number)/9)
                            {
                                make_show_love_label->set_end_x(18*(desktop_number/9));
                            }
                            else
                            {
                                make_show_love_label->set_end_x(18*(desktop_number/9+1));
                            }
                            make_show_love_label->set_now_page(1);
                            make_show_love_label->button_update();
                            delete make_show_love_label->show_desktop_label->layout();
                            for (int i=0;i<Love_view_list.size();i++)
                            {
                                for (int k=0;k<9;k++)
                                {
                                    if (k<Love_view_list[i]->model()->children().size())
                                    {
                                        delete Love_view_list[i]->model()->children()[k];
                                    }
                                }
                                delete Love_view_list[i];
                            }
                            Love_view_list.clear();
                            int no_pass_number=0;
                            //3*3
                            for (int i=0;i<desktop_number/9+1;i++)
                            {
                                OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                                Show_Desktop_Table_View->resize(234,255);
                                Show_Desktop_Table_View->move(234*i,0);
                                Show_Desktop_Table_View->setWrapping(true);
                                Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                                Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                                Show_Desktop_Table_View->setIconSize(QSize(50,50));
                                Show_Desktop_Table_View->setGridSize(QSize(77,85));
                                Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                                Show_Desktop_Table_View->setWordWrap(true);
                                Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                                Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
                                Love_view_list.append(Show_Desktop_Table_View);
                                layout->addWidget(Show_Desktop_Table_View);
                                QStandardItemModel *model_table=new QStandardItemModel;
                                QList<QStringList> desktop_list;
                                QList<QStandardItem *> item_list;
                                int number_k=0;
                                if (desktop_number!=0)
                                {
                                int help_no_pass_number=0;
                                for (int k=0;number_k<9;k++)
                                {
                                    if (desktop_files_list.size()<i*9+k+no_pass_number+1)
                                    {
                                        number_k=k;
                                    }
                                    else
                                    {
                                    bool in_love=false;
                                    for (int l=0;l<love_desktop_list.size();l++)
                                    {
                                        if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number][0]&&(desktop_files_list[i*9+k+no_pass_number][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i*9+k+no_pass_number][3]).contains(Search_string,Qt::CaseInsensitive)))
                                        {
                                            in_love=true;
                                        }
                                    }
                                    if (desktop_files_list[i*9+k+no_pass_number].size()==4&&in_love)
                                    {
                                        number_k++;
                                        QStandardItem *item;
                                        bool is_auto=false;
                                        for (int j=0;j<auto_start_program_list.size();j++)
                                        {
                                            if (desktop_files_list[i*9+k+no_pass_number][0]==auto_start_program_list[j])
                                            {
                                                is_auto=true;
                                            }
                                        }
                                        if (is_auto)
                                        {
                                            QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                                            QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]).pixmap(QSize(99,99));
                                            QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                                            result_image.fill(Qt::transparent);
                                            QPainter *painter=new QPainter(&result_image);
                                            painter->setPen(Qt::NoPen);
                                            painter->setBrush(Qt::NoBrush);
                                            painter->drawPixmap(0,0,theme_icon);
                                            painter->drawPixmap(0,50,auto_start_img);
                                            delete painter;
                                            QPixmap result_pixmap=QPixmap::fromImage(result_image);
                                            item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number][0]);
                                        }
                                        else
                                        {
                                            item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]),desktop_files_list[i*9+k+no_pass_number][0]);
                                        }
                                        item->setSizeHint(QSize(77,85));
                                        item_list.append(item);
                                        desktop_list.append(desktop_files_list[i*9+k+no_pass_number]);
                                        model_table->appendRow(item);
                                    }
                                    else
                                    {
                                        help_no_pass_number++;
                                    }
                                    }
                                }
                                no_pass_number+=help_no_pass_number;
                                }
                                Show_Desktop_Table_View->setModel(model_table);
                                Show_Desktop_Table_View->set_information(item_list,desktop_list);
                            }
                            make_show_love_label->show_desktop_label->setLayout(layout);
                            delete layout;
                        }
                        all_update();
                    }
                    if (know_what==set_auto_start)
                    {
                        QFileInfo fileinfo(Love_view_list[make_show_love_label->now_page-1]->desktop_files_list[row][3]);
                        QString run="cp '"+Love_view_list[make_show_love_label->now_page-1]->desktop_files_list[row][3]+"' '"+QDir::homePath()+"/.config/autostart/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                    if (know_what==send_to_desktop)
                    {
                        QFileInfo fileinfo(Love_view_list[make_show_love_label->now_page-1]->desktop_files_list[row][3]);
                        QString run="cp '"+Love_view_list[make_show_love_label->now_page-1]->desktop_files_list[row][3]+"' '"+QDir::homePath()+"/Desktop/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                    if (know_what==unset_auto_start)
                    {
                        QFileInfo fileinfo(Love_view_list[make_show_love_label->now_page-1]->desktop_files_list[row][3]);
                        QString run="rm '"+QDir::homePath()+"/.config/autostart/"+fileinfo.fileName()+"'";
                        string run2=run.toStdString();
                        const char* run3=run2.c_str();
                        system(run3);
                        all_update();
                    }
                    if (know_what==remove_to_desktop)
                    {
                        QFileInfo fileinfo(Love_view_list[make_show_love_label->now_page-1]->desktop_files_list[row][3]);
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
void Launcher_Widget::all_update()
{
    get_desktop_file();
    {
    for (int i=0;i<List_View_Item_List.size();i++)
    {
        delete List_View_Item_List[i];
    }
    model->clear();
    List_View_Item_List.clear();
    for (int i=0;i<desktop_files_list.size();i++)
    {
        QStandardItem *item;
        if (desktop_files_list[i].size()==4)
        {
            bool is_auto=false;
            for (int k=0;k<auto_start_program_list.size();k++)
            {
                if (desktop_files_list[i][0]==auto_start_program_list[k])
                {
                    is_auto=true;
                }
            }
            if (is_auto)
            {
                QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(15,15));
                QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i][1]).pixmap(QSize(30,30));
                QImage result_image(QSize(30,30),QImage::Format_RGBA8888);
                result_image.fill(Qt::transparent);
                QPainter *painter=new QPainter(&result_image);
                painter->setPen(Qt::NoPen);
                painter->setBrush(Qt::NoBrush);
                painter->drawPixmap(0,0,theme_icon);
                painter->drawPixmap(0,15,auto_start_img);
                delete painter;
                QPixmap result_pixmap=QPixmap::fromImage(result_image);
                item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i][0]);
            }
            else
            {
                item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i][1]),desktop_files_list[i][0]);
            }
        }
        else
        {
            item=new QStandardItem(desktop_files_list[i][0]);
            item->setSizeHint(QSize(35,35));
        }
        List_View_Item_List.append(item);
        model->appendRow(item);
    }
    Show_Desktop_List_View->setModel(model);
    if (search_line->text()!=nullptr)
    {
        for (int i=0;i<desktop_files_list.size();i++)
        {
            if (desktop_files_list[i].size()==4)
            {
                QString desktop_name=desktop_files_list[i][0];
                QString desktop_name2=from_way_to_name(desktop_files_list[i][3]);
                if (desktop_name.contains(Search_string,Qt::CaseInsensitive)||desktop_name2.contains(Search_string,Qt::CaseInsensitive))
                {
                    Show_Desktop_List_View->setRowHidden(i,false);
                }
                else
                {
                    Show_Desktop_List_View->setRowHidden(i,true);
                }
            }
        }
    }
    Show_Desktop_List_View->set_information(List_View_Item_List,desktop_files_list);
    for (int i=0;i<Table_view_list.size();i++)
    {
        Table_view_list[i]->Get_Now_Choose_type(choose_list_or_table);
    }
    }
    {
    int desktop_number=0;
    for (int i=0;i<desktop_files_list.size();i++)
    {
        if (desktop_files_list[i].size()==4)
        {
            desktop_number++;
        }
    }
    QHBoxLayout *layout=new QHBoxLayout();
    make_show_way_label->resize(351,300);
    make_show_way_label->show_desktop_label->resize((desktop_number/15+1)*351,290);
    if (float(desktop_number/15)==float(desktop_number)/15)
    {
        make_show_way_label->set_end_x(27*(desktop_number/15));
    }
    else
    {
        make_show_way_label->set_end_x(27*(desktop_number/15+1));
    }
    make_show_way_label->button_update();
    delete make_show_way_label->show_desktop_label->layout();
    for (int i=0;i<Table_view_list.size();i++)
    {
        for (int k=0;k<15;k++)
        {
            if (k<Table_view_list[i]->model()->children().size())
            {
                delete Table_view_list[i]->model()->children()[k];
            }
        }
        delete Table_view_list[i];
    }
    Table_view_list.clear();
    int no_pass_number=0;
    for (int i=0;i<desktop_number/15+1;i++)
    {
        OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
        Show_Desktop_Table_View->resize(351,290);
        Show_Desktop_Table_View->move(351*i,0);
        Show_Desktop_Table_View->setWrapping(true);
        Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
        Show_Desktop_Table_View->setViewMode(QListView::IconMode);
        Show_Desktop_Table_View->setIconSize(QSize(50,50));
        Show_Desktop_Table_View->setGridSize(QSize(69,95));
        Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
        Show_Desktop_Table_View->setWordWrap(true);
        Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
        Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(5,95)).x(),mapToGlobal(QPoint(5,95)).y());
        Show_Desktop_Table_View->Get_Now_Choose_type(choose_list_or_table);
        Table_view_list.append(Show_Desktop_Table_View);
        layout->addWidget(Show_Desktop_Table_View);
        QStandardItemModel *model_table=new QStandardItemModel;
        QList<QStringList> desktop_list;
        QList<QStandardItem *> item_list;
        int number_k=0;
        if (desktop_number!=0)
        {
        int help_no_pass_number=0;
        for (int k=0;number_k<15;k++)
        {
            if (desktop_files_list.size()<i*15+k+no_pass_number+1)
            {
                number_k=k;
            }
            else
            {
            if (desktop_files_list[i*15+k+no_pass_number].size()==4)
            {
                number_k++;
                QStandardItem *item;
                bool is_auto=false;
                for (int j=0;j<auto_start_program_list.size();j++)
                {
                    if (desktop_files_list[i*15+k+no_pass_number][0]==auto_start_program_list[j])
                    {
                        is_auto=true;
                    }
                }
                if (is_auto)
                {
                    QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                    QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]).pixmap(QSize(99,99));
                    QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                    result_image.fill(Qt::transparent);
                    QPainter *painter=new QPainter(&result_image);
                    painter->setPen(Qt::NoPen);
                    painter->setBrush(Qt::NoBrush);
                    painter->drawPixmap(0,0,theme_icon);
                    painter->drawPixmap(0,50,auto_start_img);
                    delete painter;
                    QPixmap result_pixmap=QPixmap::fromImage(result_image);
                    item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*15+k+no_pass_number][0]);
                }
                else
                {
                    item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]),desktop_files_list[i*15+k+no_pass_number][0]);
                }
                item->setSizeHint(QSize(69,95));
                item_list.append(item);
                desktop_list.append(desktop_files_list[i*15+k+no_pass_number]);
                model_table->appendRow(item);
            }
            else
            {
                help_no_pass_number++;
            }
            }
        }
        no_pass_number+=help_no_pass_number;
        }
        Show_Desktop_Table_View->setModel(model_table);
        Show_Desktop_Table_View->set_information(item_list,desktop_list);
    }
    make_show_way_label->show_desktop_label->setLayout(layout);
    delete layout;
    if (search_line->text()!=nullptr)
    {
        int desktop_number=0;
        for (int i=0;i<desktop_files_list.size();i++)
        {
            if (desktop_files_list[i].size()==4&&(desktop_files_list[i][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i][3]).contains(Search_string,Qt::CaseInsensitive)))
            {
                desktop_number++;
            }
        }
        QHBoxLayout *layout=new QHBoxLayout();
        make_show_way_label->resize(351,300);
        make_show_way_label->show_desktop_label->resize((desktop_number/15+1)*351,290);
        if (float(desktop_number/15)==float(desktop_number)/15)
        {
            make_show_way_label->set_end_x(27*(desktop_number/15));
        }
        else
        {
            make_show_way_label->set_end_x(27*(desktop_number/15+1));
        }
        make_show_way_label->set_now_page(1);
        make_show_way_label->button_update();
        delete make_show_way_label->show_desktop_label->layout();
        for (int i=0;i<Table_view_list.size();i++)
        {
            for (int k=0;k<15;k++)
            {
                if (k<Table_view_list[i]->model()->children().size())
                {
                    delete Table_view_list[i]->model()->children()[k];
                }
            }
            delete Table_view_list[i];
        }
        Table_view_list.clear();
        int no_pass_number=0;
        for (int i=0;i<desktop_number/15+1;i++)
        {
            OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
            Show_Desktop_Table_View->resize(351,290);
            Show_Desktop_Table_View->move(351*i,0);
            Show_Desktop_Table_View->setWrapping(true);
            Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
            Show_Desktop_Table_View->setViewMode(QListView::IconMode);
            Show_Desktop_Table_View->setIconSize(QSize(50,50));
            Show_Desktop_Table_View->setGridSize(QSize(69,95));
            Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
            Show_Desktop_Table_View->setWordWrap(true);
            Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
            Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(5,95)).x(),mapToGlobal(QPoint(5,95)).y());
            Show_Desktop_Table_View->Get_Now_Choose_type(choose_list_or_table);
            Table_view_list.append(Show_Desktop_Table_View);
            layout->addWidget(Show_Desktop_Table_View);
            QStandardItemModel *model_table=new QStandardItemModel;
            QList<QStringList> desktop_list;
            QList<QStandardItem *> item_list;
            int number_k=0;
            if (desktop_number!=0)
            {
            int help_no_pass_number=0;
            for (int k=0;number_k<15;k++)
            {
                if (desktop_files_list.size()<i*15+k+no_pass_number+1)
                {
                    number_k=k;
                }
                else
                {
                if (desktop_files_list[i*15+k+no_pass_number].size()==4&&(desktop_files_list[i*15+k+no_pass_number][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i*15+k+no_pass_number][3]).contains(Search_string,Qt::CaseInsensitive)))
                {
                    number_k++;
                    QStandardItem *item;
                    bool is_auto=false;
                    for (int j=0;j<auto_start_program_list.size();j++)
                    {
                        if (desktop_files_list[i*15+k+no_pass_number][0]==auto_start_program_list[j])
                        {
                            is_auto=true;
                        }
                    }
                    if (is_auto)
                    {
                        QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                        QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]).pixmap(QSize(99,99));
                        QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                        result_image.fill(Qt::transparent);
                        QPainter *painter=new QPainter(&result_image);
                        painter->setPen(Qt::NoPen);
                        painter->setBrush(Qt::NoBrush);
                        painter->drawPixmap(0,0,theme_icon);
                        painter->drawPixmap(0,50,auto_start_img);
                        delete painter;
                        QPixmap result_pixmap=QPixmap::fromImage(result_image);
                        item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*15+k+no_pass_number][0]);
                    }
                    else
                    {
                        item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*15+k+no_pass_number][1]),desktop_files_list[i*15+k+no_pass_number][0]);
                    }
                    item->setSizeHint(QSize(69,95));
                    item_list.append(item);
                    desktop_list.append(desktop_files_list[i*15+k+no_pass_number]);
                    model_table->appendRow(item);
                }
                else
                {
                    help_no_pass_number++;
                }
                }
            }
            no_pass_number+=help_no_pass_number;
            }
            Show_Desktop_Table_View->setModel(model_table);
            Show_Desktop_Table_View->set_information(item_list,desktop_list);
        }
        make_show_way_label->show_desktop_label->setLayout(layout);
        delete layout;
    }
    }
    {
        for (int i=0;i<Table_Table_View_Item_List.size();i++)
        {
            delete Table_Table_View_Item_List[i];
        }
        model_table_table->clear();
        Table_Table_View_Item_List.clear();
        for (int i=0;i<desktop_type_list.size();i++)
        {
            QStandardItem *item;
            if (desktop_type_list[i].size()==4)
            {
                bool is_auto=false;
                for (int k=0;k<auto_start_program_list.size();k++)
                {
                    if (desktop_type_list[i][0]==auto_start_program_list[k])
                    {
                        is_auto=true;
                    }
                }
                if (is_auto)
                {
                    QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(15,15));
                    QPixmap theme_icon=QIcon::fromTheme(desktop_type_list[i][1]).pixmap(QSize(30,30));
                    QImage result_image(QSize(30,30),QImage::Format_RGBA8888);
                    result_image.fill(Qt::transparent);
                    QPainter *painter=new QPainter(&result_image);
                    painter->setPen(Qt::NoPen);
                    painter->setBrush(Qt::NoBrush);
                    painter->drawPixmap(0,0,theme_icon);
                    painter->drawPixmap(0,15,auto_start_img);
                    delete painter;
                    QPixmap result_pixmap=QPixmap::fromImage(result_image);
                    item=new QStandardItem(QIcon(result_pixmap),desktop_type_list[i][0]);
                }
                else
                {
                    item=new QStandardItem(QIcon::fromTheme(desktop_type_list[i][1]),desktop_type_list[i][0]);
                }
            }
            else
            {
                item=new QStandardItem(desktop_type_list[i][0]);
                item->setSizeHint(QSize(35,35));
            }
            Table_Table_View_Item_List.append(item);
            model_table_table->appendRow(item);
        }
        Show_Desktop_Table_Table_View->setModel(model_table_table);
        if (search_line->text()!=nullptr)
        {
            for (int i=0;i<desktop_type_list.size();i++)
            {
                if (desktop_type_list[i].size()==4)
                {
                    QString desktop_name=desktop_type_list[i][0];
                    QString desktop_name2=from_way_to_name(desktop_files_list[i][3]);
                    if (desktop_name.contains(Search_string,Qt::CaseInsensitive)||desktop_name2.contains(Search_string,Qt::CaseInsensitive))
                    {
                        Show_Desktop_Table_Table_View->setRowHidden(i,false);
                    }
                    else
                    {
                        Show_Desktop_Table_Table_View->setRowHidden(i,true);
                    }
                }
            }
        }
        Show_Desktop_Table_Table_View->set_information(Table_Table_View_Item_List,desktop_type_list);
        for (int i=0;i<Table_view_list.size();i++)
        {
            Table_view_list[i]->Get_Now_Choose_type(choose_list_or_table);
        }
    }
    {
        int desktop_number=love_desktop_list.size();
        QHBoxLayout *layout=new QHBoxLayout();
        make_show_love_label->resize(234,265);
        make_show_love_label->show_desktop_label->resize((desktop_number/9+1)*234,255);
        if (float(desktop_number/9)==float(desktop_number)/9)
        {
            make_show_love_label->set_end_x(18*(desktop_number/9));
        }
        else
        {
            make_show_love_label->set_end_x(18*(desktop_number/9+1));
        }
        make_show_love_label->button_update();
        delete make_show_love_label->show_desktop_label->layout();
        for (int i=0;i<Love_view_list.size();i++)
        {
            for (int k=0;k<9;k++)
            {
                if (k<Love_view_list[i]->model()->children().size())
                {
                    delete Love_view_list[i]->model()->children()[k];
                }
            }
            delete Love_view_list[i];
        }
        Love_view_list.clear();
        int no_pass_number=0;
        //3*3
        for (int i=0;i<desktop_number/9+1;i++)
        {
            OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
            Show_Desktop_Table_View->resize(234,255);
            Show_Desktop_Table_View->move(234*i,0);
            Show_Desktop_Table_View->setWrapping(true);
            Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
            Show_Desktop_Table_View->setViewMode(QListView::IconMode);
            Show_Desktop_Table_View->setIconSize(QSize(50,50));
            Show_Desktop_Table_View->setGridSize(QSize(77,85));
            Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
            Show_Desktop_Table_View->setWordWrap(true);
            Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
            Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
            Love_view_list.append(Show_Desktop_Table_View);
            layout->addWidget(Show_Desktop_Table_View);
            QStandardItemModel *model_table=new QStandardItemModel;
            QList<QStringList> desktop_list;
            QList<QStandardItem *> item_list;
            int number_k=0;
            if (desktop_number!=0)
            {
            int help_no_pass_number=0;
            for (int k=0;number_k<9;k++)
            {
                if (desktop_files_list.size()<i*9+k+no_pass_number+1)
                {
                    number_k=k;
                }
                else
                {
                bool in_love=false;
                for (int l=0;l<love_desktop_list.size();l++)
                {
                    if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number][0])
                    {
                        in_love=true;
                    }
                }
                if (desktop_files_list[i*9+k+no_pass_number].size()==4&&in_love)
                {
                    number_k++;
                    QStandardItem *item;
                    bool is_auto=false;
                    for (int j=0;j<auto_start_program_list.size();j++)
                    {
                        if (desktop_files_list[i*9+k+no_pass_number][0]==auto_start_program_list[j])
                        {
                            is_auto=true;
                        }
                    }
                    if (is_auto)
                    {
                        QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                        QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]).pixmap(QSize(99,99));
                        QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                        result_image.fill(Qt::transparent);
                        QPainter *painter=new QPainter(&result_image);
                        painter->setPen(Qt::NoPen);
                        painter->setBrush(Qt::NoBrush);
                        painter->drawPixmap(0,0,theme_icon);
                        painter->drawPixmap(0,50,auto_start_img);
                        delete painter;
                        QPixmap result_pixmap=QPixmap::fromImage(result_image);
                        item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number][0]);
                    }
                    else
                    {
                        item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]),desktop_files_list[i*9+k+no_pass_number][0]);
                    }
                    item->setSizeHint(QSize(77,85));
                    item_list.append(item);
                    desktop_list.append(desktop_files_list[i*9+k+no_pass_number]);
                    model_table->appendRow(item);
                }
                else
                {
                    help_no_pass_number++;
                }
                }
            }
            no_pass_number+=help_no_pass_number;
            }
            Show_Desktop_Table_View->setModel(model_table);
            Show_Desktop_Table_View->set_information(item_list,desktop_list);
        }
        make_show_love_label->show_desktop_label->setLayout(layout);
        delete layout;
        for (int i=0;i<Table_view_list.size();i++)
        {
            Table_view_list[i]->Get_Now_Choose_type(choose_list_or_table);
        }
        if (search_line->text()!=nullptr)
        {
            int desktop_number=0;
            for (int i=0;i<desktop_files_list.size();i++)
            {
                if (desktop_files_list[i].size()==4)
                {
                    for (int k=0;k<love_desktop_list.size();k++)
                    {
                        if (desktop_files_list[i][0]==love_desktop_list[k])
                        {
                            if (desktop_files_list[i][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i][3]).contains(Search_string,Qt::CaseInsensitive))
                            {
                                desktop_number++;
                            }
                        }
                    }
                }
            }
            QHBoxLayout *layout=new QHBoxLayout();
            make_show_love_label->resize(234,265);
            make_show_love_label->show_desktop_label->resize((desktop_number/9+1)*234,255);
            if (float(desktop_number/9)==float(desktop_number)/9)
            {
                make_show_love_label->set_end_x(18*(desktop_number/9));
            }
            else
            {
                make_show_love_label->set_end_x(18*(desktop_number/9+1));
            }
            make_show_love_label->set_now_page(1);
            make_show_love_label->button_update();
            delete make_show_love_label->show_desktop_label->layout();
            for (int i=0;i<Love_view_list.size();i++)
            {
                for (int k=0;k<9;k++)
                {
                    if (k<Love_view_list[i]->model()->children().size())
                    {
                        delete Love_view_list[i]->model()->children()[k];
                    }
                }
                delete Love_view_list[i];
            }
            Love_view_list.clear();
            int no_pass_number=0;
            //3*3
            for (int i=0;i<desktop_number/9+1;i++)
            {
                OnlyDragListView *Show_Desktop_Table_View=new OnlyDragListView();
                Show_Desktop_Table_View->resize(234,255);
                Show_Desktop_Table_View->move(234*i,0);
                Show_Desktop_Table_View->setWrapping(true);
                Show_Desktop_Table_View->setFlow(QListView::LeftToRight);
                Show_Desktop_Table_View->setViewMode(QListView::IconMode);
                Show_Desktop_Table_View->setIconSize(QSize(50,50));
                Show_Desktop_Table_View->setGridSize(QSize(77,85));
                Show_Desktop_Table_View->setTextElideMode(Qt::ElideMiddle);
                Show_Desktop_Table_View->setWordWrap(true);
                Show_Desktop_Table_View->setEditTriggers(QListView::NoEditTriggers);
                Show_Desktop_Table_View->get_in_pos(mapToGlobal(QPoint(361,95)).x(),mapToGlobal(QPoint(361,95)).y());
                Love_view_list.append(Show_Desktop_Table_View);
                layout->addWidget(Show_Desktop_Table_View);
                QStandardItemModel *model_table=new QStandardItemModel;
                QList<QStringList> desktop_list;
                QList<QStandardItem *> item_list;
                int number_k=0;
                if (desktop_number!=0)
                {
                int help_no_pass_number=0;
                for (int k=0;number_k<9;k++)
                {
                    if (desktop_files_list.size()<i*9+k+no_pass_number+1)
                    {
                        number_k=k;
                    }
                    else
                    {
                    bool in_love=false;
                    for (int l=0;l<love_desktop_list.size();l++)
                    {
                        if (love_desktop_list[l]==desktop_files_list[i*9+k+no_pass_number][0]&&(desktop_files_list[i*9+k+no_pass_number][0].contains(Search_string,Qt::CaseInsensitive)||from_way_to_name(desktop_files_list[i*9+k+no_pass_number][3]).contains(Search_string,Qt::CaseInsensitive)))
                        {
                            in_love=true;
                        }
                    }
                    if (desktop_files_list[i*9+k+no_pass_number].size()==4&&in_love)
                    {
                        number_k++;
                        QStandardItem *item;
                        bool is_auto=false;
                        for (int j=0;j<auto_start_program_list.size();j++)
                        {
                            if (desktop_files_list[i*9+k+no_pass_number][0]==auto_start_program_list[j])
                            {
                                is_auto=true;
                            }
                        }
                        if (is_auto)
                        {
                            QPixmap auto_start_img=QIcon(":/image/image/auto_start.svg").pixmap(QSize(49,49));
                            QPixmap theme_icon=QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]).pixmap(QSize(99,99));
                            QImage result_image(QSize(99,99),QImage::Format_RGBA8888);
                            result_image.fill(Qt::transparent);
                            QPainter *painter=new QPainter(&result_image);
                            painter->setPen(Qt::NoPen);
                            painter->setBrush(Qt::NoBrush);
                            painter->drawPixmap(0,0,theme_icon);
                            painter->drawPixmap(0,50,auto_start_img);
                            delete painter;
                            QPixmap result_pixmap=QPixmap::fromImage(result_image);
                            item=new QStandardItem(QIcon(result_pixmap),desktop_files_list[i*9+k+no_pass_number][0]);
                        }
                        else
                        {
                            item=new QStandardItem(QIcon::fromTheme(desktop_files_list[i*9+k+no_pass_number][1]),desktop_files_list[i*9+k+no_pass_number][0]);
                        }
                        item->setSizeHint(QSize(77,85));
                        item_list.append(item);
                        desktop_list.append(desktop_files_list[i*9+k+no_pass_number]);
                        model_table->appendRow(item);
                    }
                    else
                    {
                        help_no_pass_number++;
                    }
                    }
                }
                no_pass_number+=help_no_pass_number;
                }
                Show_Desktop_Table_View->setModel(model_table);
                Show_Desktop_Table_View->set_information(item_list,desktop_list);
            }
            make_show_love_label->show_desktop_label->setLayout(layout);
            delete layout;
        }
    }
}
void Launcher_Widget::set_img_qmovie(QString movie_url)
{
    show_user_img->setMovie(nullptr);
    user_img_movie->stop();
    QString filesname=movie_url;
    if (filesname.contains("file:///"))
    {
        filesname.remove(0,7);
    }
    if (filesname==nullptr)
    {
        user_img_movie->setFileName(":/image/image/demo.gif");
    }
    else
    {
        QFile file(filesname);
        if (file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            user_img_movie->setFileName(filesname);
        }
        else
        {
            user_img_movie->setFileName(":/image/image/demo.gif");
        }
    }
    user_img_movie->setScaledSize(QSize(40,40));
    user_img_movie->start();
    show_user_img->resize(40,40);
    show_user_img->setMovie(user_img_movie);
}
QString Launcher_Widget::from_way_to_name(QString way)
{
    int index;
    QString new_way=way;
    index=new_way.lastIndexOf("/");
    new_way.remove(0,index);
    index=new_way.lastIndexOf(".");
    new_way.truncate(index);
    return new_way;
}
