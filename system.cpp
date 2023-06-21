#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<ctime>
#include<iomanip>
using namespace std;

string gettime()
{
    time_t t=time(NULL);
        tm *now=localtime(&t);
        int year=1900+now->tm_year;
        int mon=1+now->tm_mon;
        int day=now->tm_mday;
        int hour=now->tm_hour;
        int min=now->tm_min;
        int sec=now->tm_sec;
        string to_year=to_string( year );
        string to_month=to_string( mon );
        string to_day=to_string( day );
        string to_hour=to_string( hour );
        string to_min=to_string( min );
        string to_sec=to_string( sec );
        return to_year+"-"+to_month+"-"+to_day+" "+to_hour+":"+to_min+":"+to_sec;
}

class user
{
private:
    string username;
    string password;
public:
    void putusername(){cin>>username;}
    void putpassword(){cin>>password;}
    string getusername(){return username;}
    string getpassword(){return password;}
};

class goods
{
private:
    string no;
    string name;
    string count;
    string price;
    int num;
public:
    void putno(){cin>>no;}
    void putname(){cin>>name;}
    void putcount(){cin>>count;}
    void putprice(){cin>>price;}
    void putnum(){cin>>num;}
    void putnum(int input){num=input;}
    void putno(string input){no=input;}
    void putname(string input){name=input;}
    void putcount(string input){count=input;}
    void putprice(string input){price=input;}
    string getno(){return no;}
    string getname(){return name;}
    string getcount(){return count;}
    string getprice(){return price;}
    int getnum(){return num;}
};

class operations
{
private:
    string no;
    string kinds;
    int num;
    string acount;
    string date;
    int flag;
public:
    void putno(string input){no=input;}
    void putkinds(string input){kinds=input;}
    void putnum(int input){num=input;}
    void putacount(string input){acount=input;}
    void putdate(){date=gettime();}
    string getno(){return no;}
    string getkinds(){return kinds;}
    int getnum(){return num;}
    string getacount(){return acount;}
    string getdate(){return date;}
    int putflag(int input){flag=input;}
    int getflag(){return flag;}
};

void initialize()
{
    cout<<"********************************************"<<endl;
    cout<<"*           欢迎您使用进销存系统           *"<<endl;
    cout<<"*                                          *"<<endl;
    cout<<"*                1.用户登录                *"<<endl;
    cout<<"*                2.用户注册                *"<<endl;
    cout<<"*                0.退出系统                *"<<endl;
    cout<<"*                                          *"<<endl;
    cout<<"********************************************"<<endl;
    cout<<"请输入您需要执行的功能编号:";
}

void systeminitialize(string username)
{
    cout<<"******************************************"<<endl;
    cout<<"*                 功能菜单               *"<<endl;
    cout<<"*                                        *"<<endl;
    cout<<"*             1.新增商品种类             *"<<endl;
    cout<<"*             2.删除商品种类             *"<<endl;
    cout<<"*             3.商品进货                 *"<<endl;
    cout<<"*             4.商品销售                 *"<<endl;
    cout<<"*             5.浏览商品信息             *"<<endl;
    cout<<"*             6.显示操作记录             *"<<endl;
    cout<<"*             7.盘点                     *"<<endl;
    cout<<"*             0.退出登录                 *"<<endl;
    cout<<"*                                        *"<<endl;
    cout<<"******************************************"<<endl;
    cout<<"亲爱的用户"<<username<<",欢迎进入进销存管理平台"<<endl;
    cout<<"请输入您需要执行的功能编号:";
}

string CharToStr(char * contentChar)
{
	string tempStr;
	for (int i=0;contentChar[i]!='\0';i++)
	{
		tempStr+=contentChar[i];
	}
	return tempStr;
}

void DelLineData(char* fileName, int lineNum)
{
	ifstream in;
	in.open(fileName);
	
	string strFileData = "";
	int line = 0;
	char lineData[1024] = {0};
	while(in.getline(lineData, sizeof(lineData)))
	{
        line++;
		if (line == lineNum)
			continue;
		else
		{
			strFileData += CharToStr(lineData);
			strFileData += "\n";
		}
	}
	in.close();
 
	//写入文件
	ofstream out;
	out.open(fileName);
	out.flush();
	out<<strFileData;
	out.close();
}

