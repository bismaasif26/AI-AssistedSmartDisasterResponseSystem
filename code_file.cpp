#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


// OBSERVER INTERFACE  (Observer Design Pattern)

// Any class that wants to be notified when an Emergency's
// status changes must implement this interface.

class Observer
{
public:
    virtual void update(string message) = 0;
    virtual ~Observer() {}
};


// LOCATION CLASS   (used via Composition/Association)


class Location
{
private:
    string city;
    string area;

public:

    Location()
    {
        city = "";
        area = "";
    }

    Location(string c, string a)
    {
        city = c;
        area = a;
    }

    void setCity(string c) { city = c; }
    void setArea(string a) { area = a; }
    string getCity() { return city; }
    string getArea() { return area; }

    void displayLocation()
    {
        cout << "City : " << city << endl;
        cout << "Area : " << area << endl;
    }
};


// ABSTRACT USER CLASS   (Abstraction + Inheritance)
// Implements Observer -> every user CAN be notified


class User : public Observer
{
protected:

    int id;
    string name;
    string phone;
    Location location;

public:

    User()
    {
        id = 0;
        name = "";
        phone = "";
    }

    User(int i, string n, string p, Location l)
    {
        id = i;
        name = n;
        phone = p;
        location = l;
    }

    // Pure virtual function -> Abstraction
    virtual void login() = 0;

    virtual void logout()
    {
        cout << name << " Logged Out Successfully.\n";
    }

    // Default Observer behaviour, subclasses may override
    virtual void update(string message)
    {
        cout << "[Notification -> " << name << "] : " << message << endl;
    }

    void displayProfile()
    {
        cout << "\n========== PROFILE ==========\n";
        cout << "ID : " << id << endl;
        cout << "Name : " << name << endl;
        cout << "Phone : " << phone << endl;
        location.displayLocation();
    }

    void setName(string n) { name = n; }
    void setPhone(string p) { phone = p; }
    void setLocation(Location l) { location = l; }
    string getName() { return name; }
    string getPhone() { return phone; }
    Location getLocation() { return location; }
    int getId() { return id; }

    virtual ~User() {}
};


// VICTIM CLASS   (Encapsulation + Inheritance)


class Victim : public User
{
private:

    int injuryLevel;
    int familyMembers;
    string status;

public:

    Victim()
    {
        injuryLevel = 0;
        familyMembers = 0;
        status = "Waiting";
    }

    Victim(int i, string n, string p, Location l, int injury, int family)
        : User(i, n, p, l)
    {
        injuryLevel = injury;
        familyMembers = family;
        status = "Waiting";
    }

    void login()
    {
        cout << "\nVictim Logged In Successfully.\n";
    }

    void requestHelp()
    {
        cout << "Emergency Request Registered.\n";
    }

    void updateStatus(string s)
    {
        status = s;
    }

    void updateLocation(Location l)
    {
        location = l;
    }

    int getInjuryLevel() { return injuryLevel; }
    string getStatus() { return status; }

    void displayVictim()
    {
        displayProfile();
        cout << "Injury Level : " << injuryLevel << endl;
        cout << "Family Members : " << familyMembers << endl;
        cout << "Status : " << status << endl;
    }
};


// ADMIN CLASS


class Admin : public User
{
private:

    string username;
    string password;

public:

    Admin()
    {
        username = "";
        password = "";
    }

    Admin(int i, string n, string p, Location l, string u, string pass)
        : User(i, n, p, l)
    {
        username = u;
        password = pass;
    }

    void login()
    {
        cout << "\nAdmin Logged In Successfully.\n";
    }

    void addUser()
    {
        cout << "New User Added Successfully.\n";
    }

    void removeUser()
    {
        cout << "User Removed Successfully.\n";
    }

    void manageEmergencies()
    {
        cout << "Managing All Emergencies...\n";
    }

    void generateReport()
    {
        cout << "Generating Disaster Report...\n";
    }

    void displayAdmin()
    {
        displayProfile();
        cout << "Username : " << username << endl;
    }
};


// VOLUNTEER CLASS


class Volunteer : public User
{
private:

    string skill;
    bool available;

public:

    Volunteer()
    {
        skill = "";
        available = true;
    }

    Volunteer(int i, string n, string p, Location l, string s, bool a)
        : User(i, n, p, l)
    {
        skill = s;
        available = a;
    }

