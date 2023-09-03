#ifndef SETTING_WIDGET_H
#define SETTING_WIDGET_H
#include<QtWidgets>
class Setting_Widget:public QWidget
{
    Q_OBJECT
public:
    explicit Setting_Widget(QWidget *parent=nullptr);
    QLabel *show_set_user_img=new QLabel(tr("用户头像:"),this);
    QLineEdit *set_user_img=new QLineEdit(this);
    QLabel *show_set_fullscreen_background=new QLabel(tr("设置全屏背景:"),this);
    QLineEdit *set_fullscreen_background=new QLineEdit(this);
    QLabel *first_run_type=new QLabel(tr("初始运行方式:"),this);
    QPushButton *choose_simple_run=new QPushButton(tr("非全屏"),this);
    QPushButton *choose_fullscreen_run=new QPushButton(tr("全屏"),this);
    QPushButton *set_user_choose=new QPushButton(tr("设置"),this);
    QString user_img_url=nullptr,fullscreen_background_url=nullptr;
    int choose_simple_or_fullscreen_setting=1;
    bool can_send=false;
    QLabel *show_set_widget_pos=new QLabel("非全屏位置(默认(5,窗高-445)",this);
    QLineEdit *get_simple_pos_x=new QLineEdit(this);
    QLineEdit *get_simple_pos_y=new QLineEdit(this);
    int simple_pos_x=0,simple_pos_y=0;
    bool right_to_get_pos=false;
    QPushButton *quit_button=new QPushButton("完全退出",this);
public slots:
    void save_and_send();
    void choose_simple();
    void choose_fullscreen();
    void to_quit_event();
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // SETTING_WIDGET_H
