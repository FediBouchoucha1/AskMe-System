#include<bits/stdc++.h>
using namespace std;



class user{
private:
    int id;
    string userName;
    string password;
    string name;
    string email;
    int AQ;
    
public:
    user(){}

    user(int id , string username,string password,string name,string email,int aq)
    {
        setid(id);
        setUserName(username);
        setpass(password);
        setname(name);
        setemail(email);
        setaq(aq);
    }
    void read()
    {
        string n;
        cout<<"Enter user name. (No spaces):"<<endl;
        cin>>n;
        this->userName=n;
        cout<<"Enter password:"<<endl;
        cin>>n;
        this->password=n;
        cout<<"Enter name:"<<endl;
        cin>>n;
        this->name=n;
        cout<<"Enter email:"<<endl;
        cin>>n;
        this->email=n;
        int x;
        cout<<"Allow anonymous questions?: (0 or  1)"<<endl;
        cin>>x;
        this->AQ=x;
        srand(time(NULL));
        this->id=100+(rand()%101);
    }

    const int&  getId()const
    {
        return id;
    }
    const string&  getuserName()const
    {
        return userName;
    }
    const string&  getpassword()const
    {
        return password;
    }
    const string&  getName()const
    {
        return name;
    }
    const string&  getemail()const
    {
        return email;
    }
    const int&  getAQ()const
    {
        return AQ;
    }

   void setid(int id)
   {
      this->id=id;
   }

   void setUserName(string n)
   {
     this->userName=n;
   }

   void setpass(string n)
   {
     this->password=n;
   }

    void setname(string n)
    {
        this->name=n;
    }

    void setemail(string n)
    {
        this->email=n;
    }

    void setaq(int n)
    {
        this->AQ=n;
    }
};


class question{
private:
    int id;
    int idthread=-111;
    int sender;
    int receiver;
    string quest;
    string answer;


public:

    question()
    {

    }

    question(int id,int idthread,int sender,int receiver,string quest,string answer):id(id),idthread(idthread),sender(sender),
    receiver(receiver),quest(quest),answer(answer)
    {
    }

    void readThread(int k, int x, int y)
    {
        srand(time(NULL));
        this->id=k;
        this->idthread=200+(rand()%201);
        this->sender=y;
        this->receiver=x;
        string str;
        cout<<"Enter question text: "<<endl;
        cin>>str;
        this->quest=str;

    }

    void read(int x, int y)
    {

        srand(time(NULL));
        this->id=300+(rand()%301);
        this->sender=y;
        this->receiver=x;
        string str;
        cout<<"Enter question text: "<<endl;
        cin>>str;
        this->quest=str;

    }
    const int& getReceiver()const
    {
        return receiver;
    }
    
    const int& getIDThread()const
    {
        return idthread;
    }
    const int& getsender()const{
        return sender;
    }

    const string& getQuestion()const{
        return quest;
    }

    const string& getanswer()const{
        return answer;
    }
    void setanswer(string n)
    {
        this->answer=n;
    }

    const int& getid()const{
        return id;
    }

    void setquest(string n)
    {
        this->quest=n;
    }
    void printFormQuestion(int x,int t=0)
    {
        ostringstream oss;
        oss<<"Question Id  ";
        if(t){
            oss<<this->idthread;
        }else{
            oss<<this->id;
        }
        
        if(!x)
        {
            oss<<" from user id ";
            oss<<this->sender;
        }
        oss<<"        Question: ";
        oss<<this->quest;

        cout<<oss.str()<<endl;
    }

    void printFormAnswer()
    {
        ostringstream oss;
        oss<<"Answer: ";
        if(this->answer!="")
            oss<<answer;
        else{
            oss<<" NOT answer YET ";
        }
        cout<<oss.str()<<endl;
    }

    string tostring()
    {
        ostringstream oss;
        oss<<idthread;
        oss<<",";
        oss<<id;
        oss<<",";
        oss<<sender;
        oss<<",";
        oss<<receiver;
        oss<<",";
        oss<<quest;
        oss<<",";
        oss<<answer;

        return oss.str();

    }

    void setID(int x)
    {
        this->id=x;
    }
};