    void login()
    {
        cout << "\nVolunteer Logged In Successfully.\n";
    }

    void acceptTask()
    {
        if (available)
        {
            cout << "Volunteer Accepted Rescue Task.\n";
            available = false;
        }
        else
        {
            cout << "Volunteer is Busy.\n";
        }
    }

    void completeTask()
    {
        cout << "Volunteer Completed Task Successfully.\n";
        available = true;
    }

    bool isAvailable() { return available; }
    string getSkill() { return skill; }

    void displayVolunteer()
    {
        displayProfile();
        cout << "Skill : " << skill << endl;
        cout << "Available : " << (available ? "Yes" : "No") << endl;
    }
};


// RESCUE TEAM CLASS   (Association -> rescues a Victim)

class RescueTeam : public User
{
private:

    int teamID;
    int totalMembers;
    string vehicle;
    bool available;

public:

    RescueTeam()
    {
        teamID = 0;
        totalMembers = 0;
        vehicle = "";
        available = true;
    }

    RescueTeam(int i, string n, string p, Location l,
               int tID, int members, string v, bool a)
        : User(i, n, p, l)
    {
        teamID = tID;
        totalMembers = members;
        vehicle = v;
        available = a;
    }

    void login()
    {
        cout << "\nRescue Team Logged In Successfully.\n";
    }

    void acceptMission()
    {
        if (available)
        {
            cout << "Mission Accepted Successfully.\n";
            available = false;
        }
        else
        {
            cout << "Rescue Team is Busy.\n";
        }
    }

    // Association: RescueTeam directly interacts with a Victim object
    void rescueVictim(Victim *v)
    {
        cout << "Victim Rescued Successfully.\n";
        if (v != nullptr)
        {
            v->updateStatus("Rescued");
        }
    }

    void completeMission()
    {
        cout << "Mission Completed Successfully.\n";
        available = true;
    }

    bool isAvailable() { return available; }
    int getTeamID() { return teamID; }
    string getVehicle() { return vehicle; }

    void displayTeam()
    {
        displayProfile();
        cout << "Team ID : " << teamID << endl;
        cout << "Members : " << totalMembers << endl;
        cout << "Vehicle : " << vehicle << endl;
        cout << "Available : " << (available ? "Yes" : "No") << endl;
    }
};


// SHELTER CLASS   (Aggregation -> holds Victim*, doesn't own them)


class Shelter
{
private:

    int shelterID;
    string shelterName;
    int capacity;
    int occupiedBeds;
    Location location;
    vector<Victim *> victims; // Aggregation: victims can exist without the shelter

public:

    Shelter()
    {
        shelterID = 0;
        shelterName = "";
        capacity = 0;
        occupiedBeds = 0;
    }

    Shelter(int id, string name, int cap, int occupied, Location loc)
    {
        shelterID = id;
        shelterName = name;
        capacity = cap;
        occupiedBeds = occupied;
        location = loc;
    }

    void addVictim(Victim *v)
    {
        if (occupiedBeds < capacity)
        {
            victims.push_back(v);
            occupiedBeds++;
            cout << "Victim Added To Shelter.\n";
        }
        else
        {
            cout << "Shelter is Full.\n";
        }
    }

    void removeVictim(int victimID)
    {
        for (size_t idx = 0; idx < victims.size(); idx++)
        {
            if (victims[idx]->getId() == victimID)
            {
                victims.erase(victims.begin() + idx);
                occupiedBeds--;
                cout << "Victim Removed Successfully.\n";
                return;
            }
        }
    }

    int availableBeds() { return capacity - occupiedBeds; }
    string getShelterName() { return shelterName; }

    void displayShelter()
    {
        cout << "\n========== SHELTER ==========\n";
        cout << "Shelter ID : " << shelterID << endl;
        cout << "Shelter Name : " << shelterName << endl;
        cout << "Capacity : " << capacity << endl;
        cout << "Occupied Beds : " << occupiedBeds << endl;
        cout << "Available Beds : " << availableBeds() << endl;
        location.displayLocation();
    }
};


// AMBULANCE CLASS


class Ambulance
{
private:

    int ambulanceID;
    string driverName;
    string vehicleNumber;
    bool available;

public:

    Ambulance()
    {
        ambulanceID = 0;
        driverName = "";
        vehicleNumber = "";
        available = true;
    }

