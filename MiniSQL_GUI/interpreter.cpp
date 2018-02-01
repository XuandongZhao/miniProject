#include "stdafx.h"
#include "interpreter.h"
using namespace std;
int Interpreter::interpreter(std::string s)
{
    int index = 0;
    int &num = index;
    std::string word;
    word = getword(s, num);
    if (word == "create") {
        bool flag = exec_create(s, num);
        if (flag) {
            cout << "Interpreter: successful create!" << endl;
        }
        else
            cout << "Interpreter: create failed!" << endl;
    }
    else if (word == "select") {
        bool flag = exec_select(s, num);
        if (flag) {
            cout << "Interpreter: successful select!" << endl;
        }
        else
            cout << "Interpreter: select failed!" << endl;
    }
    else if (word == "drop") {
        bool flag = exec_drop(s, num);
        if (flag) {
            cout << "Interpreter: successful drop!" << endl;
        }
        else
            cout << "Interpreter: drop failed!" << endl;
    }
    else if (word == "delete") {
        bool flag = exec_delete(s, num);
        if (flag) {
            cout << "Interpreter: successful delete!" << endl;
        }
        else
            cout << "Interpreter: delete failed!" << endl;
    }
    else if (word == "insert") {
        bool flag = exec_insert(s, num);
        if (flag) {
            cout << "Interpreter: successful insert!" << endl;
        }
        else
            cout << "Interpreter: insert failed!" << endl;
    }
    else if (word == "commit") {
        return 1;
    }
    else if (word == "execfile")
    {
        std::string filename = path +"//txtfile//" + getword(s, num);
        cout << filename << endl;
        //system("pause");
        ifstream fin(filename, ios::in);
        if (!fin)
        {
            cout << "Can not open the file" << endl;
        }

        while (!fin.eof()) {
            std::string s;
            std::getline(fin, s, ';');
            int loc = -1;
            for (int i = 0; i<s.size() - 1; i++)
            {
                if (s[i] == '-'&&s[i + 1] == '-')
                {
                    loc == i;
                    break;
                }
            }
            if (loc != -1)
            {
                s = s.substr(0, loc);
            }
            //still need to fill
            this->interpreter(s);
        }
        fin.close();

    }
    else if (word == "quit") {
        exit(0);
        return -1;
    }
    else {
        if (word.empty()) {
            cout << "Syntax Wrror! " << word << "not found" << endl;
            return 0;
        }
    }
    return 0;
}

