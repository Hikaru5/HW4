#include "stdafx.h"
#include <iostream>
#include <string>
#include "Die.h"
using namespace std;

class ParkingTicket;

class ParkedCar
{
private:
	string make;
	string model;
	string color;
	string license;
	int time;

public:
	ParkedCar(string ma, string mo, string co, string lic, int min)
	{
		make = ma;
		model = mo;
		color = co;
		license = lic;
		time = min;
	}

	ParkedCar()
	{
		ParkedCar("", "", "", "", 0);
	}
	friend class ParkingTicket;
	friend class PoliceOfficer;
};

class ParkingMeter
{
private:
	int purchased;

public:
	ParkingMeter(int pur)
	{
		purchased = pur;
	}
	ParkingMeter()
	{
		ParkingMeter(0);
	}
	friend class ParkingTicket;
	friend class PoliceOfficer;
};

class PoliceOfficer
{
private:
	string name;
	int badge;

public:
	PoliceOfficer(string na, int id)
	{
		name = na;
		badge = id;
	}

	PoliceOfficer()
	{
		PoliceOfficer("", 0);
	}

	bool checkExpiration(ParkedCar car, ParkingMeter meter)
	{
		if (car.time > meter.purchased)
			return true;
		return false;
	}

	ParkingTicket ticket(ParkedCar &car, ParkingMeter &meter, PoliceOfficer &cop);
	friend class ParkingTicket;
};


class ParkingTicket
{
private:
	ParkedCar culprit;
	int expired;
	PoliceOfficer cop;

public:
	ParkingTicket(ParkedCar cul, ParkingMeter meter, PoliceOfficer c)
	{
		culprit = cul;
		expired = cul.time-meter.purchased;
		cop = c;
	}

	ParkingTicket()
	{
		ParkingTicket(ParkedCar(), 0, PoliceOfficer());
	}

	void reportCar()
	{
		cout <<"The car is a "<<culprit.color<<" "<<culprit.make<<" "<<culprit.model<<" with a license plate number of "<<culprit.license<<'\n';
	}

	int price()
	{
		return 25 + (expired - 1) * 10;
	}

	void reportOfficer()
	{
		cout << "The officer's name is " << cop.name << " and their badge number is " << cop.badge << '\n';
	}
	
	friend ParkingTicket PoliceOfficer::ticket(ParkedCar &car, ParkingMeter &meter, PoliceOfficer &cop);
};

ParkingTicket ticket(ParkedCar &car, ParkingMeter &meter, PoliceOfficer &cop)
{
	return ParkingTicket(car, meter, cop);
}

int main()
{
	ParkedCar car1("Toyota", "2018", "blue", "3CAR345", 150);
	ParkedCar car2("Hyundai", "2017", "gray", "2BOR234", 120);
	ParkingMeter meter1(120);
	ParkingMeter meter2(120);
	ParkingTicket ticket1;
	ParkingTicket ticket2;
	PoliceOfficer james("James McCop", 3344532);
	PoliceOfficer jess("Jessie Justice", 2345233);
	if (james.checkExpiration(car1, meter1))
	{
		ticket1 = james.ticket(car1, meter1, james);
		ticket1.reportCar();
		cout << "The owner is charged $" << ticket1.price() << '\n';
		ticket1.reportOfficer();
	}
	if (jess.checkExpiration(car2, meter2))
	{
		ticket2 = jess.ticket(car2, meter2, jess);
		ticket2.reportCar();
		cout << "The owner is charged $" << ticket2.price() << '\n';
		ticket2.reportOfficer();
	}
}