void login(string username)
{
    while(true)
    {
        fstream goodsinformation;
        goodsinformation.open("goodsinformation.txt",ios::in|ios::app);
        fstream operationinformation;
        operationinformation.open("operationinformation.txt",ios::in|ios::app);
        systeminitialize(username);//初始化界面
        //进销存系统内部操作
        string op2;
        cin>>op2;
        if(op2=="1")
        {
            goods good1;
            cout<<"请输入商品编号:";
            good1.putno();
            //检测输入商品的编号，若编号与之前的一致，则需要重新输入
            int flag1=0;
            while(true)
            {
                string no;
                goodsinformation>>no;
                string empty1;
                getline(goodsinformation,empty1);
                if(goodsinformation.eof())//判断是否读取到文件末尾
                    break;
                if(good1.getno()==no)
                {
                    cout<<"您输入的商品种类已经存在,本次录入操作失败,请重新输入"<<endl;
                    Sleep(1000);
                    flag1=1;
                    break;
                }
            }
            goodsinformation.close();
            goodsinformation.open("goodsinformation.txt",ios::in|ios::app);
            if(flag1==0)
            {
                
                cout<<"请输入商品名称:";
                good1.putname();
                cout<<"请输入商品单位:";
                good1.putcount();
                cout<<"请输入商品价格:";
                good1.putprice();
                cout<<"请输入商品库存数量:";
                good1.putnum();
                cout<<"添加商品种类成功"<<endl;
                goodsinformation<<setw(10)<<good1.getno()<<setw(10)<<good1.getname()<<setw(10)<<good1.getcount()<<setw(10)<<good1.getprice()<<setw(10)<<good1.getnum()<<endl;
                //保留操作记录
                operations operate1;
                operate1.putno(good1.getno());
                operate1.putkinds("新增商品种类");
                operate1.putnum(good1.getnum());
                operate1.putacount(username);
                operate1.putdate();
                operate1.putflag(0);
                operationinformation<<operate1.getflag()<<endl;
                operationinformation<<setw(15)<<operate1.getno()<<setw(15)<<operate1.getkinds()<<setw(15)<<operate1.getnum()<<setw(15)<<operate1.getacount()<<setw(25)<<operate1.getdate()<<endl;
                operationinformation.close();
                operationinformation.open("operationinformation.txt",ios::in|ios::app);
                system("pause");
            }
        }
        else if(op2=="2")
        {  
            cout<<"请输入您需要删除的商品编号:";
            string no1;
            cin>>no1;
            int flag2=0;
            int line=1;
            while(true)
            {
                string no2;
                goodsinformation>>no2;
                string name2;
                goodsinformation>>name2;
                string count2;
                goodsinformation>>count2;
                string price2;
                goodsinformation>>price2;
                int num2;
                goodsinformation>>num2;
                if(goodsinformation.eof())//判断是否读取到文件末尾
                    break;
                if(no2==no1)
                {
                    //删除商品信息
                    DelLineData("goodsinformation.txt", line);
                    cout<<"删除商品种类成功"<<endl;
                    flag2=1;
                    //保留操作记录
                    operations operate1;
                    operate1.putno(no2);
                    operate1.putkinds("删除商品种类");
                    operate1.putnum(num2);
                    operate1.putacount(username);
                    operate1.putdate();
                    operate1.putflag(0);
                    operationinformation<<operate1.getflag()<<endl;
                    operationinformation<<setw(15)<<operate1.getno()<<setw(15)<<operate1.getkinds()<<setw(15)<<operate1.getnum()<<setw(15)<<operate1.getacount()<<setw(25)<<operate1.getdate()<<endl;
                    operationinformation.close();
                    operationinformation.open("operationinformation.txt",ios::in|ios::app);
                    break;
                }
                line++;
            }
            goodsinformation.close();
            goodsinformation.open("goodsinformation.txt",ios::in|ios::app);
            if(flag2==0)
                cout<<"系统中没有编号为"<<no1<<"的商品信息,删除商品失败,请检查后再试"<<endl;
            system("pause");
        }
        else if(op2=="3")
        {
            cout<<"请输入需要进货的商品编号:";
            goods good2;
            string no1;
            cin>>no1;
            int flag2=0;
            int line=0;
            while(true)
            {
                line++;
                string no2;
                goodsinformation>>no2;
                string name2;
                goodsinformation>>name2;
                string count2;
                goodsinformation>>count2;
                string price2;
                goodsinformation>>price2;
                int num2;
                goodsinformation>>num2;
                if(goodsinformation.eof())//判断是否读取到文件末尾
                    break;
                if(no2==no1)
                {
                    flag2=1;
                    //显示该商品在系统中的信息
                    cout<<"编号"<<setw(10)<<"名称"<<setw(10)<<"单位"<<setw(10)<<"价格"<<setw(10)<<"库存量"<<endl;
                    cout<<no2<<setw(10)<<name2<<setw(10)<<count2<<setw(10)<<price2<<" "<<setw(10)<<num2<<endl;
                    //进货
                    cout<<"请输入进货量：";
                    int num1;
                    cin>>num1;
                    //判断非负
                    if(num1<0)
                    {
                        cout<<"进货量不能小于零,输入有误,请重新输入"<<endl;
                        break;
                    }
                    good2.putnum(num1+num2);
                    good2.putno(no2);
                    good2.putname(name2);
                    good2.putcount(count2);
                    good2.putprice(price2);
                    DelLineData("goodsinformation.txt", line);
                    goodsinformation<<setw(10)<<good2.getno()<<setw(10)<<good2.getname()<<setw(10)<<good2.getcount()<<setw(10)<<good2.getprice()<<setw(10)<<good2.getnum()<<endl;
                    cout<<"进货成功"<<endl;
                    //保留操作记录
                    operations operate1;
                    operate1.putno(no2);
                    operate1.putkinds("商品进货");
                    operate1.putnum(num2);
                    operate1.putacount(username);
                    operate1.putdate();
                    operate1.putflag(0);
                    operationinformation<<operate1.getflag()<<endl;
                    operationinformation<<setw(15)<<operate1.getno()<<setw(15)<<operate1.getkinds()<<setw(15)<<operate1.getnum()<<setw(15)<<operate1.getacount()<<setw(25)<<operate1.getdate()<<endl;
                    operationinformation.close();
                    operationinformation.open("operationinformation.txt",ios::in|ios::app);
                    break;
                }
            }
            goodsinformation.close();
            goodsinformation.open("goodsinformation.txt",ios::in|ios::app);
            if(flag2==0)
                cout<<"系统中没有编号为"<<no1<<"的商品信息,商品进货失败,请检查后再试"<<endl;
            system("pause");
        }
        else if(op2=="4")
        {
            cout<<"请输入需要售出的商品编号:";
            goods good2;
            string no1;
            cin>>no1;
            int flag2=0;
            int line=0;
            while(true)
            {
                line++;
                string no2;
                goodsinformation>>no2;
                string name2;
                goodsinformation>>name2;
                string count2;
                goodsinformation>>count2;
                string price2;
                goodsinformation>>price2;
                int num2;
                goodsinformation>>num2;
                if(goodsinformation.eof())//判断是否读取到文件末尾
                    break;
                if(no2==no1)
                {
                    flag2=1;
                    //显示该商品在系统中的信息
                    cout<<"编号"<<setw(10)<<"名称"<<setw(10)<<"单位"<<setw(10)<<"价格"<<setw(10)<<"库存量"<<endl;
                    cout<<no2<<setw(10)<<name2<<setw(10)<<count2<<setw(10)<<price2<<" "<<setw(10)<<num2<<endl;
                    //进货
                    cout<<"请输入销售量：";
                    int num1;
                    cin>>num1;
                    if(num1<0)
                    {
                        cout<<"销售量不能小于零,输入有误,请重新输入"<<endl;
                        break;
                    }
                    int out=num2-num1;
                    if(out<0)
                    {
                        cout<<"库存量不足,无法销售,请核对后重新输入"<<endl;
                        break;
                    }
                    good2.putnum(out);
                    good2.putno(no2);
                    good2.putname(name2);
                    good2.putcount(count2);
                    good2.putprice(price2);
                    DelLineData("goodsinformation.txt", line);
                    goodsinformation<<setw(10)<<good2.getno()<<setw(10)<<good2.getname()<<setw(10)<<good2.getcount()<<setw(10)<<good2.getprice()<<setw(10)<<good2.getnum()<<endl;
                    cout<<"商品销售成功"<<endl;
                    //保留操作记录
                    operations operate1;
                    operate1.putno(no2);
                    operate1.putkinds("商品销售");
                    operate1.putnum(num2);
                    operate1.putacount(username);
                    operate1.putdate();
                    operate1.putflag(0);
                    operationinformation<<operate1.getflag()<<endl;
                    operationinformation<<setw(15)<<operate1.getno()<<setw(15)<<operate1.getkinds()<<setw(15)<<operate1.getnum()<<setw(15)<<operate1.getacount()<<setw(25)<<operate1.getdate()<<endl;
                    operationinformation.close();
                    operationinformation.open("operationinformation.txt",ios::in|ios::app);
                    break;
                }
            }
            goodsinformation.close();
            goodsinformation.open("goodsinformation.txt",ios::in|ios::app);
            if(flag2==0)
                cout<<"系统中没有编号为"<<no1<<"的商品信息,商品销售失败,请检查后再试"<<endl;
            system("pause");
        }
        else if(op2=="5")
        {
            cout<<setw(10)<<"编号"<<setw(10)<<"名称"<<setw(10)<<"单位"<<setw(10)<<"价格"<<setw(10)<<"库存量"<<endl;
            while(!goodsinformation.eof())
            {
                string informate;
                getline(goodsinformation,informate);
                if(goodsinformation.fail())
                    break;
                cout<<informate<<endl;
            }
            goodsinformation.close();
            goodsinformation.open("goodsinformation.txt",ios::in|ios::app);
            system("pause");
        }
        else if(op2=="6")
        {
            int optime=1;
            cout<<setw(15)<<"编号"<<setw(15)<<"商品编号"<<setw(15)<<"所作操作"<<setw(15)<<"数量"<<setw(15)<<"操作人账户"<<setw(25)<<"操作时间"<<endl;
            while(!operationinformation.eof())
            {
                int flag;
                operationinformation>>flag;
                string empty;
                getline(operationinformation,empty);
                if (flag==0)
                {
                    string informate;
                    getline(operationinformation,informate);
                    if(operationinformation.fail())
                        break;
                    cout<<setw(15)<<optime<<informate<<endl;
                    optime++;
                }
                else if (flag==1)
                {
                    string informate;
                    getline(operationinformation,informate);
                    if(operationinformation.fail())
                        break;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                    cout<<setw(15)<<optime<<informate<<endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);
                    optime++;
                }
            }
            operationinformation.close();
            operationinformation.open("operationinformation.txt",ios::in|ios::app);
            system("pause");
        }
        else if(op2=="7")
        {
            cout<<setw(10)<<"编号"<<setw(10)<<"名称"<<setw(10)<<"单位"<<setw(10)<<"价格"<<setw(10)<<"库存量"<<endl;
            while(!goodsinformation.eof())
            {
                string informate;
                getline(goodsinformation,informate);
                if(goodsinformation.fail())
                    break;
                cout<<informate<<endl;
            }
            goodsinformation.close();
            goodsinformation.open("goodsinformation.txt",ios::in|ios::app);
            cout<<"---------------------------------------------"<<endl;
            int flagx=0;
            while(flagx==0)
            {
                cout<<"是否需要平库?(是请按1,否请按0)";
                int op3;
                cin>>op3;
                if(op3==1)
                {
                    int flagy=0;
                    while(flagy==0)
                    {
                        //设置红色字体
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                        cout << "您需要出库还是入库?(出库请按1,入库请按0):" ;
                        int op4;
                        cin>>op4;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_BLUE);//把颜色换回来
                        if(op4==0)
                        {
                            flagy=1;
                            cout<<"请输入需要入库的商品编号:";
                            goods good2;
                            string no1;
                            cin>>no1;
                            int flag2=0;
                            int line=0;
                            while(true)
                            {
                                line++;
                                string no2;
                                goodsinformation>>no2;
                                string name2;
                                goodsinformation>>name2;
                                string count2;
                                goodsinformation>>count2;
                                string price2;
                                goodsinformation>>price2;
                                int num2;
                                goodsinformation>>num2;
                                if(goodsinformation.eof())//判断是否读取到文件末尾
                                    break;
                                if(no2==no1)
                                {
                                    flag2=1;
                                    //入库
                                    cout<<"请输入入库量：";
                                    int num1;
                                    cin>>num1;
                                    //判断非负
                                    if(num1<0)
                                    {
                                        cout<<"入库量不能小于零,输入有误,请重新输入入库量:";
                                        break;
                                    }
                                    good2.putnum(num1+num2);
                                    good2.putno(no2);
                                    good2.putname(name2);
                                    good2.putcount(count2);
                                    good2.putprice(price2);
                                    DelLineData("goodsinformation.txt", line);
                                    goodsinformation<<setw(10)<<good2.getno()<<setw(10)<<good2.getname()<<setw(10)<<good2.getcount()<<setw(10)<<good2.getprice()<<setw(10)<<good2.getnum()<<endl;
                                    cout<<"商品盘点成功"<<endl;
                                    //保留操作记录
                                    operations operate1;
                                    operate1.putno(no2);
                                    operate1.putkinds("盘点入库");
                                    operate1.putnum(num2);
                                    operate1.putacount(username);
                                    operate1.putdate();
                                    operate1.putflag(1);
                                    operationinformation<<operate1.getflag()<<endl;
                                    operationinformation<<setw(15)<<operate1.getno()<<setw(15)<<operate1.getkinds()<<setw(15)<<operate1.getnum()<<setw(15)<<operate1.getacount()<<setw(25)<<operate1.getdate()<<endl;
                                    operationinformation.close();
                                    operationinformation.open("operationinformation.txt",ios::in|ios::app);
                                    break;
                                }
                            }
                            goodsinformation.close();
                            goodsinformation.open("goodsinformation.txt",ios::in|ios::app);
                            if(flag2==0)
                                cout<<"系统中没有编号为"<<no1<<"的商品信息,商品盘点失败,请检查后再试"<<endl;
                        }
                        else if(op4==1)
                        {
                            flagy=1;
                            cout<<"请输入需要出库的商品编号:";
                            goods good2;
                            string no1;
                            cin>>no1;
                            int flag2=0;
                            int line=0;
                            while(true)
                            {
                                line++;
                                string no2;
                                goodsinformation>>no2;
                                string name2;
                                goodsinformation>>name2;
                                string count2;
                                goodsinformation>>count2;
                                string price2;
                                goodsinformation>>price2;
                                int num2;
                                goodsinformation>>num2;
                                if(goodsinformation.eof())//判断是否读取到文件末尾
                                    break;
                                if(no2==no1)
                                {
                                    flag2=1;
                                    //出库
                                    cout<<"请输入出库量：";
                                    int num1;
                                    cin>>num1;
                                    if(num1<0)
                                    {
                                        cout<<"出库量不能小于零,输入有误,请重新输入出库量:";
                                        break;
                                    }
                                    int out=num2-num1;
                                    if(out<0)
                                    {
                                        cout<<"库存量不足,无法完成出库操作,请核对后重新输入出库量:";
                                        break;
                                    }
                                    good2.putnum(out);
                                    good2.putno(no2);
                                    good2.putname(name2);
                                    good2.putcount(count2);
                                    good2.putprice(price2);
                                    DelLineData("goodsinformation.txt", line);
                                    goodsinformation<<setw(10)<<good2.getno()<<setw(10)<<good2.getname()<<setw(10)<<good2.getcount()<<setw(10)<<good2.getprice()<<setw(10)<<good2.getnum()<<endl;
                                    cout<<"商品盘点成功"<<endl;
                                    //保留操作记录
                                    operations operate1;
                                    operate1.putno(no2);
                                    operate1.putkinds("盘点出库");
                                    operate1.putnum(num2);
                                    operate1.putacount(username);
                                    operate1.putdate();
                                    operate1.putflag(1);
                                    operationinformation<<operate1.getflag()<<endl;
                                    operationinformation<<setw(15)<<operate1.getno()<<setw(15)<<operate1.getkinds()<<setw(15)<<operate1.getnum()<<setw(15)<<operate1.getacount()<<setw(25)<<operate1.getdate()<<endl;
                                    operationinformation.close();
                                    operationinformation.open("operationinformation.txt",ios::in|ios::app);
                                    break;
                                }
                            }
                            goodsinformation.close();
                            goodsinformation.open("goodsinformation.txt",ios::in|ios::app);
                            if(flag2==0)
                                cout<<"系统中没有编号为"<<no1<<"的商品信息,商品进货失败,请检查后再试"<<endl;
                        }
                        else
                            cout<<"输入有误,请重新输入"<<endl;
                    }
                    flagx=1;
                }
                else if(op3==0)
                    flagx=1;
                else
                    cout<<"输入有误,请重新输入"<<endl;
            }
            goodsinformation.close();
            goodsinformation.open("goodsinformation.txt",ios::in|ios::app);
            system("pause");
        }
        else if(op2=="0")
        {
            cout<<"正在为您登出中……";
            Sleep(1000);
            return;         
        }
        else
        {
            cout<<"您输入了无效的操作代码,请重新输入";
            Sleep(1000);
        }
        goodsinformation.close();
        operationinformation.close();
        system("cls");
    }
}

