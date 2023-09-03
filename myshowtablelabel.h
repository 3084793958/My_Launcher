#ifndef MYSHOWTABLELABEL_H
#define MYSHOWTABLELABEL_H
#include<QLabel>
#include<QTimer>
#include<QPushButton>
class MyShowTableLabel:public QLabel
{
    Q_OBJECT
public:
    MyShowTableLabel(QWidget *parent=nullptr);
    QLabel *show_desktop_label=new QLabel(this);
    int now_page=1;
public slots:
    void time_update();
    void set_end_x(int new_end_x);
    void button_update();
    void set_now_page(int page);
protected:
    void wheelEvent(QWheelEvent *event);
    QTimer *timer_my_listview=new QTimer();
    int run_x=0;
    int end_x=0;
    int to_now_page=1;
    bool can_change=false;
    QList<QPushButton *>button_list;
};

#endif // MYSHOWTABLELABEL_H
