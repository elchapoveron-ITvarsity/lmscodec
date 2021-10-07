#include <iostream>
#include<stdio.h>
#include <string>
#include<math.h>
#include<iomanip>
#include<fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;
bool result;
string usersList[10];
string passwordsList[10];
string CourseCode[8][10];
string CourseName[8][10];
int crdtHour[8][10];
int cdIdx=0;
int cnIdx = 0;
int crIdx = 0;
int semIndex;
int codeIndex=0;
int studentIndex=0;
int userIdx = 0;
const char* pFileName = "Courses.txt";
const char* pUsersFile = "Users.txt";
const char* pStudentFile = "Student.txt";    //new

ofstream write1,write2;           //new
ifstream read1,read2;              //new


void startError()
{
  if (cin.fail())
  {	 system("CLS");
     cout << "ERROR -- You did not enter an integer"<<endl;
     cin.clear();
     cin.ignore();
  }
}
bool isValidCourseCode(string courseCode)
{
    if(courseCode.length()==5)
    {
        if (isalpha(courseCode[0])&&isalpha(courseCode[1])&&isdigit(courseCode[2])&&isdigit(courseCode[3])&&isdigit(courseCode[4]))
            return true;
    }
        else{
            return false;
            }
}
bool isValidCourseName(string courseName)
{
    if(courseName.length()>50)
    {
        return false;
    }
    for(int i=0;i<courseName.length();i++)
    {
        if (!(isspace(courseName[i])||(isalpha(courseName[i]))))
            return false;
    }
    return true;
}
    bool isValidCreditHours(int CrdHrs)
{
    if(CrdHrs>0 && CrdHrs<=3)
    {
        return true;
    }
    else {
            return false;
         }
}
    bool isValidSemester(int semester)
{
    if(semester>0 && semester<=8)
    {
        return true;
    }
    else{
        return false;
        }
}
void AddCourse(string code,string name,int credit,int semester)
{
    CourseCode[semester-1][cdIdx] = code;
    CourseName[semester-1][cnIdx] = name;
    crdtHour[semester-1][crIdx] = credit;
    cdIdx++;
    cnIdx++;
    crIdx++;
    cout << "Course Added Successfully";
    }
bool findCourseCode(string code)
{
      for (int i=0;i<8;i++)
      {
          for(int j = 0; j < 10; j++)
          {
            if (code == CourseCode[i][j])
            {
                semIndex=i;
                codeIndex = j;
                return true;
            }
          }
        }
        return false;
}
void UpdateCourse(string cd,string name,int credit,int semester)
    {

           CourseCode[semIndex][codeIndex] = "";
           CourseName[semIndex][codeIndex] = "";
           crdtHour[semIndex][codeIndex] = 0;
           CourseCode[semester-1][cdIdx] = cd;
           CourseName[semester-1][cnIdx] = name;
           crdtHour[semester-1][crIdx] = credit;
             cout << "Course has been edited successfully";}

     void DeleteCourse(string cdd)
{
for(int i=0;i<semIndex;i++)
for(int j=0;j<semIndex;j++)
{
    if (cdd==CourseCode[i][j])
    {
           CourseCode[semIndex][codeIndex] = "";
           CourseName[semIndex][codeIndex] = "";
           crdtHour[semIndex][codeIndex] = 0;
           cout << "Course deleted successfully" << endl;
}}}
void ViewAllCourses()
{
  cout<<setw(15)<<"Course Code"<<setw(35)<<"Name"<<setw(50)<<"Credit Hours"<<setw(15)<<"Semester"<<endl;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(CourseCode[i][j]!= "")
            {
                cout<<setw(9)<<CourseCode[i][j]<<setw(45)<<CourseName[i][j]<<setw(38)<<crdtHour[i][j]<<setw(18)<<i+1<<endl;
            }
        }
    }
}
void ViewSemesterCourse(int semester)
{
    cout<<setw(4)<<"Course Code"<<setw(4)<<"Name"<<setw(50)<<"Credit Hours"<<endl;
    for(int i = 0; i < 10; i++)
    {
        if(CourseCode[semester-1][i]!= "")
        {
            cout<<setw(4)<<CourseCode[semester-1][i]<<setw(10)<<CourseName[semester-1][i]<<setw(53 - CourseName[semester-1][i].length())<<crdtHour[semester-1][i];
            cout<<endl;}}}




bool saveCourses(){
write1.open(pFileName);
for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(CourseCode[i][j]!= "")
            {
                write1 << CourseCode[i][j]<<","<<CourseName[i][j]<<","<<crdtHour[i][j]<<","<<i+1 << endl;
            }
        }
    }
 write1.close();
