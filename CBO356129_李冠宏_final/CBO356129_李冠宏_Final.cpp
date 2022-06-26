#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class eCash{
    public:
        //constructor
        eCash(){
            for(int i=0; i<100; i++){
                money = 0;
            }
            User_number = 0;
        }

        //destructor
        ~eCash(){}

        void login(){
            FILE *read;
            FILE *write;
            string read_ID;
            int read_money;
            int i = 0;

            cout << "eCash: 請輸入您的帳號: ";
            cin >> ID;

            read = fopen("Users.txt", "r");
            write = fopen("Users.txt", "w");

            //first time
            cout << "帳號不存在, 第一次使用!" << endl;
            User_number++;
            fprintf(write, "%s\t%d\n", ID, 0);

            //while loop
            while(i <= User_number){
                fscanf(read, "%s\t%d\n", read_ID, &read_money);
                if(ID == read_ID){
                    cout << "帳號開啟完成!" << endl;
                    money = read_money;
                }
                if(feof(read)){
                    cout << "帳號不存在, 第一次使用!" << endl;
                    User_number++;
                    money = 0;
                    fprintf(write, "%s\t%d\n", ID, 0);
                }
                i++;
            }

            fclose(read);
            fclose(write);
        }

        void logout(){

        }

        void store(int m){
            money += m;
        }

        void pay(int m){
            money -= m;
        }

        void display(){
            cout << "eCash: 您尚有" << money << "元" << endl;
        }

        int GetMoney(){
            return money;
        }

        string getID(){
            return ID;
        }

    private:
        string ID;
        int money;
        int User_number;
};

int main(void){
    char input;
    int m;
    eCash wallet; //make object
    FILE *read;
    FILE *write;

    cout << "=== 歡迎使用eCash ===" << endl;
    wallet.login(); //login
    cout << endl;

    while(1){
        cout << wallet.getID() << "您好，請選擇項目:" << endl;
        cout << "s: 儲值" << endl;
        cout << "p: 消費" << endl;
        cout << "d: 顯示餘額" << endl;
        cout << "q: 離開" << endl;

        cin >> input;

        switch (input){

        //case s
        case 's':

            cout << "請輸入儲存金額:" << endl;
            cin >> m;
            if(m < 0){
                cout << "請輸入大於0的金額" << endl;
                m = 0;
                break;
            }
            wallet.store(m);
            cout << "eCash: 您存了" << m << "元" << endl;
            break;

        //case p
        case 'p':
            cout << "請輸入消費金額:" << endl;
            cin >> m;
            if(m < 0){
                cout << "eCash: 請輸入大於0的金額" << endl;
                m = 0;
                break;
            }
            if(wallet.GetMoney() -m < 0){
                cout << "eCash: 您的錢不夠" << endl;
                break;
            }
            wallet.pay(m);
            cout << "eCash: 您花了" << m << "元" << endl;
            break;

        //case d
        case 'd':
            wallet.display();
            break;

        //case q
        case 'q':
            cout << "謝謝,ByeBye!" << endl;
            return 0;
            break;
        
        default:
            cout << "請輸入有效的指令！" << endl;
            break;
        }
        cout << "請按Enter鍵繼續...";
        getchar();
        fgetc(stdin);
        system("clear");
    }

    return 0;
}