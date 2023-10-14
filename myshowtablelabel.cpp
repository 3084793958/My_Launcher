#include "myshowtablelabel.h"
#include<QWheelEvent>
#include<QDebug>
#include<QHBoxLayout>
MyShowTableLabel::MyShowTableLabel(QWidget *parent)
    :QLabel(parent)
{
    timer_my_listview->setInterval(15);
    connect(timer_my_listview,SIGNAL(timeout()),this,SLOT(time_update()));
    timer_my_listview->start();
}
void MyShowTableLabel::wheelEvent(QWheelEvent *event)
{
    if (event->orientation()==Qt::Vertical)
    {
        if (event->angleDelta().ry()>0)
        {
            run_x-=13;
            if (now_page<=end_x/27&&now_page>1)
            {
                now_page--;
                button_update();
            }
        }
        else
        {
            run_x+=13;
            if (now_page<end_x/27)
            {
                now_page++;
                button_update();
            }
        }
        if (now_page>end_x/27)
        {
            now_page=end_x/27;
        }
        else if (now_page<1)
        {
            now_page=1;
        }
    }
    //end_x/27;
    event->accept();
}
void MyShowTableLabel::time_update()
{
    if (run_x>0)
    {
        if (show_desktop_label->pos().x()>-end_x*13+351)
        {
            show_desktop_label->move(show_desktop_label->pos().x()-27,show_desktop_label->pos().y());
            run_x--;
        }
        else
        {
            run_x=0;
        }
    }
    else if (run_x<0)
    {
        if (show_desktop_label->pos().x()<0)
        {
            show_desktop_label->move(show_desktop_label->pos().x()+27,show_desktop_label->pos().y());
            run_x++;
        }
        else
        {
            run_x=0;
        }
    }
    if (to_now_page!=now_page)
    {
        if (can_change)
        {
            run_x=13*(to_now_page-now_page);
            now_page=to_now_page;
            button_update();
            can_change=false;
        }
        else
        {
            to_now_page=now_page;
        }
    }
    if (run_x==0&&now_page==1&&show_desktop_label->pos().x()!=0)
    {
        show_desktop_label->move(0,show_desktop_label->pos().y());
    }
}
void MyShowTableLabel::set_end_x(int new_end_x)
{
    end_x=new_end_x;
}
void MyShowTableLabel::button_update()
{
    for (int i=0;i<button_list.size();i++)
    {
        delete button_list[i];
    }
    button_list.clear();
    if (now_page<=end_x/27&&end_x/27!=1)
    {
        bool pass_choose=false;
        for (int i=0;i<end_x/27;i++)
        {
            QPushButton *push_button=new QPushButton(this);
            if (i==now_page-1)
            {
                push_button->resize(50,10);
                push_button->move(195-15*end_x/27/2-40+i*15,290);
                pass_choose=true;
            }
            else
            {
                push_button->resize(10,10);
                if (pass_choose)
                {
                    push_button->move(195-15*end_x/27/2+i*15,290);
                }
                else
                {
                    push_button->move(195-15*end_x/27/2-40+i*15,290);
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
void MyShowTableLabel::set_now_page(int page)
{
    run_x=13*(page-now_page);
    now_page=page;
    button_update();
}
