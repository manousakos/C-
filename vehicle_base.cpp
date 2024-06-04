#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

int vehcheck(string word)
{
	if(!strcmp(word.c_str(),"Van")) return 0;				//Motorcycle, Car, Van, Semitruck 		Check
	else if(!strcmp(word.c_str(),"Motorcycle")) return 0;
	else if(!strcmp(word.c_str(),"Car")) return 0;
	else if(!strcmp(word.c_str(),"Semitruck")) return 0;
	else return 1;
}

int dmgcheck( string word)
{
	if(!strcmp(word.c_str(),"Engine")) return 0;									// Engine, Brakes, Transmission, Gearbox, Electrical Check
	else if(!strcmp(word.c_str(),"Brakes")) return 0;
	else if(!strcmp(word.c_str(),"Transmission")) return 0;
	else if(!strcmp(word.c_str(),"Gearbox")) return 0;
	else if(!strcmp(word.c_str(),"Electrical")) return 0;
	else return 1;
}

void error(string word,string leksi, string kati)
 {
 	cout<<"--------------\n"<<word<<leksi<<kati<<"--------------\n";
 }

struct Vehicle
{
	string licensePlate;
	string vehicleType;
	vector<string> damageType;
	string estFixDays;
};

struct DailyCustomers
{
	string data;
	vector<Vehicle> 	vehicleList;
};



