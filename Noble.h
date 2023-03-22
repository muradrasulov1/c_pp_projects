//
//  Noble.hpp
//  hw07.cpp
//
//  Created by Fuad on 15.04.22.
//

#ifndef Noble_hpp
#define Noble_hpp

#include <stdio.h>


#include <iostream>
#include <vector>
#include <string>
#include <fstream>

namespace WarriorCraft{

class Protector;

class Noble{
public:
    Noble(const std::string& aname, double strengtH);
    
    double get_strength() const;
    
    std::string get_name() const;
    
    void set_strength(double new_val);
    
    bool get_life_status();
    
    void is_dead();
    
    virtual void change_strength(double new_val) = 0;
    
    void battle(Noble& opponent);
    
private:
    std::string noble_name;
    double strength;
    bool able_to_operate;
};


class Lord : public Noble{
    
public:
    Lord(const std::string& aname, double strengtH=0);
    
    
    bool hires(Protector& protector);
    
    bool fires(Protector& protector);
    
    void change_strength(double new_val);
    
    size_t searchWarrior(const std::string& protector);
    
    bool runaway(Protector* escapist);
    
private:
    std::vector<Protector*> army;
    
};

class PersonWithStrengthToFight : public Noble{
public:
    PersonWithStrengthToFight(const std::string& aname, double strengtH);
    
    

    void change_strength(double new_val);
    

};

}

#endif /* Noble_hpp */
