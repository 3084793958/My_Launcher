#ifndef MYLISTVIEW_H
#define MYLISTVIEW_H
#include<QListView>
#include<QTimer>
#include<QStandardItem>
class MyListView:public QListView
{
    Q_OBJECT
public:
    MyListView(QWidget *parent=nullptr);
public slots:
    void time_update();
    void set_information(QList<QStandardItem *> List,QList<QStringList> desktop_list);
protected:
    void wheelEvent(QWheelEvent *event);
    QTimer *timer_my_listview=new QTimer();
    int degress=0;
    void mouseMoveEvent(QMouseEvent *event);
    QList<QStandardItem *> List_View_Item_List;
    QList<QStringList> desktop_files_list;
};

#endif // MYLISTVIEW_H
