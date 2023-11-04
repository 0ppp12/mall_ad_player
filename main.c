
/**
 * @file main
 *
 */
 /*********************
  *      INCLUDES
  *********************/
#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <unistd.h>
#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lv_examples/lv_demo.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/mouse.h"
#include "lv_drivers/indev/keyboard.h"
#include "lv_drivers/indev/mousewheel.h"
static void hal_init(void);
static int tick_thread(void *data);
void lianxi(void){//文字样式
  lv_obj_t *label1=lv_label_create(lv_scr_act());
  lv_label_set_long_mode(label1,LV_LABEL_LONG_WRAP); /*Break the long lines*/
  lv_label_set_recolor(label1,
    true); /*Enable re-coloring by commands in the text*/
  lv_label_set_text(
    label1,"#0000ff xuweihui#\n #ff00ff gz2319064#\n #ff0000 8888#\n ");
  lv_obj_set_width(label1,150); /*Set smaller width to make the lines wrap*/
  lv_obj_set_style_text_align(label1,LV_TEXT_ALIGN_CENTER,0);
  lv_obj_align(label1,LV_ALIGN_CENTER,0,0);
}
void lv_example_style_22(void){//
  lv_obj_t *obj=lv_obj_create(lv_scr_act());
  lv_obj_align(obj,LV_ALIGN_CENTER,0,0);
  lv_obj_set_size(obj,180,180);
  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_bg_color(&style,lv_palette_main(LV_PALETTE_RED));
  lv_obj_add_style(obj,&style,LV_STATE_DEFAULT);
}
void obj(){
  lv_obj_t *obj=lv_obj_create(lv_scr_act());
  lv_obj_align(obj,LV_ALIGN_CENTER,0,0);
  lv_obj_set_size(obj,180,180);
  lv_obj_t *obj2=lv_obj_create(obj);
  lv_obj_align(obj2,LV_ALIGN_CENTER,0,0);
  lv_obj_set_size(obj2,90,90);
}
void btn(){
  lv_obj_t *bt2=lv_btn_create(lv_scr_act());
  lv_obj_set_size(bt2,180,180);
  lv_obj_align(bt2,LV_ALIGN_TOP_LEFT,0,0);
  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_bg_color(&style,lv_palette_main(LV_PALETTE_RED));
  lv_obj_add_style(bt2,&style,LV_STATE_DEFAULT);
  // lv_obj_add_style(bt,&style,LV_STATE_PRESSED);

  lv_obj_t *bt=lv_btn_create(lv_scr_act());
  lv_obj_set_size(bt,180,180);
  lv_obj_align(bt,LV_ALIGN_CENTER,-200,-50);
}
static void event_cb(lv_event_t *e){
  LV_LOG_USER("Clicked");
  static uint32_t cnt=1;
  lv_obj_t *btn=lv_event_get_target(e);
  lv_obj_t *label=lv_obj_get_child(btn,0);
  lv_label_set_text_fmt(label,"%d",cnt);
  cnt++;
}
void lv_example_event_12(void){
  lv_obj_t *btn=lv_btn_create(lv_scr_act());
  lv_obj_set_size(btn,100,50);
  lv_obj_center(btn);
  lv_obj_add_event_cb(btn,event_cb,LV_EVENT_CLICKED,NULL);
  lv_obj_t *label=lv_label_create(btn);
  lv_label_set_text(label,"Click me!");
  lv_obj_center(label);
}
static void event_cb2(lv_event_t *e){
  lv_event_code_t code=lv_event_get_code(e);
  lv_obj_t *label=lv_event_get_user_data(e);
  switch(code){
    case LV_EVENT_PRESSED:
      lv_label_set_text(label,"The last button event:\nLV_EVENT_PRESSED");
      break;
    case LV_EVENT_CLICKED:
      lv_label_set_text(label,"The last button event:\nLV_EVENT_CLICKED");
      break;
    case LV_EVENT_LONG_PRESSED:
      lv_label_set_text(label,"The last button event:\nLV_EVENT_LONG_PRESSED");
      break;
    case LV_EVENT_LONG_PRESSED_REPEAT:
      lv_label_set_text(label,
        "The last button event:\nLV_EVENT_LONG_PRESSED_REPEAT");
      break;
    default:
      break;
  }
}
void lv_example_event_22(void){
  lv_obj_t *btn=lv_btn_create(lv_scr_act());
  lv_obj_set_size(btn,100,50);
  lv_obj_center(btn);
  lv_obj_t *btn_label=lv_label_create(btn);
  lv_label_set_text(btn_label,"Click me!");
  lv_obj_center(btn_label);
  lv_obj_t *info_label=lv_label_create(lv_scr_act());
  lv_label_set_text(info_label,"The last button event:\nNone");
  lv_obj_add_event_cb(btn,event_cb2,LV_EVENT_ALL,info_label);
}
static lv_style_t style;
void my_event_cb(lv_event_t *e){
  // printf("按钮被点击\n");
  lv_event_code_t code=lv_event_get_code(e);
  switch(code){
    case LV_EVENT_PRESSED:
      // printf("按钮被按下\n");
      lv_style_set_bg_color(&style,lv_palette_main(LV_PALETTE_RED));
      break;
    case LV_EVENT_RELEASED:
      // printf("按钮被松开\n");
      lv_style_set_bg_color(&style,lv_palette_main(LV_PALETTE_BLUE));
      break;
    default:
      break;
  }
}
static lv_obj_t *slider_label;
static void slider_event_cb(lv_event_t *e){
  lv_obj_t *slider=lv_event_get_target(e);
  char buf[8];
  lv_snprintf(buf,sizeof(buf),"%d%%",lv_slider_get_value(slider));
  lv_label_set_text(slider_label,buf);
  lv_obj_align_to(slider_label,slider,LV_ALIGN_OUT_BOTTOM_MID,0,10);
}
void slider(){
  lv_obj_t *slider=lv_slider_create(lv_scr_act());
  lv_obj_center(slider);
  lv_obj_add_event_cb(slider,slider_event_cb,LV_EVENT_VALUE_CHANGED,NULL);
  /*Create a label below the slider*/
  slider_label=lv_label_create(lv_scr_act());
  lv_label_set_text(slider_label,"0%");
  lv_obj_align_to(slider_label,slider,LV_ALIGN_OUT_BOTTOM_MID,0,10);
}
void imgbtn(void){
  lv_obj_t*imgbtn1=lv_imgbtn_create(lv_scr_act());
  lv_obj_set_size(imgbtn1,200,200);
  lv_obj_center(imgbtn1);
  // lv_imgbtn_set_src(imgbtn1,0,NULL,"S:/root/lv_port_pc_vscode-master/play.png",NULL);
  lv_imgbtn_set_src(imgbtn1,0,NULL,"/root/lv_port_pc_vscode-master/play.png",NULL);
}
void my_event(void){
  lv_obj_t *btn=lv_btn_create(lv_scr_act());
  lv_obj_set_size(btn,100,50);
  lv_obj_center(btn);
  lv_obj_t *btn_label=lv_label_create(btn);
  lv_label_set_text(btn_label,"Click me!");
  lv_obj_center(btn_label);
  lv_obj_t *info_label=lv_label_create(lv_scr_act());
  lv_label_set_text(info_label,"The last button event:\nNone");
  // lv_obj_add_event_cb(btn, my_event_cb, LV_EVENT_ALL, info_label);
  lv_style_init(&style);
  lv_style_set_bg_color(&style,lv_palette_main(LV_PALETTE_BLUE));
  lv_obj_add_style(btn,&style,LV_STATE_DEFAULT);
  // 添加按下事件
  lv_obj_add_event_cb(btn,my_event_cb,LV_EVENT_PRESSED,NULL);
  // 添加松开事件
  lv_obj_add_event_cb(btn,my_event_cb,LV_EVENT_RELEASED,NULL);
}
int start_f=0;
void get_time_pos();
void *play_start(void *arg){
  FILE *fp=popen("mplayer -slave -quiet -input file=/root/pipe -geometry 100:100 -zoom -x 160 -y 96 /root/1.avi","r");
  if(fp==NULL){
    perror("加载播放器失败");
    return NULL;
  }
  pthread_t tid;
  pthread_create(&tid,NULL,get_time_pos,NULL);
  int h=0,m=0,s=0,t=0;
  char *str=NULL;
  while(1){
    char buf[1024]={0};
    fgets(buf,1024,fp);
    if(feof(fp)){
      printf("播放完毕\n");
      break;
    }
    str=strstr(buf,"=");
    if(str!=NULL){
      str++;
      t=(int)atof(str);
      s=t%60;
      m=t/60;
      h=t/(60*60);
      printf("%d:%d:%d\n",h,m,s);
      // printf("%s\n",buf);
    }
    // sleep(1);
  }
  pclose(fp);
  // system("mplayer -slave -quiet -input file=/root/pipe -geometry 100:100
  // -zoom -x 80 -y 48 ../wtmid.mp4");
}
int pause_f =0;
void*my_pause(void*arg){
  while(1){
    while(pause_f){
        system("echo pause>/root/pipe");
        usleep(300000);
    }
  }
}
void play_event(lv_event_t *e){
  if(!start_f){
    // play_start();
    printf("11\n");
    start_f=1;
    pthread_t tid;
    pthread_t tid2;
    pthread_create(&tid,NULL,play_start,NULL);
    pthread_create(&tid2,NULL,my_pause,NULL);
  } else{
    lv_event_code_t code=lv_event_get_code(e);
    switch(code){
      case LV_EVENT_PRESSED:
        pause_f^=1;
        break;
      default:
        break;
    }
  }
}
void play_event2(lv_event_t *e){
  lv_event_code_t code=lv_event_get_code(e);
  switch(code){
    case LV_EVENT_PRESSED:
      system("echo pause>/root/pipe");
      break;
    default:
      break;
  }
}
void play_event3(lv_event_t *e){
  lv_event_code_t code=lv_event_get_code(e);
  switch(code){
    case LV_EVENT_PRESSED:
      if(!start_f)
        break;
      system("echo seek +10>/root/pipe");
      printf("seek +10\n");
      break;
    default:
      break;
  }
}
void play_event4(lv_event_t *e){
  lv_event_code_t code=lv_event_get_code(e);
  switch(code){
    case LV_EVENT_PRESSED:
      if(!start_f)
        break;
      system("echo seek -10>/root/pipe");
      printf("seek -10\n");
      break;
    default:
      break;
  }
}
void play_event5(lv_event_t *e){
  // system("echo seek -5>/root/pipe");
  lv_event_code_t code=lv_event_get_code(e);
  switch(code){
    case LV_EVENT_PRESSED:
      system("echo pause>/root/pipe");
      break;
    default:
      break;
  }
}
void get_time_pos(){
  while(1){
    system("echo get_time_pos>/root/pipe");
    sleep(1);
  }
}
void imgbtn2(void){
  lv_obj_t * imgbtn1=lv_imgbtn_create(lv_scr_act());
  lv_obj_set_size(imgbtn1,200,200);
  lv_obj_center(imgbtn1);
  lv_imgbtn_set_src(imgbtn1,0,NULL,"S:/root/play.png",NULL);
}
void my_play(){
  // 播放&暂停按钮
  lv_obj_t *bt=lv_btn_create(lv_scr_act());
  lv_obj_set_size(bt,80,50);
  lv_obj_align(bt,LV_ALIGN_BOTTOM_MID,0,-20);
  lv_obj_t *lb=lv_label_create(bt);
  lv_label_set_text(lb,"Play|Pause");
  lv_obj_center(lb);
  lv_obj_add_event_cb(bt,play_event,LV_EVENT_PRESSED,NULL);
  // 快进按钮
  lv_obj_t *bt2=lv_btn_create(lv_scr_act());
  lv_obj_set_size(bt2,80,50);
  lv_obj_align(bt2,LV_ALIGN_BOTTOM_MID,100,-20);
  lv_obj_t *lb2=lv_label_create(bt2);
  lv_label_set_text(lb2,"seek+10");
  lv_obj_center(lb2);
  lv_obj_add_event_cb(bt2,play_event3,LV_EVENT_PRESSED,NULL);
  // 快退按钮
  lv_obj_t *bt3=lv_btn_create(lv_scr_act());
  lv_obj_set_size(bt3,80,50);
  lv_obj_align(bt3,LV_ALIGN_BOTTOM_MID,-100,-20);
  lv_obj_t *lb3=lv_label_create(bt3);
  lv_label_set_text(lb3,"seek-10");
  lv_obj_center(lb3);
  lv_obj_add_event_cb(bt3,play_event4,LV_EVENT_PRESSED,NULL);
  // 下一个按钮
  // lv_obj_t *bt4 = lv_btn_create(lv_scr_act());
  // lv_obj_set_size(bt4, 80, 50);
  // lv_obj_align(bt4, LV_ALIGN_BOTTOM_MID, 0, -20);
  // lv_obj_t *lb4 = lv_label_create(bt4);
  // lv_label_set_text(lb4, "Previous");
  // lv_obj_center(lb4);
  // lv_obj_add_event_cb(bt4, play_event5, LV_EVENT_PRESSED, NULL);
}
int main(int argc,char **argv){
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/
  /*Initialize LVGL*/
  lv_init();
  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  hal_init();
  //! 这↓里开始改
  // lv_example_style_1();//文本框
  // lv_example_style_2();//蓝色渐变框
  // lv_example_style_3();//阴影框
  // lv_example_style_4();//外框
  // lv_example_style_5();//模糊阴影
  // lv_example_style_6();//图标
  // lv_example_style_7();//圆弧滑块
  // lv_example_style_8();//链接样式
  // lv_example_style_9();//对钩
  // lv_example_style_10();//按钮框
  // lv_example_style_11();//左右两筐，颜色布局
  // lv_example_style_12();//颜色方框
  // lv_example_style_13();//滑块
  // lv_example_style_14();//颜色按钮

  // lv_example_style_22();//红色方框
  // obj();//方框调整大小
  // btn();//两个按钮，位置
  // label();//文字+滚动


  while(1){
    lv_timer_handler();
    usleep(5*1000);
  }
  return 0;
}
void test(){
  // lv_example_label_1();
  // lianxi();
  // obj();
  // btn();
  // lv_example_event_12();
  // lv_example_event_22();
  // my_event();
  // slider();
  // lv_example_imgbtn_1();
  // imgbtn();
  // imgbtn2();
  // lv_example_event_1();
  // lv_demo_widgets();
  // lv_demo_keypad_encoder();
  // lv_demo_stress();
  // lv_demo_music();
  // menu();
  my_play();
}
static void hal_init(void){
  /* Use the 'monitor' driver which creates window on PC's monitor to simulate a
   * display*/
  monitor_init();
  /* Tick init.
   * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about
   * how much time were elapsed Create an SDL thread to do this*/
  SDL_CreateThread(tick_thread,"tick",NULL);
  /*Create a display buffer*/
  static lv_disp_draw_buf_t disp_buf1;
  static lv_color_t buf1_1[MONITOR_HOR_RES*100];
  static lv_color_t buf1_2[MONITOR_HOR_RES*100];
  lv_disp_draw_buf_init(&disp_buf1,buf1_1,buf1_2,MONITOR_HOR_RES*100);
  /*Create a display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/
  disp_drv.draw_buf=&disp_buf1;
  disp_drv.flush_cb=monitor_flush;
  disp_drv.hor_res=MONITOR_HOR_RES;
  disp_drv.ver_res=MONITOR_VER_RES;
  disp_drv.antialiasing=1;
  lv_disp_t *disp=lv_disp_drv_register(&disp_drv);
  lv_theme_t *th=lv_theme_default_init(
    disp,lv_palette_main(LV_PALETTE_BLUE),lv_palette_main(LV_PALETTE_RED),
    LV_THEME_DEFAULT_DARK,LV_FONT_DEFAULT);
  lv_disp_set_theme(disp,th);
  lv_group_t *g=lv_group_create();
  lv_group_set_default(g);
  /* Add the mouse as input device
   * Use the 'mouse' driver which reads the PC's mouse*/
  mouse_init();
  static lv_indev_drv_t indev_drv_1;
  lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
  indev_drv_1.type=LV_INDEV_TYPE_POINTER;
  /*This function will be called periodically (by the library) to get the mouse
   * position and state*/
  indev_drv_1.read_cb=mouse_read;
  lv_indev_t *mouse_indev=lv_indev_drv_register(&indev_drv_1);
  keyboard_init();
  static lv_indev_drv_t indev_drv_2;
  lv_indev_drv_init(&indev_drv_2); /*Basic initialization*/
  indev_drv_2.type=LV_INDEV_TYPE_KEYPAD;
  indev_drv_2.read_cb=keyboard_read;
  lv_indev_t *kb_indev=lv_indev_drv_register(&indev_drv_2);
  lv_indev_set_group(kb_indev,g);
  mousewheel_init();
  static lv_indev_drv_t indev_drv_3;
  lv_indev_drv_init(&indev_drv_3); /*Basic initialization*/
  indev_drv_3.type=LV_INDEV_TYPE_ENCODER;
  indev_drv_3.read_cb=mousewheel_read;
  lv_indev_t *enc_indev=lv_indev_drv_register(&indev_drv_3);
  lv_indev_set_group(enc_indev,g);
  /*Set a cursor for the mouse*/
  LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  lv_obj_t *cursor_obj=
    lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
  lv_img_set_src(cursor_obj,&mouse_cursor_icon); /*Set the image source*/
  lv_indev_set_cursor(mouse_indev,
    cursor_obj); /*Connect the image  object to the driver*/
}
/**
 * A task to measure the elapsed time for LVGL
 * @param data unused
 * @return never return
 */
static int tick_thread(void *data){
  (void)data;
  while(1){
    SDL_Delay(5);
    lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
  }
  return 0;
}