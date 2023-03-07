//
// Created by Suvir Wadhwa on 18/11/21.
//

#ifndef HW07_NOBLE_H
#define HW07_NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    class Protector;

    class Noble { // Class noble, creates a Noble and enables it to
        // add warriors, fire them, and make one noble battle another.
    public:
        Noble(const std::string &noble_name);

        void battle(Noble &enemy);

        virtual void defend() = 0;

        virtual double getStrength() = 0;

        virtual void changeStrength(double power, bool dead) = 0;

        std::string getName() const;

    protected:
        bool isDead() const;

        void setDead();

    private:
        bool dead = false;
        std::string name;
    };

    class Lord : public Noble {
    public:
        Lord(const std::string &lord_name);

        void remove_warrior(Protector *prot);

        bool hires(Protector &prot);

        double getStrength() override;

        bool fires(Protector &prot);

        void defend() override;

        void changeStrength(double power, bool dead) override;

    private:
        double army_strength = 0;
        std::vector<Protector *> protectors;
    };

    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(const std::string
        &nob_name, int nob_strength);

        double getStrength() override;

        void changeStrength(double power, bool dead) override;

        void defend() override;

    private:
        double strength;
    };

}
#endif //HW07_NOBLE_H
