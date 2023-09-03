#ifndef FULLSCREENSHOWTABLELABEL_H
#define FULLSCREENSHOWTABLELABEL_H
#include<QLabel>
#include<QTimer>
#include<QPushButton>
class FullScreenShowTableLabel:public QLabel
{
    Q_OBJECT
public:
    FullScreenShowTableLabel(QWidget *parent=nullptr);
    QLabel *show_desktop_label=new QLabel(this);
    int now_page=1;
public slots:
    void time_update();
    void set_end_page(int new_end_page);
    void button_update();
    void set_now_page(int page);
protected:
    void wheelEvent(QWheelEvent *event);
    QTimer *timer_my_listview=new QTimer();
    int run_x=0;
    int end_page=0;
    int to_now_page=1;
    bool can_change=false;
    float pos_x=0;
    QRect screenRect;
    QList<QPushButton *>button_list;
};
#endif // FULLSCREENSHOWTABLELABEL_H