return true;
}




bool ifFileExists(const char* fileName)
{
    ifstream ifile(fileName);
    return (bool) ifile;
}

bool loadCourses(){
string line, crscd, crsnm, crdh, smstr;
int intchr, intsmst;

if( !ifFileExists(pFileName) )
{
    cout << "File does not exist. No need to load course info" << endl;
    return false;
}

read1.open(pFileName);
    while ( getline (read1,line) )
    {
      stringstream crdss, smstss;
      stringstream input_stringstream(line);

      getline(input_stringstream,crscd,',');
      cout << "Course code " << crscd << endl;

      getline(input_stringstream,crsnm,',');
      cout << "Course name " << crsnm << endl;

      getline(input_stringstream,crdh,',');
      crdss << crdh;
      crdss >> intchr;
      cout << "credit hour " << intchr << endl;
      crdss << "";

      getline(input_stringstream,smstr,',');
      smstss << smstr;
      smstss >> intsmst;
      cout << "semester " << intsmst << endl;
      smstss << "";

      CourseCode[intsmst-1][cdIdx] = crscd;
      CourseName[intsmst-1][cnIdx] = crsnm;
      crdtHour[intsmst-1][crIdx] = intchr;
      cdIdx++;
      cnIdx++;
      crIdx++;
    }
    read1.close();
    cout << "Course Loaded Successfully\n";
    return true;
}


bool loadUsers()
{
    string line, parsed;

    if( !ifFileExists(pUsersFile) )
    {
        cout << "Sorry, we are unable to run the program, as user data does not exist." << endl;
        return false;
    }

    read1.open(pUsersFile);
    while ( getline (read1,line) )
    {
      stringstream input_stringstream(line);

      getline(input_stringstream,parsed,',');
      cout << "User name " << parsed<< endl;
      usersList[userIdx] = parsed;

      getline(input_stringstream,parsed,',');
      cout << "User password " << parsed << endl;
      passwordsList[userIdx] = parsed;

      userIdx++;
    }
    read1.close();
    cout << "Users Loaded Successfully\n";
    return true;
}


