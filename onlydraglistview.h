#ifndef ONLYDRAGLISTVIEW_H
#define ONLYDRAGLISTVIEW_H
#include<QListView>
#include<QTimer>
#include<QStandardItem>
#include<QCursor>
#include<QLabel>
class OnlyDragListView:public QListView
{
    Q_OBJECT
public:
    OnlyDragListView(QWidget *parent=nullptr);
    QList<QStringList> desktop_files_list;
    ~OnlyDragListView();
    bool to_close_all=false;
public slots:
    void set_information(QList<QStandardItem *> List,QList<QStringList> desktop_list);
    void click_run_class();
    void time_update();
    void get_in_pos(int x,int y);
    void Get_Now_Choose_type(int choose_type);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    bool get_pos_in(int pos_x,int pos_y,int in_x,int in_y,int in_size_x,int in_size_y);
    QTimer *timer_my_listview=new QTimer();
    QList<QStandardItem *> List_View_Item_List;
    QCursor *mouse=new QCursor();
    bool can_hover=false;
    int in_pos_x=0,in_pos_y=0;
    QLabel *show_detail=new QLabel();
    int now_choose_type=0;
};
#endif // ONLYDRAGLISTVIEW_H
