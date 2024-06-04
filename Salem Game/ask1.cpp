#include "std_lib_facilities.h"
#include <cstdlib>
#include <time.h>
#include <string>
#include <sstream>
#include "include/rounds.h"
using namespace std;










// helper function for choosing one !!!ALIVE!!! player, then it returns the chosen player
// Int SELFFF displays the player that has to choose, so that the function will exclude him as an option
int choose_player(vector<string> PLAYERS,vector<int> DEADMEN,int SELFFF){

    int chosen;

    //print all the alive players
    for(int i=0; i<7; i++){

        if( DEADMEN[i]==1){

            // if SELFFF== i, loop continues and the name is not displayed as option
            if( i == SELFFF ){

                continue;
            }
            //if SELLF!=i display other alive players
            else
                cout<<"( "<< i <<" ) "<< PLAYERS[2*i]<<endl;
        }

    
    }

    // loop for error correction
    while(1){

        cout<<"Please type the number of the player that you would like to choose:\n";
        cin >> chosen;

        // error correction if
       // try{
            if ( DEADMEN[chosen]!= 1 || chosen<0 || chosen>7  || chosen== SELFFF){

                cout<<"WRONG INPUT, please try again\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

        break;

        
       
    }
        
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return chosen;
}





// menu finction showcasing how many peaple are left/ and their roles, how many are dead, last player to leave and  
int menuU( vector<string> PLAYERS,vector<int> DEADMEN){



        string str;
        int vl2go=0;
        int inf;    
        cout<<"-Info Menu:\n( 1 ) Show alive players.\n( 2 ) Show alive players and their roles\n( 3 ) Show dead players\n( 4 ) Show the last-to-die player\n"
        <<"( 5 ) Exit Info Menu\nEnter the number for the desired choice of info:     ";

        //exception time
        try{
        
            getline(cin, str);
            cout<<endl;
            if( str.empty())    throw 1;

            stringstream ss;
            ss<< str;
            ss>> inf;
            if(inf<1     || inf>5    )   throw 1;
           


        }catch( ...){


            
            cout<<"-Wrong input. Please enter integer ranging from 1-5.\n"<<endl;

            
            
            vl2go= 0;
            inf=0;
        }

        
        // error detection, if there is an error detected 

        
            // choise n1: Show alive players
         if( inf == 1){
            
            cout<< "-The players that are still alive are:\n";
           
            for(int i=0; i<7; i++){

                if( DEADMEN[i]==1){

                    cout<<PLAYERS[2*i]<<endl;
                   
                }
            } 
            vl2go=  0;
        }

        // choice no2: show alive players and their roles
        else if(inf == 2){

            cout<< "-The players that are still alive are:\n";

            for(int j =0; j<7; j++){
                
                if(DEADMEN[j]==1){

                    cout<<"player:  "<<PLAYERS[j*2]<<"  role: "<< PLAYERS[(2*j)+1]<<endl;
                    
                }
            }

             vl2go =  0;
        }

        //coice no3: show all dead players
        else if( inf == 3){

            cout<< "-The players that are still dead are:\n";

            for(int k=0; k<7; k++){

                if ( DEADMEN[k]< 1 ){
                    
                    cout<<PLAYERS[2*k]<<endl;
                }
            }
        
            vl2go=0;

        }

        // choice  n4: show last victim
        else if(inf==4){

            cout<< "-The last victim is:\n";

            for(int l=0; l<7; l++){

                if( DEADMEN[l]== -1){

                    cout<< PLAYERS[2*l]<<endl;
                }
            }
        
             vl2go=0;

        }

        //choice n5: exit info menu
        else if( inf == 5){

            vl2go= 1;
        }
        //    cin.clear();
          //  cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return vl2go;
    

}



// function for choosing a player as the gangster and an other as the doctor
void salem_init(vector<string> &player){
    
    int gnk, doc;
    string GNKK="Gangster";
    string DOCC="Doctor";

    srand( time(0) );
    //first we pick the gangster
    
    gnk= rand()%7; //by using rand%8 we generate number ranging form 0-6 ( total of 7 possible numbers )

    player[(gnk*2)+1]=GNKK ;
    //now we pick the doctor
   
   
    doc= rand()%7;

    if( doc== gnk){

        if( ( doc+1)> 5 || doc==6)  doc--;
        else doc ++;
    }

    player[(doc*2)+1]=DOCC;     
    
    // time to declare the rest of the players as "polites"
    for( int i=0; i<7; i++){
        
        // make the rest of the players ( for i != doc && i=! gnk) polites
        if( i == doc || i == gnk ){
            continue;
        }

        player[(2*i)+1]="Politis";
    
    }    



}


// function for the night phase of the game
void night_phase( vector<string> PLAYERS, vector<int> &DEADMEN){

    int gnk_chosen,doc_chosen, GANGSTER,DOCTOR;
    string killer="Gangster";
    string saver="Doctor";
    cout<<"---The phase of the night has come---\n";


    // first we find the doctor and the gangster
    for(int i=0 ;   i<7;    i++){


        if(PLAYERS[(2*i)+1].compare(killer)==0){
            GANGSTER=i;
        }
        else if( PLAYERS[(2*i)+1].compare(saver)==0){
            DOCTOR=i;
        }
    }

    // now lets get down to business


    //for both choices we call a helper function that has already error detection methods implemented within: choose_player()
    cout<<"---The Gangster may chooce a player to kill---\n";
    gnk_chosen=choose_player(PLAYERS,DEADMEN,GANGSTER);


//  check if doctor is alive
    if(DEADMEN[DOCTOR]==1){

         cout<<"---The Doctor may chooce a player to save---\n";
         doc_chosen= choose_player(PLAYERS,DEADMEN,DOCTOR);


        // if doc and gnk chose different players, the one that the gangster chose will die
        if( doc_chosen!= gnk_chosen){

            cout<<"---player: "<< PLAYERS[2*gnk_chosen]<<" is dead---\n";

            // replace last dead value from -1 to 0
            for(unsigned int k=0; k<DEADMEN.size(); k++){

                if( DEADMEN[k]== -1){

                    DEADMEN[k]=0;
                    break;
                }
            }
        
        // replace the new last dead value from 1 to -1
            DEADMEN[gnk_chosen]=-1;
        }
        //else if doc and gnk chose the same player, nothing happens
        else
        cout<<"---No one died tonight---\n";
    }
    

    else 

    cout<<"---player: "<< PLAYERS[2*gnk_chosen]<<" is dead---\n";

    // replace last dead value from -1 to 0
    for(unsigned int k=0; k<DEADMEN.size(); k++){

        if( DEADMEN[k]== -1){

            DEADMEN[k]=0;
            break;
            }
        }
    
    // replace the new last dead value from 1 to -1
        DEADMEN[gnk_chosen]=-1;
    
}







//helper function for the day_phase voting

// this function serves as a voting system, returns:
//--0 if one player is elected
//-1 if everyone has the same amount of votes
// 1 if more than one players ( but not all of the players) have same max amount of votes

// also changes the vector arguement: to_vote so that when the function returns, the vector to_vote
// has the names that have been elected with max votes ( either 1 or more)

int voting_session(vector<string> &voters, vector<string> &to_vote){
    string in_putt;
    unsigned int i=0,j=0;
    int vTT,cnt=0, max=0, more_max=0;
    int VTS[7]={0,0,0,0,0,0,0}; // hold the amount of votes for every player ( each position of the array matches each player
                                // 0 position: 0th player,1 position: )
    vector<int> t_emporalll;    // contains the numbers that match to the players, error checking helper vector
    vector<string> mdiatorr;    // contains the players with max votes

// a loop where each VOTER votes a to_vote player
    while(i< voters.size()){



            cout<<"\n\n"<<"-Player: "<< voters[i]<<" is voting\n";

            for(j=0; j< to_vote.size(); j++){

                if ( voters[i].compare(to_vote[j] ) == 0 )   continue;   // this if excludes the option fot a player
                                                                       // to vote himself

                cout<<"( "<< j<< " ) "<< to_vote[j]<< endl;

                t_emporalll.push_back(j);       // adds the number of the to_vote player, for error checking
                
            }

        cout<<"Please enter the number of the person you want to vote--->   ";
        
        
        
        getline(cin, in_putt);
        // if input is empty: error message
        if( in_putt.empty() ){

            cout<<"wrong Input, please try again\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            t_emporalll.clear();
            continue;

        }

        // converting string to int using stringstream
        stringstream ss;
        ss<< in_putt;
        ss>>vTT;

        
        //error checking loop: is input within the options? if vTT is not one of option, error message

        for(j=0; j<t_emporalll.size(); j++){

            if(vTT== t_emporalll[j]) cnt++;
            
        }

        if( cnt>1 || cnt==0 ){

            cout<<"wrong Input, please try again\n";

            cnt=0;

            t_emporalll.clear();
            
            continue;
        }
        //if chosen vote passes the error checks

        VTS[vTT]++;        // add one vote to the according to_vote player

        i++;                // next player has to vote i++
        cnt=0;              //cnt reset
        t_emporalll.clear();        // temporall clear, ready for next player

    }

    
    
    // this loop  gets the max votes
    for(i=0; i<to_vote.size(); i++){

        if( VTS[i]>max )    max= VTS[i];

        //cout<<"player: "<<to_vote[i]<<" has "<< VTS[i]<< " votes\n";
    }

    // this loop shows if there are people with the same max votes
    for( i=0; i< to_vote.size(); i++){

        if( VTS[i]== max)   more_max++;
    }


//  if everyone has the same amount of votes, voting session does not elect anyone, voting session stops
    if(more_max==to_vote.size())    return -1;



//  loop that stores max voted players in mdiatorr, then to_vote. clear and then puts the max voted players to to_vote
// for function return

    for(i=0; i< to_vote.size(); i++){

        if(VTS[i]==max){
            mdiatorr.push_back(to_vote[i]);
        }
     }

    to_vote.clear();


    // add max players ( only) to to_vote vector
    for(i=0; i< mdiatorr.size(); i++){

        to_vote.push_back(mdiatorr[i]);
    }



//  more than one people have max votes, voting session must be ressumed
     if(more_max>1)  {
        
        return 1;
    }

    
// else, a player has been elected to leave

    
    return 0;


}




// day phase: this function makes the players vote, stores the votes to an array votes[ index ]where,
// to index antistoixei ston analogo paixti, 0= 1os paixtis, 1=2os paixtis ktl
//i sinartisi episis briskei to megisto, ean iparxoun megistes isobathmies i an den yparxei pleiopsifia( oloi exoun tous idious psifous)
void day_phase(vector<string> playerss,vector<int> &deadmen){

    int rslt;
    vector<string> to_be_voted;
    vector<string> voters;
    unsigned int i, j;


    cout<<"\n---The phase of the day has come---\n\n--Vote who you think the gangster is--\n\n";

    // all the alive players have to vote to find the gagster,
    // this loop fills the vectors voters, to_be_voted with all the alive players;
    for( i=0; i<deadmen.size(); i++){

        if ( deadmen[i]== 1){

            voters.push_back( playerss[2*i] );
            to_be_voted.push_back( playerss[2*i] );
        }
    }
    
 
    // function call for the start of the voting session
    rslt= voting_session(voters, to_be_voted);

    

    if( rslt==0){
//      player was voted immidiatly
         

        cout<<"Player: "<<to_be_voted[0]<<" was elected and is now dead\n";

// time to reset the last-dead ( set ex-last dead deadmen value to 0)
        for(j=0; j< 7 ; j++){

            if(deadmen[j]== -1 ){

                deadmen[j]=0;
                                    break;
            }
        } 

            //  declare the elected player as last dead ( deadmen value = -1)
        for(i=0; i<7; i++){
            if( playerss[2*i].compare( to_be_voted[ 0 ] )== 0 )     deadmen[i]=-1;
    
        }        









    }

    // if everyone is elected ( everyone has same votes)
    else if( rslt == -1){

        cout<<"No one was elected, everyone voted everyone\n";
    }

    // if more than one players have been elected ( but not all of the players)
    // voting session must be resume to chose one of the top elected players
    // if the voting session again does not elect a single player, no one gets elected
    else if( rslt==1 ){

        cout<<"More than one people elected,Please vote again\n";
        rslt=voting_session(voters, to_be_voted);


        if (rslt == 0){

            cout<<"Player: "<<to_be_voted[0]<<" was elected and is now dead\n";

// time to reset the last-dead ( set ex-last dead deadmen value to 0)
            for(j=0; j< 7 ; j++){

                if(deadmen[j]== -1 ){

                    deadmen[j]=0;
                    break;
                }
            }

            //  declare the elected player as last dead ( deadmen value = -1)
            for(i=0; i<7; i++){

                if( playerss[2*i].compare( to_be_voted[ 0 ] )== 0 )     deadmen[i]=-1;

            }
        }


        else if( rslt== 1 || -1){

            cout<<"No one was elected, again\n";
        }
        
    }

}

// helper function that checks if gangster is alive
int gankster_check( vector<string> playerss, vector<int> deadmen){

    for( unsigned int i=0; i< 7 ; i++){

        if( playerss[ (2*i)+1 ].compare("Gangster") == 0 ){

            if ( deadmen[i]==0 || deadmen[i]==-1)   {

                
                return 1;
            }
        }
    }

     return 0;
}



int main(){

    vector<Rounds> round;
    Rounds testing;
    int doc_index,gang_index, menuU_in=0;
    int countt=0,status=0;
    unsigned int i;
    //vector that hold the initialized players and their roles
    vector<string>  players_n_roles={"AKIS","","MANOLIS","","KOSTAS","","EURIDIKI","","ANNA","","GIOTA","","ALEX",""};
    
    // vector that holds the alive or dead status of every player 
    //0 == DEAD     1== ALIVE       -1 LAST DEAD
    vector<int> dead_alive={1,1,1,1,1,1,1};


    cout<<"--- WELCOME TO SALEM!---\nREADY\nSTEADY\nGO !!!\n";
    salem_init(players_n_roles);


    // for convinience we find in witch index is gangster and doc stored
    for(  i=0; i<7; i++){
        if( players_n_roles[ (2*i)+1 ].compare("Gangster")==0 ) gang_index= i;
        if(  players_n_roles[ (2*i)+1 ].compare("Doctor")==0 ) doc_index=i;
    }

  


    //the game start and keeps going as long as the gangster is alive
   /* menuU(players_n_roles,dead_alive);

    day_phase(players_n_roles,dead_alive);

    cout<<"is gnk dead? --- status: "<<gankster_check(players_n_roles,dead_alive)<<endl; */
    
    testing.round= 1;
    testing.gank_killed="";
    testing.vote_elected="";
   
    round.push_back(testing);
    
    
    while( 1 ){

        
        //info menuu loop 
        while(menuU_in != 1){

            menuU_in = menuU(players_n_roles, dead_alive);

        }

        night_phase(players_n_roles, dead_alive);

        // enter gankcheck for the last night where 3 players were alive, gankster kills the other one and after the night there are 2 
        // left, the gangster and the other one


        
        for( i=0; i<dead_alive.size(); i++){        // counting how many people are dead

            if( dead_alive[i]== 0 || dead_alive[i]== -1 )   countt++;
        }


        if(countt==5 && status==0){

            cout<<"The GANGSTER won, what a pity...\n";
            break;
        }
        countt=0;

        day_phase(players_n_roles,dead_alive);

        
        // counting how many people are dead
        for( i=0; i<dead_alive.size(); i++){

            if( dead_alive[i]== 0 || dead_alive[i]== -1 )   countt++;
        }

        status=gankster_check(players_n_roles,dead_alive);

        //if gangster is dead while other players are alive, gangster wins
        if( status==1 && countt<6){

            cout<<"The Polites won! The gangster is dead!!!\n";
            break;
        }

        
// if 2 players are standing and one of them  is a gangster, gangster wins
        else if(countt==5 && status==0){

            cout<<"The GANGSTER won, what a pity...\n";
            break;
        }
        else 
        
        countt=0;
        continue;
   } 

    
    return 0;
}