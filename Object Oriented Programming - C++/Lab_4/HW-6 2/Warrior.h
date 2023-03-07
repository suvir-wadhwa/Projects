//
// Created by Suvir Wadhwa on 02/11/21.
//

#ifndef HW_6_WARRIOR_H
#define HW_6_WARRIOR_H
#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {

    class Noble;

    class Warrior { // Class warrior, creates a warrior
        // with a strength and name
        friend std::ostream &operator<<(std::ostream &os, const Warrior &warr);

    public:
        Warrior(const std::string &warr_name, double warr_strength);

        // Enables Noble to check if warrior already has noble.
        bool getNoble() const;

        // Enables Noble to link to a warrior
        void setNoble(bool exist, Noble *nob_pointer);

        // enables noble to get a warriors strength
        double getStrength() const;

        // enables Noble to set a warriors strength
        void setStrength(double stren);

        void setDead();

        const std::string &getName() const;

        void runaway();

        bool isHired() const;

    private:
        bool dead = false;
        double strength;
        std::string name;
        bool noble = false;
        Noble *nob = nullptr;
    };

}

#endif //HW_6_WARRIOR_H
