#include<iostream>
#include "head.h"

void readTxt(char* file, int& lx, int& ly, int& Nx, int& Ny,
    double& left,double& right,double& up,double& down, vector<int>& bc_index,
    string& u0, string& fu, string& df, double& rel_tol, double& abs_tol,string& path_det) {
    string s;
    string tmp;
    string result;
    ifstream inf;//文件读操作

    //这里路劲是：//  双斜杠
    //inf.open("d://DEV_C++//LogFile//快走300//原始log//202308211452_mayanjun_upstair100_6.txt");         
    //inf.open("d://DEV_C++//LogFile//串口log//MobaXterm_warth_9_301_20230919_161009.txt");   
    inf.open(file);
    assert(inf.is_open());   //若失败,则输出错误消息,并终止程序运行 


    cout << "starting:" << endl;
    int val = 0;
    bool exists = 1;
    int mei = 0;
    string mesh[] = { "lx","ly","Nx","Ny" };
    string mesh_ele;
    string me0;
    int ele_i = 0;
    int mesh_tmp;

    string bound[] = { "up","left","down","right" };
    //double left; double right; double up; double down;
    

    string fun[] = { "u0","fu","df" };
    //double fun_val;

    string ERR[] = { "rel_tol","abs_tol" };
    //double rel_tol; double abs_tol;

    string PATH = { "path" };
    //string path_det;

    int size_mesh = sizeof(mesh) / sizeof(mesh[0]);
    while (getline(inf, s))      //getline(inf,s)是逐行读取inf中的文件信息
    {
        if (s.empty()) {
            continue;
        }
        int idx = s.find("#");  //从每行的哪个位置开始截取
        //cout << idx << endl;
        //int num=s.find(";");
        int num = s.find(" ");   //从每行的开始位置截取到每行的哪个位置结束 ------  这里表示数据的最后没有符号  如果是 ；符号，用上面注释的那条代码
        if (idx != -1) {
            for (int i = 0; i < s.size(); i++)
            {
                int tmp = (int)s[i];
                if (tmp >= 48 && tmp <= 57)
                {
                    val = int(tmp - '0');
                    break;
                }
            }


            //bool exists = s.find("1") == string::npos;
            //if (!exists) {
            //    int val = int(s[s.find("1")]-'0');
            //    cout << val<<" "<< s[s.find("1")] << endl;
            //}
            //bool exists = s.find("函数") == string::npos;
            //cout << s << '\t' << !exists << endl;
        }

        if (idx == -1) {
            switch (val) {
            case 1:
                for (int i = 0; i < size_mesh; i++) {
                    mei += 1;
                    exists = s.find(mesh[i]) == string::npos;
                    if (!exists) {
                        ele_i = 0;
                        for (int j = 0; j < s.size(); j++) {
                            mesh_tmp = (int)s[j];
                            if (mesh_tmp >= 48 && mesh_tmp <= 57)
                            {
                                me0 = s[j];
                                mesh_ele.insert(ele_i, me0);
                                ele_i += 1;
                            }
                        }
                        break;
                    }
                }
                switch (mei) {
                case 1:

                    lx = stoi(mesh_ele, 0, 10);
                    //cout << "lx=" << lx << endl;
                    break;
                case 2:

                    ly = stoi(mesh_ele, 0, 10);
                    //cout << "ly=" << ly << endl;
                    break;
                case 3:

                    Nx = stoi(mesh_ele, 0, 10);
                    //cout << "Nx=" << Nx << endl;
                    break;
                case 4:

                    Ny = stoi(mesh_ele, 0, 10);
                    //cout << "Ny=" << Ny << endl;
                    break;
                default:
                    cout << "Invalid parameter" << endl;
                }
                break;
            case 2:
                for (int i = 0; i < 4; i++) {
                    mei += 1;
                    exists = s.find(bound[i]) == string::npos;
                    if (!exists) {
                        bc_index.push_back(mei-1);
                        ele_i = 0;
                        idx = s.find("=");
                        for (int i = idx + 1; i < s.size(); i++) {
                            me0 = s[i];
                            mesh_ele.insert(ele_i, me0);
                            ele_i++;
                        }
                        //for (int j = 0; j < s.size(); j++) {
                        //    mesh_tmp = (int)s[j];
                        //    if (mesh_tmp >= 48 && mesh_tmp <= 57)
                        //    {
                        //        me0 = s[j];
                        //        mesh_ele.insert(ele_i, me0);
                        //        ele_i += 1;
                        //    }
                        //}
                        break;
                    }
                }
                switch (mei) {
                case 1:
                    up = stod(mesh_ele);
                    break;
                case 2:
                    left = stod(mesh_ele);
                    
                    break;
                case 3:
                    down = stod(mesh_ele);
                    
                    break;
                case 4:
                    right = stod(mesh_ele);
                    
                    break;
                default:
                    cout << "Invalid parameter" << endl;
                }
                break;
            case 3:
                for (int i = 0; i < 3; i++) {
                    mei += 1;
                    exists = s.find(fun[i]) == string::npos;
                    if (!exists) {
                        ele_i = 0;
                        idx = s.find("=");
                        for (int i = idx + 1; i < s.size(); i++) {
                            me0 = s[i];
                            mesh_ele.insert(ele_i, me0);
                            ele_i++;
                        }
                        //idx = s.find("'");
                        //while (idx != -1 && me0 != "'") {
                        //    idx++;
                        //    me0 = s[idx];
                        //    mesh_ele.insert(ele_i, me0);
                        //    ele_i++;
                        //    me0 = s[idx + 1];
                        //    if (ele_i > 50) {
                        //        break;
                        //    }
                        //}
                        break;
                    }
                }
                switch (mei) {
                case 1:
                    u0 = mesh_ele;
                    //fun_val = muP<double>(u0, 2.0);
                    //cout << "u0=" << mesh_ele << "=" << fun_val << endl;
                    break;
                case 2:
                    fu = mesh_ele;
                    //fun_val = muP<double>(fu, 2.0);
                    //cout << "fu=" << mesh_ele << "=" << fun_val << endl;
                    break;
                case 3:
                    df = mesh_ele;
                    //fun_val = muP<double>(df, 2.0);
                    //cout << "df=" << mesh_ele << "=" << fun_val << endl;
                    break;
                default:
                    cout << "Invalid parameter" << endl;
                }
                break;
            case 4:
                for (int i = 0; i < 2; i++) {
                    mei += 1;
                    exists = s.find(ERR[i]) == string::npos;
                    if (!exists) {
                        ele_i = 0;
                        idx = s.find("=");
                        for (int i = idx + 1; i < s.size(); i++) {
                            me0 = s[i];
                            mesh_ele.insert(ele_i, me0);
                            ele_i++;
                        }
                        break;
                    }
                }
                switch (mei) {
                case 1:
                    rel_tol = stod(mesh_ele);
                    //cout << "rel_tol=" << rel_tol << endl;
                    break;
                case 2:
                    abs_tol = stod(mesh_ele);
                    //cout << "abs_tol=" << abs_tol << endl;
                    break;
                default:
                    cout << "Invalid parameter" << endl;
                }
                break;
            case 5:
                exists = s.find(PATH) == string::npos;
                if (!exists) {
                    ele_i = 0;
                    idx = s.find("=");
                    for (int i = idx + 1; i < s.size(); i++) {
                        me0 = s[i];
                        mesh_ele.insert(ele_i, me0);
                        ele_i++;
                    }
                }
                path_det = mesh_ele;
                break;
            default:
                cout << "Invalid parameter" << endl;
            }

            mei = 0;
            me0.clear();
            mesh_ele.clear();
        }
        // cout << idx <<" "<< num << endl;

    }
    //for (int i = 0; i < bc_index.size(); i++) {
    //    cout << bc_index[i] << endl;
    //}
    inf.close();
}