    Ambulance(int id, string driver, string number, bool a)
    {
        ambulanceID = id;
        driverName = driver;
        vehicleNumber = number;
        available = a;
    }

    void assignAmbulance()
    {
        if (available)
        {
            cout << "Ambulance Assigned Successfully.\n";
            available = false;
        }
        else
        {
            cout << "Ambulance is Not Available.\n";
        }
    }

    void transportVictim()
    {
        cout << "Victim Transported To Hospital Successfully.\n";
    }

    void releaseAmbulance()
    {
        available = true;
        cout << "Ambulance Released.\n";
    }

    bool isAvailable() { return available; }

    void displayAmbulance()
    {
        cout << "\n========== AMBULANCE ==========\n";
        cout << "Ambulance ID : " << ambulanceID << endl;
        cout << "Driver Name : " << driverName << endl;
        cout << "Vehicle Number : " << vehicleNumber << endl;
        cout << "Available : " << (available ? "Yes" : "No") << endl;
    }
};


// EMERGENCY CLASS   (Subject in the Observer Pattern)
// Composition: owns a Location (Location dies with Emergency)


class Emergency
{
private:

    int emergencyID;
    string type;
    string severity;
    Location location;
    bool active;
    vector<Observer *> observers; // subscribed users to notify

public:

    Emergency()
    {
        emergencyID = 0;
        type = "";
        severity = "";
        active = false;
    }

    Emergency(int id, string t, string s, Location l)
    {
        emergencyID = id;
        type = t;
        severity = s;
        location = l;
        active = true;
    }

    void addObserver(Observer *o)
    {
        observers.push_back(o);
    }

    void notifyObservers(string message)
    {
        for (size_t idx = 0; idx < observers.size(); idx++)
        {
            observers[idx]->update(message);
        }
    }

    void createEmergency()
    {
        active = true;
        cout << "Emergency Created Successfully.\n";
        notifyObservers("A new " + severity + " severity " + type + " emergency was registered.");
    }

    void closeEmergency()
    {
        active = false;
        cout << "Emergency Closed Successfully.\n";
        notifyObservers("The " + type + " emergency has been resolved and closed.");
    }

    bool isActive() { return active; }
    string getSeverity() { return severity; }

    void displayEmergency()
    {
        cout << "\n========== EMERGENCY ==========\n";
        cout << "Emergency ID : " << emergencyID << endl;
        cout << "Type : " << type << endl;
        cout << "Severity : " << severity << endl;
        cout << "Status : " << (active ? "Active" : "Closed") << endl;
        location.displayLocation();
    }
};


// NOTIFICATION CLASSES   (Polymorphism)


class Notification
{
public:
    virtual void sendNotification()
    {
        cout << "Sending General Notification.\n";
    }
    virtual ~Notification() {}
};

class SMSNotification : public Notification
{
public:
    void sendNotification()
    {
        cout << "SMS Notification Sent Successfully.\n";
    }
};

class EmailNotification : public Notification
{
public:
    void sendNotification()
    {
        cout << "Email Notification Sent Successfully.\n";
    }
};

class AlertNotification : public Notification
{
public:
    void sendNotification()
    {
        cout << "Emergency Alert Notification Sent Successfully.\n";
    }
};


// REPORT CLASS


class Report
{
private:

    int reportID;
    string reportType;
    string details;

public:

    Report()
    {
        reportID = 0;
        reportType = "";
        details = "";
    }

    Report(int id, string type, string d)
    {
        reportID = id;
        reportType = type;
        details = d;
    }

    void generateReport()
    {
        cout << "\nReport Generated Successfully.\n";
    }

    void displayReport()
    {
        cout << "\n========== REPORT ==========\n";
        cout << "Report ID : " << reportID << endl;
        cout << "Report Type : " << reportType << endl;
        cout << "Details : " << details << endl;
    }
};


// AI ENGINE CLASS

class AIEngine
{
private:
    string modelName;

public:

    AIEngine()
    {
        modelName = "Disaster Prediction AI";
    }

    AIEngine(string name)
    {
        modelName = name;
    }

    string predictSeverity(int victimCount, int damageLevel)
    {
        if (victimCount > 50 || damageLevel >= 8) return "Critical";
        else if (victimCount > 20 || damageLevel >= 5) return "High";
        else return "Low";
    }

    int calculatePriority(string severity)
    {
        if (severity == "Critical") return 1;
        else if (severity == "High") return 2;
        else return 3;
    }

