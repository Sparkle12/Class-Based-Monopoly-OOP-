#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Villiger {
    int health;

public:

    Villiger() {
        health = 50;
    }

    explicit Villiger(int h) {
        health = h;
    }

    void setHealth(int h) {
        health = h;
    }

    [[nodiscard]] int getHealth() const {
        return health;
    }
};

class Miner : public Villiger {

    int rate;

public:

    Miner() {
        rate = 5;
        cout << "Constructor Miner" << endl;
    }

    void setRate(int r) {
        rate = r;
    }

    [[nodiscard]] int getRate() const {
        return rate;
    }

};

class Farmer : public Villiger {
    int rate;

public:

    Farmer() {
        rate = 10;
        cout << "Constructor Farmer" << endl;
    }

    void setRate(int r) {
        rate = r;
    }

    [[nodiscard]] int getRate() const {
        return rate;
    }
};

class Lumberjack : public Villiger {
    int rate;

public:

    Lumberjack() {
        rate = 7;
        cout << "Constructor Lumberjack" << endl;
    }

    void setRate(int r) {
        rate = r;
    }

    [[nodiscard]] int getRate() const {
        return rate;
    }
};


class TownCenter {

    //factory pentru villigeri

public:

    static Miner createMiner() {
        return {};
    }

    static Farmer createFarmer() {
        return {};
    }

    static Lumberjack createLumberjack() {
        return {};
    }
};


class Swordsman : public Villiger {
    int attack, range, armor;

public:

    Swordsman() : Villiger(60) {
        armor = 2;
        attack = 10;
        range = 1;
        cout << "Constructor Swordsman" << endl;
    }

    void setAttack(int a) {
        attack = a;
    }

    [[maybe_unused]] void setRange(int r) {
        range = r;
    }

    void setArmor(int a) {
        armor = a;
    }

    [[nodiscard]] int getAttack() const {
        return attack;
    }

    [[maybe_unused]] [[nodiscard]] int getRange() const {
        return range;
    }

    [[nodiscard]] int getArmor() const {
        return armor;
    }

};

class Archer : public Villiger {
    int attack, range, armor;

public:

    Archer() : Villiger(40) {
        armor = 1;
        attack = 7;
        range = 5;
        cout << "Constructor Archer" << endl;
    }

    void setAttack(int a) {
        attack = a;
    }

    [[maybe_unused]]void setRange(int r) {
        range = r;
    }

    void setArmor(int a) {
        armor = a;
    }

    [[nodiscard]] int getAttack() const {
        return attack;
    }

    [[nodiscard]] [[maybe_unused]] int getRange() const {
        return range;
    }

    [[nodiscard]] int getArmor() const {
        return armor;
    }
};

class Barracks {
    //factory pentru trupe
public:

    static Swordsman createSwordsman() {
        return {};
    }

    static Archer createArcher() {
        return {};
    }
};

class Upgrade {
    int gold_cost, food_cost, attack, armor, rate;
    string name;
    bool gather;

public:

    explicit Upgrade(int gold_cost = 0, int food_cost = 0, int attack = 0, int armor = 0, int rate = 0,
                     bool gather = false, string name = "") {
        this->gold_cost = gold_cost;
        this->food_cost = food_cost;
        this->attack = attack;
        this->armor = armor;
        this->rate = rate;
        this->gather = gather;
        this->name = std::move(name);
    }

    string getName() {
        return name;
    }

    [[nodiscard]] bool getGather() const {
        return gather;
    }

    [[nodiscard]] int getAttack() const {
        return attack;
    }

    [[nodiscard]] int getArmor() const {
        return armor;
    }

    [[nodiscard]] int getRate() const {
        return rate;
    }

    [[nodiscard]] [[maybe_unused]] int getGoldCost() const {
        return gold_cost;
    }

    [[maybe_unused]] [[nodiscard]] int getFoodCost() const {
        return food_cost;
    }
};