bool validateUsers(string name, string password)
{
    int i;
    for(i = 0; i < 10; i++)
    {
        if( usersList[i].compare(name) == 0 )
        {
            if( passwordsList[i].compare(password) == 0 )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}



void loginScreen()
{
    bool result = false;

    cout << "** WELCOME to University Learning Management System **" << endl;
    cout << "Dear User, current software is intended for authorized users only." << endl;
    cout << "Login to the system to get access." << endl;

    while( result == false )
    {
        string username, password;
        cout << "UserName: ";
        cin >> username;
        cout << "\nPassword:";
        cin >> password;

        result = validateUsers(username, password);
        if( !result )
        {
            cout << "Dear User, Username/password is incorrect. Enter the \
userName/password again to get access to the system" <<endl;
        }
    }
}

void addStudent(string stdNamesList[],string stdRegNoList[],string studentName,string regNo)
{
    stdNamesList[studentIndex]=studentName;
    stdRegNoList[studentIndex]=regNo;
    cout<< "Student has been added successfully"<<endl;
    studentIndex++;
}

int newI;



bool findStudent(string stdRegNoList[],string regNo)
{
    for(int i=0;i<studentIndex;i++)
    {
        if (regNo==stdRegNoList[i])
            newI=i;
            return true;
    }
    return false;
}



void updateStudent(string stdNamesList[],string stdRegNoList[],string studentName,string regNo)
{

           stdRegNoList[newI]=regNo;
           stdNamesList[newI]=studentName;

}



void deleteStudent(string stdNamesList[],string stdRegNoList[],string stdCourseList[][20],string regNo)
{

        result=findStudent(stdRegNoList,regNo);
        if (result == true){
        stdRegNoList[newI]="";
        stdNamesList[newI]="";

            for(int j=0;j<20;j++)
        {
            stdCourseList[newI][j]="";
            break;
        }

        }
        else cout<<" No student to expel "<<endl;
}



void registerCourse(string stdRegNoList[],string stdCourseList[][20],string regNo,string courseCode)

{
    int j=0;
    for(int i=0;i<studentIndex;i++)
    {
        if (stdRegNoList[i]==regNo)
        {while(j<20)
        {
            if(stdCourseList[i][j]==""){
            cout << "Registered Course " << courseCode << endl;
            stdCourseList[i][j]=courseCode;
            break;
        }j++;
        }break;}}}



void unRegisterCourse(string stdRegNoList[], string stdCourseList[][20],string regNo,string courseCode)
{
    for(int i=0;i<studentIndex;i++)
    {
        if (stdRegNoList[i]==regNo){
        for(int j=0;j<20;i++)
        {
           if(stdCourseList[i][j]==courseCode)
            stdCourseList[i][j]=="";
            if(stdCourseList[i][j]=="")
                break;
        }
        break;
        }

    }
}



bool isValidRegistrationNumber(string regNo)  //Acceptable Format 201X-CY-001
{char k='-';
   if (isdigit(regNo[0]&&regNo[1]&&regNo[2]&&regNo[3]&&regNo[8]&&regNo[9]&&regNo[10])&&(regNo[4],regNo[7]==k)&&isalpha(regNo[5]&&regNo[6]))
    return true;
   else
    return false;
}



bool isValidStudentName(string studentName) // Use same rules as per course name
{
    if(studentName.length()>50)
    {
        return false;
    }
    for(int i=0;i<studentName.length();i++)
    {
        if (!(isspace(studentName[i])||(isalpha(studentName[i]))))
            return false;
    }
    return true;
}




bool saveStudents(string stdRegNoList[],string StdNameList[],string StdCourseList[][20])
{
write2.open(pStudentFile);

for(int i=0;i<20;i++){
    if(stdRegNoList[i] != ""){
    write2 << stdRegNoList[i]<<","<<StdNameList[i]<<endl;

    for(int j=0;j<20;j++){
    if(StdCourseList[i][j] != ""){
    if(j != 0) {
        write2 << ",";
    }
    write2<<StdCourseList[i][j];}
    else { break;}
}
     write2 << endl;
}
else { break;}
}
write2.close();
return true;
}




bool LoadStudents(string RegNoList[],string StdNameList[],string StdCourseList[][20])
{
     string line, parsed;
     bool regNameLine = true;

    if( !ifFileExists(pStudentFile) )
    {
        cout << "Sorry, we are unable to run the program, as student data does not exist." << endl;
        return false;
    }

    read2.open(pStudentFile);
    while ( getline (read2,line) )
    {

      stringstream input_stringstream(line);
      if (regNameLine == true)
      {
      getline(input_stringstream,parsed,',');
      cout << "Reg. No " << parsed<< endl;
      RegNoList[studentIndex] = parsed;

      getline(input_stringstream,parsed,',');
      cout << "Name " << parsed << endl;
      StdNameList[studentIndex] = parsed;
      regNameLine = false;
      }
      else
      {
          int j = 0;
          while(j < 20)
          {
            parsed = "";
            getline(input_stringstream,parsed,',');
            if (parsed != "")
            {
                cout << "Courses are " << parsed << endl;
                StdCourseList[studentIndex][j] = parsed;
            }
            else { break;}
            j++;
          }
          studentIndex++;
          regNameLine = true;
      }
      }
    read2.close();
    cout << "Students Loaded Successfully\n";
    return true;
}




void menu()
{
    cout << "\n\nYou have successfully logged into the system" << endl;
    cout << "Choose the following option" << endl;
    cout << "1     Add Course" << endl;
    cout << "2     Update Course" << endl;
    cout << "3     Delete Course" << endl;
    cout << "4     View All Courses" << endl;
    cout<<  "5     View Courses of a Semester"<<endl;
    cout<<  "6     Add New Student"<<endl;
    cout<<  "7     Update Student"<<endl;
    cout<<  "8     Delete Student"<<endl;
    cout<<  "9     View All Students"<<endl;
    cout<<  "10    Register All course For student"<<endl;
    cout<<  "11    Unregister the course for student"<<endl;
    cout<<  "12    logout of the student"<<endl;
    cout<<  "13    Exit Program"<<endl;

}

int main()
{
string stdNamesList[20];
string stdRegNoList[20];
string stdCourseList[20][20];
bool result;
string cd,code,cdd,regNo,CourseCode;
string name,studentName;
int semester;
int credit;
int n;
    result=loadCourses();
    result = loadUsers();
    result=LoadStudents(stdRegNoList,stdNamesList,stdCourseList);

    if(!result)
    {
        cout<<"Program exit"<<endl;
        return 0;
    }
int option,opt;
    cout<<"Choose the option for login "<<endl;
    cout<<"1  Admin"<<endl;
    cout<<"2  Student"<<endl;
    cout<<"Enter option"<<endl;
    cin>>option;
    if (option==1){
    loginScreen();
    menu();             //menu

    cout<<"Choose the option:"<<endl;
    cin >> n;
    startError();
    while(n != 13)
    {
    switch(n){
case 1:
    {
    cout << "Course Code: ";
    cin >> code;
    result = isValidCourseCode(code);
    if (result==true){
    cout << "Course Name: ";
    cin.ignore();
    getline(cin, name);
    result= isValidCourseName(name);
    if (result==true){
    cout << "Credit hours: ";
    cin >>credit;
    result=isValidCreditHours(credit);
    if (result==true){
    cout << "Semester: ";
    cin >>semester;
    result=isValidSemester(semester);
    if (result==true){
    AddCourse(code,name,credit,semester);}}}}
    }
    break;
case 2:{
       cout << "enter course code: ";
     cin >>cd;
     result = isValidCourseCode(cd);
     if (result==true){
     bool res = findCourseCode(cd);
     if (res==true){
     cout << "enter course name: ";
     cin.ignore();
    getline(cin,name);
     result= isValidCourseName(name);
    if (result==true){
       cout << "Credit hours: ";
        cin >>credit;
        result=isValidCreditHours(credit);
    if (result==true){
         cout << "Semester: ";
           cin >>semester;
           result=isValidSemester(semester);
    if (result==true){
    UpdateCourse(cd,name,credit,semester);}}}}}}
    break;
case 3:{
     cout << "enter course code: ";
     cin >>cdd;
     bool res = findCourseCode(cdd);
     if (res==true)
     {
    DeleteCourse(cdd);}}
    break;
case 4:
    ViewAllCourses();
    break;
case 5:{
    cout << "Enter the semester: ";
    cin >> semester;
    result=isValidSemester(semester);
    if (result==true){
    ViewSemesterCourse(semester);}}
    break;
case 6:
    {
      cout<<"  Enter student name "<<endl;               //string stdNamesList[],string stdRegNoList[],string studentName,string regNo
      cin>>studentName;
      result=isValidStudentName(studentName);
      if(result==true){
      cout<<"Enter the registration number of the student"<<endl;
      cin>>regNo;
      addStudent(stdNamesList,stdRegNoList,studentName,regNo);
                      }
    }
    break;
case 7:
    {

    cout<<"Enter registration Number of the student to edit"<<endl;
    cin>>regNo;
    findStudent(stdRegNoList,regNo);
    result=findStudent(stdRegNoList,regNo);
    if (result==true){
    cout<<"Enter new reg no."<<endl;
    cin>>regNo;
    result=isValidRegistrationNumber(regNo);
    if (result==true){
     cout << "Enter Student name to update "<<endl;
    cin>>studentName;
    result=isValidStudentName(studentName);
    if (result==true)
    updateStudent(stdNamesList,stdRegNoList,studentName,regNo);
    }
    }
    }

    break;
case 8:
    {
              cout<<"Enter reg. No of the student to delete";
              cin>>regNo;

              deleteStudent(stdNamesList,stdRegNoList,stdCourseList,regNo);                                      //string

    }
    break;
case 9:
    {
        for(int i=0;i<20;i++)
        {
            cout<<stdNamesList[i]<<endl;
            if (stdNamesList[i]=="")
            break;
        }
    }
    break;
case 10:
    {
        cout<<"Enter registration number of the student"<<endl;
        cin>>regNo;
        cout<<"Enter course code to assign"<<endl;
        cin>>CourseCode;
        result=isValidCourseCode(CourseCode);
        if(result==true){
        cout << "Registering Course"<<endl;
        registerCourse(stdRegNoList,stdCourseList,regNo,CourseCode);}
    }
    break;
    case 11:
    {
        cout<<"Enter registration number of the student"<<endl;
        cin>>regNo;
        cout<<"Enter course to delete "<<endl;
        cin>>CourseCode;
        unRegisterCourse(stdRegNoList,stdCourseList,regNo,CourseCode);
    }
    break;
case 12:
    {
        loginScreen();
        menu();
    }
    break;
    }
    menu();
    cout<<"\n\nChoose the option:"<<endl;
    cin >> n;
    }
    cout<<"Program exit"<<endl;
    cout<<"Saving the course"<<endl;
    result=saveCourses();
   result=saveStudents(stdRegNoList,stdNamesList,stdCourseList);}



   else if(option==2)
   {
        cout<<" Enter 1 to view registered course"<<endl;
        cout<<" Enter 2 to logout of the system"<<endl;
        cout<<" Enter 3 to exit"<<endl;
        cout<<" Choose option:"<<endl;
        cin>>opt;
        if(opt==1)
        {
            for(int i=0;i<20;i++)
            for(int j=0;j<20;j++)
            cout<<stdCourseList[i][j]<<endl;
        }
            else if(opt==2)

        {
        loginScreen();
        menu();
        }

            else if(opt==3)
        {
            return 0;
        }
   }
    return 0;
}



/*
Shubnam Pillay.