    // Rule-based risk prediction (simple AI simulation, no ML required)
    string predictRisk(int injuryLevel)
    {
        if (injuryLevel >= 9) return "Critical";
        else if (injuryLevel >= 6) return "High";
        else if (injuryLevel >= 3) return "Medium";
        else return "Low";
    }

    // Picks the first available rescue team from a list
    RescueTeam *assignRescueTeam(vector<RescueTeam *> &teams)
    {
        for (size_t idx = 0; idx < teams.size(); idx++)
        {
            if (teams[idx]->isAvailable())
            {
                cout << "AI Assigned Rescue Team ID: " << teams[idx]->getTeamID() << endl;
                return teams[idx];
            }
        }
        cout << "No Rescue Team Available.\n";
        return nullptr;
    }

    // Picks the first available ambulance from a list
    Ambulance *assignAmbulance(vector<Ambulance *> &ambulances)
    {
        for (size_t idx = 0; idx < ambulances.size(); idx++)
        {
            if (ambulances[idx]->isAvailable())
            {
                cout << "AI Assigned an Available Ambulance.\n";
                return ambulances[idx];
            }
        }
        cout << "No Ambulance Available.\n";
        return nullptr;
    }

    // Picks the shelter with the most available beds
    Shelter *findNearestShelter(vector<Shelter *> &shelters)
    {
        Shelter *best = nullptr;
        int maxBeds = -1;

        for (size_t idx = 0; idx < shelters.size(); idx++)
        {
            if (shelters[idx]->availableBeds() > maxBeds)
            {
                maxBeds = shelters[idx]->availableBeds();
                best = shelters[idx];
            }
        }

        if (best != nullptr)
        {
            cout << "AI Selected Shelter: " << best->getShelterName() << endl;
        }
        else
        {
            cout << "No Shelter Available.\n";
        }
        return best;
    }

    void analyzeEmergency(Emergency e)
    {
        cout << "\n========== AI ANALYSIS ==========\n";
        cout << "AI Model : " << modelName << endl;
        cout << "Emergency Severity : " << e.getSeverity() << endl;
        cout << "Priority Level : " << calculatePriority(e.getSeverity()) << endl;
        cout << "AI Recommendation : ";

        if (e.getSeverity() == "Critical")
            cout << "Send Maximum Rescue Resources.\n";
        else if (e.getSeverity() == "High")
            cout << "Send Rescue Team and Ambulance.\n";
        else
            cout << "Monitor Situation.\n";
    }

    void displayAI()
    {
        cout << "AI Engine Running : " << modelName << endl;
    }
};


// DATABASE CLASS   (Singleton Design Pattern)
// Only one Database instance can ever exist in the system.

class Database
{
private:
    static Database *instance;
    vector<string> logs;

    Database() {} // private constructor -> can't be created directly

public:

    static Database *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Database();
        }
        return instance;
    }

    void logEvent(string entry)
    {
        logs.push_back(entry);
        cout << "[Database] Logged: " << entry << endl;
    }

    void showLogs()
    {
        cout << "\n========== DATABASE LOGS ==========\n";
        for (size_t idx = 0; idx < logs.size(); idx++)
        {
            cout << (idx + 1) << ". " << logs[idx] << endl;
        }
    }
};

Database *Database::instance = nullptr;


// USER FACTORY   (Factory Method Design Pattern)
// Centralizes creation of every User subtype.


class UserFactory
{
public:

    static Victim *createVictim(int id, string name, string phone,
                                 Location loc, int injury, int family)
    {
        return new Victim(id, name, phone, loc, injury, family);
    }

    static Admin *createAdmin(int id, string name, string phone,
                               Location loc, string username, string password)
    {
        return new Admin(id, name, phone, loc, username, password);
    }

    static Volunteer *createVolunteer(int id, string name, string phone,
                                       Location loc, string skill, bool available)
    {
        return new Volunteer(id, name, phone, loc, skill, available);
    }

    static RescueTeam *createRescueTeam(int id, string name, string phone,
                                         Location loc, int teamID, int members,
                                         string vehicle, bool available)
    {
        return new RescueTeam(id, name, phone, loc, teamID, members, vehicle, available);
    }
};


// MAIN FUNCTION