class questionManager{
private:
    unordered_map<int,question*> questions;
public:

    void updatefile()
    {
        string path="questions.txt";
	    fstream file_handler(path.c_str());

        for(const pair<int,question*> &item : questions)
        {
                
                string str=item.second->tostring();
                file_handler<<str<<endl;
                  
        }

        file_handler.close();

    }
    void addLinetoMap(string str)
    {
        int id;
        int idthread;
        int sender;
        int receiver;
        string quest;
        string answer;
        int pos;
        pos=str.find(",");
        string idd=str.substr(0,pos);
        idthread=stoi(idd);// convert it to integer;

        str=str.substr(pos+1);

        pos=str.find(",");
        id=stoi(str.substr(0,pos));

        str=str.substr(pos+1);
        pos=str.find(",");
        sender=stoi(str.substr(0,pos));

        str=str.substr(pos+1);
        pos=str.find(",");
        receiver=stoi(str.substr(0,pos));

        str=str.substr(pos+1);
        pos=str.find(",");
        quest=str.substr(0,pos);

        str=str.substr(pos+1);
        answer=str;

        question* nquestion=new question(id,idthread,sender,receiver,quest,answer);
        if(idthread!=-111)
            questions[idthread]=nquestion;
        else{
            questions[id]=nquestion;
        }
    }
    void loadFromfiletoMap()
    {
        string path="questions.txt";
        fstream file_handler(path.c_str());

        if(file_handler.fail())
        {
            cout<<"Cant't open the file\n";
            return;
        }
        string line;

        while(getline(file_handler, line))
        {
            if(line!="")
            {
                addLinetoMap(line);
            }
        }
        file_handler.close();
    }

    void printthread(int idquestion,user* currentuser)
    {
        for(const pair<int,question*> &item : questions)
        {
            if(item.second->getid()==idquestion && item.second->getIDThread()!=-111 )
            {
                cout<<"\tThread:";
                cout<<"\t";
                item.second->printFormQuestion(currentuser->getAQ(),1);
                cout<<"\tThread:       ";
                cout<<"\t";
                item.second->printFormAnswer();
            }
        }
    }
    void PrintQuestionsToMe(user* currentuser)
    {
        int id=currentuser->getId();
        for(const pair<int,question*> &item : questions)
        {
            if(item.second->getReceiver()==id&&item.second->getIDThread()==-111)
            {
                if(currentuser->getAQ())
                    item.second->printFormQuestion(1);
                else{
                    item.second->printFormQuestion(0);
                }
                item.second->printFormAnswer();
                printthread(item.first,currentuser);
            }
        }
        
    }

    int findaq(int id,map<string,user*> users)
    {
        for(const pair<string,user*> &item : users)
        {
            if(item.second->getId()==id)
            {
                return item.second->getAQ();
            }
        }
        return -1;
    }   
    void PrintQuestionsFromMe(user* currentuser,map<string,user*> users)
    {

        int id=currentuser->getId();
        for(const pair<int,question*> &item : questions)
        {
            if(item.second->getsender()==id)
            {
                if(item.second->getIDThread()==-111)
                    cout<<"Question Id ("<<item.second->getid()<<")";
                else{
                    cout<<"Question Id ("<<item.second->getIDThread()<<")";
                }
                int idr=item.second->getReceiver();
                int aq=findaq(idr,users);
                if(!aq)
                {
                    cout<<" !AQ";
                }
                cout<<" to user id "<<idr<<" ";
                cout<<"Question: "<< item.second->getQuestion()<<endl;
                item.second->printFormAnswer();
            }
        }
    }


    void AnswerQuestion(user* currentuser)
    {
        int choice;
        cout<<"Enter Question id or -1 t0 cancel :"<<endl;
        cin>>choice;
        if(choice==-1)
            return;
        
        questions[choice]->printFormQuestion(currentuser->getAQ());
        string n;
        if(questions[choice]->getanswer()!="")
        {
            questions[choice]->printFormAnswer();
            cout<<"Warning: Already answered. Answer will be updated"<<endl;

        }
        cout<<"Enter answer: "<<endl;
        cin>>n;
        questions[choice]->setanswer(n);

        updatefile();

    }   

