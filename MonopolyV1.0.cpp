#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;



class Square
{
    //CLASA SQUARE ESTE FACUTA PT A FI MOSTENITA DE PROPERTY SI EFFECT PENTRU A FACE POSIBILA MEMORAREA LOR INTR-UN SINGUR VECTOR CA Square*
    
    
    public:
    
    
    virtual ~Square()= default;
};

class Property: public Square
{   
    //PROPRIETATILE AU O CULOARE(APARTENENTA LA CARTIERE PE VIITOR),UN PRET DE ACHIZITIE,UN PRET PT CASE,UN ID DE PROPRIETAR SI UN VECTOR PT CHIRIILE PT FIECARE NUMAR DE CASE UNDE rent[nr_case] ESTE CHIRIA PT NUMARU ACELA DE CASE
    
    
    int color,prop_price,house_price,id_proprietar,nr_case;
    
    
    vector<int> rent;
    
    
    public:
    
    
    explicit Property(int color = 0, int prop_price = 0, int house_price = 0,int id = 0,vector<int> rent = {0,0,0,0,0,0},int nr_case = 0):color(color),prop_price(prop_price),house_price(house_price),id_proprietar(id),nr_case(nr_case),rent(std::move(rent)){}

    Property(const Property &p):rent(p.rent)
    {
        color = p.color;
        prop_price = p.prop_price;
        house_price = p.house_price;
        id_proprietar = p.id_proprietar;
        nr_case = p.nr_case;
    }

    friend ostream& operator<<(ostream& out,const Property& sq)
    {
        out<<"["<<sq.color<<","<<sq.prop_price<<","<<sq.house_price<<","<<sq.id_proprietar<<","<<sq.nr_case<<",[";
        for(int i =0;i<6;i++)
            if(i != 5)
                out<<sq.rent[i]<<",";
            else
                out<<sq.rent[i]<<"]";
        out<<"]";
        
        return out;
    }



    friend istream& operator>>(istream& in, Property& sq)
    {
        in>>sq.color>>sq.prop_price>>sq.house_price>>sq.id_proprietar;
        for(int i = 0;i<6;i++)
            in>>sq.rent[i];
        return in;
    }

    
    
    Property& operator=( const Property &other)
    {
        color = other.color;
        prop_price = other.prop_price;
        house_price = other.house_price;
        id_proprietar = other.id_proprietar;
        nr_case = other.nr_case;
        for(int i = 0;i<6;i++)
            rent[i] = other.rent[i];
        return *this;

    }



    [[nodiscard]] int price () const
    {
        //RETURNEAZA PRETUL PROPRIETATII
        return prop_price;
    }


    void set_prop(int id)
    {
        //SCHIMBA PROPRIETARUL PROPRIETATII
        id_proprietar = id;
    }


    [[nodiscard]] int id() const
    {
        //RETURNEAZA PROPRIETARUL PROPRIETATII
        return id_proprietar;
    }


    [[nodiscard]] int houses() const
    {
        //RETURNEAZA NUMARUL DE CASE DE PE PROPRIETATE
        return nr_case;
    }


    int out_rent(int nr)
    {
        //RETURNEAZA SUMA DE PLATIT CA SI CHIRIE CU UN ANUMIT NUMAR DE CASE PE PROPRIETATE
        return rent[nr];
    }


    [[nodiscard]] int out_house_price() const
    {
        //RETURNEAZA PRETUL UNEI CASE
        return house_price;
    }
    void inc_houses()
    {
        //INCREMENTEAZA NUMARUL DE CASE
        ++nr_case;
    }
};

class Effect:public Square
{
    // EFECTELE(AU UN ID UNDE possible_effects[id] ESTE FUNCTIONALITAETA PATRATULUI) SUNT ORICE PATRAT CE NU ESTE PROPRIETATE AKA START LUXURY TAX ETC..(MOMENTAN NU AI IMPLEMENTAT NIMIC AICI)
    
    //                       0        1            2       3
   // possible_effects = {"Start","Luxury Tax","Chance","Prison"}; , DE IMPLEMENTAT PRISON
    
    
    int effect_id;
    
    
    public:
    
    
    explicit Effect(int effect_id = 0):effect_id(effect_id){}


    friend ostream& operator<<(ostream& out,const Effect& ef)
    {
        out<<ef.effect_id;
        return out;
    }
    
    
    friend istream& operator>>(istream& in,Effect& ef)
    {
        in>>ef.effect_id;
        return in;
    }
    
    
    Effect& operator=(const Effect &ef)
    {
        effect_id = ef.effect_id;
        return *this;
    }

    [[nodiscard]] int id_effect() const
    {
        return effect_id;
    }

};

class Board
{
    // TABLA ESTE UN VECTOR DE PROPRIETATI SI EFECTE TABLA[i] TINUTE SUB FORMA DE Square*(trb fct dynamic_cast ca sa vezi daca e Property sau Effect) SCOATE ELEMENTUL DE PE POZITIA i DIN VECTOR
    
    
    vector<Square*> tabla;


    public:


    explicit Board(vector<Square*> tabla =
    {new Effect(0),
     new Property(1, 50, 25, 0, {5, 10, 15, 20, 25, 40}),
     new Property(1, 60, 25, 0, {7, 12, 17, 22, 27, 50}),
     new Effect(3)})
     :tabla(std::move(tabla)){}



    ~Board()
    {
        for(auto i : tabla)
            delete i;

    }


    friend ostream& operator<<(ostream& out,const Board& b)
    {

        Effect* e;
        for(auto i : b.tabla)
        {
            Property* p;
            if ((p = dynamic_cast<Property *>(i))) {
                out << *p << endl;
            } else {
                e = dynamic_cast<Effect *>(i);
                out << *e << endl;
            }
        }
        return out;
    }