int main()
{
    while(true)
    {
        fstream userinformation;
        userinformation.open("userinformation.txt",ios::in|ios::app);
        initialize();//初始化界面
        //账号注册与登录模块
        string op1;
        cin>>op1;
        if(op1=="1")
        {
            //用户登录，先让用户输入账号和密码   
            user user1;
            int flagin=0;
            cout<<"请输入您的用户名:";
            user1.putusername();
            cout<<"请输入您的用户密码:";
            user1.putpassword();
            //将用户录入的与文件中保存的账号密码进行比对
            string use=user1.getusername()+" "+user1.getpassword();
            while(true)
            {
                string inform;
                getline(userinformation,inform);
                if(inform=="")
                    break;
                if(use==inform)
                {
                    cout<<"亲爱的用户"<<user1.getusername()<<",欢迎您登录本系统"<<endl;
                    Sleep(1000);
                    system("cls");
                    login(user1.getusername());//进入进销存系统
                    flagin=1;
                    break;
                }
            }
            if(flagin==0)
            {
                cout<<"您输入的账号或密码错误,请检查后重新输入";
                Sleep(1000);
            }
        }
        else if(op1=="2")
        {
            //用户注册，输入用户名与密码
            user user1;
            cout<<"请输入您的用户名(仅可使用数字与字母):";
            user1.putusername();
            //判断用户名是否已经存在
            int flag=0;
            while(true)
            {
                string name;
                userinformation>>name;
                string empty;
                getline(userinformation,empty);
                if(name=="")
                    break;
                if(user1.getusername()==name)
                {
                    cout<<"您输入的用户名已经存在,注册失败,请重新输入"<<endl;
                    Sleep(1000);
                    flag=1;
                    break;
                }
            }
            userinformation.close();
            userinformation.open("userinformation.txt",ios::in|ios::app);
            if(flag==0)
            {
                cout<<"请输入您的用户密码(仅可使用数字或字母,不小于6位):";
                user1.putpassword();
                //判断用户输入的密码是否符合要求，若符合要求则录入文件
                string pass=user1.getpassword();
                if(pass.length()<6)
                {
                    cout<<"您输入的密码小于6位,请重新输入"<<endl;
                    Sleep(1000);
                }
                else
                {
                    cout<<"您已成功注册,请进行登录"<<endl;
                    userinformation<<user1.getusername()<<" "<<user1.getpassword()<<endl;
                    Sleep(1000);
                }
            }
        }
        else if(op1=="0")
        {
            int fl=0;
            while(fl==0)
            {
                cout<<"您确认要退出该系统吗?(是请按1,否请按0)";
                int opp;
                cin>>opp;
                if(opp==1)
                    exit(0);
                else if(opp==0)
                    fl=1;
                else
                    cout<<"您输入有误,请重新输入"<<endl;
            }
            
        }
        else
        {
            cout<<"您输入了无效的操作代码,请重新输入";
            Sleep(1000);
        }
        userinformation.close();
        system("cls");
    }
    return 0;
}