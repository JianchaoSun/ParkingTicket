#include <iostream>

using namespace std;
class ParkingTicket;
class ParkingMeter;
class ParkedCar{
private:
    string make;
public:
    const string &getMake() const {
        return make;
    }

    void setMake(const string &make) {
        ParkedCar::make = make;
    }

public:
    const string &getModel() const {
        return model;
    }

    void setModel(const string &model) {
        ParkedCar::model = model;
    }

private:
    string model;
    string licenseNumber;
public:
    const string &getLicenseNumber() const {
        return licenseNumber;
    }

    void setLicenseNumber(const string &licenseNumber) {
        ParkedCar::licenseNumber = licenseNumber;
    }

private:
    int minute;
public:
    int getMinute() const {
        return minute;
    }

    void setMinute(int minute) {
        ParkedCar::minute = minute;
    }

public:
    ParkedCar(string m,string mo,string ln,int mi){
        make =m;
        model=mo;
        licenseNumber =ln;
        minute = mi;
    }
    friend class ParkingTicket;
    friend class PoliceOfficer;

    friend void printTicket(const ParkedCar &car, const ParkingTicket &ticket, const ParkingMeter &meter);
};

class ParkingMeter{
private:
    int minutePurchased;
public:
    int getMinutePurchased() const {
        return minutePurchased;
    }

    void setMinutePurchased(int minutePurchased) {
        ParkingMeter::minutePurchased = minutePurchased;
    }
    friend class ParkingTicket;
    friend class PoliceOfficer;

    friend void printTicket(const ParkedCar &car, const ParkingTicket &ticket, const ParkingMeter &meter);

};

class ParkingTicket{

private:
    string name;
public:
    const string &getName() const {
        return name;
    }

private:
    int number;
public:
    int getNumber() const {
        return number;
    }

private:
    int fine =0;
    bool noticket= true;
public:
    bool isNoticket() const {
        return noticket;
    }

public:
    ParkingTicket(){

    }
    ParkingTicket(string na,int n,ParkedCar &car, ParkingMeter &meter,int fine1){
        name =na;
        number = n;
        fine =fine1;
        if(n!=-1){
            noticket =false;
        }
    }

    int getFine() const {
        return fine;
    }


    void increaseFine(int x){
        fine +=x;
    }

    friend class PoliceOfficer;
    friend void printTicket(const ParkedCar &car, const ParkingTicket &ticket, const ParkingMeter &meter);

};

class PoliceOfficer{
private:
    string name;
    int number;
public:
    PoliceOfficer(string n,int nu){
        name = n;
        number =nu;
    }
    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        PoliceOfficer::name = name;
    }
    void getParkingTicket(ParkedCar &car, ParkingMeter &meter, ParkingTicket &ticket){
        int fine =0;
        if(meter.getMinutePurchased()-car.getMinute()<0){
            int minute = car.getMinute()-meter.getMinutePurchased();
            if(minute <=60){
                fine =25;
            }else{
                int hour = (minute -60)/60;
                fine =25+hour*10;
                if((minute -60)%60!=0){
                    fine +=10;
                }
            }
        }
        if(fine ==0){
            ticket = ParkingTicket(name,-1,car,meter,0);
        }else{
            ticket = ParkingTicket(name,number,car,meter,fine);
        }

    }
    int getNumber() const {
        return number;
    }

    void setNumber(int number) {
        PoliceOfficer::number = number;
    }

    friend class ParkingTicket;
};



void printTicket(const ParkedCar &car, const ParkingTicket &ticket, const ParkingMeter &meter){
    if(!ticket.isNoticket()){

        cout<<"Officer name:"<<ticket.getName()<<"\nOfficer number:"<<ticket.getNumber()
        <<"\nCar make:"<<car.getMake()<<"\nCar license:"<<car.getLicenseNumber()<<"\nParked time:"<<car.getMinute()
        <<"\nParking meter purchased:"<<meter.getMinutePurchased()<<"\nfine:"<<ticket.getFine();
    }
    else{
        cout<<"no ticket";
    }
}




int main() {
    ParkedCar c("car","mobile","vechile",900);
    ParkingMeter m;
    ParkingTicket t;
    m.setMinutePurchased(10);
    PoliceOfficer p("zhang",110);
    p.getParkingTicket(c,m,t);
    printTicket(c,t,m);

}