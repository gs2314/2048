#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;


void show_numbers(int game_array[4][4]);
int process_array(int game_array[4][4], char key_stroke);
bool load_game_array(int game_array[4][4], string array_filename);
bool valid_moves(int game_array[4][4]);

struct element_position {
    int x;
    int y;
};


int main(){
    string array_filename="";
    char key_stroke='a';
    int game_array[4][4];
    int array_status=1;
    cout << "enter initial configuration filename:" << endl;
    cin >> array_filename;
    if (!load_game_array(game_array, array_filename)){
        cout << "file not found. using default start configuration";
        array_status=1;
    }
    else{
        if (valid_moves(game_array)){
            array_status=1;
        }
        else{array_status=0;}
    }
    if (array_status){
        show_numbers(game_array);
        cin >> key_stroke;
    }
   while (array_status){
        array_status=process_array(game_array, key_stroke);
        if (array_status==1){show_numbers(game_array);}
        if (array_status){cin >> key_stroke;}
    }
    show_numbers(game_array);
    cout << endl<<  "GAME OVER" <<  endl;
    return 0;
}

bool load_game_array(int game_array[4][4], string array_filename){
    ifstream array_file;
    array_file.open(array_filename.c_str());
    if (!array_file.is_open()){ ///file not found
        for (int i=0;i<4;i++){
            for (int j=0;j<4;j++){
                game_array[i][j]=0;
            }
        }
        game_array[3][3]=2;
        return false;
    }
    else {  ///file found
        for (int i=0, k=0; i<4;i++){
            for (int j=0;j<4;j++){
                array_file >> k;
                game_array[i][j]=k;
            }
        }
        return true;
    }
}

int process_array(int game_array[4][4], char key_stroke){
    element_position zero_position;
    bool has_moved=false;
    vector<element_position> zeros_vector;
    vector<int> valid_numbers;
    unsigned l=0;
    int *array_pointer1=0, *array_pointer2=0;
    int start_point=0, end_point=0, step=0, i=0, j=0, k=0;
    if (key_stroke=='a'){
        start_point = 0;
        end_point = 4;
        step = 1;
        array_pointer1 = &i;
        array_pointer2 = &j;
    }
    else {
        if(key_stroke=='d'){
            start_point = 3;
            end_point = -1;
            step = -1;
            array_pointer1 = &i;
            array_pointer2 = &j;
        }
        else {
            if(key_stroke=='s'){
                start_point = 3;
                end_point = -1;
                step = -1;
                array_pointer1 = &j;
                array_pointer2 = &i;
            }
            else{
                if (key_stroke=='w'){
                    start_point = 0;
                    end_point = 4;
                    step = 1;
                    array_pointer1 = &j;
                    array_pointer2 = &i;
                }
                else {return 2;}
            }
        }
    }
    for (*array_pointer1=start_point;*array_pointer1!=end_point;*array_pointer1+=step){
        valid_numbers.clear();
        for (*array_pointer2=start_point;*array_pointer2!=end_point;*array_pointer2+=step){
            if (game_array[i][j]!=0) {valid_numbers.push_back(game_array[i][j]);}
        }
        for (*array_pointer2=start_point, k=0, l=0; l<valid_numbers.size();k++, *array_pointer2+=step, l++){
            if (valid_numbers[k]==valid_numbers[k+1] && l+1<valid_numbers.size()){
                game_array[i][j]=2*valid_numbers[k];
                k++;
                l++;
                has_moved=true;
            }
            else {
                if (game_array[i][j]!=valid_numbers[k]){has_moved=true;}
                game_array[i][j]=valid_numbers[k];
            }
        }
        valid_numbers.clear();
        for (;*array_pointer2!=end_point;*array_pointer2+=step){
            game_array[i][j]=0;
            zero_position.x=i;
            zero_position.y=j;
            zeros_vector.push_back(zero_position);
        }
    }
    if (has_moved){
        l=rand()%zeros_vector.size();
        game_array[zeros_vector[l].x][zeros_vector[l].y]=2;
        zeros_vector.clear();
        if (valid_moves(game_array)){return 1;}
        else {return 0;}
    }
    else {
        if (zeros_vector.size()){return 2;}
        else {
            if (valid_moves(game_array)){return 2;}
                else {return 0;}
        }
    }
}

bool valid_moves(int game_array[4][4]){
    int i,j;
        for ( i=0;i<4;i++){
            for ( j=0;j<3;j++){
                if (game_array[i][j]==game_array[i][j+1] || game_array[i][j]==0){
                    i=100;
                    j=100;
                }
            }
            if (game_array[i][j+1]==0){i=100;}
        }
        if (i<100){
            for (i=0;i<4;i++){
                for (j=0;j<3;j++){
                    if (game_array[j][i]==game_array[i][j+1]){
                        i=100;
                        j=100;
                    }
                }
            }
        }
        if (i=100){return 1;}
        else {return 0;}
}

void show_numbers(int game_array[4][4]){
    for (int i=0;i<4;i++){
        cout << endl ;
        for (int j=0;j<4;j++){cout << game_array[i][j] << "\t";}
    }
    cout << endl;
}
