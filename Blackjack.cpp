// ConsoleApplication2.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;


class Card {
    string name;
    int value;
public:
    Card(string name, int value) :name(name), value(value) {};
    
    string getCardName() {
        return name;
    }

    int getCardValue() {
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
        initializeCards();
    };
    
   
    void setCard(vector<Card>& card_vector) {
        int cardValue=0;
        string cardName;

        int x = rand()%13+2;
        if (x < 10) {
            cardValue = x;
            cardName = (char) (x+48);
            card_vector.push_back(Card(cardName, cardValue));
        }
        else {
            switch (x) {
        	case 10:
        		cardValue = 10;
                cardName = "10";
                card_vector.push_back(Card(cardName, cardValue));
                break;
            case 11:
                cardValue = 10;
                cardName = 'J';
                card_vector.push_back(Card(cardName, cardValue));
                break;
            case 12:
                cardValue = 10;
                cardName = 'Q';
                card_vector.push_back(Card(cardName, cardValue));
                break;
            case 13:
                cardValue = 10;
                cardName = 'K';
                card_vector.push_back(Card(cardName, cardValue));
                break;
            case 14:
                cardValue = 11;
                cardName = 'A';
                card_vector.push_back(Card(cardName, cardValue));
            }
        }
    }
    
     void initializeCards(){
    	for (int i = 0; i < 2; i++) {
            setCard(Player);
            setCard(Casino);
        }
    }

    void Draw(vector<Card> myVector) {
    	int card_width = 9;
    	int card_length= 5;
            for (int i = 0; i < card_length; i++) {

                
                for (int j = 0; j < card_width * myVector.size() ; j++) {

                    if ((i == 0||i==(card_length-1))&& (j % card_width != 0)&& (j % card_width != card_width-2)&& (j % card_width != (card_width-1))) {
                            cout << "-";
                    }



                    else if (j % card_width == 0 || j % card_width == (card_width-2)) {
                        cout << "|";
                    }
                    
                    else if (i == (card_length/2) && (j%card_width) == (card_width/2)) {
                        int card_number = j / card_width;
                        //indicates which card is being drawed.
                        if (myVector[card_number].getCardName() == "10") {
                            cout<<"\b";
                            cout<<"10";
                            //because 10 has 2 digits, one backspace is required.
                        }else{
                        	cout << myVector[card_number].getCardName();
						}

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



    void gameRestart(){

        Player.clear();
        Casino.clear();

        initializeCards();
        
    }
    
    int getSum(vector<Card> myVector) {
    	int ace_counter=0;
    	int total_value=0;
    	for (int i = 0; i < myVector.size(); i++) {
        	if(myVector[i].getCardName()=="A"){
        		ace_counter +=1;	
			}
			
			total_value += myVector[i].getCardValue();
        }
        
        for(int i=0;i<ace_counter;i++){
        	if(total_value>21){
        		total_value -= 10;
			}
			
		}
    	return total_value;
    }
    
    bool askDrawCard(){
    	cout << "Do you want one more card?(If yes press y, if no press n)" << endl;
        while(true){
		
    		char player_response;
        	cin >> player_response;
        	if (player_response== 'y') {
            	return true;
        	}else if (player_response == 'n') {
            	return false;
        	}else{
        		cout<<"Oops, wrong button!"<<endl;
			}
		}
    }
    
    
    bool askGameEnd(){
        cout << "Do you want to play one more time?(If yes press y, if no press n)" << endl;
        while(true){
		
    		char player_response;
        	cin >> player_response;
        	if (player_response== 'y') {
            	return false;
        	}else if (player_response == 'n') {
            	cout << "I guess you are out of money. See you!" << endl;
            	return true;
        	}else{
        		cout<<"Oops, wrong button!"<<endl;
			}
		}
	}

    void GameRun() {
        while (true) {
            drawcasino();

            drawplayer();


            if (getSum(Player) > 21) {
            	cout << "You lost the game!" << endl;
                bool game_end = askGameEnd();
                if (!game_end) {
                    gameRestart();
                }else{
                    break;
                }
            }else {

                bool response = askDrawCard();
                
                if (response) {
                    setCard(Player);
                }else {
                    while (getSum(Casino) < 17) {
                            setCard(Casino);
                            drawcasino();
                    }
                            
                    if (getSum(Casino) > getSum(Player)&&getSum(Casino)<=21) {
                        cout << "You lost!" << endl;
                    }else if(getSum(Casino)==getSum(Player)){
                        cout << "It's a tie!" << endl;
                    }else {
                        cout << "You won!" << endl;
                    }
                    
                    gameRestart();

                    bool game_end = askGameEnd();
                    if(game_end){
                    	break;
					}
                    
                }
                
                
            }

            
        }
    }
};



int main()
{
    Game a;
    a.GameRun();
    return 0;
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
