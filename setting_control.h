#ifndef SETTING_CONTROL_H
#define SETTING_CONTROL_H
#include"launcher_fullscreen.h"
#include"launcher_widget.h"
#include"setting_widget.h"
class Setting_Control:public QWidget
{
    Q_OBJECT
public:
    explicit Setting_Control(QWidget *parent=nullptr);
    Setting_Widget *launcher_setting=new Setting_Widget;
    Launcher_Widget *launcher_simple=new Launcher_Widget;
    Launcher_FullScreen *launcher_fullscreen=new Launcher_FullScreen;
    QCursor *mouse=new QCursor;
    QTimer *timer=new QTimer();
    int new_choose_s_or_f=1;
    bool can_get=false;
public slots:
    void change_to_fullscreen();
    void change_to_simple();
    void call_setting();
    void save_config();
    void load_config();
    void button_click_to_close();
    void time_update();
protected:
    bool get_pos_in(int pos_x,int pos_y,int in_x,int in_y,int in_size_x,int in_size_y);
};
extern int choose_simple_or_fullscreen;
extern bool simple_close;
extern bool fullscreen_close;
extern bool to_close_all;
#endif // SETTING_CONTROL_H
