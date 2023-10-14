#include "onlydraglistview.h"
#include<QScroller>
#include<QWheelEvent>
#include<QScrollBar>
#include<QDebug>
#include<QMimeData>
#include<QDrag>
#include<QStandardItem>
#include<QProcess>
#include<KWindowEffects>
#include<QPainterPath>
#include"setting_control.h"
OnlyDragListView::OnlyDragListView(QWidget *parent)
    :QListView(parent)
{
    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::DragOnly);
    connect(this,SIGNAL(clicked(QModelIndex)),this,SLOT(click_run_class()));
    setStyleSheet("QListView{background:rgba(0,0,0,0);color:rgb(0,0,0);border-radius:10px 10px}"
                  "QListView::item:hover{background:rgba(255,255,255,100);border-left:3px solid rgb(0,85,255);color:rgb(0,0,0);border-radius:10px 10px}"
                  "QListView::item:selected{background:rgba(0,170,255,255);color:rgb(255,255,255);border-radius:10px 10px}");
    setAlternatingRowColors(true);
    timer_my_listview->setInterval(700);
    connect(timer_my_listview,SIGNAL(timeout()),this,SLOT(time_update()));
    timer_my_listview->start();
    show_detail->setStyleSheet("QLabel{border-radius:7px 7px;background:rgba(255,255,255,25);font-size:15px;color:rgb(0,0,0)}");
    show_detail->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool|Qt::FramelessWindowHint|Qt::Popup);
    show_detail->setAttribute(Qt::WA_TranslucentBackground,true);
    show_detail->setAutoFillBackground(false);
    QPainterPath PP;
    PP.addRoundedRect(show_detail->rect(),10,10);
    KWindowEffects::enableBlurBehind(show_detail->winId(),true,PP.toFillPolygon().toPolygon());
}
void OnlyDragListView::mouseMoveEvent(QMouseEvent *event)
{
    viewport()->setCursor(Qt::PointingHandCursor);
    if (event->buttons()&Qt::LeftButton)
    {
        int row=currentIndex().row();
        if (row!=-1)
        {
            if (desktop_files_list[row].size()==4)
            {
                QStandardItem *index=List_View_Item_List[row];
                QIcon files_icon=index->icon();
                QString fileName=desktop_files_list[row][3];
                QList<QUrl> urls;
                urls.append(QUrl(fileName));
                QMimeData *mimeData=new QMimeData;
                mimeData->setUrls(urls);
                QDrag *drag=new QDrag(this);
                drag->setMimeData(mimeData);
                drag->setPixmap(files_icon.pixmap(QSize(50,50)));
                drag->setHotSpot(QPoint(13,13));
                drag->exec(Qt::CopyAction,Qt::CopyAction);
            }
        }
    }
    if (!event->buttons())
    {
        can_hover=true;
    }
    else
    {
        can_hover=false;
    }
}
void OnlyDragListView::set_information(QList<QStandardItem *> List,QList<QStringList> desktop_list)
{
    List_View_Item_List=List;
    desktop_files_list=desktop_list;
}
void OnlyDragListView::click_run_class()
{
    int row=currentIndex().row();
    if (row!=-1)
    {
        QModelIndex index=model()->index(-1,0);
        setCurrentIndex(index);
        if (desktop_files_list[row].size()==4)
        {
            if (!desktop_files_list[row][2].contains("|terminal|"))
            {
                QString run="/bin/bash -c \"cd ~;"+desktop_files_list[row][2]+"\"";
                QProcess::startDetached(run);//could not open libreoffice*;//!!!java in QC;
            }
            else
            {
                QString new_exec=desktop_files_list[row][2];
                new_exec.chop(10);
                QString run="/bin/bash -c \"cd ~;deepin-terminal -e "+new_exec+"\"";
                qDebug()<<run;
                QProcess::startDetached(run);
            }
            to_close_all=true;
        }
    }
}
void OnlyDragListView::time_update()
{
    if (can_hover)
    {
        if (get_pos_in(mouse->pos().x(),mouse->pos().y(),mapToGlobal(QPoint(0,0)).x(),mapToGlobal(QPoint(0,0)).y(),width(),height())&&get_pos_in(mouse->pos().x(),mouse->pos().y(),in_pos_x,in_pos_y,width(),height()))
        {
            if (height()==255&&choose_simple_or_fullscreen==1&&!simple_close)//love
            {
                int x=mouse->pos().x()-mapToGlobal(QPoint(0,0)).x(),y=mouse->pos().y()-mapToGlobal(QPoint(0,0)).y();
                bool found=false;
                for (int i=0;i<3;i++)//H
                {
                    for (int k=0;k<3;k++)//V
                    {
                        if (get_pos_in(x,y,77*k,85*i,77,85))
                        {
                            show_detail->move(mouse->pos().x()+10,mouse->pos().y()+10);
                            if (desktop_files_list.size()>=i*3+k+1)
                            {
                                found=true;
                                show_detail->setText(desktop_files_list[i*3+k][0]);
                                show_detail->adjustSize();
                                QPainterPath PP;
                                PP.addRoundedRect(show_detail->rect(),7,7);
                                KWindowEffects::enableBlurBehind(show_detail->winId(),true,PP.toFillPolygon().toPolygon());
                            }
                        }
                    }
                }
                if (found)
                {
                    show_detail->show();
                }
                else
                {
                    show_detail->hide();
                }
            }
            else if (height()==290&&now_choose_type==2&&choose_simple_or_fullscreen==1&&!simple_close)//table
            {
                int x=mouse->pos().x()-mapToGlobal(QPoint(0,0)).x(),y=mouse->pos().y()-mapToGlobal(QPoint(0,0)).y();
                bool found=false;
                for (int i=0;i<3;i++)//H
                {
                    for (int k=0;k<5;k++)//V
                    {
                        if (get_pos_in(x,y,69*k,96*i,69,95))
                        {
                            show_detail->move(mouse->pos().x()+10,mouse->pos().y()+10);
                            if (desktop_files_list.size()>=i*5+k+1)
                            {
                                found=true;
                                show_detail->setText(desktop_files_list[i*5+k][0]);
                                show_detail->adjustSize();
                                QPainterPath PP;
                                PP.addRoundedRect(show_detail->rect(),7,7);
                                KWindowEffects::enableBlurBehind(show_detail->winId(),true,PP.toFillPolygon().toPolygon());
                            }
                        }
                    }
                }
                if (found)
                {
                    show_detail->show();
                }
                else
                {
                    show_detail->hide();
                }
            }
            else if (width()==QApplication::desktop()->width()-80&&choose_simple_or_fullscreen==2&&!fullscreen_close)//fullscreen
            {
                int x=mouse->pos().x()-mapToGlobal(QPoint(0,0)).x(),y=mouse->pos().y()-mapToGlobal(QPoint(0,0)).y();
                bool found=false;
                for (int i=0;i<4;i++)//H
                {
                    for (int k=0;k<7;k++)//V
                    {
                        if (get_pos_in(x,y,(QApplication::desktop()->width()-170)/7*k,((QApplication::desktop()->height()-170)/4-5)*i,(QApplication::desktop()->width()-170)/7,(QApplication::desktop()->height()-170)/4-5))
                        {
                            show_detail->move(mouse->pos().x()+10,mouse->pos().y()+10);
                            if (desktop_files_list.size()>=i*7+k+1)
                            {
                                found=true;
                                show_detail->setText(desktop_files_list[i*7+k][0]);
                                show_detail->adjustSize();
                                QPainterPath PP;
                                PP.addRoundedRect(show_detail->rect(),7,7);
                                KWindowEffects::enableBlurBehind(show_detail->winId(),true,PP.toFillPolygon().toPolygon());
                            }
                        }
                    }
                }
                if (found)
                {
                    show_detail->show();
                }
                else
                {
                    show_detail->hide();
                }
            }
            else
            {
                show_detail->hide();
            }
        }
        else
        {
            show_detail->hide();
        }
    }
    else
    {
        show_detail->hide();
    }
}
bool OnlyDragListView::get_pos_in(int pos_x,int pos_y,int in_x,int in_y,int in_size_x,int in_size_y)
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
void OnlyDragListView::get_in_pos(int x,int y)
{
    in_pos_x=x;
    in_pos_y=y;
}
void OnlyDragListView::Get_Now_Choose_type(int choose_type)
{
    now_choose_type=choose_type;
}
OnlyDragListView::~OnlyDragListView()
{
    delete show_detail;
}
