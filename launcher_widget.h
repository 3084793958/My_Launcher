#ifndef LAUNCHER_WIDGET_H
#define LAUNCHER_WIDGET_H
#include<QtWidgets>
#include"mylistview.h"
#include"myshowtablelabel.h"
#include"onlydraglistview.h"
#include"myshowlovelabel.h"
class Launcher_Widget:public QWidget
{
    Q_OBJECT
public:
    explicit Launcher_Widget(QWidget *parent=nullptr);
    QLabel *show_user_img=new QLabel(this);
    QLabel *show_user_name=new QLabel(this);
    QMovie *user_img_movie=new QMovie(this);
    QString user_name;
    QLineEdit *search_line=new QLineEdit(this);
    QPushButton *to_full_screen=new QPushButton(this);
    QAction *search_img_action=new QAction(this);
    QAction *search_del_action=new QAction(this);
    QTimer *timer=new QTimer();
    bool already_remove_del=true;
    QLabel *show_class=new QLabel(this);
    QLabel *show_love=new QLabel(this);
    QLabel *show_class_result=new QLabel(this);
    QLabel *show_love_result=new QLabel(this);
    QPushButton *shutdown=new QPushButton(this);
    QPushButton *setting_dde=new QPushButton(this);
    QPushButton *setting_this=new QPushButton(this);
    QPushButton *choose_love_button=new QPushButton(this);
    QPushButton *choose_list_button=new QPushButton(this);
    QPushButton *choose_table_button=new QPushButton(this);
    QPushButton *choose_table_table_button=new QPushButton(this);
    int choose_list_or_table=1;
    MyListView *Show_Desktop_List_View=new MyListView(this);
    QList<QStringList> desktop_files_list;//(name,icon,exec,file_name);
    QList<QStandardItem *> List_View_Item_List;
    QString Search_string=nullptr;
    QStandardItemModel *model=new QStandardItemModel(this);
    QStringList auto_start_program_list;
    QLabel *show_table_label=new QLabel(this);
    MyShowTableLabel *make_show_way_label=new MyShowTableLabel(show_table_label);
    QList<OnlyDragListView *> Table_view_list;
    QList<QStringList> desktop_type_list;//as line 35
    MyListView *Show_Desktop_Table_Table_View=new MyListView(this);
    QList<QStandardItem *>Table_Table_View_Item_List;
    QStandardItemModel *model_table_table=new QStandardItemModel(this);
    QStringList love_desktop_list;//only name
    QLabel *show_love_label=new QLabel(this);
    MyShowLoveLabel *make_show_love_label=new MyShowLoveLabel(show_love_label);
    QList<OnlyDragListView *> Love_view_list;
    QStringList desktop_desktop_list;//the desktop in desktop
    //right button menu
    QMenu *result_menu=new QMenu(this);
    QMenu *love_menu=new QMenu(this);
    QMenu *result_menu_auto=new QMenu(this);//autostart
    QMenu *love_menu_auto=new QMenu(this);
    QMenu *result_menu_desktop=new QMenu(this);//desktop
    QMenu *love_menu_desktop=new QMenu(this);
    QMenu *result_menu_auto_desktop=new QMenu(this);//autostart+desktop
    QMenu *love_menu_auto_desktop=new QMenu(this);
    QAction *open_action=new QAction(tr("打开"),this);
    //result
    QAction *add_to_love=new QAction(tr("收藏"),this);
    //love
    QAction *remove_to_love=new QAction(tr("移除"),this);
    QAction *set_auto_start=new QAction(tr("开机自启动"),this);//=>restart
    QAction *unset_auto_start=new QAction(tr("取消开机自启动"),this);
    QAction *send_to_desktop=new QAction(tr("发送到桌面"),this);
    QAction *remove_to_desktop=new QAction(tr("从桌面上移除"),this);
    bool to_close_all=false;
public slots:
    void del_search_text();
    void timer_update();
    void shut_down_click();
    void setting_dde_click();
    void choose_list_slot();
    void choose_table_slot();
    void choose_table_table_slot();
    void get_desktop_file();
    void click_run_class();
    void click_run_class_table();
    void all_update();
    void set_img_qmovie(QString movie_url);
    QString from_way_to_name(QString way);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    bool get_pos_in(int pos_x,int pos_y,int in_x,int in_y,int in_size_x,int in_size_y);
};
static QStringList listPY;
static bool sort_data(QStringList list1,QStringList list2);
#endif // LAUNCHER_WIDGET_H
