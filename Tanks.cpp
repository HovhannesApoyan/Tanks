#include <iostream>
class Tank {

public:
	Tank()
	{

	}
	Tank(const std::string name_) : name(name_) {
		do {
			std::cout << "Please enter the " << name << "'s characteristics: health attack defense\n";
			std::cin >> initial_health_;
			std::cin >> attack_;
			std::cin >> defense_;
		} while (!Validate());
		current_health_ = initial_health_;
	}

	bool Hit(Tank& defender)const;
	void print_health_information()const;
	void ReportDeath()const;
	~Tank() {}
private:
	int initial_health_;
	int current_health_;
	double attack_;
	double defense_;
	std::string name;

	bool Validate()const;
	bool IsAlive()const;

};
void tanks_combat(Tank& tank1, Tank& tank2);

int main()
{
	Tank tank1("Tank1");
	Tank tank2("Tank2");
	std::cout << "Velcome to tank battle.\n";
	tanks_combat(tank1, tank2);
}

void tanks_combat(Tank& tank1, Tank& tank2) {
	int attacking_tank_no;
	while (true) {
		std::cout << "Enter the number of the attacking tank <1 or 2>.\n";
		std::cin >> attacking_tank_no;
		const Tank& attacker = (attacking_tank_no == 1) ? tank1 : tank2;
		Tank& defender = (attacking_tank_no == 1) ? tank2 : tank1;
		if (attacker.Hit(defender))
		{
			defender.ReportDeath();
			break;
		}
		else
		{
			tank1.print_health_information();
			tank2.print_health_information();
		}
	}
}

bool Tank::Validate()const {
	return initial_health_ > 0 && attack_ > 0 && defense_ >= 0. && defense_ <= 1.;
}

bool Tank::IsAlive() const {
	return current_health_ > 0;
}

bool Tank::Hit(Tank& defender)const {
	const double attacker_strength = static_cast<double>(current_health_) / initial_health_;
	const double damage = attack_ * (1 - defender.defense_) * attacker_strength;
	defender.current_health_ = static_cast<int>(defender.current_health_ - damage);
	return !(defender.IsAlive());
}

void Tank::print_health_information() const {
	std::cout << name << " health: " << current_health_ << "\n";
}

void Tank::ReportDeath()const {
	std::cout << name << " is dead\n";
}