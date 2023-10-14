#ifndef LAUNCHER_FULLSCREEN_H
#define LAUNCHER_FULLSCREEN_H
#include"launcher_widget.h"
#include"fullscreenshowtablelabel.h"
class Launcher_FullScreen:public QWidget
{
    Q_OBJECT
public:
    explicit Launcher_FullScreen(QWidget *parent=nullptr);
    QMovie *fullscreen_movie=new QMovie(this);
    QLabel *show_movie=new QLabel(this);
    QPushButton *setting_this=new QPushButton(this);
    QPushButton *back_to_simple=new QPushButton(this);
    QLineEdit *search_line=new QLineEdit(this);
    QAction *search_img_action=new QAction(this);
    QTimer *timer=new QTimer();
    QList<QStringList> desktop_files_list;
    FullScreenShowTableLabel *make_show_label=new FullScreenShowTableLabel(this);
    QList<OnlyDragListView *> make_view_list;
    QStringList auto_start_program_list;
    QList<QStringList> search_get_desktop;
    QString search_words=nullptr;
    QAction *search_del_action=new QAction(this);
    bool already_remove_del=true;
    QStringList desktop_desktop_list;
    QMenu *result_menu=new QMenu(this);
    QMenu *result_menu_auto=new QMenu(this);//autostart
    QMenu *result_menu_desktop=new QMenu(this);//desktop
    QMenu *result_menu_auto_desktop=new QMenu(this);//autostart+desktop
    QAction *open_action=new QAction(tr("打开"),this);
    QAction *set_auto_start=new QAction(tr("开机自启动"),this);//=>restart
    QAction *unset_auto_start=new QAction(tr("取消开机自启动"),this);
    QAction *send_to_desktop=new QAction(tr("发送到桌面"),this);
    QAction *remove_to_desktop=new QAction(tr("从桌面上移除"),this);
    bool to_close_all=false;
public slots:
    void set_fullscreen_movie(QString movie_url);
    void timer_update();
    void get_desktop_file();
    void del_search_text();
    void all_update();
    QString from_way_to_name(QString way);
protected:
    void contextMenuEvent(QContextMenuEvent *event);
    bool get_pos_in(int pos_x,int pos_y,int in_x,int in_y,int in_size_x,int in_size_y);
};
static QStringList listPYfullscreen;
static bool sort_data(QStringList list1,QStringList list2);
#endif // LAUNCHER_FULLSCREEN_H
