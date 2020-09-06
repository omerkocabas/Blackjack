// ConsoleApplication2.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;


class Card {
    char name;
    int value;
public:
    Card(char name, int value) :name(name), value(value) {};
    
    char getMyName() {
        return name;
    }

    int getMyValue() {
        return value;
    }

};


class Game {

    vector<Card> Player;
    vector<Card> Casino;



public:
    Game() {
        srand(time(0));
        cout << "Welcome to Omer's Casino!" << endl;
        cout << "For now we only have Blackjack without split. I hope you enjoy the time. Remember casino always wins :P" << endl;
        for (int i = 0; i < 2; i++) {
            setCard(Player);
            setCard(Casino);
        }
    };
    void setCard(vector<Card>& myVector) {
        int myVal=0;
        char myName;

        int x = rand()%13+2;
        if (x <= 10) {
            myVal = x;
            myName = (char) x;
            myVector.push_back(Card(myName, myVal));
        }
        else {
            switch (x) {
            case 11:
                myVal = 10;
                myName = 'J';
                myVector.push_back(Card(myName, myVal));
                break;
            case 12:
                myVal = 10;
                myName = 'Q';
                myVector.push_back(Card(myName, myVal));
                break;
            case 13:
                myVal = 10;
                myName = 'K';
                myVector.push_back(Card(myName, myVal));
            case 14:
                myVal = 11;
                myName = 'A';
                myVector.push_back(Card(myName, myVal));
            }
        }
    }

    void Draw(vector<Card> myVector) {
            for (int i = 0; i < 5; i++) {

                
                for (int j = 0; j < 8 * myVector.size()+2 ; j++) {

                    if ((i == 0||i==4)&& (j % 9 != 0)&& (j % 9 != 7)&& (j % 9 != 8)) {
                            cout << "-";
                    }



                    else if (j % 9 == 0 || j % 9 == 7) {
                        cout << "|";
                    }
                    
                    else if (i == 2 && j%9 == 4) {
                        int temp = j / 9;
                        if (myVector[temp].getMyValue() >= 10) {
                            cout<<"\b";
                        }
                        cout << myVector[temp].getMyValue();
                        //cout << "J";
                    }

                    else {
                        cout << " ";
                    }
                }
                cout << endl;

            }
     }

    void drawplayer() {
        cout << "You have: " << endl;
        Draw(Player);
    }

    void drawcasino() {
        cout << "Casino has: " << endl;
        Draw(Casino);
    }



    void gameEnd(){

        Player.clear();
        Casino.clear();

        for (int i = 0; i < 2; i++) {
            setCard(Player);
            setCard(Casino);
        }
        
    }
    
    int getSum(vector<Card> myVector) {
        int sum = 0;
        for (int i = 0; i < myVector.size(); i++) {
            sum += myVector[i].getMyValue();
        }
        return sum;
    }

    void GameRun() {
        while (true) {
            drawcasino();

            drawplayer();


            if (getSum(Player) > 21) {
                cout << "You lost the game! Better luck next time." << endl;
                cout << "Do you want to play one more time?(If yes press y, if no press n)" << endl;
                char q;
                cin >> q;
                if (q== 'y') {
                    gameEnd();
                }
                else if (q == 'n') {
                    cout << "I guess you are out of money. See you!" << endl;
                    break;
                }
            }
            else {

                cout << "Do you want one more card?(If yes press y, if no press n)" << endl;
                char u;
                cin >> u;
                if (u == 'y') {
                    setCard(Player);
                }
                else if (u == 'n') {
                    while (true) {
                        if (getSum(Casino) < 17 && getSum(Casino) < getSum(Player)) {
                            setCard(Casino);
                            drawcasino();
                        }
                        else {
                            
                            if (getSum(Casino) > getSum(Player)&&getSum(Casino)<=21) {
                                cout << "You lost!" << endl;
                            }
                            else if(getSum(Casino)==getSum(Player)){
                                cout << "It's a tie!" << endl;
                            }
                            else {
                                cout << "You won!" << endl;
                            }

                            cout << "Do you want to play one more time?(If yes press y, if no press n)" << endl;
                            char q;
                            cin >> q;
                            if (q == 'y') {
                                gameEnd();
                            }
                            else if (q == 'n') {
                                cout << "I guess you are out of money. See you!" << endl;
                                break;
                            }
                            break;
                        }
                    }
                }
                else {
                    cout << "You pressed a wrong button!" << endl;
                }
            }

            
        }
    }
};



int main()
{
    Game a;
    a.GameRun();
  
}

// Programı çalıştır: Ctrl + F5 veya Hata Ayıkla > Hata Ayıklamadan Başlat menüsü
// Programda hata ayıkla: F5 veya Hata Ayıkla > Hata Ayıklamayı Başlat menüsü

// Kullanmaya Başlama İpuçları: 
//   1. Dosyaları eklemek/yönetmek için Çözüm Gezgini penceresini kullanın
//   2. Kaynak denetimine bağlanmak için Takım Gezgini penceresini kullanın
//   3. Derleme çıktısını ve diğer iletileri görmek için Çıktı penceresini kullanın
//   4. Hataları görüntülemek için Hata Listesi penceresini kullanın
//   5. Yeni kod dosyaları oluşturmak için Projeye Git > Yeni Öğe ekle veya varolan kod dosyalarını projeye eklemek için Proje > Var Olan Öğeyi Ekle adımlarını izleyin
//   6. Bu projeyi daha sonra yeniden açmak için Dosya > Aç > Proje'ye gidip .sln uzantılı dosyayı seçin