int main(int argc , char** argv)
{
	string line, filename, word,meli, subvec,vecstr,licVec,vehVec,estVec;
	vector<string> dmgVec;
	int pos=0,rnd,index=0,bin=0, brkpoint=0;
	vector<int> posVec;
	filename=argv[1];
	ifstream myfile;
	myfile.open(filename.c_str(),ios::in);
	if(myfile.is_open())
	{
		cout<<"File opened succesfully.\n";
		DailyCustomers dcust;
		getline(myfile,line);
		dcust.data=line;
		getline(myfile,line);
		while(!line.empty())
		{
			//										lisencePlate
			dcust.vehicleList.push_back( Vehicle());
			pos=line.find(',');
			vecstr=line.substr(0,pos);
			line=line.substr(pos+1,line.size()-pos);
			dcust.vehicleList[index].licensePlate=vecstr;
			
		//											vehicleType
			pos=line.find(',');
			vecstr=line.substr(0,pos);
			line=line.substr(pos+1,line.size()-pos);
			dcust.vehicleList[index].vehicleType=vecstr;
			
		//											damageType
			pos=line.find(',');
			vecstr=line.substr(0,pos);
			line=line.substr(pos+1,line.size()-pos);
			do
			{
				
				pos=vecstr.find('-');
				if(pos==-1)
				{
					dcust.vehicleList[index].damageType.push_back(vecstr);
					break;
				}
				subvec=vecstr.substr(0,pos);
				vecstr=vecstr.substr(pos+1,vecstr.size()-pos);
				dcust.vehicleList[index].damageType.push_back(subvec);
				dcust.vehicleList[index].damageType.push_back("-");
				
			}while(1);
			dcust.vehicleList[index].estFixDays = line;
			
			getline(myfile,line);
			index++;
			
		
		}
		
		myfile.close();
		while(1)
		{
			/*	
			cout<< "now starts the printing::\n";
			for(rnd=0;rnd<dcust.vehicleList.size();++rnd)
			{
				for(bin=0; bin<dcust.vehicleList[rnd].damageType.size();++bin)
				{
					cout<<"dcust.vehicleList["<<rnd<<"].damageType["<<bin<<"] == "<<dcust.vehicleList[rnd].damageType[bin]<<endl;
				}
			} */
		//	cout<<"LOOP AFTAR PRINT:::::::: starting size is: "<< dcust.vehicleList.size()<<endl;
			getline(cin,line);
			pos=line.find(" ");
			word=line.substr(0,pos);
			line=line.substr(pos+1,line.size()-pos);
			if(!strcmp(word.c_str(),"a"))													/// INSTRUCTION a
			{
			//	cout<<"starting size is: "<< dcust.vehicleList.size()<<endl;;
				
			//														licensePlate
				bin=dcust.vehicleList.size()-1;
				pos=line.find(',');
				vecstr=line.substr(0,pos);
				line=line.substr(pos+1,line.size()-pos);
			//	cout<<"vec 2 lcPlate is: "<< vecstr;
				for(int j=0; j<dcust.vehicleList.size()-1; j++)
				{
					
					if(dcust.vehicleList[j].licensePlate.empty())
					{
						cout<<"Its a bit empty doe...\n";
					/*	dcust.vehicleList.erase(dcust.vehicleList.begin()+j); */
						continue;
					}
				//	cout<<"MAH NIGAAAA WOOOOOOOOOOOW\n";
					if(!strcmp(dcust.vehicleList[j].licensePlate.c_str(),vecstr.c_str()))
					{
						error("Vehicle with license plate \'",vecstr,"\' is already being serviced. Please enter an other vehicle.\n");
						dcust.vehicleList.pop_back();
						brkpoint=10;
						break;
					}
				//	cout<<"LS starting size is: "<< dcust.vehicleList.size()<<endl<<"and dcust.vehicleList[j]="<<dcust.vehicleList[j].licensePlate<<endl;
				//	cout<<"BREEEEEEEEEEEEEE\n";
				}
				
				
				if(brkpoint==10) continue;
				
				 dcust.vehicleList.push_back(Vehicle());
				
				dcust.vehicleList[bin].licensePlate=vecstr;
			//														vehicleType
				pos=line.find(',');
				vecstr=line.substr(0,pos);
				line=line.substr(pos+1,line.size()-pos);
				if(vehcheck(vecstr))
				{
					error("\'",vecstr,"\' is not a valid vehicle type. Vehicle must be one of bellow:\n-Car\n-Van\n-Motorcycle\n-Semitruck\nPlease try again.\n");
					
				
				
					dcust.vehicleList.pop_back();
					continue;
				}
				dcust.vehicleList[bin].vehicleType=vecstr;
			//	cout<<" V C starting size is: "<< dcust.vehicleList.size()<<endl;
				
			//														damageType
				pos=line.find(',');
				vecstr=line.substr(0,pos);
				line=line.substr(pos+1,line.size()-pos);
				brkpoint=0;
				while(1)
				{
					
					pos=vecstr.find('-');
					if( pos==-1)
					{
					
						if(dmgcheck(vecstr))
						{
						error("\'",vecstr,"\' is not a valid Damage Type. Damage Type must be one of bellow:\n-Gearbox\n-Electrical\n-Transmission\n-Brakes\n-Engine\nPlease try again.\n");
						dcust.vehicleList.pop_back();
						brkpoint=10;
						break;
						}
						dcust.vehicleList[bin].damageType.push_back(vecstr);
						break;
					}
					
					subvec=vecstr.substr(0,pos);
					if(dmgcheck(subvec))
					{
						error("\'",subvec,"\' is not a valid Damage Type. Damage Type must be one of bellow:\n-Gear\n-Electrical\n-Transmission\n-Brakes\n-Engine\nPlease try again.\n");
						dcust.vehicleList.pop_back();
						brkpoint=10;
						break;
					}
					vecstr=vecstr.substr(pos+1,vecstr.size()-pos);
					dcust.vehicleList[bin].damageType.push_back(subvec);
					dcust.vehicleList[bin].damageType.push_back("-");
				}
			//	cout<<" DMG starting size is: "<< dcust.vehicleList.size()<<endl;
				if(brkpoint==10) continue;
			//														estFixDays
				stringstream geko(line);
				geko>>rnd;
				if(rnd<0)
				{
					error("\'",line,"\' is not valid estimation for the days needed to fix the Vehicle. Number must be positive. Please try again.\n");
					dcust.vehicleList.pop_back();
					continue;
				}
				else if(rnd>12)
				{
					cout<<"--------------\n"<<"Vehicle with license plate "<<dcust.vehicleList[bin].licensePlate  << " needs many days. It can not be fixed\n--------------\n";
					dcust.vehicleList.pop_back();
					continue;
				}
			//	cout<<"starting size is: "<< dcust.vehicleList.size()<<endl;
				dcust.vehicleList[bin].estFixDays=line;
				
				cout<<"Vehicle added successfully.\n";
			}
			else if(!strcmp(word.c_str(),"d"))															/// INSTRUCTION d
			{
					// case gia word =d;
					
					for(int j=0; j<dcust.vehicleList.size(); j++)
					{
						if(!strcmp(dcust.vehicleList[j].licensePlate.c_str(),line.c_str()))
						{
							dcust.vehicleList.erase(dcust.vehicleList.begin()+j);
							
						cout<<"Vehicle whit license plate \'"<<line<<"\' has been succesfully deleted from the data base.\n";
							break;
						}
					}	
			}
			else if(!strcmp(word.c_str(),"pd"))															/// INSTRUCTION pd
			{
					// case gia word= pd
					int sum=0;
					rnd=0;
					for(int j=0; j<dcust.vehicleList.size(); j++)
					{
						stringstream geko(dcust.vehicleList[j].estFixDays);
						geko>>rnd;
						sum=sum+rnd;
					}
					cout<<sum<<" days in total.\n";
			}
			else if(!strcmp(word.c_str(),"pv"))															/// INSTRUCTION pv
			{
				
			
				rnd=0;
				if(vehcheck(line))
				{
					error("\'",vecstr,"\' is not a valid vehicle type. Vehicle must be one of bellow:\n-Car\n-Van\n-Motorcycle\n-Semitruck\nPlease try again.\n");
					continue;
				}
				//case gia pv
				for(bin=0; bin<dcust.vehicleList.size(); bin++)
				{
					if(!strcmp(dcust.vehicleList[bin].vehicleType.c_str(),line.c_str())) rnd++;
				}
				cout<<rnd<<" "<<line<<"s.\n";
			}
			else if(!strcmp(word.c_str(),"pdt"))														/// INSTRUCTION pdt
			{
					//case gia word= pdt
					
					if(dmgcheck(line))
					{
						error("\'",subvec,"\' is not a valid Damage Type. Damage Type must be one of bellow:\n-Gear\n-Electrical\n-Transmission\n-Brakes\n-Engine\nPlease try again.\n");
						continue;
					}
					int array[4]={0,0,0,0};
					rnd=0;
					for(int j=0; j<dcust.vehicleList.size(); j++)
					{
						for(bin=0; bin<dcust.vehicleList[j].damageType.size(); bin++)
						{
							if(!strcmp(dcust.vehicleList[j].damageType[bin].c_str(),line.c_str()))
							{
								if(!strcmp(dcust.vehicleList[j].vehicleType.c_str(),"Motorcycle")) array[0]++;
								if(!strcmp(dcust.vehicleList[j].vehicleType.c_str(),"Car")) array[1]++;
								if(!strcmp(dcust.vehicleList[j].vehicleType.c_str(),"Van")) array[2]++;
								if(!strcmp(dcust.vehicleList[j].vehicleType.c_str(),"Semitruck")) array[3]++;
							}
						}
					}
					cout<<line<<" damage in vehicles: ";
					if(array[0]==1)cout<<array[0]<<" Motorcycle, ";
					else cout<<array[0]<<" Motorcycles, ";
					if(array[1]==1)cout<<array[1]<<" Car, ";
					else cout<<array[1]<<" Cars, ";
					if(array[2]==1)cout<<array[2]<<" Van, ";
					else cout<<array[2]<<" Vans, ";
					if(array[3]==1)cout<<array[3]<<" Semitruck.\n";
					else cout<<array[3]<<" Semitrucks.\n";
			}
			else if(!strcmp(word.c_str(),"rd"))														/// INSTRUCTION rd
			{
					//case gia word= rd
					brkpoint=0;
					rnd=0;
					int help=0;
					int plis=0;
					pos=line.find(' ');
					vecstr=line.substr(0,pos);
					line=line.substr(pos+1,line.size()-pos); // vec is licensePlate, line is dmgType
					if(dmgcheck(line))
					{
						error("\'",subvec,"\' is not a valid Damage Type. Damage Type must be one of bellow:\n-Gear\n-Electrical\n-Transmission\n-Brakes\n-Engine\nPlease try again.\n");
						continue;
					}
					for(int j=0; j<dcust.vehicleList.size(); j++)
					{
						if(!strcmp(dcust.vehicleList[j].licensePlate.c_str(),vecstr.c_str()))
						{
							rnd=1;
							for(bin=0; bin<dcust.vehicleList[j].damageType.size(); bin++)
							{
								if(!strcmp(dcust.vehicleList[j].damageType[bin].c_str(),line.c_str()))
								{
									rnd++;
									plis=j;
									help=bin;
									if(dcust.vehicleList[j].damageType.size()==1)
									{
										cout<<"Fixed.\n";
										dcust.vehicleList.erase(dcust.vehicleList.begin()+plis);
										brkpoint==10;
										break;
									}
									dcust.vehicleList[j].damageType.erase(dcust.vehicleList[j].damageType.begin()+bin);
									if(!strcmp(dcust.vehicleList[j].damageType[bin].c_str(),"-"))	dcust.vehicleList[j].damageType.erase(dcust.vehicleList[j].damageType.begin()+bin);
									else dcust.vehicleList[j].damageType.erase(dcust.vehicleList[j].damageType.begin()+bin-1);
								}
							
							}
							if(brkpoint==10)break;
						}
					}
					if(brkpoint==10) continue;
					if(rnd==0) cout<<"There is no vehicle with license plate \'"<<vecstr<<"\'.\n";
					else if(rnd==1) 	cout<<"Vehicle with license plate \'"<<vecstr<<"\' does not suffer "<< line<<" damage. Please try again.\n";
					else
						for(bin=0; bin<dcust.vehicleList[plis].damageType.size();bin++)
						{
							if(!strcmp(dcust.vehicleList[plis].damageType[bin].c_str(),"-")) cout<<",";
							else cout<<dcust.vehicleList[plis].damageType[bin];
						}
					cout<<endl;
						
			}
			else if(!strcmp(word.c_str(),"q"))														/// INSTRUCTION q
			{
				//case gia word= q
				ofstream files;
				files.open(filename.c_str(),ios::out | ios::trunc);
				if(files.is_open())
				{
					files<<dcust.data<<endl;
					for(int j=0; j<dcust.vehicleList.size(); j++)
					{
						if(dcust.vehicleList[j].licensePlate.empty()) cout<<"To anagnorizei\n";
						files<<dcust.vehicleList[j].licensePlate<<","
						<<dcust.vehicleList[j].vehicleType<<",";
						for(bin=0; bin<dcust.vehicleList[j].damageType.size(); bin++)
						{
							files<<dcust.vehicleList[j].damageType[bin];
						}
						if(j==(dcust.vehicleList.size()-1)) files<<","<<dcust.vehicleList[j].estFixDays;	
						else {
							files<<","
							<<dcust.vehicleList[j].estFixDays<<endl;
						}
					}
				}
				else
				{
				cout<<"Output file \'"<<filename<<"\' did not open. Please try again.\n";	
				}
				files.close();
				break;
			}
			else cout<<"\'"<< word << "\' is not a valid instruction. Instruction must be one of the below:\n-a \n-d \n-pd\n-pdt\n-rd\n-pv\nPlease try again.\n";
		}
	}
	else
	{
		cout<<"File "<< filename<<" did not open.\n";
		myfile.close();
	}
	
	myfile.close();
	return 0;
		
}
