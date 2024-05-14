//DSA project: Implementation of simple 2048 game using c++. 
//Github: https://github.com/SChakraborty04
//Initial Commit: 5/15/24:00:00am
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

//Only used for graphical purposes. Used for bold letters.

ostream& bold_on(ostream& os)
{
    return os << "\e[1m";
}

ostream& bold_off(ostream& os)
{
    return os << "\e[0m";
}

//Starting of 2048 C++ implementation.

//struct is used to represent 2048 game
struct G2048{
    int board[4][4];
    //Used default constructor for calling init method.
    G2048(){
        init();
    }
    //Check if 2048 is reached.
    bool check_2048(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(board[i][j]==2048)
                return true;
            }
        }
        return false;
    }
    //Calculate score of the game.
    int cal_score(){
        int x=0;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                x+=board[i][j];
            }
        }
        return x;
    }
    //Print the board.
    void print(){
        int x=cal_score();
        cout<<"\nYour current "<<bold_on<<"Score: ("<<x<<")"<<bold_off<<"\n\n";
        cout<<"Playing well keep up the pace.\n";
        cout<<"_____________________\n";
        for(int i=0;i<4;i++){
            cout<<"|";
            for(int j=0;j<4;j++){
                if(board[i][j]!=0)
                cout<<setw(4)<<board[i][j]<<"|";
                else
                cout<<setw(4)<<" "<<"|";
            }
            cout<<"\n---------------------\n";
        }
    }
    //The main logic implementation.
    void swipe(int arr[4]){
        int last=4;
        int merge=0;
        for(int i=3;i>=0;i--){
            if(arr[i]!=0){
                if(merge){
                    if(arr[i]==arr[last]){
                        arr[last]*=2;
                        arr[i]=0;
                        merge=0;
                    }
                    else{
                    last--;
                    arr[last]=arr[i];
                    if(i!=last)
                    arr[i]=0;
                    merge=1;
                    }
                }
                else{
                    last--;
                    arr[last]=arr[i];
                    if(i!=last)
                    arr[i]=0;
                    merge=1;
                }
            }
        }
    }
    //Check if the game is ended.
    bool end_game(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(board[i][j]==0)
                return false;
            }
        }
        return true;
    }
    //Random number generation.
    void random_gen(){
        while(1){
        int i=rand()%4;
        int j=rand()%4;
        if(board[i][j]==0){
            int ch=rand()%2;
            if(ch==0)
            board[i][j]=2;
            else
            board[i][j]=4;
            return ;
        }
        }
    }
    //Initialize the board.
    void init(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                board[i][j]=0;
            }
        }
        random_gen();
        random_gen();
    }
    //Logic for upward movement.
    bool up(){
        for(int col=0;col<4;col++){
            int arr[4];
            for(int row=0;row<4;row++)
            arr[3-row]=board[row][col];
            swipe(arr);
            for(int row=0;row<4;row++)
            board[row][col]=arr[3-row];
        }
        random_gen();
        return if_end();
    }
    //Logic for downward movement.
    bool down(){
        for(int col=0;col<4;col++){
            int arr[4];
            for(int row=0;row<4;row++)
            arr[row]=board[row][col];
            swipe(arr);
            for(int row=0;row<4;row++)
            board[row][col]=arr[row];
        }
        random_gen();
        return if_end();
    }
    //Logic for left movement.
    bool left(){
        for(int row=0;row<4;row++){
            int arr[4];
            for(int col=0;col<4;col++)
            arr[3-col]=board[row][col];
            swipe(arr);
            for(int col=0;col<4;col++)
            board[row][col]=arr[3-col];
        }
        random_gen();
        return if_end();
    }
    //Logic for right movement.
    bool right(){
        for(int row=0;row<4;row++){
            int arr[4];
            for(int col=0;col<4;col++)
            arr[col]=board[row][col];
            swipe(arr);
            for(int col=0;col<4;col++)
            board[row][col]=arr[col];
        }
        random_gen();
        return if_end();
    }
    //Check if the game is ended.
    bool if_end(){
        if (end_game())
        return false;
        else
        return true;
    }
    //Logic if the game ends.
    void end_move(){
        print();
        char c;
        cout<<"Game Over\n";
        int x=cal_score();
        cout<<"Your final "<<bold_on<<"Score: ("<<x<<")"<<bold_off<<"\n";
        cout<<"Do you want to play more?(y/n) ";
        cin>>c;
        if(c=='y'||c=='Y'){
            init();
        }
        else{
            cout<<"Thanks for playing.\nExiting in 5 seconds.";
            Sleep(5000);
            exit(0);
        }
    }
};

int main(){
    srand(time(0));
    G2048 game;
    cout<<"Simple "<<bold_on<<"2048"<<bold_off<<" implementation in C++ by "<<bold_on<<"Sandipan Chakraborty | Github: @SChakraborty04"<<bold_off<<"\n";
    while(1){
        if(game.check_2048()){
            game.print();
            cout<<"Congratulations you have reached "<<bold_on<<"2048"<<bold_off<<".\n";
            int x=game.cal_score();
            cout<<"\nYour final "<<bold_on<<"Score: ("<<x<<")"<<bold_off<<"\n\n";
            break;
        }
        game.print();
        char ch;
        cout<<"Enter your move (U/u-> Up; D/d-> Down; L/l-> Left; R/r-> Right): ";
        cin>>ch;
        if(ch=='U'||ch=='u'){
            if(!game.up()){
                game.end_move();
            }
        }
        else if(ch=='D'||ch=='d'){
            if(!game.down()){
                game.end_move();
            }
        }
        else if(ch=='L'||ch=='l'){
            if(!game.left()){
                game.end_move();
            }
        }
        else if(ch=='R'||ch=='r'){
            if(!game.right()){
                game.end_move();
            }
        }
        else{
            cout<<"Invalid Input\n";
        }
    }
}