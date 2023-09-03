#include "mylistview.h"
#include<QScroller>
#include<QWheelEvent>
#include<QScrollBar>
#include<QDebug>
#include<QMimeData>
#include<QDrag>
#include<QStandardItem>
MyListView::MyListView(QWidget *parent)
    :QListView(parent)
{
    setViewMode(QListView::ListMode);
    setFlow(QListView::TopToBottom);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    QScroller::grabbedGesture(this);
    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::DragOnly);
    timer_my_listview->setInterval(30);
    connect(timer_my_listview,SIGNAL(timeout()),this,SLOT(time_update()));
    timer_my_listview->start();
}
void MyListView::wheelEvent(QWheelEvent *event)
{
    if (event->orientation()==Qt::Vertical)
    {
        degress=event->angleDelta().ry()/6;
    }
    event->accept();
}
void MyListView::time_update()
{
    if (degress<0)
    {
        degress++;
    }
    if (degress>0)
    {
        degress--;
    }
    verticalScrollBar()->setValue(verticalScrollBar()->value()-degress);
}
void MyListView::mouseMoveEvent(QMouseEvent *event)
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
                drag->setPixmap(files_icon.pixmap(QSize(30,30)));
                drag->setHotSpot(QPoint(8,8));
                drag->exec(Qt::CopyAction,Qt::CopyAction);
            }
        }
    }
}
void MyListView::set_information(QList<QStandardItem *> List,QList<QStringList> desktop_list)
{
    List_View_Item_List=List;
    desktop_files_list=desktop_list;
}