bool Interpreter::exec_create(std::string s, int &num)
{
    vector<AttriValue> av;
    word = getword(s, num);
    if (word == "table")
    {
        std::string primaryKey;
        std::string table_name;

        word = getword(s, num);
        if (!word.empty())
            table_name = word;
        else
        {
            cout << "Syntax Error! No table name " << endl;
            return 0;
        }

        word = getword(s, num);
        if (word.empty() || word != "(")
        {
            cout << "Sysntax Error! Unknown data type" << endl;
            return 0;
        }
        else
        {
            word = getword(s, num);

            while (!word.empty() && word != "primary" && word != ")")
            {
                AttriValue newav;
                std::string attribute_name = word;
                newav.AtrributeName = word;
                word = getword(s, num);
                if (word == "int")
                {
                    newav.type = 0;
                    newav.length = 4;
                }
                else if (word == "float")
                {
                    newav.type = 1;
                    newav.length = 4;
                }
                else if (word == "char")
                {
                    newav.type = 2;
                    word = getword(s, num);
                    if (word != "(")
                    {
                        cout << "Syntax Error! Unknown data type " << endl;
                        return 0;
                    }

                    word = getword(s, num);
                    newav.length = stoi(word);
                    //newav.AtrributeName = word;

                    word = getword(s, num);
                    if (word.empty() || word != ")")
                    {
                        cout << "Syntax Error! Unknown data type " << endl;
                        return 0;
                    }
                }// end of data type
                else
                {
                    cout << "Syntax Error! Unknown or missing of data type" << endl;
                    return 0;
                }
                word = getword(s, num);
                if (word == "unique")
                {
                    newav.isUnique = true;
                    word = getword(s, num);
                }
                if (word != ",")
                {
                    if (word != ")")
                    {
                        cout << "Systax Error for ',' !" << endl;
                        return 0;
                    }
                    else
                        break;
                }
                word = getword(s, num);
                av.push_back(newav);
            }
            if (word == "primary")
            {
                word = getword(s, num);
                if (word != "key")
                {
                    cout << "Sysntax Error! Wrong input with primary key" << endl;
                    return 0;
                }
                else
                {
                    word = getword(s, num);
                    if (word != "(")
                    {
                        cout << "Sysntax Error! Wrong input " << endl;
                        return 0;
                    }
                    else
                    {
                        word = getword(s, num);
                        primaryKey = word;
                        word = getword(s, num);
                        if (word != ")")
                        {
                            cout << "Sysntax Error! Wrong input" << endl;
                            return 0;
                        }
                    }
                }
                word = getword(s, num);
                if (word != ")")
                {
                    cout << "Sysntax Error!" << endl;
                    return 0;
                }
            }
            else if (word.empty())
            {
                cout << "Sysntax Error! ')' absent!" << endl;
                return 0;
            }
            //cout << primaryKey << "&&&&&" << endl;
            for (int l = 0; l < av.size(); l++)
            {
                av[l].cntintable = l;
                //cout << av[l].AtrributeName << "***" << endl;
                if (av[l].AtrributeName == primaryKey)
                {
                    av[l].isPrimary = 1;
                }
            }
            myapi.createtable(table_name, &av);
            return 1;
        }
    }
    else if (word == "index")
    {
        std::string index_name;
        std::string table_name;
        std::string attribute_name;
        word = getword(s, num);
        if (!word.empty())
        {
            index_name = word;
        }
        else
        {
            cout << "Sysntax Error! No index name" << endl;
            return 0;
        }
        word = getword(s, num);
        try
        {
            if (word != "on")
                throw SyntaxException();

            word = getword(s, num);
            if (word.empty())
                throw SyntaxException();
            table_name = word;

            word = getword(s, num);
            if (word != "(")
                throw SyntaxException();

            word = getword(s, num);
            if (word.empty())
                throw SyntaxException();
            attribute_name = word;

            word = getword(s, num);
            if (word != ")")
                throw SyntaxException();
            myapi.createindex(index_name, table_name, attribute_name);//do the create
            return 1;
        }
        catch (SyntaxException&)
        {
            cout << "Syntax Error! Wrong input with index" << endl;
            return 0;
        }
    }
    else
    {
        cout << "Syntax Error!" << endl;
        return 0;
    }

    return 0;
}
bool Interpreter::exec_select(std::string s, int &num)
{
    //cout << "^^^^^^" << endl;
    vector<std::string> attribute_former;
    vector<std::string> attribute_later;
    std::string table_name;
    std::string attribute_name;
    word = getword(s, num);
    if (word != "*")
    {
        while (word != "from")
        {
            if (word != ",") {
                std::string newav = word;
                attribute_former.push_back(newav);
            }
            word = getword(s, num);
        }
    }
    else {
        word = getword(s, num);//word = from
    //	string tmp = "id"; attribute_former.push_back(tmp);
    //	tmp = "name"; attribute_former.push_back(tmp);
    //	tmp = "score"; attribute_former.push_back(tmp);
    }

    //cout << "*****&&&&" << word << endl;
    if (word != "from")
    {
        //cout << "*****" << word << endl;
        cout << "Syntax Error! Wrong input " << endl;
        return 0;
    }

    word = getword(s, num);
    if (!word.empty())
    {
        table_name = word;//find the table
    }
    else
    {
        cout << "Syntax Error! There is no such table" << endl;
        return 0;
    }
    word = getword(s, num);//conditions
    if (word.empty())
    { //no confine
        vector<Condition> condition_vector;
        if (attribute_former.size() == 0) {
            //myapi.selectrecord(table_name, nullptr, nullptr);//do the select
            myapi.selectrecord(table_name, &attribute_former, &condition_vector);
        }
        else {
            myapi.selectrecord(table_name, &attribute_former, &condition_vector);//do the select
        }
        return 1;
    }
    else if (word == "where")
    {
        std::string attribute_name;
        std::string value;
        vector<Condition> condition_vector;
        word = getword(s, num);
        while (1)
        {
            try
            {
                Condition co;
                //cout << "0 " << word << endl;
                if (word.empty())
                    throw SyntaxException();
                attribute_name = word;

                //cout << "1 " << word << endl;

                std::string newav = attribute_name;
                co.attriName = newav;
                word = getword(s, num);
                if (word == "<=") {
                    co.OP = co.OPERATOR_LESS_EQUAL;
                }
                else if (word == ">=") {
                    co.OP = co.OPERATOR_MORE_EQUAL;
                }
                else if (word == "<") {
                    co.OP = co.OPERATOR_LST;
                }
                else if (word == ">") {
                    co.OP = co.OPERATOR_MOT;
                }
                else if (word == "=") {
                    co.OP = co.OPERATOR_EQUAL;
                }
                else if (word == "<>" || word == "!=") {
                    co.OP = co.OPERATOR_NOT_EQUAL;
                }
                else
                    throw SyntaxException();
                word = getword(s, num);
                if (word.empty())
                    throw SyntaxException();
                value = word;
                co.value = value;
                condition_vector.push_back(co);
                attribute_later.push_back(newav);
                word = getword(s, num);

                if (word.empty() || word == ";")
                    break;
                if (word != "and")
                    throw SyntaxException();

                word = getword(s, num);
            }
            catch (SyntaxException&)
            {
                cout << "Systax Error! Wrong input " << endl;
                return 0;
            }
        }
        myapi.selectrecord(table_name, &attribute_former, &condition_vector);//do the select
        return 1;
    }
    return 1;
}
bool Interpreter::exec_drop(std::string s, int &num)
{
    word = getword(s, num);
    if (word == "table")
    {
        word = getword(s, num);
        if (!word.empty())
        {
            myapi.droptable(word);//do the drop
            return 1;
        }
        else
        {
            cout << "Syntax Error! Table name miss" << endl;
            return 1;
        }
    }
    else if (word == "index")
    {
        word = getword(s, num);
        if (!word.empty())
        {
            myapi.dropindex(word);//do the drop
            return 1;
        }
        else
        {
            cout << "Syntx Error! Index name miss" << endl;
            return 0;
        }
    }
    else
    {
        cout << "Syntx Error! Wrong input" << endl;
        return 0;
    }
}

