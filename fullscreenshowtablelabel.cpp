#include "fullscreenshowtablelabel.h"
#include<QWheelEvent>
#include<QDebug>
#include<QHBoxLayout>
#include<QGuiApplication>
#include<QScreen>
FullScreenShowTableLabel::FullScreenShowTableLabel(QWidget *parent)
    :QLabel(parent)
{
    screenRect=QGuiApplication::primaryScreen()->geometry();
    timer_my_listview->setInterval(10);
    connect(timer_my_listview,SIGNAL(timeout()),this,SLOT(time_update()));
    timer_my_listview->start();
}
void FullScreenShowTableLabel::wheelEvent(QWheelEvent *event)
{
    if (event->orientation()==Qt::Vertical)
    {
        if (event->angleDelta().ry()>0)
        {
            if (now_page<=end_page&&now_page>1)
            {
                run_x-=26;
                now_page--;
                button_update();
            }
        }
        else
        {
            if (now_page<end_page)
            {
                run_x+=26;
                now_page++;
                button_update();
            }
        }
        if (now_page>end_page)
        {
            now_page=end_page;
        }
        else if (now_page<1)
        {
            now_page=1;
        }
    }
    event->accept();
}
void FullScreenShowTableLabel::time_update()
{
    screenRect=QGuiApplication::primaryScreen()->geometry();
    if (run_x>0)
    {
        pos_x-=float(screenRect.width()-80)/26;
        run_x--;
    }
    else if (run_x<0)
    {
        pos_x+=float(screenRect.width()-80)/26;
        run_x++;
    }
    if (pos_x>0)
    {
        pos_x=0;
    }
    if (pos_x<-(end_page-1)*(screenRect.width()-80))
    {
        pos_x=-(end_page-1)*(screenRect.width()-80);
    }
    if (to_now_page!=now_page)
    {
        if (can_change)
        {
            run_x=26*(to_now_page-now_page);
            now_page=to_now_page;
            button_update();
            can_change=false;
        }
        else
        {
            to_now_page=now_page;
        }
    }
    show_desktop_label->move(int(pos_x)+80,show_desktop_label->pos().y());
    if (run_x==0&&now_page==1&&show_desktop_label->pos().x()!=0)
    {
        show_desktop_label->move(80,show_desktop_label->pos().y());
    }
}
void FullScreenShowTableLabel::set_end_page(int new_end_page)
{
    end_page=new_end_page;
}
void FullScreenShowTableLabel::button_update()
{
    if (screenRect.height()==0)
    {
        screenRect=QGuiApplication::primaryScreen()->geometry();
    }
    for (int i=0;i<button_list.size();i++)
    {
        delete button_list[i];
    }
    button_list.clear();
    if (now_page<=end_page&&end_page!=1)
    {
        bool pass_choose=false;
        for (int i=0;i<end_page;i++)
        {
            QPushButton *push_button=new QPushButton(this);
            if (i==now_page-1)
            {
                push_button->resize(50,10);
                push_button->move(screenRect.width()/2-((end_page-1)*20+50)/2+i*20,screenRect.height()-165);
                pass_choose=true;
            }
            else
            {
                push_button->resize(10,10);
                if (pass_choose)
                {
                    push_button->move(screenRect.width()/2-((end_page-1)*20+50)/2+i*20+40,screenRect.height()-165);
                }
                else
                {
                    push_button->move(screenRect.width()/2-((end_page-1)*20+50)/2+i*20,screenRect.height()-165);
                }
            }
            push_button->setStyleSheet("QPushButton{border-radius:5px 5px;background:rgba(255,255,255,150)}"
                                       "QPushButton:hover{border-radius:5px 5px;background:rgba(255,255,255,200)}"
                                       "QPushButton:pressed{border-radius:5px 5px;background:rgba(255,255,255,150)}");
            push_button->setObjectName("button"+QString::number(i));
            push_button->show();
            connect(push_button,&QPushButton::clicked,this,[=]
            {
                can_change=true;
                to_now_page=i+1;
            });
            button_list.append(push_button);
        }
    }
    else
    {
        now_page=1;
    }
}
void FullScreenShowTableLabel::set_now_page(int page)
{
    run_x=26*(page-now_page);
    now_page=page;
    button_update();
}
