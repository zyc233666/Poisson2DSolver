#include<iostream>
#include "head.h"
#include<string>     //包含getline()

void main(int argc, char* argv[])
{
    double x; double y; double u;

    // 2，创建一个ExprTK符号表，用来链接符号与参数
    sym_table_t sym_table;
    sym_table.add_variable("x", x);  //将expression_string 中的符号“x”与double变量x链接起来
    sym_table.add_variable("y", y);
    sym_table.add_variable("u", u);
    sym_table.add_constants();

    // 3. 创建一个编译的表达式容器
    expr_t u_int;
    u_int.register_symbol_table(sym_table);  //使用符号表来注册一个表达式

    expr_t FU;
    FU.register_symbol_table(sym_table);  //使用符号表来注册一个表达式

    expr_t DF;
    DF.register_symbol_table(sym_table);  //使用符号表来注册一个表达式


    // 4. 创建一个解析器，用于将string类型的表达式编译到表达式容器
    parser_t parser;

    int lx; int ly; int n_e_x; int n_e_y;
    double left; double right; double up; double down; vector<int> bc_index;
    string u0; string fu; string df; double rel_tol; double abs_tol; string path_det;
    readTxt(argv[1],lx,ly,n_e_x,n_e_y,left,right,up,down,bc_index,u0,fu,df,rel_tol,abs_tol,path_det);//读取命令参数对应文件
    cout << "lx=" << lx << endl;
    cout << "ly=" << ly << endl;
    cout << "Nx=" << n_e_x << endl;
    cout << "Ny=" << n_e_y << endl;

    parser.compile(u0, u_int);
    parser.compile(fu, FU);
    parser.compile(df, DF);

    //vector<string> fun_form{ u0,fu,df };
    //for (int i = 0; i < 3; i++) {
    //    cout << fun_form[i] << "=" << muP<double>(fun_form[i], 2.0) << endl;
    //}

    cout << "rel_tol=" << rel_tol << endl;
    cout << "abs_tol=" << abs_tol << endl;

    path_det.erase(std::remove(path_det.begin(), path_det.end(), ' '), path_det.end());//移除多余空格
    cout << "path=" << path_det << endl;

    const int n_n_x = n_e_x + 1;//number of nodes in x
    const int n_n_y = n_e_y + 1;//number of nodes in y
    vector<double> xv = linspace(0, lx, n_n_x);
    vector<double> yv = linspace(0, ly, n_n_y);

    const int n_n = n_n_x * n_n_y;
    const int nnc = (n_e_y - 1) * n_n_x + (n_e_x - 1) + 1;

    //cout << n_n_x << "  " << xv.size() << endl;
    

    vector< vector<double> > K(n_n, vector<double>(n_n));
    vector<double> F(n_n);
    vector<double> U(n_n);

    
    int u_cnt = 0;
    for (int i = 0; i < n_n_y; i++) {
        for (int j = 0; j < n_n_x; j++) {
            x = xv[j]; y = yv[i];
            U[u_cnt] = u_int.value();
            u_cnt++;
        }
    }

    //左边
    //确定左边的边界的节点index
    vector<int>il;
    for (int i = 0; i < n_n_y; i++) {
        il.push_back(i * n_n_x);
    }

    //右边
    //确定右边边界的节点index
    vector<int>ir;
    for (int i = 0; i < n_n_y; i++) {
        ir.push_back(i * n_n_x + n_e_x);
    }

    //现在把上下也加上
    //下边
    vector<int>idd;
    for (int i = 0; i < n_n_x; i++) {
        idd.push_back(i);
    }

    //上边
    vector<int>iu;
    for (int i = 0; i < n_n_x; i++) {
        iu.push_back(i + n_e_y * n_n_x);
    }

    vector<vector<int>> FBudindex{ iu,il,idd,ir };
    vector<double> Budindex{ up,left,down,right };
    for (int i = 0; i < bc_index.size(); i++) {
        for (int j = 0; j < FBudindex[bc_index[i]].size(); j++) {
            U[FBudindex[bc_index[i]][j]] = Budindex[bc_index[i]];
        }
        //cout << bc_index[i] <<"="<< Budindex[bc_index[i]] << endl;
    }

    vector<vector<int>> mymesh(nnc, vector<int>(4));

    for (int i = 0; i < nnc; i++) {
        int j = i + 1;
        int m = j + n_n_x;
        int n = m - 1;
        mymesh[i] = { i,j,m,n };
    }

    double y0 = yv[0], y1 = yv[1];
    double x0 = xv[0], x1 = xv[1];
    int ngp = 3;
    double gradphi[2];

    cout << "iters" << "         " <<"Abs.Error"<<"          "<<"Rel.Error"<< endl;

    for (int iters = 0; iters < 20; iters++) {
        vector<vector<double>> K(n_n, vector<double>(n_n));
        vector<double> F(n_n);
        for (int e = 0; e < nnc; e++) {
            vector<int> elconn{ mymesh[e] };
            for (int gp = 0; gp < ngp * ngp; gp++) {
                double xi = gpoints(gp, ngp)[0];
                double eta = gpoints(gp, ngp)[1];
                double wi = gpoints(gp, ngp)[2];
                double wj = gpoints(gp, ngp)[3];

                vector<double> shp_val = shp_cal(xi, eta, x0, x1, y0, y1)[0];
                vector<double> shp_gradx = shp_cal(xi, eta, x0, x1, y0, y1)[1];
                vector<double> shp_grady = shp_cal(xi, eta, x0, x1, y0, y1)[2];

                double JxW = wi * wj * (x1 - x0) / 2 * (y1 - y0) / 2;
                double phi{};
                gradphi[0] = 0.0; gradphi[1] = 0.0;
                for (int i = 0; i < 4; i++) {
                    int iInd = elconn[i];
                    phi += shp_val[i] * U[iInd];
                    gradphi[0] += shp_gradx[i] * U[iInd];
                    gradphi[1] += shp_grady[i] * U[iInd];
                }

                u = phi;
                for (int i = 0; i < 4; i++) {
                    int iInd = elconn[i];
                    F[iInd] += (gradphi[0] * shp_gradx[i] + gradphi[1] * shp_grady[i]) * JxW + FU.value() * shp_val[i] * JxW;
                    for (int j = 0; j < 4; j++) {
                        int jInd = elconn[j];
                        K[iInd][jInd] += (-1.0) * (shp_gradx[j] * shp_gradx[i] + shp_grady[j] * shp_grady[i]) * JxW
                            + (-1.0) * DF.value() * shp_val[j] * shp_val[i] * JxW;
                    }
                }
            }
        }

        for (int i = 0; i < bc_index.size(); i++) {
            for (int j = 0; j < FBudindex[bc_index[i]].size(); j++) {
                F[FBudindex[bc_index[i]][j]] = 0.0;
                K[FBudindex[bc_index[i]][j]][FBudindex[bc_index[i]][j]] += 1.0e16;
            }
        }

        Matrix2 KM = converVector2Matrix2(K);
        Vector FM = converVector2Matrix(F);

        Vector dU = classic_gaussian_elimination(KM, FM);

        vector<double>dx(dU.size());

        for (int k = 0; k < U.size(); k++) {
            dx[k] = dU[k];
            U[k] += dU[k];
        }


        for (int i = 0; i < bc_index.size(); i++) {
            for (int j = 0; j < FBudindex[bc_index[i]].size(); j++) {
                U[FBudindex[bc_index[i]][j]] = Budindex[bc_index[i]];
            }
        }

        double rel_err = mynorm(dx) / mynorm(U);
        double abs_err = mynorm(F);

        cout<<iters<<"         "<<scientific << setprecision(9) << abs_err << "       " << rel_err << "      " << endl;
        if (rel_err < rel_tol && abs_err < abs_tol) {
            break;
        }

    }

    //cout << "level" << "         " << "delta.Error" << endl;
    //for (int i_lv = 1; i_lv < 10; i_lv++) {
    //    int level_num = i_lv * 10;
    //    int final_level = level_num * 2 + 1;
    //    vector<double>US = U_standard(yv, xv, n_n, level_num, 5.0, lx, ly);
    //    vector<double> DERR(n_n);
    //    for (int i = 0; i < U.size(); i++) {
    //        DERR[i] = U[i] - US[i];
    //    }
    //    double derr = mynorm(DERR)/mynorm(US);
    //    cout<<final_level << "         " << derr << endl;
    //}

    cout << "this is beginning!" << endl;
    fstream outfile;
    string filename = path_det;
    cout << filename << endl;
    outfile.open(filename, ios::out);
    if (!outfile) {
        cout << "open failed" << endl;
    }
    outfile << "# vtk DataFile Version 2.0" << endl;
    outfile << filename << endl;
    outfile << "ASCII " << endl;
    outfile << "DATASET STRUCTURED_GRID" << endl;
    outfile << "DIMENSIONS " << n_n_x << " " << n_n_y << " " << 1 << endl;
    outfile << "POINTS " << n_n_x * n_n_y * 1 << " float" << endl;
    for (int i = 0; i < n_n_y; i++) {
        for (int j = 0; j < n_n_x; j++) {
            outfile << i << " " << j << " " << 0 << endl;
        }
    }

    outfile << "POINT_DATA " << n_n_x * n_n_y * 1 << endl;
    outfile << "SCALARS CON float 1" << endl;
    outfile << "LOOKUP_TABLE default" << endl;

    srand(time(0));
    int cnt = 0;
    for (int i = 0; i < n_n_y; i++) {
        for (int j = 0; j < n_n_x; j++) {
            outfile << U[cnt] << "\t";
            cnt += 1;
        }
    }

    outfile.close();

    /*vector<double>US = U_standard(yv, xv, n_n, 20, 5.0, lx, ly);

    string filename2 = "D://Poisson2dsolver//standard.vtk";
    cout << filename2 << endl;
    outfile.open(filename2, ios::out);
    if (!outfile) {
        cout << "open failed" << endl;
    }
    outfile << "# vtk DataFile Version 2.0" << endl;
    outfile << filename2 << endl;
    outfile << "ASCII " << endl;
    outfile << "DATASET STRUCTURED_GRID" << endl;
    outfile << "DIMENSIONS " << n_n_x << " " << n_n_y << " " << 1 << endl;
    outfile << "POINTS " << n_n_x * n_n_y * 1 << " float" << endl;
    for (int i = 0; i < n_n_y; i++) {
        for (int j = 0; j < n_n_x; j++) {
            outfile << i << " " << j << " " << 0 << endl;
        }
    }

    outfile << "POINT_DATA " << n_n_x * n_n_y * 1 << endl;
    outfile << "SCALARS CON float 1" << endl;
    outfile << "LOOKUP_TABLE default" << endl;

    srand(time(0));
    int cnt2 = 0;
    for (int i = 0; i < n_n_y; i++) {
        for (int j = 0; j < n_n_x; j++) {
            outfile << US[cnt2] << "\t";
            cnt2 += 1;
        }
    }

    outfile.close();*/

    system("pause");
}
