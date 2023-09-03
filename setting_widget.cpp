#include "setting_widget.h"
using namespace std;
Setting_Widget::Setting_Widget(QWidget *parent)
    :QWidget(parent)
{
    setWindowTitle("My_Launcher设置");
    setWindowIcon(QIcon(":/image/image/setting_this.svg"));
    resize(400,300);
    close();
    show_set_user_img->move(0,0);
    show_set_user_img->resize(100,50);
    show_set_user_img->setStyleSheet("font-size:17px;color:rgb(0,0,0)");
    set_user_img->move(110,0);
    set_user_img->resize(280,50);
    set_user_img->setPlaceholderText("图像路径(空为默认)");
    show_set_fullscreen_background->move(0,60);
    show_set_fullscreen_background->resize(100,50);
    show_set_fullscreen_background->setStyleSheet("font-size:17px;color:rgb(0,0,0)");
    set_fullscreen_background->move(110,60);
    set_fullscreen_background->resize(280,50);
    set_fullscreen_background->setPlaceholderText("图像路径(空为默认)");
    first_run_type->move(0,120);
    first_run_type->resize(200,50);
    first_run_type->setStyleSheet("font-size:17px;color:rgb(0,0,0)");
    choose_simple_run->move(210,120);
    choose_simple_run->resize(85,50);
    choose_simple_run->setStyleSheet("font-size:15px;color:rgb(0,0,0)");
    choose_fullscreen_run->move(305,120);
    choose_fullscreen_run->resize(85,50);
    choose_fullscreen_run->setStyleSheet("font-size:15px;color:rgb(0,0,0)");
    set_user_choose->move(290,240);
    set_user_choose->resize(100,50);
    set_user_choose->setStyleSheet("font-size:17px;color:rgb(0,0,0)");
    connect(choose_simple_run,SIGNAL(clicked()),this,SLOT(choose_simple()));
    connect(choose_fullscreen_run,SIGNAL(clicked()),this,SLOT(choose_fullscreen()));
    connect(set_user_choose,SIGNAL(clicked()),this,SLOT(save_and_send()));
    show_set_widget_pos->resize(270,50);
    show_set_widget_pos->move(0,180);
    show_set_widget_pos->setStyleSheet("font-size:17px;color:rgb(0,0,0)");
    get_simple_pos_x->move(280,180);
    get_simple_pos_x->resize(50,50);
    get_simple_pos_x->setPlaceholderText("x");
    get_simple_pos_y->move(340,180);
    get_simple_pos_y->resize(50,50);
    get_simple_pos_y->setPlaceholderText("y");
    quit_button->move(0,240);
    quit_button->resize(100,50);
    quit_button->setStyleSheet("font-size:17px;color:rgb(0,0,0)");
    connect(quit_button,SIGNAL(clicked()),this,SLOT(to_quit_event()));
}
void Setting_Widget::to_quit_event()
{
    system("killall My_Launcher");
}
void Setting_Widget::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}
void Setting_Widget::save_and_send()
{
    user_img_url=set_user_img->text();
    fullscreen_background_url=set_fullscreen_background->text();
    if (get_simple_pos_x->text()==nullptr||get_simple_pos_y->text()==nullptr)
    {
        right_to_get_pos=false;
    }
    else
    {
        right_to_get_pos=true;
        QString x_qstring=get_simple_pos_x->text();
        QString y_qstring=get_simple_pos_y->text();
        simple_pos_x=x_qstring.toInt();
        simple_pos_y=y_qstring.toInt();
    }
    can_send=true;
}
void Setting_Widget::choose_simple()
{
    choose_simple_or_fullscreen_setting=1;
}
void Setting_Widget::choose_fullscreen()
{
    choose_simple_or_fullscreen_setting=2;
}
