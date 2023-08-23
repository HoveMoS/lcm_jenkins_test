// file: listener.cpp
//
// LCM example program.
//
// compile with:
//  $ gcc -o listener listener.cpp -llcm
//
// On a system with pkg-config, you can also use:
//  $ gcc -o listener listener.cpp `pkg-config --cflags --libs lcm`

#include <stdio.h>

#include <lcm/lcm-cpp.hpp>

#include "exlcm/example_t.hpp"


#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Multiline_Output.H>
//#include <typeinfo>
//#include <numeric>
#include <stdlib.h>

#include <string>

template <class T> void printType(const T&)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}




class Handler {
  public:
    ~Handler() {}
    void handleMessage(const lcm::ReceiveBuffer *rbuf, const std::string &chan,
                       const exlcm::example_t *msg)
    {   
        // // itoa()函数有3个参数：源字符串、目标字符串、进制
        // int num=78;
        // char str1[7];
        // std::itoa(num, str1, 10); // 按10进制转换 
        // std::cout << str1 << std::endl; 




        // 整数转字符串
        int num = 78;
        char temp[7], str[7];
        int i = 0, j = 0;

        while(num) {
            // 整数转字符串: +'0' 
            temp[i++] = num % 10 + '0';
            num = num / 10;
        } 

        // 刚刚转化的字符串是逆序的
        while(i >= 0) {
            str[j++] = temp[--i];
        } 
        std::cout << str << std::endl;
        //const char *ba=str;

        std::string s1("hello 11111");
        s1.append(msg->message_str);
        s1.append("\n");
        s1.append("hello 22222");


        //const char *ba=s1;   //bug
        const char *ba = s1.c_str();



        // // 整数转字符串
        // int num = 78;
        // char str[7];
        // itoa(num,str,10);
        // std::cout<<str<<std::endl;
        // const char *ba=str;







        //int i;

        printf("Received message on channel \"%s\":\n", chan.c_str());
        printf("  message_int64   = %lld\n", (long long) msg->message_int64);

        

        printf("  message_double1    = (%f, %f, %f)\n", msg->message_double1[0], msg->message_double1[1],
               msg->message_double1[2]);
        printf("  message_double2 = (%f, %f, %f, %f)\n", msg->message_double2[0], msg->message_double2[1],
               msg->message_double2[2], msg->message_double2[3]);
        
        printf(" message_int32 = %d", msg->message_int32);
        
        printf("\n");
        printf("  message_str        = '%s'\n", msg->message_str.c_str());
        printf("  message_bool     = %d\n", msg->message_bool);


        auto aa=msg->message_int64;
        auto ab=msg->message_str.c_str();
        auto ac=msg->message_double1[0];
        auto ad=msg->message_int32;
        auto ae=msg->message_bool;


        // std::cout << decltype(aa) << std::endl;
        // std::cout << decltype(ab) << std::endl;
        printType(aa);
        printType(ab);
        printType(ac);
        printType(ad);
        printType(ae);
        printType(str);
        printType(ba);
        // void printType(const T&) [with T = long int]
        // void printType(const T&) [with T = const char*]
        // void printType(const T&) [with T = double]
        // void printType(const T&) [with T = int]
        // void printType(const T&) [with T = signed char]




        // int gui_int64=msg->message_int64;

        // // 整数转字符串
        // //int num = 6;
        // char string_gui_int64[7];

        // // itoa()函数有3个参数：源字符串、目标字符串、进制 
        // std::itoa(gui_int64, string_gui_int64, 10); // 按10进制转换 
        // std::cout << string_gui_int64 << std::endl; 


        // this->gui_main(string_gui_int64);




        // char a;
        // a='h';
        // this->gui_main(&a);
        // gui_main(const char* i_a){
        //     mulo->value(i_a);
        // }


        
        // char aa[]="Hello 1123djoiaj";
        // const char *p = aa;
        // this->gui_main(p);


        //char aa[]=msg->message_str.c_str();
        //std::string aa=msg->message_str.c_str();

        const char *p = msg->message_str.c_str();
        this->gui_main(p,ba);



    }


    int gui_main(const char* i_a,const char* i_aa){
        Fl_Window *window;
        Fl_Box *box;
        Fl_Multiline_Output *mulo;
        
        window = new Fl_Window(500, 280);
        window->label("HelloWorld!");
        
        box = new Fl_Box(20, 40, 260, 50, "Hello World!");
        box->box(FL_UP_BOX);
        box->labelsize(36);
        box->labelfont(FL_BOLD + FL_ITALIC);
        (FL_SHADOW_LABEL);
        
        mulo = new Fl_Multiline_Output(100,100,160,70,"lcm message");
        //mulo->value(i_a);
        mulo->value(i_aa);

        
        window->end();
        window->show();
        return Fl::run();

        //Fl::run();    
    }


    //     int gui_main(int argc, char **argv){
    //     Fl_Window *window;
    //     Fl_Box *box;
    //     Fl_Multiline_Output *mulo;
        
    //     window = new Fl_Window(500, 280);
    //     window->label("HelloWorld!");
        
    //     box = new Fl_Box(20, 40, 260, 50, "Hello World!");
    //     box->box(FL_UP_BOX);
    //     box->labelsize(36);
    //     box->labelfont(FL_BOLD + FL_ITALIC);
    //     (FL_SHADOW_LABEL);
        
    //     mulo = new Fl_Multiline_Output(100,100,160,70,"lcm message");
    //     mulo->value("cesdlaksdkjalsk");

        
    //     window->end();
    //     window->show(argc, argv);
    //     return Fl::run();

    //     //Fl::run();    
    // }

};

int main(int argc, char **argv)  //, int argc, char *argv[]
{
    

    lcm::LCM lcm;

    if (!lcm.good())
        return 1;

    Handler handlerObject;
    lcm.subscribe("EXAMPLE", &Handler::handleMessage, &handlerObject);

    while (0 == lcm.handle()) {
        // Do nothing

    }

    return 0;
}