class Research {
    vector<Upgrade> upgrades = {Upgrade(100, 100, 2, 1, 0, false, "Sharp Swords"),
                                Upgrade(75, 75, 0, 0, 5, true, "Better Pickaxes")};

public:

    Upgrade research(const string &name) {
        for (auto &upgrade: upgrades) {
            if (upgrade.getName() == name) {
                cout << "Researching " << name << endl;
                return upgrade;
            }
        }
        cout << "No such research" << endl;
        return Upgrade();
    }

    [[maybe_unused]] void printUpgrades() {
        for (auto &upgrade: upgrades) {
            cout << upgrade.getName() << endl;
        }
    }
};


class Villiage {

    //Observer pentru upgradeuri

    vector<Miner> mineri;
    vector<Farmer> fermieri;
    vector<Lumberjack> lemnari;
    vector<Swordsman> baieti_cu_sabii;
    vector<Archer> arcasii;
    [[maybe_unused]] TownCenter baza;
    [[maybe_unused]] Barracks baraca;
    Research cercetare;
    double gold, food, wood;

public:
    Villiage() {
        gold = 100;
        food = 200;
        wood = 100;
    }

    void addGather(Miner m) {
        mineri.push_back(m);
    }

    [[maybe_unused]] void addGather([[maybe_unused]] Farmer f) {
        fermieri.push_back(f);
    }

    [[maybe_unused]] void addGather(Lumberjack l) {
        lemnari.push_back(l);
    }


    void createMiner() {
        if (food >= 50) {
            mineri.push_back(TownCenter::createMiner());
            food -= 50;
        } else {
            cout << "Not enough resources" << endl;
        }
    }

    [[maybe_unused]] void createFarmer() {
        if (food >= 50) {
            fermieri.push_back(TownCenter::createFarmer());
            food -= 50;
        } else {
            cout << "Not enough resources" << endl;
        }
    }

    [[maybe_unused]] void createLumberjack() {
        if (food >= 50) {
            lemnari.push_back(TownCenter::createLumberjack());
            food -= 50;
        } else {
            cout << "Not enough resources" << endl;
        }
    }

    void createSwordsman() {
        if (food >= 50 && gold >= 50) {
            baieti_cu_sabii.push_back(Barracks::createSwordsman());
            food -= 50;
            gold -= 50;
        } else {
            cout << "Not enough resources" << endl;
        }
    }

    void createArcher() {
        if (food >= 50 && gold >= 30) {
            arcasii.push_back(Barracks::createArcher());
            food -= 50;
            gold -= 30;
        } else {
            cout << "Not enough resources" << endl;
        }
    }

    void upgradeUnits(const Upgrade &up) {
        if (up.getGather()) {
            for (auto &i: mineri) {
                i.setRate(i.getRate() + up.getRate());
            }
            for (auto &i: fermieri) {
                i.setRate(i.getRate() + up.getRate());
            }
            for (auto &i: lemnari) {
                i.setRate(i.getRate() + up.getRate());
            }
        } else {
            for (auto &i: baieti_cu_sabii) {
                i.setAttack(i.getAttack() + up.getAttack());
                i.setArmor(i.getArmor() + up.getArmor());
            }
            for (auto &i: arcasii) {
                i.setAttack(i.getAttack() + up.getAttack());
                i.setArmor(i.getArmor() + up.getArmor());
            }
        }
    }

    void Research(const string &name) {
        upgradeUnits(cercetare.research(name));
    }

    void printUnits() {
        cout << "Miners: " << mineri.size() << endl;
        cout << "Farmers: " << fermieri.size() << endl;
        cout << "Lumberjacks: " << lemnari.size() << endl;
        cout << "Swordsmen: " << baieti_cu_sabii.size() << endl;
        cout << "Archers: " << arcasii.size() << endl;
    }

    void printResources() const {
        cout << "Gold: " << gold << endl;
        cout << "Food: " << food << endl;
        cout << "Wood: " << wood << endl;
    }

