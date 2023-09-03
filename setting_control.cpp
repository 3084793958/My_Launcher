#include "setting_control.h"
#include"keyscan.h"
#include<fstream>
#include<iostream>
using namespace std;
int choose_simple_or_fullscreen=1;
bool simple_close=false;
bool fullscreen_close=false;
Setting_Control::Setting_Control(QWidget *parent)
    :QWidget(parent)
{
    setWindowFlags(Qt::Tool);
    resize(0,0);
    load_config();
    if (new_choose_s_or_f==1)
    {
        launcher_simple->show();
        launcher_fullscreen->close();
    }
    if (new_choose_s_or_f==2)
    {
        launcher_simple->close();
        launcher_fullscreen->show();
    }
    keyScan * btnCheck = new keyScan(this);
    connect(btnCheck,&keyScan::sig_keyPressed,this,[=](unsigned char c){
        if (c==133||c==134)
        {
            if (new_choose_s_or_f==1)
            {
                launcher_simple->get_desktop_file();
                launcher_simple->all_update();
                launcher_fullscreen->close();
                if (launcher_simple->isHidden())
                {
                    launcher_simple->show();
                }
                else
                {
                    launcher_simple->close();
                }
            }
            if (new_choose_s_or_f==2)
            {
                launcher_fullscreen->get_desktop_file();
                launcher_fullscreen->all_update();
                launcher_simple->close();
                if (launcher_fullscreen->isHidden())
                {
                    launcher_fullscreen->show();
                }
                else
                {
                    launcher_fullscreen->close();
                }
            }
        }
        if (c==9)
        {
            launcher_simple->close();
            launcher_fullscreen->close();
        }
    });
    connect(btnCheck,&keyScan::sig_buttonPressed,this,[=](unsigned char c){
        if (new_choose_s_or_f==1)
        {
            if (!this->get_pos_in(mouse->pos().x(),mouse->pos().y(),launcher_simple->pos().x(),launcher_simple->pos().y(),launcher_simple->width(),launcher_simple->height()))
            {
                launcher_simple->close();
                launcher_fullscreen->close();
            }
        }
        if (new_choose_s_or_f==2)
        {
            if (!this->get_pos_in(mouse->pos().x(),mouse->pos().y(),launcher_fullscreen->pos().x(),launcher_fullscreen->pos().y(),launcher_fullscreen->width(),launcher_fullscreen->height()))
            {
                launcher_simple->close();
                launcher_fullscreen->close();
            }
        }
    });
    btnCheck->start();
    /*launcher_simple->close();
    launcher_fullscreen->close();*/
    can_get=false;
    launcher_setting->close();
    launcher_setting->can_send=false;
    connect(launcher_simple->to_full_screen,SIGNAL(clicked()),this,SLOT(change_to_fullscreen()));
    connect(launcher_fullscreen->back_to_simple,SIGNAL(clicked()),this,SLOT(change_to_simple()));
    connect(launcher_simple->setting_this,SIGNAL(clicked()),this,SLOT(call_setting()));
    connect(launcher_fullscreen->setting_this,SIGNAL(clicked()),this,SLOT(call_setting()));
    connect(launcher_simple->shutdown,SIGNAL(clicked()),this,SLOT(button_click_to_close()));
    connect(launcher_simple->setting_dde,SIGNAL(clicked()),this,SLOT(button_click_to_close()));
    timer->setInterval(100);
    connect(timer,SIGNAL(timeout()),this,SLOT(time_update()));
    timer->start();
    can_get=true;
}
void Setting_Control::time_update()
{
    if (launcher_setting->can_send&&can_get)
    {
        launcher_setting->can_send=false;
        if (launcher_setting->choose_simple_or_fullscreen_setting==1||launcher_setting->choose_simple_or_fullscreen_setting==2)
        {
            new_choose_s_or_f=launcher_setting->choose_simple_or_fullscreen_setting;
            choose_simple_or_fullscreen=new_choose_s_or_f;
        }
        launcher_fullscreen->set_fullscreen_movie(launcher_setting->fullscreen_background_url);
        launcher_simple->set_img_qmovie(launcher_setting->user_img_url);
        if (launcher_setting->right_to_get_pos)
        {
            launcher_simple->move(launcher_setting->simple_pos_x,launcher_setting->simple_pos_y);
        }
        else
        {
            launcher_simple->move(5,QApplication::desktop()->height()-40-5-400);
        }
    }
    if (launcher_simple->to_close_all)
    {
        launcher_simple->to_close_all=false;
        launcher_fullscreen->close();
        launcher_simple->close();
    }
    for (int i=0;i<launcher_simple->Table_view_list.size();i++)
    {
        if (launcher_simple->Table_view_list[i]->to_close_all)
        {
            launcher_simple->Table_view_list[i]->to_close_all=false;
            launcher_fullscreen->close();
            launcher_simple->close();
        }
    }
    for (int i=0;i<launcher_simple->Love_view_list.size();i++)
    {
        if (launcher_simple->Love_view_list[i]->to_close_all)
        {
            launcher_simple->Love_view_list[i]->to_close_all=false;
            launcher_fullscreen->close();
            launcher_simple->close();
        }
    }
    if (launcher_fullscreen->to_close_all)
    {
        launcher_fullscreen->to_close_all=false;
        launcher_fullscreen->close();
        launcher_simple->close();
    }
    for (int i=0;i<launcher_fullscreen->make_view_list.size();i++)
    {
        if (launcher_fullscreen->make_view_list[i]->to_close_all)
        {
            launcher_fullscreen->make_view_list[i]->to_close_all=false;
            launcher_fullscreen->close();
            launcher_simple->close();
        }
    }
    choose_simple_or_fullscreen=new_choose_s_or_f;
    simple_close=launcher_simple->isHidden();
    fullscreen_close=launcher_fullscreen->isHidden();
}
void Setting_Control::change_to_fullscreen()
{
    new_choose_s_or_f=2;
    choose_simple_or_fullscreen=2;
    launcher_setting->choose_simple_or_fullscreen_setting=2;
    launcher_fullscreen->get_desktop_file();
    launcher_fullscreen->all_update();
    launcher_simple->close();
    launcher_fullscreen->show();
    save_config();
}
void Setting_Control::change_to_simple()
{
    new_choose_s_or_f=1;
    choose_simple_or_fullscreen=1;
    launcher_setting->choose_simple_or_fullscreen_setting=1;
    launcher_simple->get_desktop_file();
    launcher_simple->all_update();
    launcher_fullscreen->close();
    launcher_simple->show();
    save_config();
}
void Setting_Control::call_setting()
{
    launcher_setting->choose_simple_or_fullscreen_setting=new_choose_s_or_f;
    launcher_fullscreen->close();
    launcher_simple->close();
    launcher_setting->show();
}
void Setting_Control::save_config()
{
    system("mkdir ~/.local/lib/my_launcher_data;touch ~/.local/lib/my_launcher_data/launcher_data1.txt");
    string files_name1=getenv("HOME")+string("/.local/lib/my_launcher_data/launcher_data1.txt");
    fstream f;
    f.open(files_name1,ios::out);
    f<<"//data"<<endl;
    f<<new_choose_s_or_f<<endl;
    f<<launcher_setting->fullscreen_background_url.toStdString()<<endl;
    f<<launcher_setting->user_img_url.toStdString()<<endl;
    f<<launcher_setting->can_send<<endl;
    if (launcher_setting->right_to_get_pos&&launcher_setting->get_simple_pos_x->text()!=nullptr&&launcher_setting->get_simple_pos_y->text()!=nullptr)
    {
        f<<launcher_setting->simple_pos_x<<endl<<launcher_setting->simple_pos_y<<endl;
    }
    else
    {
        f<<"nullptr"<<endl<<"nullptr"<<endl;
    }
    f.close();
}
void Setting_Control::load_config()
{
    system("mkdir ~/.local/lib/my_launcher_data;touch ~/.local/lib/my_launcher_data/launcher_data1.txt");
    //get
    string files_name1=getenv("HOME")+string("/.local/lib/my_launcher_data/launcher_data1.txt");
    ifstream load_data;
    load_data.open(files_name1,ios::in);
    string s;
    int load_time=-1;
    while(getline(load_data,s))
    {
        load_time++;
        if (load_time==1)
        {
            new_choose_s_or_f=QString::fromStdString(s).toInt();
        }
        if (load_time==2)
        {
            launcher_setting->fullscreen_background_url=QString::fromStdString(s);
            launcher_setting->set_fullscreen_background->setText(QString::fromStdString(s));
            launcher_fullscreen->set_fullscreen_movie(QString::fromStdString(s));
        }
        if (load_time==3)
        {
            launcher_setting->user_img_url=QString::fromStdString(s);
            launcher_setting->set_user_img->setText(QString::fromStdString(s));
            launcher_simple->set_img_qmovie(QString::fromStdString(s));
        }
        if (load_time==4)
        {
            if (s=="1")
            {
                launcher_setting->can_send=true;
            }
            else
            {
                launcher_setting->can_send=false;
            }
        }
        if (load_time==5)
        {
            if (s!="nullptr")
            {
            launcher_setting->simple_pos_x=QString::fromStdString(s).toInt();
            launcher_setting->get_simple_pos_x->setText(QString::fromStdString(s));
            }
            else
            {
                launcher_setting->simple_pos_x=5;
                launcher_setting->get_simple_pos_x->setText(nullptr);
            }
        }
        if (load_time==6)
        {
            if (s!="nullptr")
            {
            launcher_setting->simple_pos_y=QString::fromStdString(s).toInt();
            launcher_setting->get_simple_pos_y->setText(QString::fromStdString(s));
            }
            else
            {
                launcher_setting->simple_pos_y=QApplication::desktop()->height()-40-5-400;
                launcher_setting->get_simple_pos_y->setText(nullptr);
            }
            if (launcher_setting->right_to_get_pos&&launcher_setting->get_simple_pos_x->text()!=nullptr&&launcher_setting->get_simple_pos_y->text()!=nullptr)
            {
                launcher_simple->move(launcher_setting->simple_pos_x,launcher_setting->simple_pos_y);
            }
            else
            {
                launcher_simple->move(5,QApplication::desktop()->height()-40-5-400);
            }
        }
    }
    //get
}
void Setting_Control::button_click_to_close()
{
    launcher_simple->close();
    launcher_fullscreen->close();
}
bool Setting_Control::get_pos_in(int pos_x,int pos_y,int in_x,int in_y,int in_size_x,int in_size_y)
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