    void updatefile1(bool append)
    {
        auto status = ios::in | ios::out | ios::app;
        string path="questions.txt";
        if (!append)
		    status = ios::in | ios::out | ios::trunc;

	    fstream file_handler(path.c_str(), status);

        for(const pair<int,question*> &item : questions)
        {
                if(item.second->getQuestion()!="DELETED")
                {
                    string str=item.second->tostring();
                    file_handler<<str<<endl;
                }
                
                  
        }

        file_handler.close();

    }
    
    void DeleteQuestion()
    {
        int choice;
        cout<<"Enter Question id or -1 to cancel :"<<endl;
        cin>>choice;
        if(choice==-1)
            return;
        
        for(const pair<int,question*> &item : questions)
        {
            if(item.second->getid()==choice||item.second->getIDThread()==choice)
            {
                item.second->setquest("DELETED");
                
            }
        }
        updatefile1(false);
        questions.clear();
        loadFromfiletoMap();
    }


    void AskQuestion(user* currentuser,map<string,user*> users)
    {
        int choice;
        cout<<"Enter user id or -1 to cancel"<<endl;
        cin>>choice;
        if(choice==-1)
            return;
        if(!findaq(choice,users))
        {
            cout<<"Note: Anonymous questions are not allowed for this user"<<endl;
        }
        cout<<"For thread questions: Enter question id or -1 for new question: "<<endl;
        int k;
        cin>>k;
        if(k==-1)
        {
            //creating a new question;
            question* nquestion=new question();
            nquestion->read(choice,currentuser->getId());
            questions[nquestion->getid()]=nquestion;
        }else{
            question* nquestion=new question();
            nquestion->readThread(k,choice,currentuser->getId());
            questions[nquestion->getIDThread()]=nquestion;
            
        }
        updatefile();
    }

   
    void feed(map<string,user*> users)
    {
        for(const pair<int,question*> &item : questions)
        {
            int re=item.second->getReceiver();
            int id=item.second->getid();
            if(item.second->getIDThread()==-111)
            {
                item.second->printFormQuestion(findaq(re,users));
                item.second->printFormAnswer();
                for(const pair<int,question*> &it : questions)
                {
                    if(it.second->getIDThread()!=-111&&it.second->getid()==id)
                    {
                        cout<<"Thread Parent ";
                        it.second->printFormQuestion(findaq(re,users),1);
                        it.second->printFormAnswer();
                    }
                }


            }
        }
    }

};

class userManager{
private:
    user* currentUser{};
    map<string,user*> users;
    questionManager &questions;
public:
    userManager(questionManager &q):questions(q)
    {
        questions.loadFromfiletoMap();
        currentUser=new user();
    }
    void addLinetoMap(string str)
    {
        int id; 
        string userName;
        string password;
        string name;
        string email;
        int aq;

        int pos;
        pos=str.find(",");
        string idd=str.substr(0,pos);
        id=stoi(idd);// convert it to integer;

        str=str.substr(pos+1);

        pos=str.find(",");
        userName=str.substr(0,pos);

        str=str.substr(pos+1);
        pos=str.find(",");
        password=str.substr(0,pos);

        str=str.substr(pos+1);
        pos=str.find(",");
        name=str.substr(0,pos);

        str=str.substr(pos+1);
        pos=str.find(",");
        email=str.substr(0,pos);

        str=str.substr(pos+1);
        aq=stoi(str);

        user *Nuser=new user(id,userName,password,name,email,aq);
        users[userName]=Nuser;
    }