    Square* operator[](int i)
    {
        //RETURNEAZA POINTER-UL DE SQUARE DE LA POZITIA I DIN TABLA
        return this->tabla[i];
    }


    int size()
    {
        //RETURNEAZA NUMARUL DE PATRATE DIN TABLA
        return int(tabla.size());
    }


};

class Player
{
    // JUCATORUL ARE UN ID, POZITIE ,SUMA DE BANI SI UN VECTOR DE PROPRIETATI. EL SE POATE MUTA PE TABLA SI POATE CUMPARA PROPRIETATI(NU AI CHECK DACA ARE DESTUI BANI)
    int money,player_id,pozitie;


    vector<Property*> proprietati;

    public:

    explicit Player(int player_id = 0,int money = 0,int poz = 0,vector<Property*> proprietati = {}):money(money),player_id(player_id),pozitie(poz),proprietati(std::move(proprietati)){}
   
   
    friend ostream& operator<<(ostream& out,const Player& p)
    {
        out<<"{"<<p.player_id<<","<<p.money<<","<<p.pozitie<<",[";
        for( auto const i: p.proprietati)
            out<<*i<<" ";
        out<<"]}";
        return out;
    }


    Property* operator[](int i)
    {
        //RETURNEAZA POINTER-UL SPRE PROPRIETATEA DE PE POZITIA I DIN VECTORUL PROPRIETATI
        return this->proprietati[i];
    }

    void move(Board &b,int step = 0)
    {
        //SIMULEAZA 2 ARUNCARI DE ZAR CU 6 FETE SI MUTA JUCATORUL SUMA CELOR 2 ARUNCARI PATRATE AVAND GRIJA SA RAMANA PE TABLA
       if(!step)
       {
        int s = 0;
        for(int i = 0;i<2;i++)
            s += (1 +(rand() % 6));
        
        pozitie += (pozitie+s)% b.size();
       }
       else
       {
        pozitie += (pozitie+step)% b.size();
       }
    }

    void add_money(int amount)
    {
        money += amount;
    }

    void buy(Board &b)
    {
        //CUMPARA PROPRIETATEA PE CARE JUCATORUL SE AFLA
        Property *p;
        if((p = dynamic_cast<Property*>(b[pozitie])))
        {
            this->add_money(-p->price());
            p->set_prop(player_id);
            proprietati.push_back(p);
        }
    }


    [[nodiscard]] int position() const
    {
        //RETURNEAZA POZITIA
        return pozitie;
    }


    [[nodiscard]] int id() const
    {
        //RETURNEAZA IDENTIFICATORUL JUCATORULUI
        return player_id;
    }

    void pay(Player &other,Board &b)
    {
        //PLATESTE UNUI ALT JUCATOR CHIRIA PENTRU PROPRIETATEA PE CARE SE AFLA
        Property *p;
        p = dynamic_cast<Property*>(b[pozitie]);
        this->add_money(-p->out_rent(p->houses()));
        other.add_money((*p).out_rent((*p).houses()));
    }

    void buy_house(Property* p)
    {
        //CUMPARA O CASA PE PROPRIETATEA DATA CA ARGUMENT
        money -= p->out_house_price();
        p->inc_houses();

    }

    void do_effect(const Effect& e,Board &b)
    {
        int effect_id = e.id_effect();
        if(effect_id == 0)
            this->add_money(200); //ADAUGA BANII DE LA START
        else if(effect_id == 1)
            this->add_money(-150); //SCADE BANII DE LA LUXURY TAX
        else if(effect_id == 2)
        {
            //                         0                 1                   2         3
            //carti_posibile = {"Move to start","Move 5 square forward","Gain 50$","Pay 100$"}
            int carte = rand()%4;
            if(carte == 0)
            {
                pozitie = 0;
                this->add_money(200);
            }
            else if(carte == 1)
            {
                this->move(b,5);
            }
            else if(carte == 2)
            {
                this->add_money(50);
            }
            else if(carte == 3)
            {
                this->add_money(-100);
            }
        } 
    }

};

int main()
{
    srand(time(nullptr));
    
    //DECLARARI


    Property *p;
    vector<Player> jucatori;
    vector<Player> jucatori2;
    Board table({new Effect(),new Property(1,100,50,1,{10,20,30,40,50,600})});
    Board table2({new Effect(),new Effect(1)});
    jucatori.emplace_back(1,500,1);
    jucatori.emplace_back(2,500,0);
    jucatori2.emplace_back(1,500,1);
    jucatori2.emplace_back(2,500,0);


    //COD TEST

    for(Player i:jucatori2)
        {
            Effect *e;
           if((e = dynamic_cast<Effect*>(table2[i.position()])))
               i.do_effect(*e,table2);
            cout<<i<<endl; 
        }




    jucatori[0].buy(table);
    cout<<jucatori[0][0]<<endl;
    cout<<dynamic_cast<Property*>(table[1])<<endl;
    jucatori[0].buy_house(jucatori[0][0]);
    jucatori[0].buy_house(jucatori[0][0]);
    jucatori[0].buy_house(jucatori[0][0]);
    jucatori[0].buy_house(jucatori[0][0]);
    jucatori[0].buy_house(jucatori[0][0]);
    cout<<dynamic_cast<Property*>(table[1])->houses()<<endl;
    jucatori[1].move(table);
    if((p = dynamic_cast<Property*>(table[jucatori[1].position()])))
        if((*p).id() != 0 && (*p).id() != jucatori[1].id())
            jucatori[1].pay(jucatori[(*p).id() -1],table);
    
    cout<<jucatori[1]<<endl<<jucatori[0];





    

    return 0;
}