bool Interpreter::exec_delete(std::string s, int &num)
{
    std::string table_name;
    vector<std::string> av;
    word = getword(s, num);
    //cout << "****delete" << word << endl;
    if (word != "from")
    {
        cout << "Syntax Error! Wrong input" << endl;
        return 0;
    }
    word = getword(s, num);
    //cout << "1" << word << endl;
    if (!word.empty())
    {
        table_name = word;
    }
    else
    {
        cout << "Syntax Error! No table name " << endl;
        return 0;
    }

    word = getword(s, num);
    if (word.empty())
    {
        myapi.deleterecord(table_name, nullptr);//do the delete
        return 1;
    }
    else if (word == "where")
    {
        std::string attribute_name;
        std::string value;
        vector<Condition> condition_vector;

        word = getword(s, num);
        //cout << "2" << word << endl;
        while (1)
        {
            try
            {
                Condition co;
                if (word.empty())
                    throw SyntaxException();
                attribute_name = word;
                std::string newav = attribute_name;

                word = getword(s, num);
                //cout << "3" << word << endl;

                if (word == "<=") {
                    co.OP = co.OPERATOR_LESS_EQUAL;
                }
                else if (word == ">=") {
                    co.OP = co.OPERATOR_MORE_EQUAL;
                }
                else if (word == "<") {
                    co.OP = co.OPERATOR_LST;
                }
                else if (word == ">") {
                    co.OP = co.OPERATOR_MOT;
                }
                else if (word == "=") {
                    co.OP = co.OPERATOR_EQUAL;
                }
                else if (word == "<>" || word == "!=") {
                    co.OP = co.OPERATOR_NOT_EQUAL;
                }
                else
                    throw SyntaxException();
                word = getword(s, num);
                //cout << "4" << word << endl;
                if (word.empty())
                    throw SyntaxException();
                value = word;
                co.value = value;
                co.attriName = newav;
                condition_vector.push_back(co);
                av.push_back(newav);
                word = getword(s, num);
                if (word.empty() || word == ";")
                    break;

                if (word != "and")
                    throw SyntaxException();
                word = getword(s, num);
            }
            catch (SyntaxException&)
            {
                cout << "Systax Error! Wrong input " << endl;
                return 0;
            }
        }
        myapi.deleterecord(table_name, &condition_vector);//do the delete
        return 1;
    }
    else
        return 1;
}
bool Interpreter::exec_insert(std::string s, int &num)
{
    std::string table_name;
    vector<std::string> value;
    word = getword(s, num);
    try
    {
        if (word != "into")
            throw SyntaxException();
        word = getword(s, num);
        if (word.empty())
            throw SyntaxException();

        table_name = word;
        word = getword(s, num);
        if (word != "values")
            throw SyntaxException();
        word = getword(s, num);
        if (word != "(")
            throw SyntaxException();
        word = getword(s, num);


        while (!word.empty() && word != ")")
        {
            value.push_back(word);
            word = getword(s, num);
            if (word == ",")
            {
                word = getword(s, num);
            }
        }
        if (word != ")") {
            throw SyntaxException();
        }
    }
    catch (SyntaxException&) {
        cout << "Syntax Error! Wrong input " << endl;
        return 0;
    }
    myapi.insertrecord(table_name, &value);// do the insert
    return 1;
}