int main()
{
    cout << "=================================\n";
    cout << " AI SMART DISASTER RESPONSE SYSTEM\n";
    cout << "=================================\n";

    Database *db = Database::getInstance(); // Singleton in use

    // Location Object (fixed: only 2 args, city/area)
    Location loc1("Karachi", "Sindh");

    // ---- Objects created through the Factory Pattern ----
    Victim *victim1 = UserFactory::createVictim(1, "unzila", "03001234567", loc1, 7, 4);
    victim1->updateStatus("Injured");

    RescueTeam *team1 = UserFactory::createRescueTeam(2, "Rescue Team Alpha", "021111111",
                                                       loc1, 501, 8, "Rescue Truck", true);

    Admin *admin1 = UserFactory::createAdmin(3, "aman", "03111111111", loc1, "admin_aman", "pass123");

    Volunteer *vol1 = UserFactory::createVolunteer(4, "bisma", "03222222222", loc1, "First Aid", true);

    cout << "\nVictim Information\n";
    victim1->displayVictim();

    cout << "\nRescue Team Information\n";
    team1->displayTeam();

    cout << "\nAdmin Information\n";
    admin1->displayAdmin();

    cout << "\nVolunteer Information\n";
    vol1->displayVolunteer();

    // Shelter Object
    Shelter shelter1(301, "Safe Shelter", 100, 20, loc1);
    shelter1.displayShelter();

    // Ambulance Object
    Ambulance ambulance1(401, "ahmed", "ABC-123", true);
    ambulance1.displayAmbulance();

    // Emergency Object (the Observer Pattern's Subject)
    Emergency emergency1(601, "Flood", "Critical", loc1);

    // Subscribe users to this emergency -> Observer Pattern
    emergency1.addObserver(victim1);
    emergency1.addObserver(team1);
    emergency1.addObserver(admin1);
    emergency1.addObserver(vol1);

    emergency1.createEmergency(); // notifies all observers automatically
    emergency1.displayEmergency();
    db->logEvent("Flood emergency (ID 601) registered in Karachi, Sindh.");

    // AI Engine
    AIEngine ai;
    ai.displayAI();
    ai.analyzeEmergency(emergency1);

    // AI decision-making: risk prediction + resource assignment
    cout << "\n========== AI DECISION MAKING ==========\n";
    cout << "AI Risk Level (based on injury) : " << ai.predictRisk(victim1->getInjuryLevel()) << endl;

    vector<RescueTeam *> availableTeams = {team1};
    vector<Ambulance *> availableAmbulances = {&ambulance1};
    vector<Shelter *> availableShelters = {&shelter1};

    RescueTeam *assignedTeam = ai.assignRescueTeam(availableTeams);
    Ambulance *assignedAmbulance = ai.assignAmbulance(availableAmbulances);
    Shelter *assignedShelter = ai.findNearestShelter(availableShelters);

    if (assignedTeam != nullptr && assignedAmbulance != nullptr && assignedShelter != nullptr)
    {
        cout << "AI Confirms: Resources Are Ready For Dispatch.\n";
    }

    // Rescue Operation
    cout << "\n========== RESCUE OPERATION ==========\n";
    team1->acceptMission();
    ambulance1.assignAmbulance();
    team1->rescueVictim(victim1); // Association: team acts directly on the victim
    ambulance1.transportVictim();
    shelter1.addVictim(victim1);  // Aggregation: shelter holds the victim, doesn't own it
    db->logEvent("Victim ID 1 rescued and transported to Safe Shelter.");

    // Notification Polymorphism
    cout << "\n========== NOTIFICATION SYSTEM ==========\n";
    Notification *notify;

    SMSNotification sms;
    EmailNotification email;
    AlertNotification alert;

    notify = &sms;
    notify->sendNotification();

    notify = &email;
    notify->sendNotification();

    notify = &alert;
    notify->sendNotification();

    // Report
    Report report1(701, "Rescue Report", "Victim rescued and shifted to shelter");
    report1.generateReport();
    report1.displayReport();

    // Completing Mission
    team1->completeMission();
    ambulance1.releaseAmbulance();
    emergency1.closeEmergency(); // notifies all observers again

    // Show everything the Database has logged
    db->showLogs();

    cout << "\n=================================\n";
    cout << " Disaster Response Completed\n";
    cout << "=================================\n";

    // Clean up dynamically allocated objects
    delete victim1;
    delete team1;
    delete admin1;
    delete vol1;

    return 0;
}
