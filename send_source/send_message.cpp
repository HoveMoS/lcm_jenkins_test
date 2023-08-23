// file: send_message.cpp
//
// LCM example program.
//
// compile with:
//  $ g++ -o send_message send_message.cpp -llcm
//
// On a system with pkg-config, you can also use:
//  $ g++ -o send_message send_message.cpp `pkg-config --cflags --libs lcm`

#include <lcm/lcm-cpp.hpp>

#include "exlcm/example_t.hpp"

#include <iostream>

#include <string>

#include <fstream>
#include "rapidjson/document.h"



using namespace std;

int main(int argc, char **argv)
{
    // 读取Json文件
    ifstream ifs("data.json");
    if (!ifs.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
    string json_str((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());

    // 解析Json字符串
    rapidjson::Document doc;
    doc.Parse(json_str.c_str());

    // 获取Json对象
    const rapidjson::Value& obj = doc.GetObject();

    // 输出Json对象中的属性值
    cout << "message_str: " << obj["message_str"].GetString() << endl;
    cout << "message_int64: " << obj["message_int64"].GetInt() << endl;
    cout << "message_int32: " << obj["message_int32"].GetInt() << endl;






    // //方案2
    // string ss;
    // ifstream in("test.txt");
    // if (! in.is_open())
    // { cout << "Error opening file"; exit (1); }
    // while (!in.eof() )
    // {
    //     in.getline (ss,10);
    //     cout << ss << endl;
    // }



    cout<<"hello"<<endl;

    lcm::LCM lcm;
    if (!lcm.good())
        return 1;

    exlcm::example_t my_data;
    my_data.message_int64 = obj["message_int64"].GetInt();

    my_data.message_double1[0] = 1;
    my_data.message_double1[1] = 2;
    my_data.message_double1[2] = 3;

    my_data.message_double2[0] = 1;
    my_data.message_double2[1] = 0;
    my_data.message_double2[2] = 0;
    my_data.message_double2[3] = 0;

    my_data.message_int32 = obj["message_int32"].GetInt();

    //my_data.message_str = "example string";
    //my_data.message_str = ss;
    my_data.message_str = obj["message_str"].GetString();

    //my_data.message_bool = obj["message_bool"].GetBool();  //bug?
    my_data.message_bool = 1;

    lcm.publish("EXAMPLE", &my_data);

    return 0;
}