std::string Interpreter::getword(std::string s, int &num)
{
    std::string word;
    int flag1 = 0, flag2 = 0;

    while ((s[num] == ' ' || s[num] == '\n' || s[num] == '\t') && s[num] != 0)
        num++;
    flag1 = num;

    if (s[num] == '(' || s[num] == ',' || s[num] == ')') {
        num++;
        flag2 = num;
        word = s.substr(flag1, flag2 - flag1);
        return word;
    }

    else if (s[num] == '\'') {
        num++;
        while (s[num] != '\''  && s[num] != 0)
            num++;
        if (s[num] == '\'') {
            flag1++;
            flag2 = num;
            num++;
            word = s.substr(flag1, flag2 - flag1);
            return word;
        }
        else {
            word = "";
            return word;
        }
    }
    else if (s[num] == '=')
    {
        num++;
        flag2 = num;
        word = s.substr(flag1, flag2 - flag1);
        return word;
    }
    else if (s[num] == '<')
    {
        if (s[num + 1] == '=' || s[num + 1] == '>') {
            num = num + 2;
            flag2 = num;
            word = s.substr(flag1, flag2 - flag1);
            return word;
        }
        else {
            num++;
            flag2 = num;
            word = s.substr(flag1, flag2 - flag1);
            return word;
        }
    }
    else if (s[num] == '>')
    {
        if (s[num + 1] == '=') {
            num = num + 2;
            flag2 = num;
            word = s.substr(flag1, flag2 - flag1);
            return word;
        }
        else {
            num++;
            flag2 = num;
            word = s.substr(flag1, flag2 - flag1);
            return word;
        }
    }
    else if (s[num] == '!')
    {
        if (s[num + 1] == '=') {
            num = num + 2;
            flag2 = num;
            word = s.substr(flag1, flag2 - flag1);
            return word;
        }
        else {
            num++;
            flag2 = num;
            word = s.substr(flag1, flag2 - flag1);
            return word;
        }
    }
    else {
        while (s[num] != ' ' &&s[num] != '(' && s[num] != '\n' && s[num] != 0 && s[num] != ')' && s[num] != ','&&s[num] != '='&&s[num] != '!'&&s[num] != '<'&&s[num] != '>')
            (num)++;
        flag2 = num;
        if (flag1 != flag2)
            word = s.substr(flag1, flag2 - flag1);
        else
            word = "";
        return word;
    }
}