    void Raid(Villiage &target) {
        int stat_sum = 0, target_stat_sum = 0;

        for (auto i: baieti_cu_sabii) {
            stat_sum += i.getAttack() + i.getArmor();
        }

        for (auto i: arcasii) {
            stat_sum += i.getAttack() + i.getArmor();
        }

        for (auto i: target.baieti_cu_sabii) {
            target_stat_sum += i.getAttack() + i.getArmor();
        }

        for (auto i: target.arcasii) {
            target_stat_sum += i.getAttack() + i.getArmor();
        }

        if (stat_sum > target_stat_sum) {
            gold += target.gold * 0.5;
            food += target.food * 0.5;
            wood += target.wood * 0.5;

            target.gold = target.gold * 0.5;
            target.food = target.food * 0.5;
            target.wood = target.wood * 0.5;

            target.baieti_cu_sabii.clear();
            target.arcasii.clear();
            cout << "Raid successful" << endl;
        } else {
            baieti_cu_sabii.clear();
            arcasii.clear();
            cout << "Raid failed" << endl;
        }
    }

    void nextTurn() {
        for (auto i: mineri) {
            gold += i.getRate();
        }

        for (auto i: fermieri) {
            food += i.getRate();
        }

        for (auto i: lemnari) {
            wood += i.getRate();
        }
    }
};


template<class T>
class Refuges {
    vector<T> refuges;
public:

    explicit Refuges(int i) {
        for (int j = 0; j < i; j++)
            refuges.push_back(T());
    }

    //get data type of refuge


    void joinVilliage([[maybe_unused]] Villiage v) {
        for (auto &refugiat: refuges) {
            v.addGather(refugiat);
        }
    }
};

template<class U>
//makes a combat unit a hero
U makeHero(U target) {
    target.setAttack(target.getAttack() + 5);
    target.setHealth(target.getHealth() + 10);
    target.setArmor(target.getArmor() + 2);
    return target;
}

int main() {
    Swordsman baiat_cu_sabie;
    Archer arcas;

    cout << "Test makeHero start" << endl;
    baiat_cu_sabie = makeHero(baiat_cu_sabie);
    arcas = makeHero(arcas);

    cout << arcas.getAttack() << endl;
    cout << baiat_cu_sabie.getAttack() << endl;

    cout << "Test makeHero end" << endl << endl;

    Refuges<Miner> r1(2);
    Refuges<Farmer> r2(3);

    Villiage v1, v2;

    cout << "Test joinVilliage start" << endl;
    v1.printUnits();
    cout << endl;

    r1.joinVilliage(v1);
    r2.joinVilliage(v1);

    v1.printUnits();

    cout << "Test joinVilliage end" << endl << endl;

    cout << "Test unit creation start" << endl;
    v2.createArcher();
    v2.createArcher();
    v2.createArcher();
    v2.createSwordsman();
    v2.createSwordsman();
    v2.createSwordsman();

    v2.printUnits();
    cout << "Test unit creation end" << endl << endl;

    cout << "Test raid start" << endl;

    cout << "V1:" << endl;
    v1.printResources();
    v1.printUnits();
    cout << endl;

    cout << "V2:" << endl;
    v2.printResources();
    v2.printUnits();
    cout << endl;

    v2.Raid(v1);

    cout << "V1:" << endl;
    v1.printResources();
    v1.printUnits();
    cout << endl;

    cout << "V2:" << endl;
    v2.printResources();
    v2.printUnits();
    cout << endl;

    cout << "Test raid end" << endl << endl;

    cout << "Test research start" << endl;

    v2.Research("Sharp Swords");
    v2.Research("Sharp arrows");
    cout << "Test research end" << endl << endl;


    v2.createMiner();
    v2.createMiner();

    cout << "Test nextTurn start" << endl;
    v2.printUnits();
    v2.printResources();
    v2.nextTurn();
    v2.printResources();
    cout << "Test nextTurn end" << endl;

    return 0;
}