#include<iostream>
#include"AST.hpp"
#include<fstream>
int globalstep = 0;

std::ofstream visual_fp;
using namespace AST;
using namespace std;

void Program::visualization(int n, std::string file_path)
{
    visual_fp.open(file_path);
    visual_fp<<"a"<<n<<" [label= \"program:\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    Define_List_->visualization(i);
    visual_fp.close();
}

void Specifier::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"specifier:"<<type<<"\"]\n"<<std::endl;
}

void Exp_Bin::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Exp_Bin : "<<bin_operation<<"\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    a->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    b->visualization(i);
}

void Exp_Uni::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Exp_Uni : "<<uni_operation<<"\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    a->visualization(i);
}

void Exp_Con::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Exp_Con : \"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    a->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    b->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    c->visualization(i);
}

void Exp_List::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Exp_List \"]\n"<<std::endl;
    for (auto iter = Exp_List_.begin(); iter != Exp_List_.end(); iter++)
	{
        int i=++globalstep;
        visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
        (*iter)->visualization(i);
    }
}

void Exp_Func::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Exp_Func : "<<Func_Name<<"\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    Parameters->visualization(i);
}

void Exp_Comma::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Exp_Comma \"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    a->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    b->visualization(i);
}

void Exp_Assign::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Exp_Assign \"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    a->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    b->visualization(i);
}

void Exp_ID::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Exp_ID:"<<ID_Name<<"\"]\n"<<std::endl;
}

void Constant_Int::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Constant_Int:"<<Val<<"\"]\n"<<std::endl;
}

void Constant_Double::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Constant_Double:"<<Val<<"\"]\n"<<std::endl;
}

void Constant_Bool::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Constant_Bool:"<<Val<<"\"]\n"<<std::endl;
}

void Constant_Char::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Constant_Char:"<<Val<<"\"]\n"<<std::endl;
}

void Constant_String::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Constant_String:"<<Val<<"\"]\n"<<std::endl;
}

void Stat_List::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Stat_List \"]\n"<<std::endl;
    for (auto iter = Stat_List_.begin(); iter != Stat_List_.end(); iter++)
	{
        int i=++globalstep;
        visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
        (*iter)->visualization(i);
    }
}

void Block::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Block\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    StatList_->visualization(i);
}

void Stat_Exp::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Stat_Exp\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    a->visualization(i);
}

void Stat_Return::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Stat_Return\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    a->visualization(i);
}

void Stat_If::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Stat_If\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    a->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    t->visualization(i);
}

void Stat_IfElse::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Stat_IfElse\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    a->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    t->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    f->visualization(i);
}

void Stat_For::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Stat_For\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    a->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    b->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    c->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    t->visualization(i);
}

void Stat_While::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Stat_While\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    a->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    t->visualization(i);
}

void Stat_DoWhile::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Stat_DoWhile\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    a->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    t->visualization(i);
}

void Define_List::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Define_List \"]\n"<<std::endl;
    for (auto iter = DefineList_.begin(); iter != DefineList_.end(); iter++)
	{
        int i=++globalstep;
        visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
        (*iter)->visualization(i);
    }
}

void Var_Dec::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Var_Dec: "<<ID<<"\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    Type->visualization(i);
}

void Fun_Imp::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Define_Block "<<Fun_ID<<"\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    Return_Type->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    Fun_Block->visualization(i);
    if(ParaList_==NULL||(ParaList_->Specifier_List_).empty())
    {
        i=++globalstep;
        visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
        visual_fp<<"a"<<i<<" [label= \" void \"]\n"<<std::endl;
    }
    else
    {
        i=++globalstep;
        visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
        ParaList_->visualization(i);
    }
}

void Var_Init::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \" Var_Init\"]\n"<<std::endl;
    int i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    ID->visualization(i);
    i=++globalstep;
    visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
    Val->visualization(i);
}

void Var_List::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Var_List \"]\n"<<std::endl;
    for (auto iter = Var_Init_List_.begin(); iter != Var_Init_List_.end(); iter++)
	{
        int i=++globalstep;
        visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
        (*iter)->visualization(i);
    }
}

void Para_List::visualization(int n)
{
    visual_fp<<"a"<<n<<" [label= \"Para_List \"]\n"<<std::endl;
    for (auto iter = Specifier_List_.begin(); iter != Specifier_List_.end(); iter++)
	{
        int i=++globalstep;
        visual_fp<<"a"<<n<<" -> "<<"a"<<i<<std::endl;
        (*iter)->visualization(i);
    }
}