    void loadFromFileTomap()
    {
        string path="users.txt";
        fstream file_handler(path.c_str());

        if(file_handler.fail())
        {
            cout<<"Cant't open the file\n";
            return;
        }
        string line;

        while(getline(file_handler, line))
        {
            if(line!="")
            {
                addLinetoMap(line);
            }
        }
        file_handler.close();
    }
    string changeToString()
    {
        ostringstream oss;
        oss<<currentUser->getId();
        oss<<",";
        oss<<currentUser->getuserName();
        oss<<",";
        oss<<currentUser->getpassword();
        oss<<",";
        oss<<currentUser->getName();
        oss<<",";
        oss<<currentUser->getemail();
        oss<<",";
        oss<<currentUser->getAQ();

        return oss.str();
    }
    void writeTofile()
    {
        bool append = true;

	    auto status = ios::in | ios::out | ios::app;

	    if (!append)
		    status = ios::in | ios::out | ios::trunc;	

	    string path = "users.txt";
	    fstream file_handler(path.c_str(), status);

	    if (file_handler.fail()) {
		    cout << "Can't open the file\n";
		    return ;
	    }

        string str=changeToString();

        file_handler<<endl<<str;

        file_handler.close();

    }
    void addToUsers(user* nuser)
    {
        string userName=nuser->getuserName();
        users[userName]=nuser;
        writeTofile();
    }
    void login()
    {
        
        loadFromFileTomap();
        while(true)
        {
            string n;
            cout<<"Enter user name "<<endl;
            cin>>n;
            if(!users.count(n))
            {
                cout<<"this userName does not exist in the database"<<endl;
                continue;
            }
            currentUser=users[n];
            cout<<"Enter password"<<endl;
            cin>>n;
            if(currentUser->getpassword()!=n)
            {
                cout<<"verify your username of password something is wrong"<<endl;
                continue;
            }else{
                break;
            }
        }
        
        menu();
    }

    void ListSystemUsers() // choice6
    {
        for(const pair<string,user*> &item : users)
        {
            cout<<"ID: "<<item.second->getId()<<"      "<<"Name: "<<item.second->getName()<<endl; 
        }
        cout<<endl;
    }

     user* getCurrentuser()const
    {
        return currentUser;
    }


    void menu()
    {
        while(true)
        {
            
            cout<<"Menu:"<<endl;
            cout<<"\t1: Print Questions to Me"<<endl;
            cout<<"\t2: Print Questions from Me"<<endl;
            cout<<"\t3: Answer Question"<<endl;
            cout<<"\t4: Delete Question"<<endl;
            cout<<"\t5: Ask Question"<<endl;
            cout<<"\t6: List System Users"<<endl;
            cout<<"\t7: Feed"<<endl;
            cout<<"\t8: Logout"<<endl;

            int choice;
            cin>>choice;

            while(choice>8&&choice<1)
            {
                cout<<"ERROR: invalid number ... Try again"<<endl;
            }
            if(choice==1)
            {
                questions.PrintQuestionsToMe(currentUser);
            }else if(choice==2)
            {
                questions.PrintQuestionsFromMe(currentUser,users);
            }else if(choice==3)
            {
                questions.AnswerQuestion(currentUser);
                
            }else if(choice==4)
            {
                questions.DeleteQuestion();
               
            }else if(choice==5)
            {
                questions.AskQuestion(currentUser,users);
                
            }else if(choice==6)
            {
                ListSystemUsers();
            }else if(choice==7)
            {
                questions.feed(users);
            }else if(choice==8)
            {
                break;
            }
        } 
    }
    void signup()
    {
        loadFromFileTomap();
        while(true)
        {
            currentUser->read();
            if(!users.count(currentUser->getuserName()))
            {
                addToUsers(currentUser);
                break;
            }else{
                cout<<"this userName exists before change it !!\n";
                continue;
            }  
        }   
        menu();
    }
    
    
};


class ASKME{
private:
    userManager *users;
    questionManager *questions;

public:
    ASKME()
    {
        questions=new questionManager();
        users=new userManager(*questions);
    }
    void run()
    {
        while(true)
        {
            int choice;
            cout<<"Menu:"<<endl;
            cout<<"\t1: Login"<<endl;
            cout<<"\t2: Sign Up"<<endl;

            cout<<"Enter number in range 1 - 2:"<<endl;
            cin>>choice;
            if(choice==1)
            {
                users->login();
            }else if(choice==2)
            {
                users->signup();
            }else{
                cout<<"Please enter a valid Number"<<endl;
            }
        }
    }

};



int main()
{
    ASKME test;
    test.run();
    return 0;
}